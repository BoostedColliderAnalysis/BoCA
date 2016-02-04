/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "plotting/Results.hh"

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
//
#include "Types.hh"
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

Rectangle<float> const& Results::Bounds() const
{
    INFO0;
    return bounds_;
}

Rectangle<float> & Results::Bounds()
{
    INFO0;
    return bounds_;
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

std::vector<Crosssection> const& Results::ModelIndependentCrosssection() const
{
    INFO0;
    return crosssections_;
}

std::vector<Crosssection>& Results::ModelIndependentCrosssection()
{
    INFO0;
    return crosssections_;
}

Results::Results(std::vector<Result> signals, std::vector<Result> backgrounds)
{
    INFO0;
    signals_ = signals;
    backgrounds_ = backgrounds;
    significances_.resize(Steps(), 0);
    crosssections_.resize(Steps(), 0_fb);
    acceptances_.resize(Steps(), 0);
    x_values_.resize(Steps(), 0);
    for (auto & x_value : x_values_) x_value = XValue(&x_value - &x_values_.front());
    ExtremeXValues();
}

void Results::ExtremeXValues()
{
    INFO0;
    switch (Mva()) {
    case TMVA::Types::kBDT : {
        for (auto const & result : backgrounds_) {
            float min_0 = *boost::range::min_element(result.Bdts());
            if (min_0 < bounds_.XMin()) bounds_.SetXMin(min_0);
        }
        for (auto const & result : signals_) {
            float max_0 = *boost::range::max_element(result.Bdts());
            if (max_0 > bounds_.XMax()) bounds_.SetXMax(max_0);
        }
        break;
    }
    case TMVA::Types::kCuts : {
        if (!x_values_.empty()) bounds_.SetXMin(x_values_.front());
        if (!x_values_.empty()) bounds_.SetXMax(x_values_.back());
        break;
    }
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

int Results::Steps() const
{
    INFO0;
    if (signals_.empty()) return 0;
    return signals_.front().Steps();
}

TMVA::Types::EMVA Results::Mva() const
{
    INFO0;
    if (signals_.empty()) return TMVA::Types::kVariable;
    return signals_.front().Mva();
}

void Results::CalculateSignificances()
{
    INFO0;
    for (auto const & step : Range(Steps())) {
        float signal_events = 0;
        Crosssection signal_efficiencies_crossection = 0_fb;
        Crosssection crosssection = 0_fb;
        for (auto const & signal : signals_) {
            signal_events += signal.Events().at(step);
            signal_efficiencies_crossection += double(signal.Efficiencies().at(step)) * signal.InfoBranch().Crosssection();
            if (signal.InfoBranch().Crosssection() > crosssection) crosssection = signal.InfoBranch().Crosssection();
        }
        float signal_efficiencies = signal_efficiencies_crossection / crosssection;
        float background_events = 0;
//         float background_efficiencies = 0;
        for (auto const & background : backgrounds_) {
            background_events += background.Events().at(step);
//             background_efficiencies += background.Efficiencies().at(step);
        }
        if (signal_events + background_events > 0) significances_.at(step) = signal_events / std::sqrt(signal_events + background_events);
        else significances_.at(step) = 0;
        if (background_events > 0) acceptances_.at(step) = signal_events / std::sqrt(background_events);
        else acceptances_.at(step) = 0;

        float exclusion = 2;
        if (signal_efficiencies > 0) crosssections_.at(step) = (exclusion + std::sqrt(sqr(exclusion) + 4. * background_events)) * exclusion / 2. / signal_efficiencies / DetectorGeometry::Luminosity();
        else crosssections_.at(step) = 0_fb;
    }
    BestBin();
}

void Results::BestBin()
{
    INFO0;
    std::vector<float> efficiencies(backgrounds_.size(), 0);
    int counter = 0;
    for (auto const & number : Range(backgrounds_.size())) {
        while (efficiencies.at(number) == 0 && counter < Steps()) {
            best_model_dependent_bin_ = std::distance(significances_.begin(), std::max_element(std::begin(significances_), std::end(significances_) - counter));
            best_model_independent_bin_ = std::distance(crosssections_.begin(), std::min_element(std::begin(crosssections_), std::end(crosssections_) - counter));
            efficiencies.at(number) = backgrounds_.at(number).Efficiencies().at(best_model_independent_bin_);
            best_acceptance_bin_ = std::distance(acceptances_.begin(), std::max_element(std::begin(acceptances_), std::end(acceptances_) - counter));
            ++counter;
        }
    }
    ERROR(best_model_dependent_bin_, best_model_independent_bin_, best_acceptance_bin_);
}

float Results::XValue(int value) const
{
    INFO(value);
    switch (Mva()) {
    case TMVA::Types::kBDT : return 2. * value / Steps() - 1;
    case TMVA::Types::kCuts : return (1. + value) / (Steps() + 1);
    DEFAULT(Mva(),0);
    }
}

}
