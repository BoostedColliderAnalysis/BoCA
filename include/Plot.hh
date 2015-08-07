#pragma once

#include <functional>

#include "Tagger.hh"
#include "Result.hh"

class TMultiGraph;
class TAttLine;
class TTree;
class TH2;
class TProfile2D;
class TExec;
class TFile;
class TLegend;
class TH1F;

class ExRootTreeBranch;
class ExRootTreeReader;
namespace exroot
{
typedef ::ExRootTreeBranch TreeBranch;
typedef ::ExRootTreeReader TreeReader;
}

namespace analysis
{

class Tagger;

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Plot
{

public:

    /**
     * @brief Constructor
     *
     */
    Plot(analysis::Tagger& tagger);

    void TaggingEfficiency() const;

    void OptimalSignificance() const;

    void RunPlots() const;

private:

    void DoPlot(analysis::Plots& signals, analysis::Plots& backgrounds, analysis::Stage stage) const;

    void Plotting(const analysis::Plot3d& signal, const analysis::Plot3d& background, analysis::Stage stage) const;

    void SetHistogram(TH2& histogram, const analysis::Plot3d& plot, EColor color, TExec& exec) const;

    void SetProfile(TProfile2D& histogram, const analysis::Plot3d& signal, const analysis::Plot3d& background) const;

    std::string IncludeGraphic(std::string& file_name, std::string caption) const;

    void CommmonHist(TH2& histogram, const analysis::Plot3d& plot, EColor color) const;

    std::vector<Plots> Import(analysis::Stage stage, analysis::Tag tag) const;

    Plots PlotResult(TFile& file, const std::string& tree_name, analysis::Stage stage) const;

    Plot3d ReadTree(TTree& tree, const std::string& leaf_1, const std::string& leaf_2, analysis::Stage stage) const;

    void PlotHistogram(const analysis::Plot3d& signal, const analysis::Plot3d& background, const analysis::Point& min, const analysis::Point& max) const;

    void PlotProfile(const analysis::Plot3d& signal, const analysis::Plot3d& background, const analysis::Point& min, const analysis::Point& max) const;

    void SetMultiGraph(TMultiGraph& multi_graph) const;

    void SetPlotStyle(TAttLine& att_line, int index) const;

    TLegend Legend(float x_min, float y_max, float width, float height, const std::string& name = "") const;

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, analysis::Tag tag) const;

    TH1F Histogram(const analysis::Result& result, analysis::Point& max, analysis::Point& min, int index) const;

    void PlotAcceptanceGraph(const analysis::Results& results) const;

    std::string PlotHistograms(analysis::Results& results) const;

    void SetHistogram(TH1F& histogram, TLegend& legend, std::string& nice_name, const Point& max) const;

    analysis::Tagger& Tagger() const;

    analysis::InfoBranch InfoBranch(TFile& file, const std::string& tree_name) const;

    Result BdtDistribution(TFile& file, const std::string& tree_name, TFile& export_file) const;

    std::string Table(const Results& results) const;

    std::string PlotEfficiencyGraph(const analysis::Results& results) const;

    std::string PlotSignificanceGraph(const analysis::Results& results) const;

    void LatexHeader(std::ofstream& latex_file) const;

    void LatexFooter(std::ofstream& latex_file) const;

    int ColorCode(int number) const;

    Plot3d CoreVector(const Plot3d& points, const std::function<bool(Point&, Point&)>& function) const;

    std::string ExportFileSuffix() const;

    std::string Reader()const;

    analysis::Tagger* tagger_;

};

}
