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
    Result(boca::InfoBranch const& info_branch, std::vector<float> const& bdts, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva);
    boca::InfoBranch const& InfoBranch() const;
    std::vector<float> const& Bdts() const;
    std::vector<float> const& Events() const;
    std::vector<float> const& Efficiencies() const;
    std::vector<float> const& PureEfficiencies() const;
    std::vector<Crosssection> const& Crosssections() const;
    std::vector<int> const& EventSums() const;
    int Steps() const;
    TMVA::Types::EMVA const& Mva() const;
    void SetModelIndependent(Crosssection crosssection, int step);
    std::vector<Crosssection> ModelIndependent() const;
    void SetModelIndependentSB(Crosssection crosssection, int step);
    std::vector<Crosssection> ModelIndependentSB() const;
    void SetModelIndependentSig(Crosssection crosssection, int step);
    std::vector<Crosssection> ModelIndependentSig() const;
    std::vector<float> const& SelectedEfficiencies() const;
    void AddSelectedEfficiency(float selected_efficiency);
    void AddSelectedEfficiency(int selected_efficiency);
private:
    void Inititialize();
    void Calculate();
    int XBin(float value) const;
    std::vector<int> bins_;
    std::vector<int> event_sums_;
    std::vector<float> events_;
    std::vector<float> efficiencies_;
    std::vector<float> pure_efficiencies_;
    std::vector<float> bdts_;
    std::vector<Crosssection> crosssections_;
    std::vector<Crosssection> model_independent_;
    std::vector<Crosssection> model_independent_sb_;
    std::vector<Crosssection> model_independent_sig_;
    boca::InfoBranch info_branch_;
    std::vector<std::vector<bool>> passed_;
    TMVA::Types::EMVA mva_;
    std::vector<float> selected_efficiencies_;
};

}
