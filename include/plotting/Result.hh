/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include <boost/range/algorithm/sort.hpp>

#include "physics/Vector2.hh"
#include "physics/Vector3.hh"
#include "physics/Units.hh"
#include "plotting/Canvas.hh"
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
    void Add(Vector3<float> const& point);
    std::vector<Vector3<float>> const& Data() const;
    void Join(std::vector<Vector3<float>> const& data);
    std::vector<Vector3<float>> CoreData(std::function<bool (Vector3<float> const&, Vector3<float> const&)> const& function) const;
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
    std::vector<Plot> plots;
    InfoBranch info_branch;
    std::string name;
    void SetNames(NamePairs const& names, NamePairs const& latex_names);
};

class Result
{
public:
    Result(InfoBranch const& info_branch);
    void Calculate();
    int XBin(float value) const;
    void AddBdt(float bdt_value);
    std::vector<int> bins;
    std::vector<int> event_sums;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<float> pure_efficiency;
    std::vector<float> bdt;
    std::vector<Crosssection> crosssection;
    InfoBranch info_branch_;
    const static int steps = 100;

    std::vector<float> XSec() const {
        std::vector<float> values;
        values.reserve(crosssection.size());
        for (auto const & xsec : crosssection) values.emplace_back(xsec / fb);
        return values;
    }
private:
    long event_sum_;
};

class Results
{
public:
    Results();
    void Significances();
    void BestBin();
    static float XValue(int value);
    void ExtremeXValues();
    std::vector<Result> signals;
    std::vector<Result> backgrounds;
    std::vector<float> significances;
    std::vector<float> acceptances;
    std::vector<Crosssection> crosssections;
    std::vector<float> x_values;
    int best_model_dependent_bin = 0;
    int best_model_independent_bin = 0;
    int best_acceptance_bin = 0;
    Limits<float> limits_x;
    Limits<float> limits_y;

    std::vector<float> Crosssections() const {
        std::vector<float> values;
        values.reserve(crosssections.size());
        for (auto const & crosssection : crosssections) values.emplace_back(crosssection / fb);
        // TODO remove the loop and make use of std lib
// std::transform(crosssections.begin(), crosssections.end(), values.begin(), std::bind1st(std::multiplies<float>(), 1. / fb));
        return values;
    }


};






class CutResult
{
public:
    CutResult(InfoBranch const& info_branch);
    void Inititialize();
    void Calculate();
    int XBin(float value) const;
    void AddPassed(std::vector<bool> passed) {
        passed_.emplace_back(passed);
    };
    std::vector<int> bins;
    std::vector<int> event_sums;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<float> pure_efficiency;
    std::vector<float> bdt;
    std::vector<Crosssection> crosssection;
    InfoBranch info_branch_;
    std::vector<std::vector<bool>> passed_;
    int steps;

    std::vector<float> XSec() const {
        std::vector<float> values;
        values.reserve(crosssection.size());
        for (auto const & xsec : crosssection) values.emplace_back(xsec / fb);
        return values;
    }
private:
    long event_sum_;
};

class CutResults
{
public:
    CutResults();
    void Inititialize();
    void Significances();
    void BestBin();
    float XValue(int value) const;
    void ExtremeXValues();
    std::vector<CutResult> signals;
    std::vector<CutResult> backgrounds;
    std::vector<float> significances;
    std::vector<float> acceptances;
    std::vector<Crosssection> crosssections;
    std::vector<float> x_values;
    int best_model_dependent_bin = 0;
    int best_model_independent_bin = 0;
    int best_acceptance_bin = 0;
    Limits<float> limits_x;
    Limits<float> limits_y;

    std::vector<float> Crosssections() const {
        std::vector<float> values;
        values.reserve(crosssections.size());
        for (auto const & crosssection : crosssections) values.emplace_back(crosssection / fb);
        // TODO remove the loop and make use of std lib
        // std::transform(crosssections.begin(), crosssections.end(), values.begin(), std::bind1st(std::multiplies<float>(), 1. / fb));
        return values;
    }


};

}
