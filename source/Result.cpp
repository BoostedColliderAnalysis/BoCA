#include "Result.hh"

#include "Types.hh"
#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace analysis
{

void Plots::SetNames(Names const& names, Names const& nice_names)
{
    for (auto & plot : plots) {
        int index = &plot - &plots[0];
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
    return std::floor((value + 1) * steps / 2);
}

void Result::AddBdt(float bdt_value)
{
    bdt.emplace_back(bdt_value);
    ++bins.at(XBin(bdt_value));
    ++event_sum_;
}

Results::Results()
{
    significances.resize(Result::steps, 0);
    x_values.resize(Result::steps, 0);
    for (auto & x_value : x_values) x_value = XValue(&x_value - &x_values[0]);
}

void Results::BestBin()
{
    std::vector<float> efficiencies(background.size(), 0);
    int counter = 0;
    for (auto const & number : Range(background.size())) {
        while (efficiencies.at(number) == 0 && counter < Result::steps) {
            best_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
            efficiencies.at(number) = background.at(number).efficiency.at(best_bin);
            ++counter;
        }
    }
}

void Results::Significances()
{
    for (auto const & step : Range(Result::steps)) {
        float signal_events = 0;
        for (auto const & signal_results : signal) signal_events += signal_results.events[step];

        float background_events = 0;
        for (auto const & background_result : background) background_events += background_result.events[step];

        if (signal_events + background_events > 0) significances.at(step) = signal_events / std::sqrt(signal_events + background_events);
        else significances.at(step) = 0;
//         x_values.at(step) = XValue(step);
    }
}

float Results::XValue(int value) const
{
    return 2. * value / Result::steps - 1;
}

void Results::ExtremeXValues()
{
    for (auto const & result : background) {
        float min_0 = *std::min_element(result.bdt.begin(), result.bdt.end());
        if (min_0 < min.x) min.x = min_0;
    }
    for (auto const & result : signal) {
        float max_0 = *std::max_element(result.bdt.begin(), result.bdt.end());
        if (max_0 > max.x) max.x = max_0;
    }
}

float Results::BestXValue() const
{
    return XValue(best_bin);
}

int ColorCode(int number)
{
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
    return "#font[" + std::to_string(FontCode(Font::times, true, false, 2)) + "]{" + text + "}";
}

int FontCode(Font font, bool italic, bool bold, int precision)
{
    return 10 * FontNumber(font, italic, bold) + precision;
}

int FontNumber(Font font, bool italic, bool bold)
{
    switch (font) {
    case Font::times:
        if (bold && italic) return 3;
        else if (bold) return 2;
        else if (italic) return 1;
        else return 13;
    case Font::helvetica:
        if (bold && italic) return 7;
        else if (bold) return 6;
        else if (italic) return 5;
        else return 4;
    case Font::courier:
        if (bold && italic) return 11;
        else if (bold) return 10;
        else if (italic) return 9;
        else return 8;
    case Font::symbol:
        if (bold && italic) return 14;
        else if (bold) return 14;
        else if (italic) return 15;
        else return 12;
    default :
        return 13;
    }
}

}
