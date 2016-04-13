/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TMVA/Types.h"

#include "physics/Units.hh"
#include "Branches.hh"

namespace boca
{

class Result
{
public:
    Result(){};
    Result(boca::InfoBranch const& info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::pair<boca::InfoBranch,int> const& trainer_info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::pair<boca::InfoBranch,int> const& trainer_info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva);
    boca::InfoBranch const& InfoBranch() const;
    boca::InfoBranch const& TrainerInfoBranch() const;
    std::vector<double> const& Bdts() const;
    std::vector<double> const& Events() const;
    std::vector<double> const& Efficiencies() const;
    std::vector<double> const& PureEfficiencies() const;
    std::vector<Crosssection> const& Crosssections() const;
    std::vector<int> const& EventSums() const;
    int Steps() const;
    TMVA::Types::EMVA const& Mva() const;
    void SetModelIndependent(const boca::Crosssection& crosssection, int step);
    std::vector<Crosssection> ModelIndependent() const;
    void SetModelIndependentSB(const boca::Crosssection& crosssection, int step);
    std::vector<Crosssection> ModelIndependentSB() const;
    void SetModelIndependentSig(const boca::Crosssection& crosssection, int step);
    std::vector<Crosssection> ModelIndependentSig() const;
    std::vector<double> const& SelectedEfficiencies() const;
    void AddSelectedEfficiency(double selected_efficiency);
    void AddSelectedEfficiency(int selected_efficiency);
    int TrainerSize() const;
private:
    void Inititialize();
    void Calculate();
    int XBin(double value) const;
    std::vector<int> bins_;
    std::vector<int> event_sums_;
    std::vector<double> events_;
    std::vector<double> efficiencies_;
    std::vector<double> pure_efficiencies_;
    std::vector<double> bdts_;
    std::vector<Crosssection> crosssections_;
    std::vector<Crosssection> model_independent_;
    std::vector<Crosssection> model_independent_sb_;
    std::vector<Crosssection> model_independent_sig_;
    boca::InfoBranch info_branch_;
    boca::InfoBranch trainer_info_branch_;
    int trainer_size_;
    std::vector<std::vector<bool>> passed_;
    TMVA::Types::EMVA mva_;
    std::vector<double> selected_efficiencies_;
};

}
