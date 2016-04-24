/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <map>

#include "TMVA/Types.h"

#include "generic/Mutable.hh"
#include "generic/Flag.hh"
#include "physics/Units.hh"
#include "Branches.hh"

namespace boca
{

enum class Significance
{
    none = 0,
    experimental = 1 << 0,
    background = 1 << 1,
    sum = 1 << 2,
    poisson = 1 << 3,
};

std::string Name(Significance significance);

std::string LatexName(Significance significance);

template<>
struct Flag<Significance> {
    static const bool enable = true;
};

std::vector<Significance> Significances();
std::vector<Significance> SignificancesConstrained();
std::vector<Significance> SignificancesUnConstrained();

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
