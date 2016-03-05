/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Tagger.hh"
#include "physics/Rectangle.hh"

class TFile;
class TTree;

namespace boca
{

class Plots;
class Result;
class Results;
class Plot;
class Graphs;

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

    void OptimalCuts() const;

    void RunPlots(Stage stage) const;

    void RunPlotHist() const;

private:

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, Tag tag) const;

    Result BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const;

    Result CutDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const;

    void DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const;

    void PlotDetails(Plot& signal, Plot& background, Stage stage) const;

    std::vector<Plots> Import(Stage stage, Tag tag) const;

    std::vector<Plots> Import2() const;

    Plots PlotResult(TFile& file, std::string const& tree_name, Stage stage) const;

    Plots PlotResult2(const Observable& variable, Tag tag, Plots& plots) const;

    Plots PlotResult3(const Observable& variable) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const;

    Plot ReadTree2(TTree& tree, std::string const& leaf_name) const;

    void PlotHistogram(const Plot& signal, const Plot& background, Rectangle<float> const& range) const;

    void PlotProfile(const Plot& signal, const Plot& background, Rectangle<float> const& range) const;

    std::vector<std::string> PlotAcceptanceGraph(Results const& results) const;

    std::string PlotCrosssectionsGraph(Results const& results) const;

    std::string PlotCrosssectionGraph(Results const& results) const;

    std::string PlotSBGraph(Results const& results) const;

    std::string PlotSBvsSsqrtBGraph(Results const& results) const;

    std::string PlotHistograms(Results const& results) const;

    boca::InfoBranch InfoBranch(TFile& file, std::string const& tree_name) const;

    std::string BestValueTable(Results const& results) const;

    std::string BestValueRow(Results const& results, int bin, std::string const& name) const;

    std::string EfficienciesTable(Results const& results, int bin) const;

    std::string EfficienciesRow(const Result& result, int index, Tag tag, int bin) const;

    std::string CutEfficiencyTable(Results const& results) const;

    std::string CutEfficiencyRow(Result const& result, int index, Tag tag) const;

    std::string PlotEfficiencyGraph(Results const& results) const;

    std::string PlotModelDependentGraph(Results const& results) const;

    std::string PlotModelIndependentGraph(Results const& results) const;

    std::string PlotModelIndependentGraphSig(Results const& results) const;

    std::string PlotModelIndependentGraphSB(Results const& results) const;

    void SetDefaultXAxis(Graphs& graphs, Results const& results) const;

    void PlotVariables(Plots const& plots) const;

    boca::Tagger const& Tagger() const;

    boca::Tagger& tagger_;

};

}
