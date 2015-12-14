/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <sys/stat.h>
#include <fstream>
#include <algorithm>
#include <numeric>

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TClonesArray.h"
#include "TTree.h"

#include "exroot/ExRootAnalysis.hh"
#include "physics/Math.hh"
#include "plotting/Plotting.hh"
#include "plotting/LatexFile.hh"
#include "plotting/Graphs.hh"
#include "plotting/Result.hh"
#include "plotting/Histograms.hh"
#include "plotting/Histogram2Dim.hh"
#include "plotting/Profile.hh"
#include "Vector.hh"
#include "Types.hh"
#include "Branches.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Plotting::Plotting(boca::Tagger& tagger) :
    tagger_(tagger)
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
    results.CalculateSignificances();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.Mass(double(results.Signals().front().InfoBranch().Mass) * GeV);
    latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.IncludeGraphic(PlotCrosssectionsGraph(results), "Crosssection in fb");
    latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of the crosssection for the model-independent result");
    latex_file.IncludeGraphic(PlotModelDependentGraph(results), "Maximization of the significance for the model-dependent result");
    latex_file.IncludeGraphic(PlotCrosssectionGraph(results), "Maximization of $S/\\sqrt B$");
    latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelInDependentBin()), "Model independent efficiencies");
    latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelDependentBin()), "Model dependent efficiencies");
    latex_file.Table("rlll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
}

Results Plotting::ReadBdtFiles() const
{
    Info0;
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    return Results(ReadBdtFile(file, Tag::signal), ReadBdtFile(file, Tag::background));
}

std::vector<Result> Plotting::ReadBdtFile(TFile& export_file, Tag tag) const
{
    Info0;
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    Debug(file_name);
    if (!Exists(file_name)) Error("non existent", file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<Result> results;
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT : for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(BdtDistribution(file, tree_name, export_file));
        break;
    case TMVA::Types::EMVA::kCuts: for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(CutDistribution(file, tree_name, export_file));
        break;
    }
    return results;
}

Result Plotting::BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    Info0;
    std::string branch_name = Tagger().BranchName(Stage::reader);
    Debug(branch_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& result_branch = *tree_writer.NewBranch(branch_name.c_str(), BdtBranch::Class());
    std::vector<float> bdts;
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
            float bdt_value =  static_cast<BdtBranch&>(*clones_array.At(entry)).Bdt;
            static_cast<BdtBranch&>(*result_branch.NewEntry()).Bdt = bdt_value;
            bdts.emplace_back(bdt_value);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    return Result(InfoBranch(file, tree_name), bdts, Tagger().Mva());
}

Result Plotting::CutDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    INFO(tree_name);
    std::string branch_name = Tagger().BranchName(Stage::reader);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& cut_branch = *tree_writer.NewBranch(branch_name.c_str(), CutBranch::Class());
    std::vector<std::vector<bool>> passeds;
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
            std::vector<bool> passed = dynamic_cast<CutBranch&>(*clones_array.At(entry)).passed_;
            static_cast<CutBranch&>(*cut_branch.NewEntry()).passed_ = passed;
            passeds.emplace_back(passed);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    return Result(InfoBranch(file, tree_name), passeds, Tagger().Mva());
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
    Histograms histograms(Tagger().ExportFolderName(), "Bdt");
    for (auto const & result : results.Signals()) histograms.AddHistogram(result.Bdts(), result.InfoBranch().Name, results.Bounds());
    for (auto const & result : results.Backgrounds()) histograms.AddHistogram(result.Bdts(), result.InfoBranch().Name, results.Bounds());
    histograms.SetLegend(Orientation::top);
    histograms.SetXAxis("BDT");
    histograms.SetYAxis("N");
    histograms.AddLine(results.BestModelDependentValue());
    histograms.AddLine(results.BestModelInDependentValue());
//     TLine line = Line(results.BestModelDependentBin(), histograms.LimitsY(), results.max.Y() * 1.05, results.Signals().size() + results.Backgrounds().size() + 1);
//     TLine line2 = Line(results.BestModelInDependentBin(), histograms.LimitsY(), results.max.Y() * 1.05, results.Signals().size() + results.Backgrounds().size() + 2);
    return histograms.FileName();
}

std::string Plotting::PlotEfficiencyGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Efficiency");
//     graphs.SetLog();
    for (auto const & result : results.Signals()) graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().Name);
    for (auto const & result : results.Backgrounds()) graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().Name);
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    graphs.SetXAxis("BDT", results.Bounds().Horizontal());
    graphs.SetYAxis("Efficiency");
//     graphs.AddLine(results.BestModelDependentValue());
//     graphs.AddLine(results.BestModelInDependentValue());

//     TLine line = Line(results.BestModelDependentBin() , graphs.LimitsY(), results.Signals().size() + results.Backgrounds().size() + 1);
//     TLine line2 = Line(results.BestModelInDependentBin(), graphs.LimitsY(), results.Signals().size() + results.Backgrounds().size() + 2);
    return graphs.FileName();
}

// void Plotting::PlotAcceptanceGraph(Results const& results) const
// {
//     Info0;
//     for (auto const & signal : results.Signals()) {
//         Canvas canvas;
// //         TMultiGraph graphs("", Tagger().LatexName().c_str());
//         TMultiGraph graphs("", "");
//         std::vector<TGraph> graphs;
//         std::vector<std::string> nice_names;
//         Vector2<float> min(0.2, std::numeric_limits<float>::max());
//         Vector2<float> max(0.9, 0);
//         for (auto const & background : results.Backgrounds()) {
//             float min_y = background.pure_efficiency.at(Closest(signal.pure_efficiency, min.X()));
//             if (min_y < min.Y() && min_y > 0) min.Y() = min_y;
//             float max_y = background.pure_efficiency.at(Closest(signal.pure_efficiency, max.X()));
//             if (max_y > max.Y()) max.Y() = max_y;
//             graphs.emplace_back(TGraph(background.steps, &signal.pure_efficiency.front(), &background.pure_efficiency.front()));
//             nice_names.emplace_back(background.InfoBranch().Name);
//         }
//         if (min.Y() == std::numeric_limits<float>::max()) min.Y() = 0;
//         canvas.SetLog(min.Y(), max.Y());
//         Legend legend(Orientation::right | Orientation::bottom, nice_names, signal.InfoBranch().Name);
//         for (auto & graph : graphs) AddGraph(graph, graphs, legend, nice_names, &graph - &graphs.front());
//         SetMultiGraph(graphs, min, max);
//         legend.Draw();
//         canvas.SaveAs(Tagger().ExportFolderName() /*+ "-" + signal.InfoBranch().Name*/ + "-Acceptance");
//     }
// }

void Plotting::PlotAcceptanceGraph(Results const& results) const
{
    Info0;
    for (auto const & signal : results.Signals()) {
        Graphs graphs(Tagger().ExportFolderName(), "Acceptance");
        Bounds<float> limit_x(0.2, 0.9);
        Bounds<float> limit_y(std::numeric_limits<float>::max(), 0);
        for (auto const & background : results.Backgrounds()) {
            float min_y = background.Efficiencies().at(Closest(signal.Efficiencies(), limit_x.Min()));
            if (min_y < limit_y.Min() && min_y > 0) limit_y.SetMin(min_y);
            float max_y = background.Efficiencies().at(Closest(signal.Efficiencies(), limit_x.Max()));
            if (max_y > limit_y.Max()) limit_y.SetMax(max_y);
            graphs.AddGraph(signal.Efficiencies(), background.Efficiencies(), background.InfoBranch().Name);
        }
        if (limit_y.Min() == std::numeric_limits<float>::max()) limit_y.SetMin(0);
        graphs.SetLegend(Orientation::right | Orientation::bottom, signal.InfoBranch().Name);
        graphs.SetXAxis("Signal acceptance", limit_x);
        graphs.SetYAxis("Background acceptance", limit_y);
    }
}

std::string Plotting::PlotCrosssectionsGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Crosssection");
//     graphs.SetLog();
//     std::vector<std::string> nice_names;
//     std::vector<TGraph> graphs;
    Bounds<float> bounds_y(std::numeric_limits<float>::max(), 0);
//     float min = std::numeric_limits<float>::max();
//     float max = 0;
    for (auto const & result : results.Signals()) {
//         nice_names.emplace_back(result.InfoBranch().Name);
//         graphs.emplace_back(TGraph(result.steps, &results.XValues().front(), &result.XSec().front()));
        graphs.AddGraph(results.XValues(), FloatVector(result.Crosssections()), result.InfoBranch().Name);
        float xsec = *boost::range::min_element(result.Crosssections()) / fb;
//         if (min > xsec) min = xsec;
        if (bounds_y.Min() > xsec) bounds_y.SetMin(xsec);
        xsec = *boost::range::max_element(result.Crosssections()) / fb;
//         if (max > xsec) max = xsec;
        if (bounds_y.Max() > xsec) bounds_y.SetMax(xsec);
    }
    for (auto const & result : results.Backgrounds()) {
        graphs.AddGraph(results.XValues(), FloatVector(result.Crosssections()), result.InfoBranch().Name);
//         nice_names.emplace_back(result.InfoBranch().Name);
//         graphs.emplace_back(TGraph(result.steps, &results.XValues().front(), &result.XSec().front()));
        float xsec = *boost::range::min_element(result.Crosssections()) / fb;
//         if (min > xsec) min = xsec;
        if (bounds_y.Min() > xsec) bounds_y.SetMin(xsec);
        xsec = *boost::range::max_element(result.Crosssections()) / fb;
//         if (max > xsec) max = xsec;
        if (bounds_y.Max() > xsec) bounds_y.SetMax(xsec);
    }
//     Legend legend(Orientation::bottom | Orientation::left, nice_names);
    graphs.SetLegend(Orientation::bottom | Orientation::left);
//     for (auto & graph : graphs) AddGraph(graph, graphs, legend, nice_names, &graph - &graphs.front());
//     graphs.Draw("al");
    graphs.SetXAxis("BDT", results.Bounds().Horizontal());
    graphs.SetYAxis("Crosssection [fb]", bounds_y);
//     graphs.GetXaxis()->SetLimits(results.min.X(), results.max.X());
//     graphs.GetYaxis()->SetLimits(min, max);
//     SetAxis(*graphs.GetXaxis(), "BDT");
//     SetAxis(*graphs.GetYaxis(), "Crosssection [fb]");
//     TLine line = Line(results.BestModelDependentBin() , graphs.GetYaxis()->GetXmin(), graphs.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 1);
//     TLine line = Line(results.BestModelDependentBin() , graphs.LimitsY(), results.Signals().size() + results.Backgrounds().size() + 1);
//     TLine line2 = Line(results.BestModelInDependentBin(), graphs.LimitsY(), results.Signals().size() + results.Backgrounds().size() + 2);
    graphs.AddLine(results.BestModelDependentValue());
    graphs.AddLine(results.BestModelInDependentValue());
//     legend.Draw();
//     return canvas.SaveAs(Tagger().ExportFolderName() + "-Crosssection");
    return graphs.FileName();
}

std::string Plotting::PlotModelDependentGraph(Results& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Significance");
    graphs.AddGraph(results.XValues(), results.Significances());
    graphs.SetXAxis("BDT", results.Bounds().Horizontal());
    graphs.SetYAxis("Significance");
    graphs.AddLine(results.BestModelDependentValue());
    return graphs.FileName();


//     Canvas canvas(Tagger().ExportFolderName(), "Significance");
//     TGraph graph = Graph(results, results.Significances(), "Significance");
//     TLine line  = Line(results.BestModelDependentBin(), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 1);
//     return canvas.SaveAs(Tagger().ExportFolderName() + "-Significance");
}

std::string Plotting::PlotCrosssectionGraph(Results& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "SB");
    graphs.AddGraph(results.XValues(), results.Acceptances());
    graphs.SetXAxis("BDT", results.Bounds().Horizontal());
    graphs.SetYAxis("S/#sqrt{B}");
    graphs.AddLine(results.BestAcceptanceValue());
    return graphs.FileName();

//     Canvas canvas(Tagger().ExportFolderName(), "SB");
//     TGraph graph = Graph(results, results.acceptances, "S/#sqrt{B}");
//     TLine line  = Line(results.BestAcceptanceBin(), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 3);
//     return canvas.SaveAs(Tagger().ExportFolderName() + "-SB");
}

std::string Plotting::PlotModelIndependentGraph(Results& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Exclusion");
    graphs.AddGraph(results.XValues(), FloatVector(results.ModelIndependentCrosssection()));
    graphs.SetLog(Bounds<Crosssection>(*boost::range::min_element(boost::remove_erase(results.ModelIndependentCrosssection(), 0_fb)), *boost::range::max_element(results.ModelIndependentCrosssection())));
    graphs.SetXAxis("BDT", results.Bounds().Horizontal());
    graphs.SetYAxis("Crosssection");
    graphs.AddLine(results.BestAcceptanceValue());
    return graphs.FileName();


//     Canvas canvas(Tagger().ExportFolderName(), "Exclusion");
//     TGraph graph = Graph(results, results.ModelIndependentCrosssection(), "Crosssection");
//     canvas.SetLog(min(results.ModelIndependentCrosssection(), true) / fb, max(results.ModelIndependentCrosssection()) / fb);
//     TLine line  = Line(results.BestModelInDependentBin(), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 2);
//     return canvas.SaveAs(Tagger().ExportFolderName() + "-Exclusion");
}

std::string Plotting::BestValueTable(Results const& results) const
{
    Info0;
    std::stringstream table;
    table << "    Model\n  & Cut\n  & $p$-value\n  & Crosssection [fb]";
    table << "\n \\\\ \\midrule\n   ";
    table << BestValueRow(results, results.BestModelDependentBin(), "Dependet");
    table << BestValueRow(results, results.BestModelInDependentBin(), "Independet");
    table << BestValueRow(results, results.BestAcceptanceBin(), "$S/\\sqrt B$");
    return table.str();
}

std::string Plotting::BestValueRow(Results const& results, int bin, std::string const& name) const
{
    Info0;
    std::stringstream row;
    row << " " << name;
    row << "\n  & " << RoundToDigits(results.XValue(bin));
    row << "\n  & " << RoundToDigits(results.Significances().at(bin));
    row << "\n  & " << RoundToDigits(results.ModelIndependentCrosssection().at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

std::string Plotting::EfficienciesTable(Results const& results, int bin) const
{
    Info0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << float(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << EfficienciesRow(result, &result - &results.Signals().front(), Tag::signal, bin);
    for (auto const & result : results.Backgrounds()) table << EfficienciesRow(result, &result - &results.Backgrounds().front(), Tag::background, bin);
    return table.str();
}

std::string Plotting::EfficienciesRow(Result const& result, int index, Tag tag, int bin) const
{
    Info0;
    std::stringstream row;
    row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
    row << "\n  & " << result.InfoBranch().EventNumber;
    row << "\n  & " << result.EventSums().at(bin);
    row << "\n  & " << RoundToDigits(result.Efficiencies().at(bin));
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection);
    row << "\n  & " << RoundToDigits(to_crosssection(result.InfoBranch().Crosssection) * DetectorGeometry::Luminosity() * result.Efficiencies().at(bin));
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
            background = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), background, [](Plots & sum, Plots const & plots) {
                for (auto & plot : sum.plots()) plot.Join(plots.plots().at(&plot - &sum.plots().front()).Data());
                return sum;
            });
            background.SetName("background");
        }
        for (auto & signal : signals) DoPlot(signal, background, stage);
    }
}

void Plotting::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    Info0;
    NamePairs latex_names = unordered_pairs(tagger_.Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return std::make_pair(variable_1.nice_name(), variable_2.nice_name());
    });
    NamePairs names = unordered_pairs(tagger_.Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return std::make_pair(variable_1.name(), variable_2.name());
    });
    signals.SetNames(names, latex_names);
    backgrounds.SetNames(names, latex_names);
    for (auto & signal : signals.plots()) PlotDetails(signal, backgrounds.plots().at(&signal - &signals.plots().front()), stage);
}

void Plotting::PlotDetails(Plot& signal, Plot& background, Stage stage) const
{
    INFO(signal.Data().size(), background.Data().size());
    std::vector<Vector3<float>> signal_x = signal.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.X() < b.X();
    });
    std::vector<Vector3<float>> signal_y = signal.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Y() < b.Y();
    });
    std::vector<Vector3<float>> background_x = background.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.X() < b.X();
    });
    std::vector<Vector3<float>> background_y = background.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Y() < b.Y();
    });
    Rectangle<float> bounds;
    bounds.SetXMin(std::min(signal_x.front().X(), background_x.front().X()));
    bounds.SetYMin(std::min(signal_y.front().Y(), background_y.front().Y()));
    bounds.SetXMax(std::max(signal_x.back().X(), background_x.back().X()));
    bounds.SetYMax(std::max(signal_y.back().Y(), background_y.back().Y()));
    switch (stage) {
    case Stage::trainer :
        PlotHistogram(signal, background, bounds);
        break;
    case Stage::reader :
        PlotProfile(signal, background, bounds);
        break;
    }
}

void Plotting::PlotHistogram(Plot const& signal, Plot const& background, Rectangle<float> const& bounds) const
{
//     INFO(min.X(), min.Y(), max.X(), max.Y());
//     Canvas canvas(Tagger().ExportFolderName() + "/" + "Hist-" + background.tree_name, signal.name_x + "-" + signal.name_y);
    Histogram2Dim histogram(Tagger().ExportFolderName() + "/" + "Hist-" + background.Title().Name(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    histogram.canvas().SetBottomMargin(0.15);
    int bin_number = 20;

    histogram.AddHistogram(Tagger().LatexName(), bin_number, bounds, background.Data(), kBlue);
//     TExec exec_1;
//     TH2F background_histogram("", Tagger().LatexName().c_str(), bin_number, min.X(), max.X(), bin_number, min.Y(), max.Y());
//     SetHistogram(background_histogram, background, kBlue, exec_1);
    histogram.AddHistogram(Tagger().LatexName(), bin_number, bounds, signal.Data(), kRed);
//     TExec exec_2;
//     TH2F signal_histogram("", Tagger().LatexName().c_str(), bin_number, min.X(), max.X(), bin_number, min.Y(), max.Y());
//     SetHistogram(signal_histogram, signal, kRed, exec_2);
    histogram.SetLegend(Rectangle<float>(Vector2<float>(0.35, 0), 0.3, 0.1));
//     Legend legend(Vector3<float>(0.35, 0), 0.3, 0.1);
//     legend.TwoColumn();
    histogram.Legend().TwoColumn();
//     legend.AddEntry(signal_histogram, "Signal");
//     legend.AddEntry(background_histogram, "Background");
//     mkdir(Tagger().ExportFolderName().c_str(), 0700);
    histogram.SetXAxis(signal.XAxis().LatexName().c_str());
    histogram.SetYAxis(signal.YAxis().LatexName().c_str());

//     histogram.SaveAs(Tagger().ExportFolderName() + "/" + "Hist-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y);
}

void Plotting::PlotProfile(Plot const& signal, Plot const& background, Rectangle<float> const& bounds) const
{
    Info0;
//     Canvas canvas(Tagger().ExportFolderName() + "/" + "Prof-" + background.tree_name, signal.name_x + "-" + signal.name_y);
    Profile profile(Tagger().ExportFolderName() + "/" + "Prof-" + background.Title().Name(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    profile.canvas().SetRightMargin(0.15);
    int bin_number = 30;
//     TProfile2D profile("", Tagger().LatexName().c_str(), bin_number, min.X(), max.X(), bin_number, min.Y(), max.Y());
    profile.SetDimensions(Tagger().LatexName(), bin_number, bounds);
    profile.SetProfile(signal, background);
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    profile.SaveAs(Tagger().ExportFolderName() + "/" + "Prof-" + background.Title().Name() + "-" + signal.XAxis().Name() + "-" + signal.YAxis().Name());
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
    Plots plots(InfoBranch(file, tree_name));
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(1);
    plots.plots() = unordered_pairs(tagger_.Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return ReadTree(tree, variable_1.name(), variable_2.name(), stage);
    });
    plots.SetName(tree_name);
    Debug(plots.plots().size(), tagger_.Branch().Variables().size());
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
        for (auto const & element : Range(branch_size)) plot.Add(Vector3<float>(leaf_values_1.at(element), leaf_values_2.at(element), bdt_values.at(element)));
    }
    return plot;
}




Tagger const& Plotting::Tagger() const
{
    return tagger_;
}
void Plotting::SetBranch(TTree& tree, std::vector< float >& values, const std::string& name) const
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &values.front());
}
void Plotting::SetBranch(TTree& tree, int& value, const std::string& name) const
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &value);
}

























// Results Plotting::ReadCutFiles() const
// {
//     Info0;
//     TFile file(Tagger().ExportFileName().c_str(), "Recreate");
//     return Results(ReadCutFile(file, Tag::signal), ReadCutFile(file, Tag::background));
// }
//
// std::vector<Result> Plotting::ReadCutFile(TFile& export_file, Tag tag) const
// {
//     Info0;
//     std::string file_name = Tagger().FileName(Stage::reader, tag);
//     Debug(file_name);
//     if (!Exists(file_name)) Error("non existent", file_name);
//     TFile file(file_name.c_str(), "Read");
//     std::vector<Result> results;
//     INFO(Tagger().TreeNames(tag).size());
//     for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(CutDistribution(file, tree_name, export_file));
//     return results;
// }
//
//
// void Plotting::Cuts() const
// {
//     Info0;
//     Results results(ReadCutFiles());
//     results.Significances();
//     LatexFile latex_file(Tagger().ExportFolderName());
//     latex_file.Mass(double(results.Signals().front().InfoBranch().Mass) * GeV);
//     latex_file.IncludeGraphic(PlotCutEfficiencyGraph(results), "Efficiencies");
//     latex_file.Table("rlll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
//     latex_file.IncludeGraphic(PlotResult(results), "Significances");
//     latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelDependentBin()), "Model dependent efficiencies");
//     latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelInDependentBin()), "Model independent efficiencies");
//     latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of the crosssection for the model-independent result");
// }
//
//
// std::string Plotting::PlotResult(boca::Results& results) const
// {
//     Info0;
//     Graphs graphs(Tagger().ExportFolderName(), "Significance");
//     graphs.AddGraph(results.XValues(), results.Significances());
//     graphs.SetXAxis("BDT", results.Bounds().Horizontal());
//     graphs.SetYAxis("Significance");
//     graphs.AddLine(results.BestModelDependentValue());
//     return graphs.FileName();
// //     Canvas canvas(Tagger().ExportFolderName(), "Significance");
// //     TGraph graph = CutGraph(results, results.Significances(), "Significance");
// //     TLine line  = CutLine(results.XValue(results.BestModelDependentBin()), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 1);
// //     return canvas.SaveAs(Tagger().ExportFolderName() + "-Significance");
// }
//
//
// std::string Plotting::PlotCutEfficiencyGraph(Results const& results) const
// {
//     Info0;
//     Graphs graphs(Tagger().ExportFolderName(), "Efficiency");
// //     graphs.SetLog();
// //     std::vector<std::string> nice_names;
// //     std::vector<TGraph> graphs;
//     for (auto const & result : results.Signals()) {
// //         nice_names.emplace_back(result.InfoBranch().Name);
// //         graphs.emplace_back(TGraph(result.steps, &results.XValues().front(), &result.Efficiencies().front()));
//         graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().Name);
//     }
//     for (auto const & result : results.Backgrounds()) {
// //         nice_names.emplace_back(result.InfoBranch().Name);
// //         graphs.emplace_back(TGraph(result.steps, &results.XValues().front(), &result.Efficiencies().front()));
//         graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().Name);
//     }
//     graphs.SetLegend(Orientation::bottom | Orientation::left);
// //     Legend legend(Orientation::bottom | Orientation::left, nice_names);
// //     for (auto & graph : graphs) AddGraph(graph, graphs, legend, nice_names, &graph - &graphs.front());
// //     graphs.Draw("al");
//     graphs.SetXAxis("Calculated", results.Bounds().Horizontal());
//     graphs.SetYAxis("Measured");
// //     graphs.GetXaxis()->SetLimits(results.min.X(), results.max.X());
// //     SetAxis(*graphs.GetXaxis(), "Calculated");
// //     SetAxis(*graphs.GetYaxis(), "Measured");
//     graphs.AddLine(results.XValue(results.BestModelDependentBin()));
//     graphs.AddLine(results.XValue(results.BestModelInDependentBin()));
// //     TLine line = CutLine(results.XValue(results.BestModelDependentBin()) , graphs.GetYaxis()->GetXmin(), graphs.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 1);
// //     TLine line2 = CutLine(results.XValue(results.BestModelInDependentBin()), graphs.GetYaxis()->GetXmin(), graphs.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 2);
// //     legend.Draw();
// //     return graphs.SaveAs(Tagger().ExportFolderName() + "-Efficiency");
//     return graphs.FileName();
// }

// std::string Plotting::BestValueTable(Results const& results) const
// {
//     Info0;
//     std::stringstream table;
//     table << "    Model\n  & Cut\n  & $p$-value\n  & Crosssection [fb]";
//     table << "\n \\\\ \\midrule\n   ";
//     table << BestValueRow(results, results.BestModelDependentBin(), "Dependet");
//     table << BestValueRow(results, results.BestModelInDependentBin(), "Independet");
//     table << BestValueRow(results, results.BestAcceptanceBin(), "$S/\\sqrt B$");
//     return table.str();
// }
//
// std::string Plotting::BestValueRow(Results const& results, int bin, std::string const& name) const
// {
//     Info0;
//     std::stringstream row;
//     row << " " << name;
//     row << "\n  & " << RoundToDigits(results.XValue(bin));
//     row << "\n  & " << RoundToDigits(results.Significances().at(bin));
//     row << "\n  & " << RoundToDigits(results.ModelIndependentCrosssection().at(bin) / fb);
//     row << "\n \\\\";
//     return row.str();
// }

// std::string Plotting::EfficienciesTable(Results const& results, int bin) const
// {
//     Info0;
//     std::stringstream table;
//     table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << float(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
//     table << "\n \\\\ \\midrule\n   ";
//     for (auto const & result : results.Signals()) table << EfficienciesRow(result, &result - &results.Signals().front(), Tag::signal, bin);
//     for (auto const & result : results.Backgrounds()) table << EfficienciesRow(result, &result - &results.Backgrounds().front(), Tag::background, bin);
//     return table.str();
// }
//
// std::string Plotting::EfficienciesRow(Result const& result, int index, Tag tag, int bin) const
// {
//     Info0;
//     std::stringstream row;
//     row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
//     row << "\n  & " << result.InfoBranch().EventNumber;
//     row << "\n  & " << result.EventSums().at(bin);
//     row << "\n  & " << RoundToDigits(result.Efficiencies().at(bin));
//     row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection);
//     row << "\n  & " << RoundToDigits(to_crosssection(result.InfoBranch().Crosssection) * DetectorGeometry::Luminosity() * result.Efficiencies().at(bin));
//     row << "\n \\\\";
//     return row.str();
// }

// std::string Plotting::PlotModelIndependentGraph(Results& results) const
// {
//     Info0;
//     Graphs graphs(Tagger().ExportFolderName(), "Exclusion");
//     graphs.AddGraph(results.XValues(), results.ModelIndependentCrosssection());
//     graphs.SetLog(Bounds<Crosssection>(*boost::range::min_element(boost::remove_erase(results.ModelIndependentCrosssection(), 0_fb)), *boost::range::max_element(results.ModelIndependentCrosssection())));
//     graphs.SetXAxis("BDT", results.Bounds().Horizontal());
//     graphs.SetYAxis("Crosssection");
//     graphs.AddLine(results.BestAcceptanceValue());
//     return graphs.FileName();
//
// //     Canvas canvas(Tagger().ExportFolderName(), "Exclusion");
// //     TGraph graph = CutGraph(results, results.ModelIndependentCrosssection(), "Crosssection");
// //     canvas.SetLog(min(results.ModelIndependentCrosssection(), true) / fb, max(results.ModelIndependentCrosssection()) / fb);
// //     TLine line  = CutLine(results.XValue(results.BestModelInDependentBin()), graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.Signals().size() + results.Backgrounds().size() + 2);
// //     return canvas.SaveAs(Tagger().ExportFolderName() + "-Exclusion");
// }

}

