/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/plotting/Result.hh"
#include "boca/multivariant/Phase.hh"

class TFile;
class TTree;

namespace boca
{

class Plots;
class FileWriter;
class Results;
class Plot;
class Graphs;
class InfoBranch;
template<typename Type_>
class Rectangle;
class Tagger;
class LatexRow;
class LatexTable;

/**
 * @brief Presents result of multivariant analysis
 *
 */
class PlottingBase
{

public:

    void TaggingEfficiency() const;

    void OptimalCuts() const;

    void RunPlots(Stage stage) const;

    void RunPlotHist() const;

private:

    Results ReadBdtFiles(boca::Stage stage) const;

    std::vector<Result> ReadBdtFile(boca::FileWriter& file_writer, const boca::Phase& phase) const;

    Result BdtDistribution(boca::FileWriter& file_writer, const boca::Phase& phase, int tree_number) const;

    Result CutDistribution(boca::FileWriter& file_writer, const boca::Phase& phase, int tree_number) const;

    std::pair<boca::InfoBranch, int> InfoBranch(Phase const& phase, int tree_number) const;

    void DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const;

    void PlotDetails(Plot& signal, Plot& background, Stage stage) const;

    std::vector<Plots> Import(Phase const& phase) const;

    std::vector<Plots> Import2() const;

    Plots PlotResult(TFile& file, int tree_number, const boca::Phase& phase) const;

    Plots PlotResult2(const Observable& variable, Tag tag, Plots& plots) const;

    Plots PlotResult3(const Observable& variable) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const;

    Plot ReadTree2(TTree& tree, std::string const& leaf_name) const;

    void PlotHistogram(const Plot& signal, const Plot& background, Rectangle<double> const& range) const;

    void PlotProfile(const Plot& signal, const Plot& background, Rectangle<double> const& range) const;

    std::vector<std::string> PlotAcceptanceGraph(Results const& results) const;

    std::string PlotCrosssectionsGraph(Results const& results) const;

    std::string PlotMDExperimentalGraph(Results const& results) const;

    std::string PlotExperimentalVsSignificance(Results const& results) const;

    std::string PlotHistograms(Results const& results) const;

    LatexTable BestValueTable(const boca::Result& signal, const std::vector< double >& x_values) const;

    LatexRow BestValueRow(const boca::Result& signal, const std::vector< double >& x_values, boca::Significance significance, const std::__cxx11::string& model, int bin) const;

//     std::string ScalingTable(boca::Results& results) const;

//     std::string ScalingRow(const boca::Results& results, double factor) const;

    LatexTable EfficienciesTable(const boca::Results& results, int bin) const;

    LatexRow EfficienciesRow(const boca::Result& result, int, boca::Tag, int bin) const;

    LatexTable EfficienciesTableMI(const boca::Results& results, boca::Significance significance) const;

    LatexRow EfficienciesRowMI(const boca::Result& result, int bin) const;

    LatexTable CutEfficiencyTable(Results const& results) const;

    LatexRow CutEfficiencyRow(const boca::Result& result, int, boca::Tag) const;

    LatexTable TruthLevelCutTable(const boca::Results& results) const;

    LatexRow TruthLevelCutRow(const boca::Result& result, boca::Tag) const;

    std::string PlotEfficiencyGraph(Results const& results) const;

    std::string PlotMDGraph(Results const& results) const;

    std::string PlotMIExclusion(Results const& results) const;

    std::string PlotMIDiscovery(Results const& results) const;

    std::string PlotMISignificanceExclusion(Results const& results) const;

    std::string PlotMISignificanceDiscovery(Results const& results) const;

    std::string PlotMIExperimentalGraph(Results const& results) const;

    void SetDefaultXAxis(Graphs& graphs, Results const& results) const;

    void PlotVariables(Plots const& plots) const;

    virtual boca::Tagger const& Tagger() const = 0;

    virtual boca::Tagger & Tagger() = 0;

    template<typename Branch_>
    Branch_ ConstCast(Branch_ const& branch) const{
      return const_cast<Branch_&>(branch);
    }

};

}

