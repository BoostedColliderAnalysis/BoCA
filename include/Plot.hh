#pragma once

#include "Tagger.hh"
#include "TLegend.h"
#include "TFile.h"
#include "Branches.hh"
#include <functional>

class TMultiGraph;
class TAttLine;
class TTree;
class TH2;
class TProfile2D;
class TExec;

class ExRootTreeBranch;
class ExRootTreeReader;
namespace exroot
{
typedef ::ExRootTreeBranch TreeBranch;
typedef ::ExRootTreeReader TreeReader;
}

namespace analysis
{

class Result
{

public:

    Result();
    std::vector<int> CutIntegral() const;

    int steps;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<int> analysis_event_number;
    std::vector<float> bdt;
    std::vector<int> bins;
    InfoBranch info_branch;
    long event_sum() const;
    void set_event_sum(const long int event_sum);
private:
    long event_sum_;
};

struct Results {

public:

    Results();

    std::vector<Result> signal;
    std::vector<Result> background;
    std::vector<float> significances;
    std::vector<float> x_values;
    int best_bin = 0;

    void Significances();

    void BestBin();



};




struct Point2d {
    float x;
    float y;
    float z;
};

struct Plot2d {
    std::vector<Point2d> points;
    std::string name_x;
    std::string name_y;
    std::string nice_name_x;
    std::string nice_name_y;
    std::string name;
    std::string tree_name;
};

struct Plots {
    std::vector<Plot2d> plots;
    analysis::InfoBranch info_branch;
    std::string name;
};

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Plot
{

public:

    /**
     * @brief Default constructor
     *
     */
//     Plot();

    /**
     * @brief Constructor
     *
     */
    Plot(Tagger &tagger);

    void TaggingEfficiency() const;

    void OptimalSignificance() const;

    void RunPlots() const;

    void DoPlot(analysis::Plots &signals, analysis::Plots &backgrounds) const;

    void Plotting(const analysis::Plot2d &signal, const analysis::Plot2d &background) const;

    void SetHistogram(TH2 &histogram, const analysis::Plot2d &plot, const EColor color, TExec &exec) const;

    void SetProfile(TProfile2D &histogram, const analysis::Plot2d &signal, const analysis::Plot2d &background) const;

private:

    std::vector< Plots > Import(const std::string &file_name, const analysis::Strings &treename) const;

    Plots PlotResult(TFile &file, const std::string &tree_name) const;

    Plot2d ReadTree(TTree &tree, const std::string &leaf_1, const std::string &leaf_2) const;

    void PlotHistogram(const analysis::Plot2d &signal, const analysis::Plot2d &background, const float x_min, const float x_max, const float y_min, const float y_max) const;

    void PlotProfile(const analysis::Plot2d &signal, const analysis::Plot2d &background, const float x_min, const float x_max, const float y_min, const float y_max) const;

    float Bdt() const;

    void SetMultiGraph(TMultiGraph &multi_graph) const;

    void SetPlotStyle(TAttLine &att_line, const int index) const;

    TLegend Legend(float x_min, float y_max, float width, float height, const std::string &name = "") const;

    Results ExportFile() const;

    std::vector<Result> Export(TFile &export_file, const std::string &file_name, const analysis::Strings &treename) const;

    void PlotAcceptanceGraph(const analysis::Results &results) const;

    std::string PlotHistograms(const analysis::Results &results) const;

    Tagger &tagger() const {
        return *tagger_;
    }

    Tagger *tagger_;

    analysis::InfoBranch InfoBranch(TFile &file, const std::string &tree_name) const;

    Result BdtDistribution(exroot::TreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const;

    Result BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const;

    std::string PlotEfficiencyGraph(const analysis::Results &results, const std::vector< float > &x_values, const int best_bin) const;

    std::string PlotSignificanceGraph(const Results &results, const std::vector<float> &x_values, const std::vector<float> &significances, const int best_bin) const;

    void LatexHeader(std::ofstream &latex_file) const;

    void LatexFooter(std::ofstream &latex_file) const;

    int ColorCode(const int number) const;

    std::string ExportName() const;

    Plot2d CoreVector(const Plot2d &points, std::function<bool(Point2d&, Point2d&)> function) const;

    std::string ExportFileSuffix() const {
      return ".png";
    }

};

}
