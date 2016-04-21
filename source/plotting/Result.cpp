/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Result.hh"
#include "generic/Types.hh"
#include "generic/Vector.hh"
#include "DetectorGeometry.hh"
// #define DEBUGGING
#include "generic/DEBUG.hh"

namespace boca
{

std::vector< Significance > SignificancesUnConstrained()
{
    return {Significance::background, Significance::sum, Significance::poisson};
}

std::vector< Significance > SignificancesConstrained()
{
    return Transform(SignificancesUnConstrained(), [](Significance significance) {
        return significance | Significance::experimental;
    });
}

std::vector< Significance > Significances()
{
    return Combine( {Significance::experimental}, SignificancesConstrained(), SignificancesUnConstrained());
}

std::string Name(Significance significance)
{
    std::string name;
    FlagSwitch(significance, [&](Significance significance) {
        switch (significance) {
        case Significance::none : name += "None ";
            break;
        case Significance::experimental : name += "Experimental ";
            break;
        case Significance::background : name += "Background ";
            break;
        case Significance::sum : name += "Sum ";
            break;
        case Significance::poisson : name += "Poisson ";
            break;
            DEFAULT(to_int(significance));
        }
    });
    return name;
}

int Result::Steps() const
{
    INFO0;
    switch (mva_) {
    case TMVA::Types::EMVA::kBDT : return 200;
    case TMVA::Types::EMVA::kCuts : return passed_.front().size();
        DEFAULT(mva_, 0);
    }
}

double Result::XValue(int value) const
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
    return XValue(BestMDBin(significance));
}

double Result::BestMIValue(Significance significance) const
{
    return XValue(BestMIBin(significance));
}

const InfoBranch& Result::InfoBranch() const
{
    INFO0;
    return info_branch_;
}

const InfoBranch& Result::TrainerInfoBranch() const
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
            return crosssection * DetectorGeometry::Luminosity();
        });
    });
}

std::vector<double> const& Result::PreCutEfficiencies() const
{
    INFO0;
    return efficiencies_.Get([&]() {
        return Transform(PartialSum(), [&](double event_sum) {
            return event_sum / InfoBranch().EventNumber();
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
            return InfoBranch().Crosssection() * efficiency;
        });
    });
}

std::vector<int> const& Result::PartialSum() const
{
    INFO0;
    return event_sums_.Get([&]() {
        std::vector<int> event_sums(Steps());
        switch (mva_) {
        case TMVA::Types::EMVA::kBDT : std::partial_sum(Bins().rbegin(), Bins().rend(), event_sums.rbegin());
            return event_sums;
        case TMVA::Types::EMVA::kCuts : for (auto const & passed : passed_) for (auto const & step : IntegerRange(Steps())) if (passed.at(step)) ++event_sums.at(step);
            return event_sums;
            DEFAULT(mva_, event_sums);
        };
    });
}

std::vector<int> const& Result::Bins() const
{
    return bins_.Get([&]() {
        std::vector<int> bins(Steps());
        for (auto const & bdt : Bdts()) ++bins.at(XBin(bdt));
        return bins;
    });
}

Result::Result(boca::InfoBranch const& info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva)
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

Result::Result(boca::InfoBranch const& info_branch, std::pair<boca::InfoBranch, int> const& trainer_info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva)
{
    INFO0;
    info_branch_ = info_branch;
    trainer_info_branch_ = trainer_info_branch.first;
    trainer_size_ = trainer_info_branch.second;
    bdts_ = bdts;
    mva_ = mva;
    Inititialize();
}

Result::Result(boca::InfoBranch const& info_branch, std::pair<boca::InfoBranch, int> const& trainer_info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva)
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
    INFO(value);
    switch (mva_) {
    case TMVA::Types::kBDT : return std::floor((value + 1) * (Steps() - 1) / 2);
    case TMVA::Types::kCuts : return std::floor((value - 1) * (Steps() - 1) * 10);
        DEFAULT(mva_, 0);
    }
}

TMVA::Types::EMVA const& Result::Mva() const
{
    return mva_;
}

std::vector< Crosssection >& Result::MI(Significance significance)
{
    return model_independent_.at(significance);
}

std::vector<double>& Result::MD(Significance significance)
{
    return model_dependent_.at(significance);
}

int& Result::BestMDBin(Significance significance)
{
    return best_model_dependent_bin_.at(significance);
}

int& Result::BestMIBin(Significance significance)
{
    return best_model_independent_bin_.at(significance);
}

std::vector< Crosssection > const& Result::MI(Significance significance) const
{
    return model_independent_.at(significance);
}

std::vector<double> const& Result::MD(Significance significance) const
{
    return model_dependent_.at(significance);
}

int Result::BestMDBin(Significance significance) const
{
    return best_model_dependent_bin_.at(significance);
}

int Result::BestMIBin(Significance significance) const
{
    return best_model_independent_bin_.at(significance);
}

std::vector<double > const& Result::SelectedEfficiencies() const
{
    return selected_efficiencies_;
}

void Result::AddSelectedEfficiency(double selected_efficiency)
{
    selected_efficiencies_.emplace_back(selected_efficiency);
}

void Result::AddSelectedEfficiency(int index)
{
    selected_efficiencies_.emplace_back(PureEfficiencies().at(index));
}

int Result::TrainerSize() const
{
    return trainer_size_;
}

}
