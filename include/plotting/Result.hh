/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include <boost/range/algorithm/sort.hpp>

#include "TMVA/Types.h"

#include "physics/Vector2.hh"
#include "physics/Vector3.hh"
#include "physics/Units.hh"
#include "physics/Rectangle.hh"
#include "Branches.hh"
#include "Flag.hh"
#include "Vector.hh"

namespace boca
{

class Names
{
public:
    std::string const& Name()const;
    std::string const& LatexName()const;
    void SetName(std::string const& name);
    void SetLatexName(std::string const& latex_name);
private:
    std::string name_;
    std::string latex_name_;
};

class Plot
{
public:
    Names const& XAxis()const;
    Names const& YAxis()const;
    Names const& Title()const;
    Names& XAxis();
    Names& YAxis();
    Names& Title();
    std::vector<Vector3<float>> const& Data() const;
    std::vector<Vector3<float>> CoreData(std::function<bool (Vector3<float> const&, Vector3<float> const&)> const& function) const;
    void Add(Vector3<float> const& point);
    void Join(std::vector<Vector3<float>> const& data);
private:
    std::vector<Vector3<float>> data_;
    Names x_axis_;
    Names y_axis_;
    Names title_;
};

typedef std::vector<std::pair<std::string, std::string>> NamePairs;

class Plots
{
public:
    Plots(InfoBranch const& info_branch);
    void SetNames(NamePairs const& names, NamePairs const& latex_names);
    std::vector<Plot> const& plots() const;
    std::vector<Plot>& plots();
    void SetName(std::string const& name);
private:
    std::vector<Plot> plots_;
    InfoBranch info_branch_;
    std::string name_;
};


class Result
{
public:
    Result(boca::InfoBranch const& info_branch, std::vector<float> const& bdts, TMVA::Types::EMVA mva);
    Result(boca::InfoBranch const& info_branch, std::vector<std::vector<bool>> const& passed, TMVA::Types::EMVA mva);
    boca::InfoBranch const& InfoBranch() const;
    std::vector<float> const& Bdts() const;
    std::vector<float> const& Events() const;
    std::vector<float> const& Efficiencies() const;
    std::vector<Crosssection> const& Crosssections() const;
    std::vector<int> const& EventSums() const;
    int Steps() const;
    TMVA::Types::EMVA const& Mva() const;
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
    boca::InfoBranch info_branch_;
    std::vector<std::vector<bool>> passed_;
//     const static int steps_ = 100;
    TMVA::Types::EMVA mva_;
};

class Results
{
public:
    Results(std::vector<Result> signals, std::vector<Result> backgrounds);
    void CalculateSignificances();
    std::vector<Result> const& Signals()const;
    std::vector<Result> const& Backgrounds()const;
    int BestModelDependentBin()const;
    int BestModelInDependentBin()const;
    int BestAcceptanceBin()const;
    int BestModelDependentValue()const;
    int BestModelInDependentValue()const;
    int BestAcceptanceValue()const;
    Rectangle<float> const& Bounds()const;
    Rectangle<float>& Bounds();
    float XValue(int value) const;
    std::vector<float> const& XValues()const;
    std::vector<float> const& Significances()const;
    std::vector<float> const& Acceptances()const;
    std::vector<Crosssection> const& ModelIndependentCrosssection()const;
    std::vector<Crosssection>& ModelIndependentCrosssection();
private:
    int Steps() const;
    TMVA::Types::EMVA Mva() const;
    void ExtremeXValues();
    void BestBin();
    Rectangle<float> bounds_;
    std::vector<Result> signals_;
    std::vector<Result> backgrounds_;
    std::vector<float> significances_;
    std::vector<float> acceptances_;
    std::vector<Crosssection> crosssections_;
    std::vector<float> x_values_;
    int best_model_dependent_bin_ = 0;
    int best_model_independent_bin_ = 0;
    int best_acceptance_bin_ = 0;
};






// class CutResult
// {
// public:
//     boca::InfoBranch const& InfoBranch() const;
//     std::vector<float> const& Bdts() const;
//     std::vector<Crosssection> const& Crosssections() const;
//     std::vector<int> const& EventSums() const;
//     std::vector<float> const& Events() const;
//     CutResult(boca::InfoBranch const& info_branch);
//     void Inititialize();
//     void Calculate();
//     int XBin(float value) const;
//     void AddPassed(std::vector<bool> passed);;
//     std::vector<float> const& Efficiencies() const;
//     std::vector<int> bins;
//     std::vector<int> event_sums;
//     std::vector<float> events;
//     std::vector<float> efficiencies_;
//     std::vector<float> pure_efficiency;
//     std::vector<float> bdt;
//     std::vector<Crosssection> crosssection;
//     boca::InfoBranch info_branch_;
//     std::vector<std::vector<bool>> passed_;
//     int steps;
//     std::vector<float> XSec() const;
// private:
//     long event_sum_;
// };

// class CutResults
// {
// public:
//     CutResults();
//     void Inititialize();
//     void Significances();
//     void BestBin();
//     float XValue(int value) const;
//     void ExtremeXValues();
//     std::vector<CutResult> signals;
//     std::vector<CutResult> backgrounds;
//     std::vector<float> significances;
//     std::vector<float> acceptances;
//     std::vector<Crosssection> crosssections;
//     std::vector<float> x_values;
//     int best_model_dependent_bin = 0;
//     int best_model_independent_bin = 0;
//     int best_acceptance_bin = 0;
//     Rectangle<float> bounds;
//     std::vector<float> Crosssections() const;
// };

}
