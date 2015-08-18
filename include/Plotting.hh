/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>

#include "Tagger.hh"
#include "Result.hh"
#include "Flag.hh"

class TMultiGraph;
class TAttLine;
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
class TAxis;

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
    center = 0,
    left = 1 << 0,
    right = 1 << 1,
    top = 1 << 2,
    bottom = 1 << 3
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

    void CommmonHist(TH2& histogram, const analysis::Plot& plot, EColor color) const;

    std::vector<Plots> Import(analysis::Stage stage, analysis::Tag tag) const;

    Plots PlotResult(TFile& file, std::string const& tree_name, analysis::Stage stage) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1, std::string const& leaf_2, analysis::Stage stage) const;

    void PlotHistogram(const analysis::Plot& signal, const analysis::Plot& background, const analysis::Point& min, const analysis::Point& max) const;

    void PlotProfile(const analysis::Plot& signal, const analysis::Plot& background, const analysis::Point& min, const analysis::Point& max) const;

    void SetMultiGraph(TMultiGraph& multi_graph, const analysis::Point& min, const analysis::Point& max) const;

    void SetPlotStyle(TAttLine& att_line, int index) const;

    TLegend Legend(float x_min, float y_min, float width, float height, std::string const& title = "") const;

    TLegend Legend(analysis::Orientation orientation, analysis::Strings const& entries, std::string const& title = "") const;

    int Letters(std::vector<Result> result) const;

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, analysis::Tag tag) const;

    TH1F Histogram(const analysis::Result& result, analysis::Point& max, analysis::Point& min, int index) const;

    TLine Line(analysis::Results results, float y_min, float y_max) const;

    void AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, Strings const& name, int index) const;

    void PlotAcceptanceGraph(const analysis::Results& results) const;

    std::string PlotHistograms(analysis::Results& results) const;

    void AddHistogram(THStack& stack, TH1F& histogram, TLegend& legend) const;

    analysis::Tagger& Tagger() const;

    analysis::InfoBranch InfoBranch(TFile& file, std::string const& tree_name) const;

    Result BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const;

    std::string Table(Results const& results) const;

    std::string PlotEfficiencyGraph(const analysis::Results& results) const;

    std::string PlotSignificanceGraph(const analysis::Results& results) const;

    Plot CoreVector(Plot& plot, std::function<bool(Point&, Point&)> const& function) const;

    std::string ExportFileSuffix() const;

    analysis::Tagger* tagger_;

    void SetAxis(TAxis& axis, std::string const& title) const;

    float TextSize() const;

    float LabelSize() const;

};

}
