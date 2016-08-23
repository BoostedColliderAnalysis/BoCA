/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "TMath.h"
#include "Math/RootFinder.h"

#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/physics/Units.hh"
#include "boca/plotting/Results.hh"
#include "boca/Settings.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace
{

auto SignificanceExperimental(double signal, double background)
{
    INFO0;
    return background > 0 ? signal / background : 0;
}

auto SignificanceBackground(double signal, double background)
{
    INFO0;
    return background > 0 ? signal / std::sqrt(background) : 0;
}

auto SignificanceSum(double signal, double background)
{
    INFO0;
    return background > 0 ? signal / std::sqrt(signal + background) : 0;
}

auto LogLikelihoodRatio(boca::Significance significance, double signal, double background)
{
    INFO(Name(significance));
    auto sum = background + signal;
    auto ratio = -1.;
    FlagSwitch(significance, [&](Significance sig) {
        switch (sig) {
        case Significance::discovery : ratio = signal + sum * std::log(background / sum); break;
        case Significance::exclusion : ratio = - signal - background * std::log(background / sum); break;
        default : ;
        };
    });
    CHECK(ratio != -1, ratio, Name(significance));
    return ratio;
}

auto SignificancePoisson(boca::Significance significance, double signal, double background)
{
    INFO0;
    if (signal <= 0 || background <= 0) return 0.;
    auto ratio = LogLikelihoodRatio(significance, signal, background);
    CHECK(ratio < 0, ratio, signal, background);
    if (ratio > 0) ratio = 0;
    return std::sqrt(- 2 * ratio);
}

auto MD(boca::Significance significance, double signal, double background)
{
    INFO(Name(significance));
    auto md = -1.;
    FlagSwitch(significance, [&](Significance sig) {
        switch (sig) {
        case Significance::experimental : md = SignificanceExperimental(signal, background); break;
        case Significance::background : md = SignificanceBackground(signal, background); break;
        case Significance::sum : md = SignificanceSum(signal, background); break;
        case Significance::poisson : md = SignificancePoisson(significance, signal, background); break;
        default : ;
        };
    });
    CHECK(md != -1, md, Name(significance));
    return md;
}

template <typename Value>
auto BestMDBin(std::vector<Value> vector)
{
    INFO0;
    return std::distance(vector.begin(), boost::range::max_element(vector));
}

auto BestMIBin(std::vector<Crosssection> const& vector)
{
    INFO0;
    return std::distance(vector.begin(), boost::range::min_element(vector, [](Crosssection const & i, Crosssection const & j) {
        return i > 0_b ? i < j : i > j;
    }));
}

auto PValue(Significance significance)
{
    INFO0;
    auto pvalue = 0.;
    FlagSwitch(significance, [&](Significance sig) {
        switch (sig) {
        case Significance::discovery : pvalue = 5; break;
        case Significance::exclusion : pvalue = 2; break;
        default : ;
        };
    });
    CHECK(pvalue != 0, pvalue, Name(significance));
    return pvalue;
}

}

Results::Results(std::vector<Result> const& signals, std::vector<Result> const& backgrounds) :
    signals_(signals),
    backgrounds_(backgrounds)
{
    INFO0;
    for(auto & signal : signals_) signal.SetScalingFactor(ScalingFactor(Tag::signal));
    for(auto & background : backgrounds_) background.SetScalingFactor(ScalingFactor(Tag::background));
}

std::vector<double> const& Results::XValues() const
{
    INFO0;
    return x_values_.Get([&]() {
        std::vector<double> x_values(Result::Steps());
        for (auto & x_value : x_values) x_value = Result::XValue(Position(x_values, x_value));
        return x_values;
    });
}

void Results::CalculateSignificances()
{
    INFO0;
    for (auto & signal : signals_) for (auto const & significance : Significances()) CalculateSignificance(signal, significance);
}

void Results::CalculateSignificance(Result& signal, Significance significance)
{
    INFO0;
    for (auto step : IntegerRange(Result::Steps())) CalculateSignificance(signal, significance, step);
    BestBins(signal, significance);
}

void Results::CalculateSignificance(Result& signal, Significance significance, int step)
{
    INFO0;
    signal.MD(significance).at(step) = MD(significance, signal.Events().at(step), BackgroundEvents(step));
    signal.MI(significance).at(step) = MI(significance, signal.PreCutEfficiencies().at(step), step);
}

void Results::BestBins(Result& signal, Significance significance)
{
    INFO0;
    signal.BestMDBin(significance) = BestMDBin(signal.MD(significance));
    signal.BestMIBin(significance) = BestMIBin(signal.MI(significance));
}

Rectangle<double> const& Results::Range() const
{
    INFO0;
    return range_.Get([&]() {
        auto range = Rectangle<double>{};
        switch (Result::Mva()) {
        case TMVA::Types::kBDT : for (auto const & signal : signals_) range.WidenXMax(*boost::range::max_element(signal.Bdts()));
            for (auto const & background : backgrounds_) range.WidenXMin(*boost::range::min_element(background.Bdts()));
            break;
        case TMVA::Types::kCuts : if (!XValues().empty()) range.SetX(XValues().front(), XValues().back());
            break;
            DEFAULT(Result::Mva());
        }
        return range;
    });
}

void Results::CutEfficiencies()
{
    INFO0;
    auto steps = 10;
    auto sig_eff = signals_.front().PureEfficiencies();
    for (double eff : IntegerRange(1, steps)) {
        auto& elem = *(boost::range::lower_bound(sig_eff, eff / steps, [](double i, double j) {
            return i > j;
        }) - 1);
        signals_.front().AddSelectedEfficiency(elem);
        auto index = Position(sig_eff, elem);
        selected_efficiencies_.emplace_back(Result::XValue(index));
        if (index >= sig_eff.size()) index = 0;
        for (auto & background : backgrounds_) background.AddSelectedEfficiency(static_cast<int>(index));
    }
}

double Results::BackgroundEvents(int step) const
{
    INFO0;
    return BackgroundCrosssections().at(step) * Settings::Luminosity();
}

std::vector<Crosssection> Results::BackgroundCrosssections() const
{
    INFO0;
    return background_crosssections_.Get([&]() {
        return Transform(IntegerRange(Result::Steps()), [&](int step) {
            auto empty = false;
            auto crosssection = boost::accumulate(backgrounds_, 0_b, [&](Crosssection & sum, Result const & background) {
                if (background.Crosssections().at(step) == 0_b) empty = true;
                return sum  + background.Crosssections().at(step);
            });
            return empty ? 0_b : crosssection;
        });
    });
}

Crosssection Results::MIExperimental(double signal_efficiency, int step) const
{
    INFO(signal_efficiency, step);
    if (signal_efficiency == 0 || BackgroundCrosssections().at(step) == 0_b) return 0_b;
    return BackgroundCrosssections().at(step) / signal_efficiency * Settings::Experimental();
}

Crosssection Results::MIBackground(Significance significance, double signal_efficiency, int step) const
{
    INFO(Name(significance), signal_efficiency, step);
    if (signal_efficiency == 0 || BackgroundCrosssections().at(step) == 0_b) return 0_b;
    return sqrt(BackgroundCrosssections().at(step) / Settings::Luminosity()) / signal_efficiency * PValue(significance);
}

Crosssection Results::MISum(Significance significance, double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents(step) == 0) return 0_b;
    auto numerator = PValue(significance) + std::sqrt(sqr(PValue(significance)) + 4. * BackgroundEvents(step));
    return numerator * PValue(significance) / 2. / signal_efficiency / Settings::Luminosity();
}

Crosssection Results::MIConstrained(Significance significance, double signal_efficiency, int step) const
{
    INFO(Name(significance));
    auto sig = MI(significance, signal_efficiency, step);
    auto sb = MIExperimental(signal_efficiency, step);
    return sig > 0_b && sb > 0_b ? max(sig, sb) : 0_b;
}

Crosssection Results::MIPoisson(Significance significance, double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents(step) == 0) return 0_b;
    auto function = [&](double crosssection) {
        return SignificancePoisson(significance, crosssection * fb * Settings::Luminosity() * signal_efficiency, BackgroundEvents(step)) - PValue(significance);
    };
    auto range = boca::Range<double>{MIBackground(significance, signal_efficiency, step) / fb};
    do {
        range.Widen(1.1);
    } while (sgn(function(range.Min())) == sgn(function(range.Max())));
    ROOT::Math::RootFinder root_finder(ROOT::Math::RootFinder::kGSL_BRENT);
    auto success = root_finder.Solve(function, range.Min(), range.Max());
    auto crosssection = root_finder.Root() * fb;
    CHECK(success && std::abs(function(crosssection / fb)) < std::numeric_limits<float>::epsilon(), success, step, crosssection/*, function(crosssection / fb)*/);
    return crosssection;
}

Crosssection Results::MI(Significance significance, double signal_efficiency, int step) const
{
    INFO(Name(significance));
    auto mi = 0_b;
    if (!is(significance, Significance::discovery) && !is(significance, Significance::exclusion) && significance != Significance::experimental) return mi;
    if (significance != Significance::experimental && is(significance, Significance::experimental)) {
        auto signif = significance &~Significance::experimental;
        FlagSwitch(signif, [&](Significance sig) {
            switch (sig) {
            case Significance::background : mi = MIConstrained(signif, signal_efficiency, step); break;
            case Significance::sum : mi = MIConstrained(signif, signal_efficiency, step); break;
            case Significance::poisson : mi = MIConstrained(signif, signal_efficiency, step); break;
            default : ;
            }
        });
    } else FlagSwitch(significance, [&](Significance sig) {
        switch (sig) {
        case Significance::experimental : mi = MIExperimental(signal_efficiency, step); break;
        case Significance::background : mi = MIBackground(significance, signal_efficiency, step); break;
        case Significance::sum : mi = MISum(significance, signal_efficiency, step); break;
        case Significance::poisson : mi = MIPoisson(significance, signal_efficiency, step); break;
        default : ;
        };
    });
    return mi;
}

double Results::ScalingFactor(Tag tag)
{
    INFO0;
    return 1; // should usually be 1
    ERROR("Singal and background are scaled differently");
    switch(tag){
      case Tag::signal : return 0.79608; //< remove lambda_T from coupling
//       case Tag::signal : return 0.20392;
      case Tag::background : return 1;
    }
    ERROR("Semi leptonic BR is beeing removed");
    return 1. / (0.22 * 0.65 * 2); // remove semileptonic branching ratio
}

std::vector<Result> const& Results::Signals() const
{
    INFO0;
    return signals_;
}

std::vector<Result> const& Results::Backgrounds() const
{
    INFO0;
    return backgrounds_;
}

const std::vector< double >& Results::SelectedEfficiencies() const
{
    INFO0;
    return selected_efficiencies_;
}

}

