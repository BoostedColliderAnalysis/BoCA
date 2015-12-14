/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "plotting/Result.hh"

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>

#include "Types.hh"
#include "DetectorGeometry.hh"
#include "physics/Math.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

const std::string& Names::Name() const
{
    return name_;
}

const std::string& Names::LatexName() const
{
    return latex_name_;
}

void Names::SetName(const std::string& name)
{
    name_ = name;
}

void Names::SetLatexName(const std::string& latex_name)
{
    latex_name_ = latex_name;
}


const Names& Plot::XAxis() const
{
    return x_axis_;
}

const Names& Plot::YAxis() const
{
    return y_axis_;
}

const Names& Plot::Title() const
{
    return title_;
}

Names& Plot::XAxis()
{
    return x_axis_;
}

Names& Plot::YAxis()
{
    return y_axis_;
}

Names& Plot::Title()
{
    return title_;
}


void Plot::Add(const Vector3< float >& point)
{
    data_.emplace_back(point);
}

const std::vector< Vector3< float > >& Plot::Data() const
{
    return data_;
}

void Plot::Join(const std::vector< Vector3< float > >& data)
{
    data_ = boca::Join(data_, data);
}

std::vector< Vector3< float > > Plot::CoreData(std::function<bool (Vector3<float> const&, Vector3<float> const&)> const& function) const
{
    std::vector<Vector3<float>> data = data_;
    // TODO sorting the whole vector when you just want to get rid of the extrem values might not be the fastest solution
    boost::range::sort(data, [&](Vector3<float> const & a, Vector3<float> const & b) {
        return function(a, b);
    });
    int cut_off = data.size() / 25;
    data.erase(data.end() - cut_off, data.end());
    data.erase(data.begin(), data.begin() + cut_off);
    return data;
}


void Plots::SetNames(NamePairs const& names, NamePairs const& latex_names)
{
    Info0;
    for (auto & plot : plots_) {
        int index = &plot - &plots_.front();
        plot.XAxis().SetName(names.at(index).first);
        plot.XAxis().SetLatexName(latex_names.at(index).first);
        plot.YAxis().SetName(names.at(index).second);
        plot.YAxis().SetLatexName(latex_names.at(index).second);
        plot.Title().SetName(name_);
        plot.Title().SetLatexName(info_branch_.Name);
    }
}


int Result::Steps() const
{
    switch (mva_) {
    case TMVA::Types::EMVA::kBDT : return 200;
    case TMVA::Types::EMVA::kCuts : return passed_.front().size();
        Default(mva_, 0);
    }
}

const InfoBranch& Result::InfoBranch() const
{
    return InfoBranch();
}

const std::vector< float >& Result::Bdts() const
{
    return bdts_;
}

const std::vector< float >& Result::Events() const
{
    return events_;
}

const std::vector< float >& Result::Efficiencies() const
{
    return efficiencies_;
}

const std::vector< Crosssection >& Result::Crosssections() const
{
    return crosssections_;
}

const std::vector< int >& Result::EventSums() const
{
    return event_sums_;
}

// int Steps()
// {
//     return Steps();
// }


Result::Result(boca::InfoBranch const& info_branch, std::vector<float> const& bdts, TMVA::Types::EMVA mva)
{
    Info0;
    info_branch_ = info_branch;
    bdts_ = bdts;
    mva_ = mva;
    Inititialize();
}

Result::Result(boca::InfoBranch const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva)
{
    Info0;
    info_branch_ = info_branch;
    passed_ = passed;
    mva_ = mva;
    Inititialize();
}

void Result::Inititialize()
{
    Info0;
    events_.resize(Steps(), 0);
    efficiencies_.resize(Steps(), 0);
    crosssections_.resize(Steps(), 0);
    pure_efficiencies_.resize(Steps(), 0);
    event_sums_.resize(Steps(), 0);
    bins_.resize(Steps(), 0);
    Calculate();
}

void Result::Calculate()
{
    Info0;

    switch (mva_) {
    case TMVA::Types::EMVA::kBDT : {
        for (auto const & bdt : bdts_) ++bins_.at(XBin(bdt));
        event_sums_.at(Steps() - 1) = bins_.at(Steps() - 1);
        for (int step = Steps() - 2; step >= 0; --step) event_sums_.at(step) = event_sums_.at(step + 1) + bins_.at(step);
        break;
    }
    case TMVA::Types::EMVA::kCuts : {
        for (auto const & passed : passed_) {
            int counter = 0;
            for (auto const & p : passed) {
                if (p) ++event_sums_.at(counter);
                ++counter;
            }
        }
        break;
    }
    }

    for (auto const & step : Range(Steps())) {
        efficiencies_.at(step) = float(event_sums_.at(step)) / InfoBranch().EventNumber;
        pure_efficiencies_.at(step) = float(event_sums_.at(step)) / event_sums_.front();
        crosssections_.at(step) = to_crosssection(InfoBranch().Crosssection * efficiencies_.at(step));
        events_.at(step) = crosssections_.at(step) * DetectorGeometry::Luminosity();
        Debug(efficiencies_.at(step), events_.at(step));
    }
    INFO(InfoBranch().EventNumber, event_sums_.front());
}

int Result::XBin(float value) const
{
    INFO(value);
    switch(mva_){
      case TMVA::Types::kBDT : return std::floor((value + 1) * (Steps() - 1) / 2);
      case TMVA::Types::kCuts : return std::floor((value - 1) * (Steps() - 1) * 10);
      Default(mva_,0);
    }
}

std::vector< Result > const& Results::Signals() const
{
    return signals_;
}

std::vector< Result > const& Results::Backgrounds() const
{
    return backgrounds_;
}

int Results::BestModelDependentBin() const
{
    return best_model_dependent_bin_;
}

int Results::BestModelInDependentBin() const
{
    return best_model_independent_bin_;
}

int Results::BestAcceptanceBin() const
{
    return best_acceptance_bin_;
}

const Rectangle< float >& Results::Bounds() const
{
    return bounds_;
}

Rectangle< float >& Results::Bounds()
{
    return bounds_;
}

const std::vector< float >& Results::XValues() const
{
    return x_values_;
}

const std::vector< float >& Results::Significances() const
{
    return significances_;
}

const std::vector< float >& Results::Acceptances() const
{
    return acceptances_;
}

const std::vector< Crosssection >& Results::ModelIndependentCrosssection() const
{
    return crosssections_;
}

std::vector< Crosssection >& Results::ModelIndependentCrosssection()
{
    return crosssections_;
}

Results::Results(std::vector<Result> signals, std::vector<Result> backgrounds)
{
    Info0;
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
  Info0;
  switch (Mva()) {
    case TMVA::Types::kBDT :{
    for (auto const & result : backgrounds_) {
        float min_0 = *boost::range::min_element(result.Bdts());
        if (min_0 < bounds_.XMin()) bounds_.SetXMin(min_0);
    }
    for (auto const & result : signals_) {
        float max_0 = *boost::range::max_element(result.Bdts());
        if (max_0 > bounds_.XMax()) bounds_.SetXMax(max_0);
    }
    }
    case TMVA::Types::kCuts :{
      if (!x_values_.empty()) bounds_.SetXMin(x_values_.front());
      if (!x_values_.empty()) bounds_.SetXMax(x_values_.back());
    }
  }
}
const TMVA::Types::EMVA& Result::Mva() const
{
    return mva_;
}
Plots::Plots(const InfoBranch& info_branch)
{
    info_branch_ = info_branch;
}
const std::vector< Plot >& Plots::plots() const
{
    return plots_;
}
std::vector< Plot >& Plots::plots()
{
    return plots_;
}
void Plots::SetName(const std::__cxx11::string& name)
{
    name_ = name;
}
int Results::BestModelDependentValue() const
{
    return XValue(BestModelDependentBin());
}
int Results::BestModelInDependentValue() const
{
    return XValue(BestModelInDependentBin());
}
int Results::BestAcceptanceValue() const
{
    return XValue(BestModelDependentBin());
}
int Results::Steps() const
{
    if (signals_.empty()) return 0;
    return signals_.front().Steps();
}
TMVA::Types::EMVA Results::Mva() const
{
    if (signals_.empty()) return TMVA::Types::kVariable;
    return signals_.front().Mva();
}

void Results::CalculateSignificances()
{
    Info0;
    for (auto const & step : Range(Steps())) {
        float signal_events = 0;
        float signal_efficiencies = 0;
        float crosssection = 0;
        for (auto const & signal : signals_) {
            signal_events += signal.Events().at(step);
            signal_efficiencies += signal.Efficiencies().at(step) * signal.InfoBranch().Crosssection;
            if (signal.InfoBranch().Crosssection > crosssection) crosssection = signal.InfoBranch().Crosssection;
        }
        signal_efficiencies /= crosssection;
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
    Info0;
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
}

float Results::XValue(int value) const
{
    INFO(value);
    switch (Mva()) {
    case TMVA::Types::kBDT : return 2. * value / Steps() - 1;
    case TMVA::Types::kCuts : (1. + value) / (Steps() + 1);
    }
}

















// CutResult::CutResult(boca::InfoBranch const& info_branch)
// {
//     Info0;
//     info_branch_ = info_branch;
// }
//
// void CutResult::Inititialize()
// {
//     Info0;
//     steps = passed_.front().size();
//     events.resize(steps, 0);
//     efficiencies_.resize(steps, 0);
//     crosssection.resize(steps, 0);
//     pure_efficiency.resize(steps, 0);
//     event_sums.resize(steps, 0);
//     bins.resize(steps, 0);
// }
//
//
// void CutResult::Calculate()
// {
//     Info0;
//     Inititialize();
//     for (auto const & passed : passed_) {
//         int counter = 0;
//         for (auto const & p : passed) {
//             if (p) ++event_sums.at(counter);
//             ++counter;
//         }
//     }
//
//
//     for (auto const & step : Range(steps)) {
//         efficiencies_.at(step) = float(event_sums.at(step)) / InfoBranch().EventNumber;
//         pure_efficiency.at(step) = float(event_sums.at(step)) / event_sums.front();
//         crosssection.at(step) = to_crosssection(InfoBranch().Crosssection * efficiencies_.at(step));
//         events.at(step) = crosssection.at(step) * DetectorGeometry::Luminosity();
//         INFO(Efficiencies().at(step), Events().at(step));
//     }
//     INFO(InfoBranch().EventNumber, EventSums().front());
//
//
// }
//
// int CutResult::XBin(float value) const
// {
//     INFO(value);
//     return std::floor((value - 1) * (steps - 1) * 10);
// }
//
//
//
// CutResults::CutResults()
// {
//     Info0;
// }
//
// void CutResults::Inititialize()
// {
//     int steps = 0;
//     if (!signals.empty()) steps = signals.front().steps;
//     significances.resize(steps, 0);
//     crosssections.resize(steps, 0_fb);
//     acceptances.resize(steps, 0);
//     x_values.resize(steps, 0);
//     for (auto & x_value : x_values) x_value = XValue(&x_value - &x_values.front());
// }
//
// void CutResults::Significances()
// {
//     Info0;
//     for (auto const & step : Range(signals.front().steps)) {
//         float signal_events = 0;
//         float signal_efficiencies = 0;
//         float crosssection = 0;
//         for (auto const & signal : signals) {
//             signal_events += signal.Events().at(step);
//             signal_efficiencies += signal.Efficiencies().at(step) * signal.InfoBranch().Crosssection;
//             if (signal.InfoBranch().Crosssection > crosssection) crosssection = signal.InfoBranch().Crosssection;
//         }
//         signal_efficiencies /= crosssection;
//         float background_events = 0;
//         //         float background_efficiencies = 0;
//         for (auto const & background : backgrounds) {
//             background_events += background.Events().at(step);
//             //             background_efficiencies += background.Efficiencies().at(step);
//         }
//         if (signal_events + background_events > 0) significances.at(step) = signal_events / std::sqrt(signal_events + background_events);
//         else significances.at(step) = 0;
//         if (background_events > 0) acceptances.at(step) = signal_events / std::sqrt(background_events);
//         else acceptances.at(step) = 0;
//
//         float exclusion = 2;
//         if (signal_efficiencies > 0) crosssections.at(step) = (exclusion + std::sqrt(sqr(exclusion) + 4. * background_events)) * exclusion / 2. / signal_efficiencies / DetectorGeometry::Luminosity();
//         else crosssections.at(step) = 0_fb;
//     }
//     BestBin();
//
// }
//
// void CutResults::BestBin()
// {
//     Info0;
//     std::vector<float> efficiencies(backgrounds.size(), 0);
//     int counter = 0;
//     for (auto const & number : Range(backgrounds.size())) {
//         while (efficiencies.at(number) == 0 && counter < signals.front().steps) {
//             best_model_dependent_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
//             best_model_independent_bin = std::distance(crosssections.begin(), std::min_element(std::begin(crosssections), std::end(crosssections) - counter));
//             efficiencies.at(number) = backgrounds.at(number).Efficiencies().at(best_model_independent_bin);
//             best_acceptance_bin = std::distance(acceptances.begin(), std::max_element(std::begin(acceptances), std::end(acceptances) - counter));
//             ++counter;
//         }
//     }
//     Error(best_model_independent_bin, best_model_dependent_bin);
// }
//
// float CutResults::XValue(int value) const
// {
//     INFO(value);
//     return (1. + value) / (signals.front().steps + 1);
// }
//
// void CutResults::ExtremeXValues()
// {
//     Inititialize();
//     Info0;
// //   for (auto const & result : backgrounds) {
// //     float min_0 = *boost::range::min_element(result.bdt);
// //     if (min_0 < min.x)
//     if (!x_values.empty()) bounds.SetXMin(x_values.front());
// //   }
// //   for (auto const & result : signals) {
// //     float max_0 = *boost::range::max_element(result.bdt);
// //     if (max_0 > max.x)
//     if (!x_values.empty()) bounds.SetXMax(x_values.back());
//     //   }
// }
// const InfoBranch& CutResult::InfoBranch() const
// {
//     return info_branch_;
// }
// const std::vector< float >& CutResult::Bdts() const
// {
//     return bdt;
// }
// const std::vector< Crosssection >& CutResult::Crosssections() const
// {
//     return crosssection;
// }
// const std::vector< int >& CutResult::EventSums() const
// {
//     return event_sums;
// }
// const std::vector< float >& CutResult::Events() const
// {
//     return events;
// }
// void CutResult::AddPassed(std::vector< bool > passed)
// {
//     passed_.emplace_back(passed);
// }
// const std::vector< float >& CutResult::Efficiencies() const
// {
//     return efficiencies_;
// }
// std::vector< float > CutResult::XSec() const
// {
//     std::vector<float> values;
//     values.reserve(crosssection.size());
//     for (auto const & xsec : crosssection) values.emplace_back(xsec / fb);
//     return values;
// }
// std::vector< float > CutResults::Crosssections() const
// {
//     std::vector<float> values;
//     values.reserve(crosssections.size());
//     for (auto const & crosssection : crosssections) values.emplace_back(crosssection / fb);
//     // TODO remove the loop and make use of std lib
//     // std::transform(crosssections.begin(), crosssections.end(), values.begin(), std::bind1st(std::multiplies<float>(), 1. / fb));
//     return values;
// }

}
