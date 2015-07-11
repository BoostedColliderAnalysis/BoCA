#pragma once

#include "Tagger.hh"
#include "TLegend.h"
#include "TFile.h"
#include "Branches.hh"

class TMultiGraph;
class TAttLine;
class TTree;
class TH2F;
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




struct PlotPoint {
    float x;
    float y;
};

class Plot2d
{
public:
  void operator =(std::vector<PlotPoint> &points){points_=points;}
    void NewPoint(const PlotPoint &plot_point) {
        points_.emplace_back(plot_point);
    }
    const std::vector<PlotPoint> &points()const {
        return points_;
    }
private:
    std::vector<PlotPoint> points_;
};

class Plots
{
public:
    Plots(const int size) {
        plots_.resize(size);
    }
//     Plot2d &At(const int i) {
//       std::cout<< plots_.size() << " " << i << std::endl;
//         return plots_.at(i);
//     }
std::vector<Plot2d> &plots() {
      return plots_;
    }
private:
    std::vector<Plot2d> plots_;
};

struct PlotResults {
  std::vector<std::vector<std::vector<PlotPoint>>> signal;
  std::vector<std::vector<std::vector<PlotPoint>>> background;
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

    void InputFiles() const;

    void DoPlot(const std::vector< std::vector< analysis::PlotPoint > > &signal, const std::vector< std::vector< analysis::PlotPoint > > &background) const;

    void Plotting(const std::vector< analysis::PlotPoint > &signal, const std::vector< analysis::PlotPoint > &background, const std::pair< std::string, std::string > &pair) const;

    void SetHist(TH2F &histogram, const std::vector< analysis::PlotPoint > &data, const std::pair< std::string, std::string > &pair, const bool signal) const;

private:



    std::vector< std::vector< std::vector< PlotPoint > > > Import(const std::string &file_name, const analysis::Strings &treename) const;

    std::vector<std::vector<PlotPoint>> PlotResult(TFile &file, const std::string &tree_name) const;

    std::vector<PlotPoint> ReadTree(TTree &tree, const std::string &leaf_1, const std::string &leaf_2) const;


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

};

}
