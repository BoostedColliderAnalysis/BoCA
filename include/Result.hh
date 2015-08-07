#pragma once

#include "Branches.hh"

namespace analysis
{

class Result
{
public:
    Result(const InfoBranch &info_branch);
    void Calculate();
    int XBin(float value) const;
    void AddBdt(float bdt_value);
    std::vector<int> bins;
    std::vector<int> event_sums;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<float> bdt;
    InfoBranch info_branch_;
    const static int steps = 20000;
private:
    long event_sum_;
};

struct Point {
    Point();
    float x;
    float y;
    float z;
};

class Results
{
public:
    Results();
    void Significances();
    void BestBin();
    float XValue(int value) const;
    float BestXValue() const;
    void ExtremeXValues();
    std::vector<Result> signal;
    std::vector<Result> background;
    std::vector<float> significances;
    std::vector<float> x_values;
    int best_bin = 0;
    Point min;
    Point max;
};

struct Plot3d {
    std::vector<Point> points;
    std::string name_x;
    std::string name_y;
    std::string nice_name_x;
    std::string nice_name_y;
    std::string name;
    std::string tree_name;
};

struct Plots {
    std::vector<Plot3d> plots;
    analysis::InfoBranch info_branch;
    std::string name;
};

}
