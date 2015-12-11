/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Branches.hh"
#include "Flag.hh"
#include "plotting/Canvas.hh"
#include "physics/Units.hh"
#include "../HeavyHiggs/include/Branch.hh"

namespace boca
{

class Point
{
public:
    Point() {};
    Point(float xx, float yy, float zz = 0) {
        x = xx;
        y = yy;
        z = zz;
    }
    float x = 0;
    float y = 0;
    float z = 0;
};

class Plot
{
public:
    std::vector<Point> points;
    std::string name_x;
    std::string name_y;
    std::string nice_name_x;
    std::string nice_name_y;
    std::string name;
    std::string tree_name;
    void Add(Point const& point) {
        points.emplace_back(point);
    }
};

typedef std::vector<std::pair<std::string, std::string>> Names;

class Plots
{
public:
    std::vector<Plot> plots;
    InfoBranch info_branch;
    std::string name;
    void SetNames(Names const& names, Names const& nice_names);
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
    Point min;
    Point max;
    Limits limits_x;
    Limits limits_y;

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
  void AddPassed(std::vector<bool> passed){
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
  Point min;
  Point max;

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
