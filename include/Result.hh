#pragma once

#include "Branches.hh"
#include "Flag.hh"

namespace analysis
{


enum class Font
{
    times,
    helvetica,
    courier,
    symbol
};

enum class Style
{
  normal = 0,
  bold = 1 << 0,
  italic = 1 << 1
};

template<>
struct Flag<Style> {
  static const bool enable = true;
};

struct Point {
    Point() {};
    Point(float xx, float yy) {
        x = xx;
        y = yy;
    }
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

typedef std::vector<std::pair<std::string, std::string>> Names;

class Plots
{
public:
    std::vector<Plot> plots;
    analysis::InfoBranch info_branch;
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

std::string Formula(std::string const& text);

int FontCode(Font font = Font::times, Style style = Style::normal, int precision = 2);

int FontNumber(Font font = Font::times, Style style = Style::normal);

}
