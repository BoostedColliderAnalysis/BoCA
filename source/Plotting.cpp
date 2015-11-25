/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Plotting.hh"

#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <numeric>

#include <boost/range/algorithm/sort.hpp>

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TClonesArray.h"
#include "TDirectoryFile.h"
#include "TTree.h"
#include "TMultiGraph.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TColor.h"
#include "TExec.h"
#include "THStack.h"
#include "TLegendEntry.h"

#include "exroot/ExRootAnalysis.hh"
#include "Vector.hh"
#include "Types.hh"
#include "Branches.hh"
#include "LatexFile.hh"
#include "Graph.hh"
#include "Result.hh"
#include "Canvas.hh"
#include "Math.hh"
#define INFORMATION
#include "Debug.hh"


#include "../HeavyHiggs/include/Branch.hh"

namespace boca
{

Plotting::Plotting(boca::Tagger& tagger) : tagger_(tagger)
{
    Info0;
}

void Plotting::TaggingEfficiency() const
{
    Info0;
    Results results = ReadBdtFiles();
    PlotHistograms(results);
    PlotEfficiencyGraph(results);
    PlotAcceptanceGraph(results);
}

void Plotting::OptimalCuts() const
{
    Info0;
    Results results = ReadBdtFiles();
    results.Significances();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.Mass(double(results.signals.front().info_branch_.Mass) * GeV);
    latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.IncludeGraphic(PlotCrosssectionsGraph(results), "Crosssection in fb");
    latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of the crosssection for the model-independent result");
    latex_file.IncludeGraphic(PlotModelDependentGraph(results), "Maximization of the significance for the model-dependent result");
    latex_file.IncludeGraphic(PlotCrosssectionGraph(results), "Maximization of $S/\\sqrt B$");
    latex_file.Table("rlllll", EfficienciesTable(results, results.best_model_independent_bin), "Model independent efficiencies");
    latex_file.Table("rlllll", EfficienciesTable(results, results.best_model_dependent_bin), "Model dependent efficiencies");
    latex_file.Table("rlll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
}

Results Plotting::ReadBdtFiles() const
{
    Info0;
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    Results results;
    results.signals = ReadBdtFile(file, Tag::signal);
    results.backgrounds = ReadBdtFile(file, Tag::background);
    results.ExtremeXValues();
    return results;
}

std::vector<Result> Plotting::ReadBdtFile(TFile& export_file, Tag tag) const
{
    Info0;
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    Debug(file_name);
    if (!Exists(file_name)) Error("non existent", file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<Result> results;
    for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(BdtDistribution(file, tree_name, export_file));
    return results;
}

Result Plotting::BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    Info0;
    std::string branch_name = Tagger().BranchName(Stage::reader);
    Debug(branch_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Result result(InfoBranch(file, tree_name));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& result_branch = *tree_writer.NewBranch(branch_name.c_str(), BdtBranch::Class());
    long entries = 0;
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
//             float bdt_value = Tagger().ReadBdt(clones_array, entry);
            float bdt_value =  static_cast<BdtBranch&>(*clones_array.At(entry)).Bdt;
            Check(bdt_value >= -1 && bdt_value <= 1, bdt_value);
            static_cast<BdtBranch&>(*result_branch.NewEntry()).Bdt = bdt_value;
            result.AddBdt(bdt_value);
            ++entries;
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    result.Calculate();
    return result;
}

InfoBranch Plotting::InfoBranch(TFile& file, std::string const& tree_name) const
{
    INFO(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Error(tree_name, Tagger().WeightBranchName());
    TClonesArray* clones_array = tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    return static_cast<boca::InfoBranch&>(*clones_array->Last());
}

std::string Plotting::PlotHistograms(boca::Results& results) const
{
    Info0;
    Canvas canvas;
    THStack stack("", Tagger().NiceName().c_str());
    std::vector<TH1F> histograms;
    Strings nice_names;
    for (auto const & result : results.signals) {
        histograms.emplace_back(Histogram(result, results.max, results.min, &result - &results.signals.front()));
        nice_names.emplace_back(result.info_branch_.Name);
    }
    for (auto const & result : results.backgrounds) {
        histograms.emplace_back(Histogram(result, results.max, results.min, &result - &results.backgrounds.front() + results.signals.size()));
        nice_names.emplace_back(result.info_branch_.Name);
    }
    TLegend legend = Legend(Orientation::top, nice_names);
    for (auto & histogram : histograms) AddHistogram(stack, histogram, legend);
    stack.Draw("nostack");
    canvas.SetAxis(*stack.GetXaxis(), "BDT");
    canvas.SetAxis(*stack.GetYaxis(), "N");
    TLine line = Line(results.best_model_dependent_bin, stack.GetYaxis()->GetXmin(), /*stack.GetYaxis()->GetXmax() */results.max.y * 1.05, results.signals.size() + results.backgrounds.size() + 1);
    TLine line2 = Line(results.best_model_independent_bin, stack.GetYaxis()->GetXmin(), /*stack.GetYaxis()->GetXmax()*/results.max.y * 1.05, results.signals.size() + results.backgrounds.size() + 2);
    legend.Draw();
    return canvas.SaveAs(Tagger().ExportFolderName() + "-Bdt");
}

std::string Plotting::PlotEfficiencyGraph(Results const& results) const
{
    Info0;
    Canvas canvas;
    canvas.SetLog();
    TMultiGraph multi_graph("", Tagger().NiceName().c_str());
    Strings nice_names;
    std::vector<TGraph> graphs;
    for (auto const & result : results.signals) {
        nice_names.emplace_back(result.info_branch_.Name);
        graphs.emplace_back(TGraph(result.steps, &results.x_values.front(), &result.efficiency.front()));
    }
    for (auto const & result : results.backgrounds) {
        nice_names.emplace_back(result.info_branch_.Name);
        graphs.emplace_back(TGraph(result.steps, &results.x_values.front(), &result.efficiency.front()));
    }
    TLegend legend = Legend(Orientation::bottom | Orientation::left, nice_names);
    for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names, &graph - &graphs.front());
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    canvas.SetAxis(*multi_graph.GetXaxis(), "BDT");
    canvas.SetAxis(*multi_graph.GetYaxis(), "Efficiency");
    TLine line = Line(results.best_model_dependent_bin , multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
    TLine line2 = Line(results.best_model_independent_bin, multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
    legend.Draw();
    return canvas.SaveAs(Tagger().ExportFolderName() + "-Efficiency");
}

void Plotting::PlotAcceptanceGraph(Results const& results) const
{
    Info0;
    for (auto const & signal : results.signals) {
        Canvas canvas;
//         TMultiGraph multi_graph("", Tagger().NiceName().c_str());
        TMultiGraph multi_graph("", "");
        std::vector<TGraph> graphs;
        Strings nice_names;
        Point min(0.2, LargeNumber());
        Point max(0.9, 0);
        for (auto const & background : results.backgrounds) {
            float min_y = background.pure_efficiency.at(Closest(signal.pure_efficiency, min.x));
            if (min_y < min.y && min_y > 0) min.y = min_y;
            float max_y = background.pure_efficiency.at(Closest(signal.pure_efficiency, max.x));
            if (max_y > max.y) max.y = max_y;
            graphs.emplace_back(TGraph(background.steps, &signal.pure_efficiency.front(), &background.pure_efficiency.front()));
            nice_names.emplace_back(background.info_branch_.Name);
        }
        if (min.y == LargeNumber()) min.y = 0;
        canvas.SetLog(min.y, max.y);
        TLegend legend = Legend(Orientation::right | Orientation::bottom, nice_names, signal.info_branch_.Name);
        for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names, &graph - &graphs.front());
        SetMultiGraph(multi_graph, min, max);
        legend.Draw();
        canvas.SaveAs(Tagger().ExportFolderName() + "-" + signal.info_branch_.Name + "-Acceptance");
    }
}

std::string Plotting::PlotCrosssectionsGraph(Results const& results) const
{
    Info0;
    Canvas canvas;
    canvas.SetLog();
    TMultiGraph multi_graph("", Tagger().NiceName().c_str());
    Strings nice_names;
    std::vector<TGraph> graphs;
    float min = LargeNumber();
    float max = 0;
    for (auto const & result : results.signals) {
        nice_names.emplace_back(result.info_branch_.Name);
        graphs.emplace_back(TGraph(result.steps, &results.x_values.front(), &result.XSec().front()));
        float xsec = *boost::range::min_element(result.crosssection) / fb;
        if (min > xsec) min = xsec;
        xsec = *boost::range::max_element(result.crosssection) / fb;
        if (max > xsec) max = xsec;
    }
    for (auto const & result : results.backgrounds) {
        nice_names.emplace_back(result.info_branch_.Name);
        graphs.emplace_back(TGraph(result.steps, &results.x_values.front(), &result.XSec().front()));
        float xsec = *boost::range::min_element(result.crosssection) / fb;
        if (min > xsec) min = xsec;
        xsec = *boost::range::max_element(result.crosssection) / fb;
        if (max > xsec) max = xsec;
    }
    TLegend legend = Legend(Orientation::bottom | Orientation::left, nice_names);
    for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names, &graph - &graphs.front());
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    multi_graph.GetYaxis()->SetLimits(min, max);
    canvas.SetAxis(*multi_graph.GetXaxis(), "BDT");
    canvas.SetAxis(*multi_graph.GetYaxis(), "Crosssection [fb]");
    TLine line = Line(results.best_model_dependent_bin , multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
    TLine line2 = Line(results.best_model_independent_bin, multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
    legend.Draw();
    return canvas.SaveAs(Tagger().ExportFolderName() + "-Crosssection");
}

std::string Plotting::PlotModelDependentGraph(Results& results) const
{
    Info0;
    Canvas canvas;
    TGraph graph = Graph(results, results.significances, "Significance");
    TLine line  = Line(results.best_model_dependent_bin, graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
    return canvas.SaveAs(Tagger().ExportFolderName() + "-Significance");
}

std::string Plotting::PlotCrosssectionGraph(Results& results) const
{
    Info0;
    Canvas canvas;
    TGraph graph = Graph(results, results.acceptances, "S/#sqrt{B}");
    TLine line  = Line(results.best_acceptance_bin, graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 3);
    return canvas.SaveAs(Tagger().ExportFolderName() + "-SB");
}

std::string Plotting::PlotModelIndependentGraph(Results& results) const
{
    Info0;
    Canvas canvas;
    TGraph graph = Graph(results, results.Crosssections(), "Crosssection");
    canvas.SetLog(min(results.crosssections, true) / fb, max(results.crosssections) / fb);
    TLine line  = Line(results.best_model_independent_bin, graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
    return canvas.SaveAs(Tagger().ExportFolderName() + "-Exclusion");
}

std::string Plotting::BestValueTable(Results const& results) const
{
    Info0;
    std::stringstream table;
    table << "    Model\n  & Cut\n  & $p$-value\n  & Crosssection [fb]";
    table << "\n \\\\ \\midrule\n   ";
    table << BestValueRow(results, results.best_model_dependent_bin, "Dependet");
    table << BestValueRow(results, results.best_model_independent_bin, "Independet");
    table << BestValueRow(results, results.best_acceptance_bin, "$S/\\sqrt B$");
    return table.str();
}

std::string Plotting::BestValueRow(Results const& results, int bin, std::string const& name) const
{
    Info0;
    std::stringstream row;
    row << " " << name;
    row << "\n  & " << RoundToDigits(results.XValue(bin));
    row << "\n  & " << RoundToDigits(results.significances.at(bin));
    row << "\n  & " << RoundToDigits(results.crosssections.at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

std::string Plotting::EfficienciesTable(Results const& results, int bin) const
{
    Info0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << float(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.signals) table << EfficienciesRow(result, &result - &results.signals.front(), Tag::signal, bin);
    for (auto const & result : results.backgrounds) table << EfficienciesRow(result, &result - &results.backgrounds.front(), Tag::background, bin);
    return table.str();
}

std::string Plotting::EfficienciesRow(Result const& result, int index, Tag tag, int bin) const
{
    Info0;
    std::stringstream row;
    row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
    row << "\n  & " << result.info_branch_.EventNumber;
    row << "\n  & " << result.event_sums.at(bin);
    row << "\n  & " << RoundToDigits(result.efficiency.at(bin));
    row << "\n  & " << RoundToDigits(result.info_branch_.Crosssection);
    row << "\n  & " << RoundToDigits(to_crosssection(result.info_branch_.Crosssection) * DetectorGeometry::Luminosity() * result.efficiency.at(bin));
    row << "\n \\\\";
    return row.str();
}

void Plotting::RunPlots() const
{
    Info0;
    for (auto const & stage : std::vector<Stage> {Stage::trainer, Stage::reader}) {
        Debug(Tagger().FileName(stage, Tag::signal), Tagger().TreeNames(Tag::signal).size());
        std::vector<Plots> signals = Import(stage, Tag::signal);
        Debug(Tagger().FileName(stage, Tag::background), Tagger().TreeNames(Tag::background).size());
        std::vector<Plots> backgrounds = Import(stage, Tag::background);
        Plots background = backgrounds.front();
        if (backgrounds.size() > 1) {
            background = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), background, [](Plots & sum, Plots const & elem) {
                for (auto & plot : sum.plots) plot.points = Join(plot.points, elem.plots.at(&plot - &sum.plots.front()).points);
                return sum;
            });
            background.name = "background";
        }
        for (auto & signal : signals) DoPlot(signal, background, stage);
    }
}

void Plotting::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    Info0;
    Names nice_names = unordered_pairs(tagger_.Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return std::make_pair(variable_1.nice_name(), variable_2.nice_name());
    });
    Names names = unordered_pairs(tagger_.Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return std::make_pair(variable_1.name(), variable_2.name());
    });
    signals.SetNames(names, nice_names);
    backgrounds.SetNames(names, nice_names);
    for (auto & signal : signals.plots) PlotDetails(signal, backgrounds.plots.at(&signal - &signals.plots.front()), stage);
}

void Plotting::PlotDetails(Plot& signal, Plot& background, Stage stage) const
{
    INFO(signal.points.size(), background.points.size());
    Plot signal_x = CoreVector(signal, [](Point const & a, Point const & b) {
        return a.x < b.x;
    });
    Plot signal_y = CoreVector(signal, [](Point const & a, Point const & b) {
        return a.y < b.y;
    });
    Plot background_x = CoreVector(background, [](Point const & a, Point const & b) {
        return a.x < b.x;
    });
    Plot background_y = CoreVector(background, [](Point const & a, Point const & b) {
        return a.y < b.y;
    });
    Point min;
    min.x = std::min(signal_x.points.front().x, background_x.points.front().x);
    min.y = std::min(signal_y.points.front().y, background_y.points.front().y);
    Point max;
    max.x = std::max(signal_x.points.back().x, background_x.points.back().x);
    max.y = std::max(signal_y.points.back().y, background_y.points.back().y);
    switch (stage) {
    case Stage::trainer :
        PlotHistogram(signal, background, min, max);
        break;
    case Stage::reader :
        PlotProfile(signal, background, min, max);
        break;
    }
}

void Plotting::PlotHistogram(Plot const& signal, Plot const& background, Point const& min, Point const& max) const
{
    INFO(min.x, min.y, max.x, max.y);
    Canvas canvas;
    canvas.canvas().SetBottomMargin(0.15);
    int bin_number = 20;
    TExec exec_1;
    TH2F background_histogram("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetHistogram(background_histogram, background, kBlue, exec_1);
    TExec exec_2;
    TH2F signal_histogram("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetHistogram(signal_histogram, signal, kRed, exec_2);
    TLegend legend = Legend(Point(0.35, 0), 0.3, 0.1);
    legend.SetNColumns(2);
    legend.SetColumnSeparation(0.2);
    legend.AddEntry(&signal_histogram, "Signal", "l");
    legend.AddEntry(&background_histogram, "Background", "l");
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    canvas.SaveAs(Tagger().ExportFolderName() + "/" + "Hist-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y);
}

void Plotting::PlotProfile(Plot const& signal, Plot const& background, Point const& min, Point const& max) const
{
    Info0;
    Canvas canvas;
    canvas.canvas().SetRightMargin(0.15);
    int bin_number = 30;
    TProfile2D profile("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetProfile(profile, signal, background);
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    canvas.SaveAs(Tagger().ExportFolderName() + "/" + "Prof-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y);
}

std::vector<Plots> Plotting::Import(Stage stage, Tag tag) const
{
    INFO(Tagger().FileName(stage, tag), Tagger().TreeNames(tag).size());
    TFile file(Tagger().FileName(stage, tag).c_str(), "Read");
    std::vector<Plots> results;
    for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(PlotResult(file, tree_name, stage));
    return results;
}

Plots Plotting::PlotResult(TFile& file, std::string const& tree_name, Stage stage) const
{
    INFO(tree_name);
    Plots plots;
    plots.info_branch = InfoBranch(file, tree_name);
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(1);
    plots.plots = unordered_pairs(tagger_.Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return ReadTree(tree, variable_1.name(), variable_2.name(), stage);
    });
    plots.name = tree_name;
    Debug(plots.plots.size(), tagger_.Branch().Variables().size());
    return plots;
}

Plot Plotting::ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const
{
    Info0;
    tree.SetBranchStatus("*", false);
    std::string branch_name = Tagger().BranchName(stage);
    Debug(branch_name);

    int branch_value = 0;
    SetBranch(tree, branch_value, branch_name);

    int branch_size = 0;
    SetBranch(tree, branch_size, branch_name + "_size");

    //FIXME remove this magic number
    size_t max_value = 200;
    std::vector<float> leaf_values_1(max_value);
    SetBranch(tree, leaf_values_1, branch_name + "." + leaf_1_name);

    std::vector<float> leaf_values_2(max_value);
    SetBranch(tree, leaf_values_2, branch_name + "." + leaf_2_name);

    std::vector<float> bdt_values(max_value);
    SetBranch(tree, bdt_values, branch_name + ".Bdt");

    Plot plot;
    for (auto const & entry : Range(tree.GetEntries())) {
        Detail(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        Detail(branch_size, leaf_values_1.size(), leaf_values_2.size());
        for (auto const & element : Range(branch_size)) plot.Add(Point(leaf_values_1.at(element), leaf_values_2.at(element), bdt_values.at(element)));
    }
    return plot;
}


Plot Plotting::CoreVector(Plot& plot, std::function<bool (Point const&, Point const&)> const& function) const
{
    Info0;
    // TODO sorting the whole vector when you just want to get rid of the extrem values might not be the fastest solution
    boost::range::sort(plot.points, [&](Point const & a, Point const & b) {
        return function(a, b);
    });
    int cut_off = plot.points.size() / 25;
    plot.points.erase(plot.points.begin(), plot.points.begin() + cut_off);
    plot.points.erase(plot.points.end() - cut_off, plot.points.end());
    return plot;
}

Tagger const& Plotting::Tagger() const
{
    return tagger_;
}
void Plotting::SetBranch(TTree& tree, std::vector< float >& values, const std::__cxx11::string& name) const
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &values.front());
}
void Plotting::SetBranch(TTree& tree, int& value, const std::__cxx11::string& name) const
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &value);
}

























CutResults Plotting::ReadCutFiles() const
{
    Info0;
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    CutResults results;
    results.signals = ReadCutFile(file, Tag::signal);
    results.backgrounds = ReadCutFile(file, Tag::background);
    results.ExtremeXValues();
    return results;
}

std::vector<CutResult> Plotting::ReadCutFile(TFile& export_file, Tag tag) const
{
    Info0;
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    Debug(file_name);
    if (!Exists(file_name)) Error("non existent", file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<CutResult> results;
    INFO(Tagger().TreeNames(tag).size());
    for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(CutDistribution(file, tree_name, export_file));
    return results;
}

CutResult Plotting::CutDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    INFO(tree_name);
    std::string branch_name = Tagger().BranchName(Stage::reader);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    CutResult result(InfoBranch(file, tree_name));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& cut_branch = *tree_writer.NewBranch(branch_name.c_str(), CutBranch::Class());
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
            std::vector<bool> passed = dynamic_cast<CutBranch&>(*clones_array.At(entry)).passed_;
            static_cast<CutBranch&>(*cut_branch.NewEntry()).passed_ = passed;
            result.AddPassed(passed);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    result.Calculate();
    return result;
}



void Plotting::Cuts() const
{
    Info0;
    CutResults results = ReadCutFiles();
    results.Significances();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.Mass(double(results.signals.front().info_branch_.Mass) * GeV);
    latex_file.IncludeGraphic(PlotCutEfficiencyGraph(results), "Efficiencies");
    latex_file.Table("rlll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
    latex_file.IncludeGraphic(PlotCutResult(results), "Significances");
    latex_file.Table("rlllll", EfficienciesTable(results, results.best_model_dependent_bin), "Model dependent efficiencies");
    latex_file.Table("rlllll", EfficienciesTable(results, results.best_model_independent_bin), "Model independent efficiencies");
    latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of the crosssection for the model-independent result");
}


std::string Plotting::PlotCutResult(boca::CutResults& results) const
{
    Info0;
    Canvas canvas;
    TGraph graph = CutGraph(results, results.significances, "Significance");
    TLine line  = CutLine(results.XValue(results.best_model_dependent_bin), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
    return canvas.SaveAs(Tagger().ExportFolderName() + "-Significance");
}


std::string Plotting::PlotCutEfficiencyGraph(CutResults const& results) const
{
  Info0;
  Canvas canvas;
  canvas.SetLog();
  TMultiGraph multi_graph("", "Efficiencies");
  Strings nice_names;
  std::vector<TGraph> graphs;
  for (auto const & result : results.signals) {
    nice_names.emplace_back(result.info_branch_.Name);
    graphs.emplace_back(TGraph(result.steps, &results.x_values.front(), &result.efficiency.front()));
  }
  for (auto const & result : results.backgrounds) {
    nice_names.emplace_back(result.info_branch_.Name);
    graphs.emplace_back(TGraph(result.steps, &results.x_values.front(), &result.efficiency.front()));
  }
  TLegend legend = Legend(Orientation::bottom | Orientation::left, nice_names);
  for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names, &graph - &graphs.front());
  multi_graph.Draw("al");
  multi_graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
  canvas.SetAxis(*multi_graph.GetXaxis(), "Calculated");
  canvas.SetAxis(*multi_graph.GetYaxis(), "Measured");
  TLine line = CutLine(results.XValue(results.best_model_dependent_bin) , multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
  TLine line2 = CutLine(results.XValue(results.best_model_independent_bin), multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
  legend.Draw();
  return canvas.SaveAs(Tagger().ExportFolderName() + "-Efficiency");
}

std::string Plotting::BestValueTable(CutResults const& results) const
{
  Info0;
  std::stringstream table;
  table << "    Model\n  & Cut\n  & $p$-value\n  & Crosssection [fb]";
  table << "\n \\\\ \\midrule\n   ";
  table << BestValueRow(results, results.best_model_dependent_bin, "Dependet");
  table << BestValueRow(results, results.best_model_independent_bin, "Independet");
  table << BestValueRow(results, results.best_acceptance_bin, "$S/\\sqrt B$");
  return table.str();
}

std::string Plotting::BestValueRow(CutResults const& results, int bin, std::string const& name) const
{
  Info0;
  std::stringstream row;
  row << " " << name;
  row << "\n  & " << RoundToDigits(results.XValue(bin));
  row << "\n  & " << RoundToDigits(results.significances.at(bin));
  row << "\n  & " << RoundToDigits(results.crosssections.at(bin) / fb);
  row << "\n \\\\";
  return row.str();
}

std::string Plotting::EfficienciesTable(CutResults const& results, int bin) const
{
  Info0;
  std::stringstream table;
  table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << float(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
  table << "\n \\\\ \\midrule\n   ";
  for (auto const & result : results.signals) table << EfficienciesRow(result, &result - &results.signals.front(), Tag::signal, bin);
  for (auto const & result : results.backgrounds) table << EfficienciesRow(result, &result - &results.backgrounds.front(), Tag::background, bin);
  return table.str();
}

std::string Plotting::EfficienciesRow(CutResult const& result, int index, Tag tag, int bin) const
{
  Info0;
  std::stringstream row;
  row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
  row << "\n  & " << result.info_branch_.EventNumber;
  row << "\n  & " << result.event_sums.at(bin);
  row << "\n  & " << RoundToDigits(result.efficiency.at(bin));
  row << "\n  & " << RoundToDigits(result.info_branch_.Crosssection);
  row << "\n  & " << RoundToDigits(to_crosssection(result.info_branch_.Crosssection) * DetectorGeometry::Luminosity() * result.efficiency.at(bin));
  row << "\n \\\\";
  return row.str();
}

std::string Plotting::PlotModelIndependentGraph(CutResults& results) const
{
  Info0;
  Canvas canvas;
  TGraph graph = CutGraph(results, results.Crosssections(), "Crosssection");
  canvas.SetLog(min(results.crosssections, true) / fb, max(results.crosssections) / fb);
  TLine line  = CutLine(results.XValue(results.best_model_independent_bin), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
  return canvas.SaveAs(Tagger().ExportFolderName() + "-Exclusion");
}

}

