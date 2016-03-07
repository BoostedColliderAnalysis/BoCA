/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Results.hh"

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "Types.hh"
#include "Vector.hh"
#include "physics/Units.hh"
#include "DetectorGeometry.hh"
// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

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

int Results::BestModelDependentBin() const
{
    INFO0;
    return best_model_dependent_bin_;
}

int Results::BestModelInDependentBin() const
{
    INFO0;
    return best_model_independent_bin_;
}

int Results::BestAcceptanceBin() const
{
    INFO0;
    return best_acceptance_bin_;
}

int Results::BestSOverBBin() const
{
    INFO0;
    return best_s_over_b_bin_;
}

Rectangle<float> const& Results::Range() const
{
    INFO0;
    return range_;
}

Rectangle<float>& Results::Range()
{
    INFO0;
    return range_;
}

std::vector<float> const& Results::XValues() const
{
    INFO0;
    return x_values_;
}

std::vector<float> const& Results::Significances() const
{
    INFO0;
    return significances_;
}

std::vector<float> const& Results::Acceptances() const
{
    INFO0;
    return acceptances_;
}

std::vector<float> const& Results::SOverB() const
{
    INFO0;
    return s_over_b_;
}

Results::Results(std::vector<Result> signals, std::vector<Result> backgrounds)
{
    INFO0;
    signals_ = signals;
    backgrounds_ = backgrounds;
    significances_.resize(Steps(), 0);
    acceptances_.resize(Steps(), 0);
    s_over_b_.resize(Steps(), 0);
    x_values_.resize(Steps(), 0);
    for (auto & x_value : x_values_) x_value = XValue(Position(x_values_, x_value));
    ExtremeXValues();
}

void Results::ExtremeXValues()
{
    INFO0;
    switch (Mva()) {
    case TMVA::Types::kBDT :
        for (auto const & signal : signals_) range_.WidenXMax(*boost::range::max_element(signal.Bdts()));
        for (auto const & background : backgrounds_) range_.WidenXMin(*boost::range::min_element(background.Bdts()));
        break;
    case TMVA::Types::kCuts :
        if (!x_values_.empty()) range_.SetXMin(x_values_.front());
        if (!x_values_.empty()) range_.SetXMax(x_values_.back());
        break;
        DEFAULT(Mva());
    }
}

float Results::BestModelDependentValue() const
{
    INFO0;
    return XValue(BestModelDependentBin());
}

float Results::BestModelInDependentValue() const
{
    INFO0;
    return XValue(BestModelInDependentBin());
}

float Results::BestAcceptanceValue() const
{
    INFO0;
    return XValue(BestAcceptanceBin());
}

float Results::BestSOverBValue() const
{
    INFO0;
    return XValue(BestSOverBBin());
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

void Results::CalculateSignificances()
{
    INFO0;
    for (auto const & step : IntegerRange(Steps())) CalculateSignificances(step);
    BestBins();
}

void Results::CalculateSignificances(int step)
{
    INFO0;
    auto signal_events = SignalEvents(step);
    auto background_events = BackgroundEvents(step);
    significances_.at(step) = Significance(signal_events, background_events);
    acceptances_.at(step) = Acceptances(signal_events, background_events);
    s_over_b_.at(step) = SOverB(signal_events, background_events);
    for (auto & signal : signals_) signal.SetModelIndependentSig(ModelIndependentCrosssectionSig(signal.Efficiencies().at(step), step), step);
    for (auto & signal : signals_) signal.SetModelIndependentSB(ModelIndependentCrosssectionSB(signal.Efficiencies().at(step), step), step);
    for (auto & signal : signals_) signal.SetModelIndependent(ModelIndependentCrosssection(signal.Efficiencies().at(step), step), step);
}

namespace
{
template <typename Value>
int BestBin(std::vector<Value> vector, int step)
{
    return std::distance(vector.begin(), std::max_element(std::begin(vector), std::end(vector) - step));
}

int BestMIBin(std::vector<Result> const& signals_, int step, std::function<std::vector<Crosssection>(Result const&)> const& function)
{
    std::map<Crosssection, int> map;
    for (auto const & signal : signals_) {
//         auto vector = signal.ModelIndependent();
        auto vector = function(signal);
        auto min = std::min_element(std::begin(vector), std::end(vector) - step, [](Crosssection i, Crosssection j) {
            return i > 0_b ? i < j : i > j;
        });
        auto dist = std::distance(vector.begin(), min);
        map.emplace(*min, dist);
        ERROR(*min, dist);
    }
    return map.rbegin()->second;
}

}
void Results::BestBins()
{
    INFO0;
    std::vector<float> efficiencies(backgrounds_.size(), 0);
    int counter = 0;
    for (auto const & number : IntegerRange(backgrounds_.size())) {
        while (efficiencies.at(number) == 0 && counter < Steps()) {
            best_model_dependent_bin_ = BestBin(significances_, counter);
            best_model_independent_bin_ = BestMIBin(signals_, counter, [](Result const & signal) {
                return signal.ModelIndependent();
            });
            efficiencies.at(number) = backgrounds_.at(number).Efficiencies().at(best_model_dependent_bin_);
            best_acceptance_bin_ = BestMIBin(signals_, counter, [](Result const & signal) {
                return signal.ModelIndependentSig();
            });
            //BestBin(acceptances_, counter);
            best_s_over_b_bin_ = BestMIBin(signals_, counter, [](Result const & signal) {
                return signal.ModelIndependentSB();
            });
            //BestBin(s_over_b_, counter);
            ++counter;
        }
    }
}

void Results::Efficiencies()
{
    INFO0;
    int steps = 10;
    auto sig_eff = signals_.front().PureEfficiencies();
    for (float eff : IntegerRange(1, steps)) {
        float& elem = *(boost::range::lower_bound(sig_eff, eff / steps, [](float i, float j) {
            return i > j;
        }) - 1);
        signals_.front().AddSelectedEfficiency(elem);
        int index = Position(sig_eff, elem);
        selected_efficiencies_.emplace_back(XValue(index));
        if (index >= sig_eff.size()) index = 0;
        for (auto & background : backgrounds_) background.AddSelectedEfficiency(index);
    }
}

float Results::XValue(int value) const
{
    INFO(value);
    switch (Mva()) {
    case TMVA::Types::kBDT : return 2. * value / Steps() - 1;
    case TMVA::Types::kCuts : return (1. + value) / (Steps() + 1);
        DEFAULT(Mva(), 0);
    }
}

float Results::SignalEvents(int step) const
{
    INFO0;
    return boost::accumulate(signals_, 0., [&](float sum, Result const & signal) {
        return sum + signal.Events().at(step);
    });
}

float Results::BackgroundEvents(int step) const
{
    INFO0;
    return boost::accumulate(backgrounds_, 0., [&](float sum, Result const & background) {
        return sum + background.Events().at(step);
    });
}

float Results::Significance(float signal_events, float background_events) const
{
    return /*signal_events +*/ background_events > 0 ? signal_events / std::sqrt(signal_events + background_events) : 0;
}

float Results::Acceptances(float signal_events, float background_events) const
{
    return background_events > 0 ? signal_events / std::sqrt(background_events) : 0;
}

float Results::SOverB(float signal_events, float background_events) const
{
    return background_events > 0 ? signal_events / background_events : 0;
}

Crosssection Results::BackgroundEfficiencyCrosssection(int step) const
{
    INFO0;
    return boost::accumulate(backgrounds_, 0_b, [&](Crosssection sum, Result const & background) {
        return sum  + double(background.Efficiencies().at(step)) * background.InfoBranch().Crosssection();
    });
}

double Results::ScalingFactor()
{
    return 1; // should usually be 1
    ERROR("Semi leptonic BR is beeing removed");
    return 1. / (0.22 * 0.65 * 2); // remove semileptonic branching ratio
}

Crosssection Results::ModelIndependentCrosssectionSB(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0) return 0_b;
    auto s_over_b_ = 0.01;
    return BackgroundEfficiencyCrosssection(step) / signal_efficiency * s_over_b_ * ScalingFactor();
}

Crosssection Results::ModelIndependentCrosssectionSig(double signal_efficiency, int step) const
{
    INFO0;
    if (signal_efficiency == 0) return 0_b;
    auto exclusion = 2.;
    auto numerator = exclusion + std::sqrt(sqr(exclusion) + 4. * BackgroundEvents(step));
    return numerator * exclusion / 2. / signal_efficiency / DetectorGeometry::Luminosity() * ScalingFactor();
}

Crosssection Results::ModelIndependentCrosssection(double signal_efficiency, int step) const
{
    INFO0;
    auto sig = ModelIndependentCrosssectionSig(signal_efficiency, step);
    auto sb = ModelIndependentCrosssectionSB(signal_efficiency, step);
    return sig > 0_b && sb > 0_b ? max(sig, sb) : 0_b;
}

const std::vector< float >& Results::SelectedEfficiencies() const
{
    return selected_efficiencies_;
}

}
