/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>

#include "Tagger.hh"
#include "Flag.hh"

class TMultiGraph;
class TAttLine;
class TTree;
class TH2;
class TProfile2D;
class TExec;
class TFile;
class TLegend;
class TH1;
class TH1F;
class TLine;
class THStack;
class TGraph;
class TAxis;
class TAttFill;

class ExRootTreeBranch;
class ExRootTreeReader;
namespace exroot
{
typedef ::ExRootTreeBranch TreeBranch;
typedef ::ExRootTreeReader TreeReader;
}

namespace boca
{

class Plots;
class Plot;
class Point;
class Result;
class Results;

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
    Plotting(boca::Tagger& tagger);

    void TaggingEfficiency() const;

    void OptimalSignificance() const;

    void RunPlots() const;

private:

    void DoPlot(boca::Plots& signals, boca::Plots& backgrounds, boca::Stage stage) const;

    void PlotDetails(boca::Plot& signal, boca::Plot& background, boca::Stage stage) const;

    void SetHistogram(TH2& histogram, const boca::Plot& plot, EColor color, TExec& exec) const;

    void SetProfile(TProfile2D& histogram, const boca::Plot& signal, const boca::Plot& background) const;

    void Fill(TAttFill& pad) const;

    void CommmonHist(TH1& histogram, const boca::Plot& plot, EColor color) const;

    std::vector<Plots> Import(boca::Stage stage, boca::Tag tag) const;

    Plots PlotResult(TFile& file, std::string const& tree_name, boca::Stage stage) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1, std::string const& leaf_2, boca::Stage stage) const;

    void PlotHistogram(const boca::Plot& signal, const boca::Plot& background, const boca::Point& min, const boca::Point& max) const;

    void PlotProfile(const boca::Plot& signal, const boca::Plot& background, const boca::Point& min, const boca::Point& max) const;

    void SetMultiGraph(TMultiGraph& multi_graph, const boca::Point& min, const boca::Point& max) const;

    void SetPlotStyle(TAttLine& att_line, int index) const;

    void SetPad() const;

    TLegend Legend(float x_min, float y_min, float width, float height, std::string const& title = "") const;

    TLegend Legend(boca::Orientation orientation, boca::Strings const& entries, std::string const& title = "") const;

    int Letters(std::vector<Result> result) const;

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, boca::Tag tag) const;

    TH1F Histogram(const boca::Result& result, boca::Point& max, boca::Point& min, int index) const;

    TLine Line(const boca::Results& results, float y_min, float y_max) const;

    void AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, Strings const& name, int index) const;

    void PlotAcceptanceGraph(const boca::Results& results) const;

    std::string PlotHistograms(boca::Results& results) const;

    void AddHistogram(THStack& stack, TH1& histogram, TLegend& legend) const;

    boca::InfoBranch InfoBranch(TFile& file, std::string const& tree_name) const;

    Result BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const;

    std::string Table(Results const& results) const;

    std::string PlotEfficiencyGraph(const boca::Results& results) const;

    std::string PlotSignificanceGraph(boca::Results& results) const;

    Plot CoreVector(Plot& plot, std::function<bool(Point const&, Point const&)> const& function) const;

    std::string ExportFileSuffix() const;

    void SetAxis(TAxis& axis, std::string const& title) const;

    float TextSize() const;

    float LabelSize() const;

    boca::Tagger& Tagger() const;

    boca::Tagger* tagger_;

};

}
