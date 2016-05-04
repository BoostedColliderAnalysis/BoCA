/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>

#include "boca/generic/Types.hh"
#include "boca/generic/Vector.hh"
#include "boca/plotting/Result.hh"
#include "boca/DetectorGeometry.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

std::vector< Significance > Constrained(std::vector<Significance> const& significances)
{
    INFO0;
    return Transform(significances, [](Significance significance) {
        return significance | Significance::experimental;
    });
}

std::vector< Significance > Exclusion(std::vector<Significance> const& significances)
{
    INFO0;
    return Transform(significances, [](Significance significance) {
        return significance | Significance::exclusion;
    });
}

std::vector< Significance > Discovery(std::vector<Significance> const& significances)
{
    INFO0;
    return Transform(significances, [](Significance significance) {
        return significance | Significance::discovery;
    });
}
std::vector< Significance > SignificancesSimple()
{
    INFO0;
    return {Significance::sum, Significance::background};
}

std::vector< Significance > SignificancesMD()
{
    INFO0;
    return Combine(SignificancesSimple(), Exclusion( {Significance::poisson}), Discovery( {Significance::poisson}));
}

std::vector< Significance > SignificancesBase()
{
    INFO0;
    return Combine(SignificancesSimple(), {Significance::poisson});
}

std::vector< Significance > SignificancesMI()
{
    INFO0;
    return Combine(Exclusion(SignificancesBase()), Discovery(SignificancesBase()));
}

std::vector< Significance > SignificancesMDI()
{
    INFO0;
    return Combine(SignificancesMI(), SignificancesSimple(), {Significance::experimental});
}

std::vector< Significance > Significances()
{
    INFO0;
    return Combine(Constrained(Combine(SignificancesMI(), SignificancesSimple())), SignificancesMDI());
}

std::string Name(Significance significance)
{
    INFO0;
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
        case Significance::discovery : name += "Discovery ";
            break;
        case Significance::exclusion : name += "Exclusion ";
            break;
        case Significance::poisson : name += "Poisson ";
            break;
            DEFAULT(to_int(significance));
        }
    });
    return name;
}

latex::String LatexName(Significance significance)
{
    INFO0;
    latex::String name;
    FlagSwitch(significance, [&](Significance significance) {
        switch (significance) {
        case Significance::experimental :
            name += name.empty() ? "" : " and " ;
            name += "\\frac{S}{B}";
            break;
        case Significance::background :
            name += name.empty() ? "" : " and " ;
            name += "\\frac{S}{\\sqrt{B}}";
            break;
        case Significance::sum :
            name += name.empty() ? "" : " and " ;
            name += "\\frac{S}{\\sqrt{S + B}}";
            break;
        case Significance::discovery :
//           name += name.empty() ? "" : " and " ;
            name += "|_{5}";
            break;
        case Significance::exclusion :
//           name += name.empty() ? "" : " and " ;
            name += "|_{2}";
            break;
        case Significance::poisson :
            name += name.empty() ? "" : " and " ;
            name += "\\sqrt{2\\frac{L_{1}}{L_{0}}}";
            break;
            DEFAULT(to_int(significance));
        }
    });
    return name;
}

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
        switch (Mva()) {
        case TMVA::Types::EMVA::kBDT : boost::partial_sum(boost::adaptors::reverse(Bins()) , event_sums.rbegin());
            break;
        case TMVA::Types::EMVA::kCuts : for (auto const & passed : passed_) for (auto const & step : IntegerRange(Steps())) if (passed.at(step)) ++event_sums.at(step);
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

}

