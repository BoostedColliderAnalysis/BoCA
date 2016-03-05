/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Result.hh"
#include "Types.hh"
#include "DetectorGeometry.hh"
// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

int Result::Steps() const
{
    INFO0;
    switch (mva_) {
    case TMVA::Types::EMVA::kBDT : return 200;
    case TMVA::Types::EMVA::kCuts : return passed_.front().size();
        DEFAULT(mva_, 0);
    }
}

const InfoBranch& Result::InfoBranch() const
{
    INFO0;
    return info_branch_;
}

std::vector<float> const& Result::Bdts() const
{
    INFO0;
    return bdts_;
}

std::vector<float> const& Result::Events() const
{
    INFO0;
    return events_;
}

std::vector<float> const& Result::Efficiencies() const
{
    INFO0;
    return efficiencies_;
}

std::vector<float> const& Result::PureEfficiencies() const
{
    INFO0;
    return pure_efficiencies_;
}

std::vector<Crosssection> const& Result::Crosssections() const
{
    INFO0;
    return crosssections_;
}

std::vector<int> const& Result::EventSums() const
{
    INFO0;
    return event_sums_;
}

Result::Result(boca::InfoBranch const& info_branch, std::vector<float> const& bdts, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    bdts_ = bdts;
    mva_ = mva;
    Inititialize();
}

Result::Result(boca::InfoBranch const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    passed_ = passed;
    mva_ = mva;
    Inititialize();
}

void Result::Inititialize()
{
    INFO0;
    events_.resize(Steps(), 0);
    efficiencies_.resize(Steps(), 0);
    crosssections_.resize(Steps(), 0);
    model_independent_.resize(Steps(), 0);
    model_independent_sig_.resize(Steps(), 0);
    model_independent_sb_.resize(Steps(), 0);
    pure_efficiencies_.resize(Steps(), 0);
    event_sums_.resize(Steps(), 0);
    bins_.resize(Steps(), 0);
    Calculate();
}

void Result::Calculate()
{
    INFO0;
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
    default : ERROR(mva_, "Default case");
    }

    for (auto const & step : IntegerRange(Steps())) {
        efficiencies_.at(step) = float(event_sums_.at(step)) / InfoBranch().EventNumber();
        pure_efficiencies_.at(step) = float(event_sums_.at(step)) / event_sums_.front();
        crosssections_.at(step) = InfoBranch().Crosssection() * double(efficiencies_.at(step));
        events_.at(step) = crosssections_.at(step) * DetectorGeometry::Luminosity();
        DEBUG(efficiencies_.at(step), events_.at(step));
    }
    INFO(InfoBranch().EventNumber(), event_sums_.front());
}

int Result::XBin(float value) const
{
    INFO(value);
    switch (mva_) {
    case TMVA::Types::kBDT : return std::floor((value + 1) * (Steps() - 1) / 2);
    case TMVA::Types::kCuts : return std::floor((value - 1) * (Steps() - 1) * 10);
        DEFAULT(mva_, 0);
    }
}

TMVA::Types::EMVA const& Result::Mva() const
{
    INFO0;
    return mva_;
}
void Result::SetModelIndependent(Crosssection crosssection, int step)
{
    INFO0;
    model_independent_.at(step) = crosssection;
}
std::vector< Crosssection > Result::ModelIndependent() const
{
    return model_independent_;
}
void Result::SetModelIndependentSB(Crosssection crosssection, int step)
{
  INFO0;
  model_independent_sb_.at(step) = crosssection;
}
std::vector< Crosssection > Result::ModelIndependentSB() const
{
  return model_independent_sb_;
}
void Result::SetModelIndependentSig(Crosssection crosssection, int step)
{
  INFO0;
  model_independent_sig_.at(step) = crosssection;
}
std::vector< Crosssection > Result::ModelIndependentSig() const
{
  return model_independent_sig_;
}
std::vector<float > const& Result::SelectedEfficiencies() const
{
    return selected_efficiencies_;
}
void Result::AddSelectedEfficiency(float selected_efficiency)
{
    selected_efficiencies_.emplace_back(selected_efficiency);
}
void Result::AddSelectedEfficiency(int index)
{
  selected_efficiencies_.emplace_back(PureEfficiencies().at(index));
}

}
