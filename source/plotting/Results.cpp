/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "TMath.h"
#include "Math/RootFinder.h"

#include "generic/Types.hh"
#include "generic/Vector.hh"
#include "physics/Units.hh"
#include "plotting/Results.hh"
#include "DetectorGeometry.hh"
// #define INFORMATION
#include "generic/DEBUG.hh"

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

auto MD(boca::Significance significance, double signal_events, double background_events)
{
    switch (significance) {
    case Significance::experimental : return SignificanceExperimental(signal_events, background_events);
    case Significance::background : return SignificanceBackground(signal_events, background_events);
    case Significance::sum : return SignificanceSum(signal_events, background_events);
    case Significance::poisson : return SignificancePoisson(signal_events, background_events);
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
    backgrounds_(backgrounds)
{
    INFO0;
    x_values_.resize(Steps(), 0);
    for (auto & x_value : x_values_) x_value = XValue(Position(x_values_, x_value));
    ExtremeXValues();
}

void Results::ExtremeXValues()
{
    INFO0;
    switch (Mva()) {
    case TMVA::Types::kBDT : for (auto const & signal : signals_) range_.WidenXMax(*boost::range::max_element(signal.Bdts()));
        for (auto const & background : backgrounds_) range_.WidenXMin(*boost::range::min_element(background.Bdts()));
        break;
    case TMVA::Types::kCuts : if (!x_values_.empty()) range_.SetX( {x_values_.front(), x_values_.back()});
        break;
        DEFAULT(Mva());
    }
}

int Results::Steps() const
{
    INFO0;
    return signals_.empty() ? 0 : signals_.front().Steps();
}

TMVA::Types::EMVA Results::Mva() const
{
    INFO0;
    return signals_.empty() ? TMVA::Types::kVariable : signals_.front().Mva();
}

double Results::XValue(int value) const
{
    INFO(value);
    return signals_.empty() ? 0 : signals_.front().XValue(value);
}

void Results::CalculateSignificances()
{
    INFO0;
    for (auto & signal : signals_) for (auto const & significance : Significances()) CalculateSignificance(signal, significance);
}

void Results::CalculateSignificance(Result& signal, Significance significance)
{
    INFO0;
    for (auto const & step : IntegerRange(Steps())) CalculateSignificance(signal, significance, step);
    BestBins(signal, significance);
}

void Results::CalculateSignificance(Result& signal, Significance significance, int step)
{
    INFO0;
    signal.MD(significance).at(step) = MD(significance, signal.Events().at(step), BackgroundEvents().at(step));
    signal.MI(significance).at(step) = MI(significance, signal.PreCutEfficiencies().at(step), step);
}

void Results::BestBins(Result& signal, Significance significance)
{
    INFO0;
    signal.BestMDBin(significance) = BestMDBin(signal.MD(significance));
    signal.BestMIBin(significance) = BestMIBin(signal.MI(significance));
}

void Results::Efficiencies()
{
    INFO0;
    auto steps = 10;
    auto sig_eff = signals_.front().PureEfficiencies();
    for (double eff : IntegerRange(1, steps)) {
        double& elem = *(boost::range::lower_bound(sig_eff, eff / steps, [](double i, double j) {
            return i > j;
        }) - 1);
        signals_.front().AddSelectedEfficiency(elem);
        auto index = Position(sig_eff, elem);
        selected_efficiencies_.emplace_back(XValue(index));
        if (index >= sig_eff.size()) index = 0;
        for (auto & background : backgrounds_) background.AddSelectedEfficiency(int(index));
    }
}

double Results::SignalEvents(int step) const
{
    INFO0;
    return boost::accumulate(signals_, 0., [&](double & sum, Result const & signal) {
        return sum + signal.Events().at(step);
    });
}

std::vector<double> Results::BackgroundEvents() const
{
    INFO0;
    return background_events_.Get([&]() {
        return Transform(IntegerRange(Steps()), [&](int step) {
            return BackgroundEvent(step);
        });
    });
}

double Results::BackgroundEvent(int step) const
{
    INFO0;
    auto empty = false;
    auto events = boost::accumulate(backgrounds_, 0., [&](double & sum, Result const & background) {
        if (background.Events().at(step) == 0) empty = true;
        return sum + background.Events().at(step);
    });
    return empty ? 0. : events;
}

std::vector<Crosssection> Results::BackgroundCrosssections() const
{
    return background_crosssections_.Get([&]() {
        return Transform(IntegerRange(Steps()), [&](int step) {
            return BackgroundCrosssection(step);
        });
    });
}

Crosssection Results::BackgroundCrosssection(int step) const
{
    INFO0;
    auto empty = false;
    auto crosssection = boost::accumulate(backgrounds_, 0_b, [&](Crosssection & sum, Result const & background) {
        return sum  + background.Crosssections().at(step);
    });
    return empty ? 0_b : crosssection;
}

Crosssection Results::MIExperimental(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents().at(step) == 0) return 0_b;
    auto s_over_b_ = 0.01;
    return BackgroundCrosssections().at(step) / signal_efficiency * s_over_b_;
}

Crosssection Results::MIBackground(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents().at(step) == 0) return 0_b;
    auto exclusion = 2.;
    return sqrt(BackgroundCrosssections().at(step) / DetectorGeometry::Luminosity()) / signal_efficiency * exclusion;
}

Crosssection Results::MISum(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0 || BackgroundEvents().at(step) == 0) return 0_b;
    auto exclusion = 2.;
    auto numerator = exclusion + std::sqrt(sqr(exclusion) + 4. * BackgroundEvents().at(step));
    return numerator * exclusion / 2. / signal_efficiency / DetectorGeometry::Luminosity();
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
    auto background_events = BackgroundEvents().at(step);
    if (signal_efficiency == 0 || background_events == 0) return 0_b;
    auto exclusion = 2.;
    ROOT::Math::Functor1D function([&](double signalxs) {
        double signal_events = signalxs * fb * DetectorGeometry::Luminosity() / signal_efficiency;
        CHECK(background_events > 0 && signal_events > 0, background_events, signal_events);
        return SignificancePoisson(signal_events, background_events) - exclusion;
    });
    boca::Range<double> range(MIBackground(signal_efficiency, step) / fb);
    while (sgn(function(range.Min())) == sgn(function(range.Max()))) range.Widen(1.1);
    ROOT::Math::RootFinder root_finder(ROOT::Math::RootFinder::kGSL_BRENT);
    auto success = root_finder.Solve(function, range.Min(), range.Max());
    auto xsec = root_finder.Root() * fb;
    CHECK(success && function(xsec / fb) < std::numeric_limits<double>::epsilon(), step, signal_efficiency, xsec, function(xsec / fb));
    if (xsec < 0.0004_fb) ERROR(xsec, signal_efficiency, step, function(xsec / fb));
    return xsec;
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

Rectangle<double> const& Results::Range() const
{
    return range_;
}

Rectangle<double>& Results::Range()
{
    return range_;
}

std::vector<double> const& Results::XValues() const
{
    return x_values_;
}

const std::vector< double >& Results::SelectedEfficiencies() const
{
    return selected_efficiencies_;
}

}



