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

namespace latex{
class Row;
class Table;
class Graphic;
}

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

    Results ReadBdtFiles(Stage stage) const;

    std::vector<Result> ReadBdtFile(FileWriter& file_writer, const Phase& phase) const;

    Result BdtDistribution(FileWriter& file_writer, const Phase& phase, const std::string& tree_name) const;

    Result CutDistribution(FileWriter& file_writer, const Phase& phase, std::string const& tree_name) const;

    std::pair<boca::InfoBranch, int> InfoBranch(Phase const& phase, std::string const& tree_name) const;

    void DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const;

    void PlotDetails(Plot& signal, Plot& background, Stage stage) const;

    std::vector<Plots> Import(Phase const& phase) const;

    std::vector<Plots> Import2() const;

    Plots PlotResult(TFile& file, const std::string& tree_name, const Phase& phase) const;

    Plots PlotResult2(const Observable& variable, Tag tag, Plots& plots) const;

    Plots PlotResult3(const Observable& variable) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const;

    Plot ReadTree2(TTree& tree, std::string const& leaf_name) const;

    void PlotHistogram(const Plot& signal, const Plot& background, Rectangle<double> const& range) const;

    void PlotProfile(const Plot& signal, const Plot& background, Rectangle<double> const& range) const;

    latex::Graphic PlotAcceptanceGraph(Results const& results) const;

    latex::Graphic PlotCrosssectionsGraph(Results const& results) const;

    latex::Graphic PlotMDExperimentalGraph(Results const& results) const;

    latex::Graphic PlotExperimentalVsSignificance(Results const& results) const;

    latex::Graphic PlotHistograms(Results const& results) const;

    latex::Table BestValueTable(Result const& signal, const std::vector< double >& x_values) const;

    latex::Row BestValueRow(Result const& signal, const std::vector< double >& x_values, Significance significance, const std::string& model, int bin) const;

    latex::Table EfficienciesTable(Results const& results, int bin) const;

    latex::Row EfficienciesRow(Result const& result, int, Tag, int bin) const;

    latex::Table EfficienciesTableMI(Results const& results, Significance significance) const;

    latex::Row EfficienciesRowMI(Result const& result, int bin) const;

    latex::Table CutEfficiencyTable(Results const& results) const;

    latex::Row CutEfficiencyRow(Result const& result, int, Tag) const;

    latex::Table TruthLevelCutTable(Results const& results) const;

    latex::Row TruthLevelCutRow(Result const& result, Tag) const;

    latex::Graphic PlotEfficiencyGraph(Results const& results) const;

    latex::Graphic PlotMDGraph(Results const& results) const;

    latex::Graphic PlotMIExclusion(Results const& results) const;

    latex::Graphic PlotMIDiscovery(Results const& results) const;

    latex::Graphic PlotMISignificanceExclusion(Results const& results) const;

    latex::Graphic PlotMISignificanceDiscovery(Results const& results) const;

    latex::Graphic PlotMIExperimentalGraph(Results const& results) const;

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

