#pragma once

#include "Branches.hh"

namespace analysis
{

struct Point {
    float x = 0;
    float y = 0;
    float z = 0;
};

struct Plot {
    std::vector<Point> points;
    std::string name_x;
    std::string name_y;
    std::string nice_name_x;
    std::string nice_name_y;
    std::string name;
    std::string tree_name;
};

class Plots
{
public:
    std::vector<Plot> plots;
    analysis::InfoBranch info_branch;
    std::string name;
    void SetNames(const std::vector<std::pair<std::string, std::string>>& names, const std::vector<std::pair<std::string, std::string>>& nice_names) {
        for (auto & plot : plots) {
            int index = &plot - &plots[0];
            plot.nice_name_x = nice_names.at(index).first;
            plot.nice_name_y = nice_names.at(index).second;
            plot.name = info_branch.Name;
            plot.name_x = names.at(index).first;
            plot.name_y = names.at(index).second;
            plot.tree_name = name;
        }
    }

};

class Result
{
public:
    Result(const InfoBranch& info_branch);
    void Calculate();
    int XBin(float value) const;
    void AddBdt(float bdt_value);
    std::vector<int> bins;
    std::vector<int> event_sums;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<float> pure_efficiency;
    std::vector<float> bdt;
    InfoBranch info_branch_;
    const static int steps = 20000;
private:
    long event_sum_;
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

int ColorCode(int number);

}
