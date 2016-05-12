/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <map>

#include "TMVA/Types.h"

#include "boca/generic/Mutable.hh"
#include "boca/generic/Flag.hh"
#include "boca/Branches.hh"

namespace boca
{

enum class Significance
{
    none = 0,
    experimental = 1 << 0, //< experimental error $s/b$
    sum = 1 << 1, //< simple significance estimator $s / sqrt b$
    background = 1 << 2, //< slighly more complicated estimator for significance $s/sqrt{s+b}$
    poisson = 1 << 3, //< poisson estimator for significance $sqrt{-2 ln L1 / L 0}$
    discovery = 1 << 4, //< discovery hypothesis and requirement
    exclusion = 1 << 5, //< exclusion hypothesis and requirement
};

std::string Name(Significance significance);

latex::String LatexName(Significance significance);

template<>
struct Flag<Significance> {
    static const bool enable = true;
};

std::vector<Significance> Constrained(std::vector<Significance> const& significances);
std::vector<Significance> Exclusion(std::vector<Significance> const& significances);
std::vector<Significance> Discovery(std::vector<Significance> const& significances);
std::vector<Significance> SignificancesSimple();
std::vector<Significance> SignificancesBase();
std::vector<Significance> SignificancesMD();
std::vector<Significance> SignificancesMI();
std::vector<Significance> Significances();

class Result
{
public:
    Result() {};
    Result(boca::InfoBranch const& info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::pair<boca::InfoBranch, int> const& trainer_info_branch, std::vector<double> const& bdts, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::pair<boca::InfoBranch, int> const& trainer_info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva);
    boca::InfoBranch const& InfoBranch() const;
    boca::InfoBranch const& TrainerInfoBranch() const;
    std::vector<double> const& Bdts() const;
    std::vector<double> const& Events() const;
    std::vector<double> const& PreCutEfficiencies() const;
    std::vector<double> const& PureEfficiencies() const;
    std::vector<Crosssection> const& Crosssections() const;
    std::vector<int> const& PartialSum() const;
    std::vector<int> const& Bins() const;
    static int Steps();
    static double XValue(int value);
    double BestMDValue(Significance significance) const;
    double BestMIValue(Significance significance) const;
    static TMVA::Types::EMVA const& Mva();
    std::vector<Crosssection>& MI(Significance significance);
    std::vector<Crosssection> const& MI(Significance significance)const;
    std::vector<double>& MD(Significance significance);
    std::vector<double> const& MD(Significance significance) const;
    int& BestMDBin(Significance significance);
    int BestMDBin(Significance significance) const;
    int& BestMIBin(Significance significance);
    int BestMIBin(Significance significance)const;
    std::vector<double> const& SelectedEfficiencies() const;
    void AddSelectedEfficiency(double selected_efficiency);
    void AddSelectedEfficiency(int selected_efficiency);
    int TrainerSize() const;
private:
    void Inititialize();
    int XBin(double value) const;
    int trainer_size_;
    static TMVA::Types::EMVA mva_;
    boca::InfoBranch info_branch_;
    boca::InfoBranch trainer_info_branch_;
    Mutable<std::vector<int>> bins_;
    Mutable<std::vector<int>> event_sums_;
    std::vector<double> bdts_;
    std::vector<double> selected_efficiencies_;
    Mutable<std::vector<double>> events_;
    Mutable<std::vector<double>> efficiencies_;
    Mutable<std::vector<double>> pure_efficiencies_;
    Mutable<std::vector<Crosssection>> crosssections_;
    static std::vector<std::vector<bool>> passed_;
    std::map<Significance, int> best_model_dependent_bin_;
    std::map<Significance, int> best_model_independent_bin_;
    std::map<Significance, std::vector<double>> model_dependent_;
    std::map<Significance, std::vector<Crosssection>> model_independent_;
};

}
