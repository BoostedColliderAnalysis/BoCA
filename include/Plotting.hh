#pragma once

#include <functional>

#include "Tagger.hh"
#include "Result.hh"
#include "Flag.hh"

class TMultiGraph;
class TAttLine;
class TAttText;
class TAxis;
class TTree;
class TH2;
class TProfile2D;
class TExec;
class TFile;
class TLegend;
class TH1F;
class TLine;
class THStack;
class TGraph;

class ExRootTreeBranch;
class ExRootTreeReader;
namespace exroot
{
typedef ::ExRootTreeBranch TreeBranch;
typedef ::ExRootTreeReader TreeReader;
}

namespace analysis
{

enum class Orientation
{
    center = 1,
    left = 1<<1,
    right = 1<<2,
    top = 1<<3,
    bottom = 1<<4
};

template<>
struct Flag<Orientation> {
  static const bool enable = true;
};

class Tagger;

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Plotting
{

public:

    /**
     * @brief Constructor
     *
     */
    Plotting(analysis::Tagger& tagger);

    void TaggingEfficiency() const;

    void OptimalSignificance() const;

    void RunPlots() const;

private:

    void DoPlot(analysis::Plots& signals, analysis::Plots& backgrounds, analysis::Stage stage) const;

    void PlotDetails(analysis::Plot& signal, analysis::Plot& background, analysis::Stage stage) const;

    void SetHistogram(TH2& histogram, const analysis::Plot& plot, EColor color, TExec& exec) const;

    void SetProfile(TProfile2D& histogram, const analysis::Plot& signal, const analysis::Plot& background) const;

    std::string IncludeGraphic(std::string& file_name, std::string caption) const;

    void CommmonHist(TH2& histogram, const analysis::Plot& plot, EColor color) const;

    std::vector<Plots> Import(analysis::Stage stage, analysis::Tag tag) const;

    Plots PlotResult(TFile& file, const std::string& tree_name, analysis::Stage stage) const;

    Plot ReadTree(TTree& tree, const std::string& leaf_1, const std::string& leaf_2, analysis::Stage stage) const;

    void PlotHistogram(const analysis::Plot& signal, const analysis::Plot& background, const analysis::Point& min, const analysis::Point& max) const;

    void PlotProfile(const analysis::Plot& signal, const analysis::Plot& background, const analysis::Point& min, const analysis::Point& max) const;

    void SetMultiGraph(TMultiGraph& multi_graph) const;

    void SetPlotStyle(TAttLine& att_line, int index) const;
    
    void SetTextStyle(TAttText& att_text) const;
    void SetTextStyle(TAxis& att_text) const;

    TLegend Legend(float x_min, float y_min, float width, float height, const std::string& title = "") const;

    TLegend Legend(analysis::Orientation orientation, const analysis::Strings& entries, const std::string& title = "") const;

    int Letters(std::vector<Result> result) const;

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, analysis::Tag tag) const;

    TH1F Histogram(const analysis::Result& result, analysis::Point& max, analysis::Point& min, int index) const;
    
    TLine Line(analysis::Results results, float y_min, float y_max) const;

    void AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, const std::string& name, int index) const;

    void PlotAcceptanceGraph(const analysis::Results& results) const;

    std::string PlotHistograms(analysis::Results& results) const;

    void AddHistogram(THStack& stack, TH1F& histogram, TLegend& legend) const;

    analysis::Tagger& Tagger() const;

    analysis::InfoBranch InfoBranch(TFile& file, const std::string& tree_name) const;

    Result BdtDistribution(TFile& file, const std::string& tree_name, TFile& export_file) const;

    std::string Table(const Results& results) const;

    std::string PlotEfficiencyGraph(const analysis::Results& results) const;

    std::string PlotSignificanceGraph(const analysis::Results& results) const;

    void LatexHeader(std::ofstream& latex_file) const;

    void LatexFooter(std::ofstream& latex_file) const;

    Plot CoreVector(Plot& plot, const std::function<bool(Point&, Point&)>& function) const;

    std::string ExportFileSuffix() const;

    analysis::Tagger* tagger_;

};

}
