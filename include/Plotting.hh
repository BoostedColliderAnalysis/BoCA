/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>

#include "Tagger.hh"
#include "TTree.h"

// class TTree;
class TProfile2D;
class TFile;

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
class Result;
class Results;
class CutResult;
class CutResults;
class Point;
class Plot;

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

    void RunPlots() const;

    void Cuts() const;

private:

    void DoPlot(boca::Plots& signals, boca::Plots& backgrounds, boca::Stage stage) const;

    void PlotDetails(boca::Plot& signal, boca::Plot& background, Stage stage) const;

    std::vector<Plots> Import(Stage stage, boca::Tag tag) const;

    Plots PlotResult(TFile& file, std::string const& tree_name, Stage stage) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const;

    void PlotHistogram(const boca::Plot& signal, const boca::Plot& background, const boca::Point& min, const boca::Point& max) const;

    void PlotProfile(const boca::Plot& signal, const boca::Plot& background, const boca::Point& min, const boca::Point& max) const;

    void SetPad() const;

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, boca::Tag tag) const;

    void PlotAcceptanceGraph(const boca::Results& results) const;

    std::string PlotCrosssectionsGraph(const boca::Results& results) const;

    std::string PlotCrosssectionGraph(Results& results) const;

    std::string PlotHistograms(boca::Results& results) const;

    boca::InfoBranch InfoBranch(TFile& file, std::string const& tree_name) const;

    Result BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const;

    std::string BestValueTable(Results const& results) const;

    std::string BestValueRow(Results const& results, int bin, std::string const& name) const;

    std::string EfficienciesTable(Results const& results, int bin) const;

    std::string EfficienciesRow(const boca::Result& result, int index, boca::Tag tag, int bin) const;

    std::string PlotEfficiencyGraph(const boca::Results& results) const;

    std::string PlotModelDependentGraph(boca::Results& results) const;

    std::string PlotModelIndependentGraph(boca::Results& results) const;

    Plot CoreVector(Plot& plot, std::function<bool(Point const&, Point const&)> const& function) const;

    void SetBranch(TTree &tree, int &value, std::string const& name) const;

    void SetBranch(TTree &tree, std::vector<float> &values, std::string const& name) const;

    boca::Tagger const& Tagger() const;

    boca::Tagger& tagger_;






    CutResults ReadCutFiles() const;

    std::vector<CutResult> ReadCutFile(TFile& export_file, boca::Tag tag) const;

    CutResult CutDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const;

    std::string PlotCutResult(boca::CutResults& results) const;

    std::string PlotCutEfficiencyGraph(const CutResults& results) const;

};

}
