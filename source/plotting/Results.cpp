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
#include "boca/DetectorGeometry.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace
{

auto SignificanceExperimental(double signal, double background)
{
    return background > 0 ? signal / background : 0;
}

auto SignificanceBackground(double signal, double background)
{
    return background > 0 ? signal / std::sqrt(background) : 0;
}

auto SignificanceSum(double signal, double background)
{
    return background > 0 ? signal / std::sqrt(signal + background) : 0;
}

auto SignificancePoisson(double signal, double background)
{
    if (signal <= 0 || background <= 0) return 0.;
    auto sum = background + signal;
    auto log = signal + sum * std::log(background / sum);
    CHECK(log < 0, log, signal, background);
    if (log > 0) log = 0;
    auto significance = std::sqrt(- 2 * log);
    CHECK(significance > 0, significance, signal, background);
    return significance;
}

auto MD(boca::Significance significance, double signal, double background)
{
    switch (significance) {
    case Significance::experimental : return SignificanceExperimental(signal, background);
    case Significance::background : return SignificanceBackground(signal, background);
    case Significance::sum : return SignificanceSum(signal, background);
    case Significance::poisson : return SignificancePoisson(signal, background);
    default : return 0.;
    }
}

template <typename Value>
auto BestMDBin(std::vector<Value> vector)
{
    return std::distance(vector.begin(), std::max_element(std::begin(vector), std::end(vector)));
}

auto BestMIBin(std::vector<Crosssection> const& vector)
{
    return std::distance(vector.begin(), std::min_element(std::begin(vector), std::end(vector), [](Crosssection const & i, Crosssection const & j) {
        return i > 0_b ? i < j : i > j;
    }));
}

}

Results::Results(std::vector<Result> const& signals, std::vector<Result> const& backgrounds) :
    signals_(signals),
    backgrounds_(backgrounds) {}

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
    for (auto const & step : IntegerRange(Result::Steps())) CalculateSignificance(signal, significance, step);
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
    return range_.Get([&]() {
        Rectangle<double> range;
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
        for (auto & background : backgrounds_) background.AddSelectedEfficiency(int(index));
    }
}

double Results::BackgroundEvents(int step) const
{
    INFO0;
    return BackgroundCrosssections().at(step) * DetectorGeometry::Luminosity();
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
    INFO0;
    if (signal_efficiency == 0 || BackgroundCrosssections().at(step) == 0_b) return 0_b;
    return BackgroundCrosssections().at(step) / signal_efficiency * DetectorGeometry::Experimental();
}

Crosssection Results::MIBackground(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundCrosssections().at(step) == 0_b) return 0_b;
    return sqrt(BackgroundCrosssections().at(step) / DetectorGeometry::Luminosity()) / signal_efficiency * DetectorGeometry::Exclusion();
}

Crosssection Results::MISum(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents(step) == 0) return 0_b;
    auto numerator = DetectorGeometry::Exclusion() + std::sqrt(sqr(DetectorGeometry::Exclusion()) + 4. * BackgroundEvents(step));
    return numerator * DetectorGeometry::Exclusion() / 2. / signal_efficiency / DetectorGeometry::Luminosity();
}

Crosssection Results::MIConstrained(Significance significance, double signal_efficiency, int step) const
{
    INFO(Name(significance));
    auto sig = MI(significance, signal_efficiency, step);
    auto sb = MIExperimental(signal_efficiency, step);
    return sig > 0_b && sb > 0_b ? max(sig, sb) : 0_b;
}

Crosssection Results::MIPoisson(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents(step) == 0) return 0_b;
    ROOT::Math::Functor1D function([&](double crosssection) {
      return SignificancePoisson(crosssection * fb * DetectorGeometry::Luminosity() * signal_efficiency, BackgroundEvents(step)) - DetectorGeometry::Exclusion();
    });
    boca::Range<double> range(MIBackground(signal_efficiency, step) / fb);
    do {
        range.Widen(1.1);
    } while (sgn(function(range.Min())) == sgn(function(range.Max())));
    ROOT::Math::RootFinder root_finder(ROOT::Math::RootFinder::kGSL_BRENT);
    auto success = root_finder.Solve(function, range.Min(), range.Max());
    auto crosssection = root_finder.Root() * fb;
    CHECK(success && std::abs(function(crosssection / fb)) < std::numeric_limits<float>::epsilon(), success, step, crosssection, function(crosssection / fb));
    return crosssection;
}

Crosssection Results::MI(Significance significance, double signal_efficiency, int step) const
{
    INFO(Name(significance));
    if (significance != Significance::experimental && (significance & Significance::experimental) == Significance::experimental) {
        auto test = significance &~Significance::experimental;
        switch (test) {
        case Significance::background : return MIConstrained(Significance::background, signal_efficiency, step);
        case Significance::sum : return MIConstrained(Significance::sum, signal_efficiency, step);
        case Significance::poisson : return MIConstrained(Significance::poisson, signal_efficiency, step);
//         DEFAULT(Name(significance), 0_b);
        default : return 0_b;
        }
    } else switch (significance) {
        case Significance::experimental : return MIExperimental(signal_efficiency, step);
        case Significance::background : return MIBackground(signal_efficiency, step);
        case Significance::sum : return MISum(signal_efficiency, step);
        case Significance::poisson : return MIPoisson(signal_efficiency, step);
//             DEFAULT(Name(significance), 0_b);
        default : return 0_b;
        }
}

double Results::ScalingFactor()
{
    return 1; // should usually be 1
    ERROR("Semi leptonic BR is beeing removed");
    return 1. / (0.22 * 0.65 * 2); // remove semileptonic branching ratio
}

std::vector<Result> const& Results::Signals() const
{
    return signals_;
}

std::vector<Result> const& Results::Backgrounds() const
{
    return backgrounds_;
}

const std::vector< double >& Results::SelectedEfficiencies() const
{
    return selected_efficiencies_;
}

}



