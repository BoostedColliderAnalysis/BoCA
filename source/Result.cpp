/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Result.hh"

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>

#include "Types.hh"
#include "DetectorGeometry.hh"
#include "Math.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

void Plots::SetNames(Names const& names, Names const& nice_names)
{
    Info0;
    for (auto & plot : plots) {
        int index = &plot - &plots.front();
        plot.nice_name_x = nice_names.at(index).first;
        plot.nice_name_y = nice_names.at(index).second;
        plot.name = info_branch.Name;
        plot.name_x = names.at(index).first;
        plot.name_y = names.at(index).second;
        plot.tree_name = name;
    }
}

Result::Result(InfoBranch const& info_branch)
{
    Info0;
//     steps = 20000;
    events.resize(steps, 0);
    efficiency.resize(steps, 0);
    crosssection.resize(steps, 0);
    pure_efficiency.resize(steps, 0);
    event_sums.resize(steps, 0);
    bins.resize(steps, 0);
    info_branch_ = info_branch;
}

void Result::Calculate()
{
    Info0;
    event_sums.at(steps - 1) = bins.at(steps - 1);
    for (int step = steps - 2; step >= 0; --step) event_sums.at(step) = event_sums.at(step + 1) + bins.at(step);
    for (auto const & step : Range(steps)) {
        efficiency.at(step) = float(event_sums.at(step)) / info_branch_.EventNumber;
        pure_efficiency.at(step) = float(event_sums.at(step)) / event_sums.front();
        crosssection.at(step) = to_crosssection(info_branch_.Crosssection * efficiency.at(step));
        events.at(step) = crosssection.at(step) * DetectorGeometry::Luminosity();
        Debug(efficiency.at(step), events.at(step));
    }
    Info(info_branch_.EventNumber, event_sums.front());
}

int Result::XBin(float value) const
{
    Info(value);
    return std::floor((value + 1) * (steps - 1) / 2);
}

void Result::AddBdt(float bdt_value)
{
    Info(bdt_value);
    bdt.emplace_back(bdt_value);
    ++bins.at(XBin(bdt_value));
    ++event_sum_;
}

Results::Results()
{
    Info0;
    significances.resize(Result::steps, 0);
    crosssections.resize(Result::steps, 0.*fb);
    acceptances.resize(Result::steps, 0);
    x_values.resize(Result::steps, 0);
    for (auto & x_value : x_values) x_value = XValue(&x_value - &x_values.front());
}

void Results::Significances()
{
    Info0;
    for (auto const & step : Range(Result::steps)) {
        float signal_events = 0;
        float signal_efficiencies = 0;
        float crosssection = 0;
        for (auto const & signal : signals) {
            signal_events += signal.events.at(step);
            signal_efficiencies += signal.efficiency.at(step) * signal.info_branch_.Crosssection;
            if (signal.info_branch_.Crosssection > crosssection) crosssection = signal.info_branch_.Crosssection;
        }
        signal_efficiencies /= crosssection;
        float background_events = 0;
//         float background_efficiencies = 0;
        for (auto const & background : backgrounds) {
            background_events += background.events.at(step);
//             background_efficiencies += background.efficiency.at(step);
        }
        if (signal_events + background_events > 0) significances.at(step) = signal_events / std::sqrt(signal_events + background_events);
        else significances.at(step) = 0;
        if (background_events > 0) acceptances.at(step) = signal_events / std::sqrt(background_events);
        else acceptances.at(step) = 0;

        float exclusion = 2;
        if (signal_efficiencies > 0) crosssections.at(step) = (exclusion + std::sqrt(sqr(exclusion) + 4. * background_events)) * exclusion / 2. / signal_efficiencies/ DetectorGeometry::Luminosity();
        else crosssections.at(step) = 0.*fb;
    }
    BestBin();
}

void Results::BestBin()
{
    Info0;
    std::vector<float> efficiencies(backgrounds.size(), 0);
    int counter = 0;
    for (auto const & number : Range(backgrounds.size())) {
        while (efficiencies.at(number) == 0 && counter < Result::steps) {
            best_model_dependent_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
            best_model_independent_bin = std::distance(crosssections.begin(), std::min_element(std::begin(crosssections), std::end(crosssections) - counter));
            efficiencies.at(number) = backgrounds.at(number).efficiency.at(best_model_independent_bin);
            best_acceptance_bin = std::distance(acceptances.begin(), std::max_element(std::begin(acceptances), std::end(acceptances) - counter));
            ++counter;
        }
    }
}

float Results::XValue(int value)
{
    Info(value);
    return 2. * value / Result::steps - 1;
}

void Results::ExtremeXValues()
{
    Info0;
    for (auto const & result : backgrounds) {
        float min_0 = *boost::range::min_element(result.bdt);
        if (min_0 < min.x) min.x = min_0;
    }
    for (auto const & result : signals) {
        float max_0 = *boost::range::max_element(result.bdt);
        if (max_0 > max.x) max.x = max_0;
    }
}

}
