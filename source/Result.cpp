/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Result.hh"

#include "Types.hh"
#include "DetectorGeometry.hh"
#include "Math.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

void Plots::SetNames(Names const& names, Names const& nice_names)
{
    Info();
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
    Info();
//     steps = 20000;
    events.resize(steps, 0);
    efficiency.resize(steps, 0);
    pure_efficiency.resize(steps, 0);
    event_sums.resize(steps, 0);
    bins.resize(steps, 0);
    info_branch_ = info_branch;
}

void Result::Calculate()
{
    Info();
    event_sums.at(steps - 1) = bins.at(steps - 1);
    for (int step = steps - 2; step >= 0; --step) event_sums.at(step) = event_sums.at(step + 1) + bins.at(step);
    for (auto const & step : Range(steps)) {
        efficiency.at(step) = float(event_sums.at(step)) / info_branch_.EventNumber;
        pure_efficiency.at(step) = float(event_sums.at(step)) / event_sums.at(0);
        events.at(step) = efficiency.at(step) * info_branch_.Crosssection * DetectorGeometry::Luminosity();
        Debug(efficiency.at(step), events.at(step));
    }
    Error(info_branch_.EventNumber, event_sums.at(0));
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
    Info();
    significances.resize(Result::steps, 0);
    crosssections.resize(Result::steps, 0);
    x_values.resize(Result::steps, 0);
    for (auto & x_value : x_values) x_value = XValue(&x_value - &x_values.front());
}

void Results::Significances()
{
    Info();
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
        float background_efficiencies = 0;
        for (auto const & background : backgrounds) {
            background_events += background.events.at(step);
            background_efficiencies += background.efficiency.at(step);
        }
        if (signal_events + background_events > 0) significances.at(step) = signal_events / std::sqrt(signal_events + background_events);
        else significances.at(step) = 0;

        float exclusion = 2;
        if (signal_efficiencies > 0) crosssections.at(step) = (exclusion + std::sqrt(sqr(exclusion) + 4 * background_events)) * exclusion / 2 / DetectorGeometry::Luminosity() / signal_efficiencies;
        else crosssections.at(step) = 0;
    }
    BestBin();
}

void Results::BestBin()
{
    Info();
    std::vector<float> efficiencies(backgrounds.size(), 0);
    int counter = 0;
    for (auto const & number : Range(backgrounds.size())) {
        while (efficiencies.at(number) == 0 && counter < Result::steps) {
            best_model_dependent_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
            best_model_independent_bin = std::distance(crosssections.begin(), std::min_element(std::begin(crosssections), std::end(crosssections) - counter));
            efficiencies.at(number) = backgrounds.at(number).efficiency.at(best_model_independent_bin);
            ++counter;
        }
    }
}

float Results::XValue(int value) const
{
    Info(value);
    return 2. * value / Result::steps - 1;
}

void Results::ExtremeXValues()
{
    Info();
    for (auto const & result : backgrounds) {
        float min_0 = *std::min_element(result.bdt.begin(), result.bdt.end());
        if (min_0 < min.x) min.x = min_0;
    }
    for (auto const & result : signals) {
        float max_0 = *std::max_element(result.bdt.begin(), result.bdt.end());
        if (max_0 > max.x) max.x = max_0;
    }
}

float Results::BestModelDependentXValue() const
{
    Info();
    return XValue(best_model_dependent_bin);
}

float Results::BestModelInDependentXValue() const
{
    Info();
    return XValue(best_model_independent_bin);
}

int ColorCode(int number)
{
    Info();
    switch (number) {
    case 0 :
        return kBlack;
    case 1 :
        return kRed;
    case 2 :
        return kBlue;
    case 3 :
        return kTeal - 5;
    case 4 :
        return kPink + 1;
    case 5 :
        return kViolet;
    case 6 :
        return kOrange;
    case 7 :
        return kYellow - 9;
    case 8 :
        return kSpring - 5;
    case 9 :
        return kGreen + 3;
    case 10 :
        return kCyan - 3;
    case 11 :
        return kMagenta - 3;
    case 12 :
        return kAzure;
    case 13 :
        return kGray;
    default :
        return kBlack;
    }
}

std::string Formula(std::string const& text)
{
    Info(text);
    return "#font[" + std::to_string(FontCode(Font::times, Style::italic)) + "]{" + text + "}";
}

int FontCode(Font font, Style style, int precision)
{
    Info();
    return 10 * FontNumber(font, style) + precision;
}

int FontNumber(Font font, Style style)
{
    Info();
    switch (font) {
    case Font::times:
        if (style == Style::italic) return 1;
        if (style == Style::bold) return 2;
        if (style == (Style::italic | Style::bold)) return 3;
        return 13;
    case Font::helvetica:
        if (style == Style::italic) return 5;
        if (style == Style::bold) return 6;
        if (style == (Style::italic | Style::bold)) return 7;
        return 4;
    case Font::courier:
        if (style == Style::italic) return 9;
        if (style == Style::bold) return 10;
        if (style == (Style::italic | Style::bold)) return 11;
        else return 8;
    case Font::symbol:
        if (style == Style::italic) return 15;
        if (style == Style::bold) return 14;
        if (style == (Style::italic | Style::bold)) return 14;
        return 12;
    default :
        return 13;
    }
}

}
