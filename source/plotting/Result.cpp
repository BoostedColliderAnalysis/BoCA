/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>

#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/plotting/Result.hh"
#include "boca/Settings.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

TMVA::Types::EMVA Result::mva_ = TMVA::Types::EMVA::kVariable;

std::vector<std::vector<bool>> Result::passed_;

int Result::Steps()
{
    DEBUG0;
    switch (Mva()) {
    case TMVA::Types::EMVA::kBDT : return 200;
    case TMVA::Types::EMVA::kCuts : return passed_.front().size();
        DEFAULT(Mva(), 0);
    }
}

double Result::XValue(int value)
{
    INFO(value);
    switch (Mva()) {
    case TMVA::Types::kBDT : return 2. * value / Steps() - 1;
    case TMVA::Types::kCuts : return (1. + value) / (Steps() + 1);
        DEFAULT(Mva(), 0);
    }
}

double Result::BestMDValue(Significance significance) const
{
    INFO0;
    return XValue(BestMDBin(significance));
}

double Result::BestMIValue(Significance significance) const
{
    INFO0;
    return XValue(BestMIBin(significance));
}

const branch::Info& Result::Info() const
{
    INFO0;
    return info_branch_;
}

const branch::Info& Result::TrainerInfo() const
{
    INFO0;
    return trainer_info_branch_;
}

std::vector<double> const& Result::Bdts() const
{
    INFO0;
    return bdts_;
}

std::vector<double> const& Result::Events() const
{
    INFO0;
    return events_.Get([&]() {
        return Transform(Crosssections(), [](Crosssection const & crosssection) -> double {
            return crosssection * Settings::Luminosity();
        });
    });
}

std::vector<double> const& Result::PreCutEfficiencies() const
{
    INFO0;
    return efficiencies_.Get([&]() {
        return Transform(PartialSum(), [&](double event_sum) {
            return event_sum / Info().EventNumber();
        });
    });
}

std::vector<double> const& Result::PureEfficiencies() const
{
    INFO0;
    return pure_efficiencies_.Get([&]() {
        return Transform(PartialSum(), [&](double event_sum) {
            return event_sum / PartialSum().front();
        });
    });
}

std::vector<Crosssection> const& Result::Crosssections() const
{
    INFO0;
    return crosssections_.Get([&]() {
        return Transform(PreCutEfficiencies(), [&](double efficiency) {
            return Info().Crosssection() * efficiency * ScalingFactor();
        });
    });
}

std::vector<int> const& Result::PartialSum() const
{
    INFO0;
    return event_sums_.Get([&]() {
        auto event_sums = std::vector<int>(Steps());
        switch (Mva()) {
        case TMVA::Types::EMVA::kBDT : boost::partial_sum(boost::adaptors::reverse(Bins()), event_sums.rbegin());
            break;
        case TMVA::Types::EMVA::kCuts : for (auto const & passed : passed_) for (auto step : IntegerRange(Steps())) if (passed.at(step)) ++event_sums.at(step);
            break;
            DEFAULT(Mva());
        };
        return event_sums;
    });
}

std::vector<int> const& Result::Bins() const
{
    INFO0;
    return bins_.Get([&]() {
        auto bins = std::vector<int>(Steps());
        for (auto const & bdt : Bdts()) ++bins.at(XBin(bdt));
        return bins;
    });
}

Result::Result(boca::branch::Info const& info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    bdts_ = bdts;
    mva_ = mva;
    Inititialize();
}

Result::Result(boca::branch::Info const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    passed_ = passed;
    mva_ = mva;
    Inititialize();
}

Result::Result(boca::branch::Info const& info_branch, std::pair<boca::branch::Info, int> const& trainer_info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    trainer_info_branch_ = trainer_info_branch.first;
    trainer_size_ = trainer_info_branch.second;
    bdts_ = bdts;
    mva_ = mva;
    Inititialize();
}

Result::Result(boca::branch::Info const& info_branch, std::pair<boca::branch::Info, int> const& trainer_info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    trainer_info_branch_ = trainer_info_branch.first;
    trainer_size_ = trainer_info_branch.second;
    passed_ = passed;
    mva_ = mva;
    Inititialize();
}

void Result::Inititialize()
{
    INFO0;
    for (auto const & significance : Significances()) {
        model_dependent_[significance].resize(Steps(), 0.);
        model_independent_[significance].resize(Steps(), 0_b);
        best_model_dependent_bin_[significance] = 0;
        best_model_independent_bin_[significance] = 0;
    }
}

int Result::XBin(double value) const
{
    DEBUG(value);
    switch (Mva()) {
    case TMVA::Types::kBDT : return std::floor((value + 1) * (Steps() - 1) / 2);
    case TMVA::Types::kCuts : return std::floor((value - 1) * (Steps() - 1) * 10);
        DEFAULT(Mva(), 0);
    }
}

TMVA::Types::EMVA const& Result::Mva()
{
    DEBUG0;
    return mva_;
}

std::vector< Crosssection >& Result::MI(Significance significance)
{
    INFO0;
    return model_independent_.at(significance);
}

std::vector<double>& Result::MD(Significance significance)
{
    INFO0;
    return model_dependent_.at(significance);
}

int& Result::BestMDBin(Significance significance)
{
    INFO0;
    return best_model_dependent_bin_.at(significance);
}

int& Result::BestMIBin(Significance significance)
{
    INFO0;
    return best_model_independent_bin_.at(significance);
}

std::vector< Crosssection > const& Result::MI(Significance significance) const
{
    INFO0;
    return model_independent_.at(significance);
}

std::vector<double> const& Result::MD(Significance significance) const
{
    INFO0;
    return model_dependent_.at(significance);
}

int Result::BestMDBin(Significance significance) const
{
    INFO0;
    return best_model_dependent_bin_.at(significance);
}

int Result::BestMIBin(Significance significance) const
{
    INFO0;
    return best_model_independent_bin_.at(significance);
}

std::vector<double > const& Result::SelectedEfficiencies() const
{
    INFO0;
    return selected_efficiencies_;
}

void Result::AddSelectedEfficiency(double selected_efficiency)
{
    INFO0;
    selected_efficiencies_.emplace_back(selected_efficiency);
}

void Result::AddSelectedEfficiency(int index)
{
    INFO0;
    selected_efficiencies_.emplace_back(PureEfficiencies().at(index));
}

int Result::TrainerSize() const
{
    INFO0;
    return trainer_size_;
}

void Result::SetScalingFactor(double scaling_factor)
{
    scaling_factor_ = scaling_factor;
}

double Result::ScalingFactor() const
{
    return scaling_factor_;
}

}

