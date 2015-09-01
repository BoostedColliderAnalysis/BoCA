#include "Result.hh"

#include "Types.hh"
#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace analysis
{

Result::Result(const InfoBranch& info_branch)
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
    for (const auto & step : Range(steps)) {
        efficiency.at(step) = float(event_sums.at(step)) / info_branch_.EventNumber;
        pure_efficiency.at(step) = float(event_sums.at(step)) / event_sums.at(0);
        events.at(step) = efficiency.at(step) * info_branch_.Crosssection * DetectorGeometry::Luminosity();
        Debug(efficiency.at(step), events.at(step));
    }
    Error(info_branch_.PreCutNumber, event_sums.at(0), info_branch_.EventNumber);
}

int Result::XBin(float value) const
{
    return std::floor((value + 1) * (steps-1) / 2);
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
    for(auto& x_value : x_values) x_value = XValue(&x_value - &x_values[0]);
}

void Results::BestBin()
{
    std::vector<float> efficiencies(background.size(), 0);
    int counter = 0;
    for (const auto & number : Range(background.size())) {
        while (efficiencies.at(number) == 0 && counter < Result::steps) {
            best_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
            efficiencies.at(number) = background.at(number).efficiency.at(best_bin);
            ++counter;
        }
    }
}

void Results::Significances()
{
    for (const int step : Range(Result::steps)) {
        float signal_events = 0;
        for (const auto & signal_results : signal) signal_events += signal_results.events[step];

        float background_events = 0;
        for (const auto & background_result : background) background_events += background_result.events[step];

        if (signal_events + background_events > 0) significances.at(step) = signal_events / std::sqrt(signal_events + background_events);
        else significances.at(step) = 0;
//         x_values.at(step) = XValue(step);
    }
}

float Results::XValue(int value) const
{
    return float(value) * 2 / Result::steps - 1;
}

void Results::ExtremeXValues()
{
    for (const auto & result : background) {
        float min_0 = *std::min_element(result.bdt.begin(), result.bdt.end());
        if (min_0 < min.x) min.x = min_0;
    }
    for (const auto & result : signal) {
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

}
