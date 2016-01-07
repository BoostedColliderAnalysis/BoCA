/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "plotting/Result.hh"
#include "Types.hh"
#include "DetectorGeometry.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

int Result::Steps() const
{
    Info0;
    switch (mva_) {
    case TMVA::Types::EMVA::kBDT : return 200;
    case TMVA::Types::EMVA::kCuts : return passed_.front().size();
        Default(mva_, 0);
    }
}

const InfoBranch& Result::InfoBranch() const
{
    Info0;
    return info_branch_;
}

std::vector<float> const& Result::Bdts() const
{
    Info0;
    return bdts_;
}

std::vector<float> const& Result::Events() const
{
    Info0;
    return events_;
}

std::vector<float> const& Result::Efficiencies() const
{
    Info0;
    return efficiencies_;
}

std::vector<Crosssection> const& Result::Crosssections() const
{
    Info0;
    return crosssections_;
}

std::vector<int> const& Result::EventSums() const
{
    Info0;
    return event_sums_;
}

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
    default : Error(mva_, "Default case");
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
    switch (mva_) {
    case TMVA::Types::kBDT : return std::floor((value + 1) * (Steps() - 1) / 2);
    case TMVA::Types::kCuts : return std::floor((value - 1) * (Steps() - 1) * 10);
        Default(mva_, 0);
    }
}

TMVA::Types::EMVA const& Result::Mva() const
{
    Info0;
    return mva_;
}

}
