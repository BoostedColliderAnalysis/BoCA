/**
 * Copyright (C) 2015 Jan Hajer
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
    boca::InfoBranch info_branch_;
    std::vector<std::vector<bool>> passed_;
    TMVA::Types::EMVA mva_;
};

}
