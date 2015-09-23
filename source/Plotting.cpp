/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Plotting.hh"

#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <numeric>

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TClonesArray.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TDirectoryFile.h"
#include "TTree.h"
#include "TMultiGraph.h"
#include "TLine.h"
#include "TStyle.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TGraph.h"
#include "TColor.h"
#include "TExec.h"
#include "TLegend.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegendEntry.h"

#include "TRandom3.h"
#include "TUnfoldDensity.h"
#include "TVirtualFitter.h"

#include "exroot/ExRootAnalysis.hh"
#include "Vector.hh"
#include "Types.hh"
#include "Math.hh"
#include "Branches.hh"
#include "LatexFile.hh"
#include "Result.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Plotting::Plotting(boca::Tagger& tagger)
{
    Info();
    tagger_ = &tagger;
    gStyle->SetOptStat("");
    gStyle->SetTitleFont(FontCode(), "t");
    gStyle->SetTitleFontSize(TextSize());
}

void Plotting::Fill(TAttFill& pad) const
{
    Info();
//     pad.SetFillColorAlpha(kWhite, 0);
//     gPad->SetFillColorAlpha(kWhite,0);
//     gPad->SetFillColor(0);
//     gPad->SetFillStyle(0);
//     gPad->SetFrameFillColor(0);
//     gPad->SetFrameFillStyle(0);
}

void Plotting::TaggingEfficiency() const
{
    Info();
    Results results = ReadBdtFiles();
    PlotHistograms(results);
    PlotEfficiencyGraph(results);
    PlotAcceptanceGraph(results);
}

std::string Plotting::Mass(Results const& results) const
{
    Info();
    int mass = results.signals.front().info_branch_.Mass;
    std::string mass_string;
    if (mass > 0) mass_string = "\\section*{Mass: " + std::to_string(mass) + "}\n";
    return mass_string;
}

void Plotting::OptimalCuts() const
{
    Info();
    Results results = ReadBdtFiles();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file << Mass(results);
    results.Significances();
    latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of the crosssection for the model-independent result");
    latex_file.IncludeGraphic(PlotModelDependentGraph(results), "Maximization of the significance for the model-dependent result");
    latex_file.IncludeGraphic(PlotCrosssectionGraph(results), "Maximization of $S/\\sqrt B$");
    latex_file.Table("rlllll", EfficienciesTable(results, results.best_model_independent_bin), "Model independent efficiencies");
    latex_file.Table("rlllll", EfficienciesTable(results, results.best_model_dependent_bin), "Model dependent efficiencies");
    latex_file.Table("rlll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
}

Results Plotting::ReadBdtFiles() const
{
    Info();
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    Results results;
    results.signals = ReadBdtFile(file, Tag::signal);
    results.backgrounds = ReadBdtFile(file, Tag::background);
    results.ExtremeXValues();
    return results;
}

std::vector<Result> Plotting::ReadBdtFile(TFile& export_file, Tag tag) const
{
    Info();
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
    Info();
    std::string branch_name = Tagger().BranchName(Stage::reader);
    Debug(branch_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Result result(InfoBranch(file, tree_name));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& result_branch = *tree_writer.NewBranch(branch_name.c_str(), ResultBranch::Class());
    long entries = 0;
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
            float bdt_value = Tagger().ReadBdt(clones_array, entry);
            Check(bdt_value >= -1 && bdt_value <= 1, bdt_value);
            static_cast<ResultBranch&>(*result_branch.NewEntry()).Bdt = bdt_value;
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
    Debug(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Debug(tree_name, Tagger().WeightBranchName());
    TClonesArray& clones_array = *tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    return static_cast<boca::InfoBranch&>(*clones_array.Last());
}

std::string Plotting::PlotHistograms(boca::Results& results) const
{
    Info();
    TCanvas canvas;
    Fill(canvas);
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
    canvas.Update();
    TLegend legend = Legend(Orientation::top, nice_names);
    for (auto & histogram : histograms) AddHistogram(stack, histogram, legend);
    stack.Draw("nostack");
    SetAxis(*stack.GetXaxis(), "BDT");
    SetAxis(*stack.GetYaxis(), "N");
    TLine line = Line(results.best_model_dependent_bin, stack.GetYaxis()->GetXmin(), stack.GetYaxis()->GetXmax() /*results.max.y * 1.05*/, results.signals.size() + results.backgrounds.size() + 1);
    TLine line2 = Line(results.best_model_independent_bin, stack.GetYaxis()->GetXmin(), stack.GetYaxis()->GetXmax()/*results.max.y * 1.05*/, results.signals.size() + results.backgrounds.size() + 2);
    std::string file_name = Tagger().ExportFolderName() + "-Bdt" + ExportFileSuffix();
    legend.Draw();
    canvas.SaveAs(file_name.c_str());
    return file_name;
}

TH1F Plotting::Histogram(Result const& result, Point& max, Point& min, int index) const
{
    Info();
    TH1F histogram(result.info_branch_.Name.c_str(), "", 50, FloorToDigits(min.x, 1), CeilToDigits(max.x, 1));
    for (auto const & bdt : result.bdt) histogram.Fill(bdt);
    if (histogram.Integral() != 0)  histogram.Scale(1. / histogram.Integral());
    SetPlotStyle(histogram, index);
    float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
    if (max_0 > max.y) max.y = max_0;
    return histogram;
}

void Plotting::AddHistogram(THStack& stack, TH1& histogram, TLegend& legend) const
{
    Info();
    stack.Add(&histogram);
    legend.AddEntry(&histogram, histogram.GetName(), "l");
}

TLegend Plotting::Legend(float x_min, float y_min, float width, float height, std::string const& title) const
{
    Info();
    TLegend legend(x_min, y_min, x_min + width, y_min + height);
    if (!title.empty()) {
        legend.SetHeader(title.c_str());
        static_cast<TLegendEntry&>(*legend.GetListOfPrimitives()->First()).SetTextFont(FontCode());
        static_cast<TLegendEntry&>(*legend.GetListOfPrimitives()->First()).SetTextSize(TextSize());
    }
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
    legend.SetTextFont(FontCode());
    legend.SetTextSize(TextSize());
    legend.Draw();
    return legend;
}

TLegend Plotting::Legend(Orientation orientation, Strings const& entries, std::string const& title) const
{
    Info();
    int letters = std::max_element(entries.begin(), entries.end(), [](std::string const & entry_1, std::string const & entry_2) {
        return entry_1.size() < entry_2.size();
    })->size();
    float letter_width = 0.01;
    float letter_height = 0.06;
    float image_width = 0.1;
    float width = letter_width * letters + image_width;
    float height = entries.size() * letter_height;
    if (!title.empty()) height += letter_height;
    // default values for Orientation::center
    float x_shift = 0.5;
    float y_shift = 0.5;
    float x_offset = width / 4; // FIXME why is this necessary; why not 1/2?
    float y_offset = height / 2;
    FlagSwitch(orientation, [&](Orientation orientation) {
        switch (orientation) {
        case Orientation::left:
            x_shift = 0;
            x_offset = 0;
            break;
        case Orientation::right:
            x_shift = 1;
            x_offset = width / 2;
            break;
        case Orientation::top:
            y_shift = 1;
            y_offset = height;
            break;
        case Orientation::bottom:
            y_shift = 0;
            y_offset = 0;
            break;
        default : break;
        }
    });
    float margin = 0.03;
    float x_unit = 1 - gPad->GetLeftMargin() - gPad->GetRightMargin() - 2 * margin;
    float y_unit = 1 - gPad->GetBottomMargin() - gPad->GetTopMargin() - 2 * margin;
    float x_min = gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset;
    float y_min = gPad->GetBottomMargin() + margin + y_shift * y_unit - y_offset;
    return Legend(x_min, y_min, width, height, title);
}

std::string Plotting::PlotEfficiencyGraph(Results const& results) const
{
    Info();
    TCanvas canvas;
    Fill(canvas);
    canvas.SetLogy();
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
    SetAxis(*multi_graph.GetXaxis(), "BDT");
    SetAxis(*multi_graph.GetYaxis(), "Efficiency");
    TLine line = Line(results.best_model_dependent_bin , multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
    TLine line2 = Line(results.best_model_independent_bin, multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
    std::string file_name = Tagger().ExportFolderName() + "-Efficiency" + ExportFileSuffix();
    legend.Draw();
    canvas.SaveAs(file_name.c_str());
    return file_name;
}

TLine Plotting::Line(float bin, float y_min, float y_max, int index) const
{
    Info();
    TLine line(Results::XValue(bin), y_min, Results::XValue(bin), y_max);
    line.SetLineStyle(index + 1);
    line.SetLineColor(ColorCode(index));
    if (bin != 0) line.Draw();
    return line;
}

void Plotting::AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, Strings const& names, int index) const
{
    Info();
    SetPlotStyle(graph, index);
    multi_graph.Add(&graph);
    legend.AddEntry(&graph, names.at(index).c_str(), "l");
}

void Plotting::PlotAcceptanceGraph(Results const& results) const
{
    Info();
    for (auto const & signal : results.signals) {
        TCanvas canvas;
        Fill(canvas);
        TMultiGraph multi_graph("", Tagger().NiceName().c_str());
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
        if (min.y > 0 && min.y / max.y < 0.1) canvas.SetLogy();
        TLegend legend = Legend(Orientation::left | Orientation::top, nice_names, signal.info_branch_.Name);
        for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names, &graph - &graphs.front());
        SetMultiGraph(multi_graph, min, max);
        legend.Draw();
        std::string file_name = Tagger().ExportFolderName() + "-Acceptance" + ExportFileSuffix();
        canvas.SaveAs(file_name.c_str());
    }
}

void Plotting::SetPlotStyle(TAttLine& att_line, int index) const
{
    Info();
    att_line.SetLineColor(ColorCode(index));
    att_line.SetLineStyle(index + 1);
}

void Plotting::SetMultiGraph(TMultiGraph& multi_graph, Point const& min, Point const& max) const
{
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(min.x, max.x);
    multi_graph.SetMaximum(max.y);
    multi_graph.SetMinimum(min.y);
    SetAxis(*multi_graph.GetXaxis(), "Signal acceptance");
    SetAxis(*multi_graph.GetYaxis(), "Background acceptance");
}

std::string Plotting::PlotModelDependentGraph(Results& results) const
{
    Info();
    TCanvas canvas;
    Fill(canvas);
    TGraph graph = Graph(results, results.significances, "Significance");
    canvas.Update();
    TLine line  = Line(results.best_model_dependent_bin, graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 1);
    std::string file_name = Tagger().ExportFolderName() + "-Significance" + ExportFileSuffix();
    canvas.SaveAs(file_name.c_str());
    return file_name;
}

std::string Plotting::PlotCrosssectionGraph(Results& results) const
{
    Info();
    TCanvas canvas;
    Fill(canvas);
    TGraph graph = Graph(results, results.acceptances, "S/#sqrt{B}");
    canvas.Update();
    TLine line  = Line(results.best_acceptance_bin, graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 3);
    std::string file_name = Tagger().ExportFolderName() + "-SB" + ExportFileSuffix();
    canvas.SaveAs(file_name.c_str());
    return file_name;
}

std::string Plotting::PlotModelIndependentGraph(Results& results) const
{
    Info();
    TCanvas canvas;
    Fill(canvas);
    TGraph graph = Graph(results, results.crosssections, "Crosssection");
    if (min(results.crosssections, true) / max(results.crosssections) < 0.1) canvas.SetLogy();
    canvas.Update();
    TLine line  = Line(results.best_model_independent_bin, graph.GetYaxis()->GetXmin(), graph.GetYaxis()->GetXmax(), results.signals.size() + results.backgrounds.size() + 2);
    std::string file_name = Tagger().ExportFolderName() + "-Exclusion" + ExportFileSuffix();
    canvas.SaveAs(file_name.c_str());
    return file_name;
}

TGraph Plotting::Graph(Results const& results, std::vector<float> const& values, std::string const& title) const
{
    TGraph graph(Result::steps, &results.x_values.front(), &values.front());
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    SetAxis(*graph.GetXaxis(), "BDT");
    SetAxis(*graph.GetYaxis(), title.c_str());
    return graph;
}

std::string Plotting::BestValueTable(Results const& results) const
{
    Info();
    std::stringstream table;
    table << "    Model\n  & Cut\n  & $p$-value\n  & Crosssection [fb]";
    table << "\n \\\\ \\midrule\n";
    table << "    Dependet\n  & " << RoundToDigits(results.BestModelDependentXValue()) << "\n  & " << RoundToDigits(results.significances.at(results.best_model_dependent_bin)) << "\n  & " << RoundToDigits(results.crosssections.at(results.best_model_dependent_bin)) << "\n";
    table << " \\\\ Independet\n  & " << RoundToDigits(results.BestModelInDependentXValue()) << "\n  & " << RoundToDigits(results.significances.at(results.best_model_independent_bin)) << "\n  & " << RoundToDigits(results.crosssections.at(results.best_model_independent_bin)) << "\n \\\\";
    return table.str();
}

std::string Plotting::EfficienciesTable(Results const& results, int bin) const
{
    Info();
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << DetectorGeometry::Luminosity() << "]{fb^{-1}}}$";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.signals) table << EfficienciesRow(result, &result - &results.signals.front(), Tag::signal, bin);
    for (auto const & result : results.backgrounds) table << EfficienciesRow(result, &result - &results.backgrounds.front(), Tag::background, bin);
    return table.str();
}

std::string Plotting::EfficienciesRow(Result const& result, int index, Tag tag, int bin) const
{
    std::stringstream row;
    row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|"
        << "\n  & " << result.info_branch_.EventNumber
        << "\n  & " << result.event_sums.at(bin)
        << "\n  & " << RoundToDigits(result.efficiency.at(bin))
        << "\n  & " << RoundToDigits(result.info_branch_.Crosssection)
        << "\n  & " << std::round(result.info_branch_.Crosssection * (fb * DetectorGeometry::Luminosity()) * result.efficiency.at(bin))
        << "\n \\\\";
    return row.str();
}

void Plotting::RunPlots() const
{
    Info();
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
    Info();
    Names nice_names = unordered_pairs(Tagger().Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return std::make_pair(variable_1.nice_name(), variable_2.nice_name());
    });
    Names names = unordered_pairs(Tagger().Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return std::make_pair(variable_1.name(), variable_2.name());
    });
    signals.SetNames(names, nice_names);
    backgrounds.SetNames(names, nice_names);
    for (auto & signal : signals.plots) PlotDetails(signal, backgrounds.plots.at(&signal - &signals.plots.front()), stage);
}

void Plotting::PlotDetails(Plot& signal, Plot& background, Stage stage) const
{
    Info(signal.points.size(), background.points.size());
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
    Info(min.x, min.y, max.x, max.y);
    TCanvas canvas;
    Fill(canvas);
    canvas.SetBottomMargin(0.15);
    int bin_number = 20;
    TExec exec_1;
    TH2F background_histogram("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetHistogram(background_histogram, background, kBlue, exec_1);
    TExec exec_2;
    TH2F signal_histogram("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetHistogram(signal_histogram, signal, kRed, exec_2);
    TLegend legend = Legend(0.35, 0, 0.3, 0.1);
    legend.SetNColumns(2);
    legend.SetColumnSeparation(0.2);
    legend.AddEntry(&signal_histogram, "Signal", "l");
    legend.AddEntry(&background_histogram, "Background", "l");
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    std::string file_name = Tagger().ExportFolderName() + "/" + "Hist-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y + ExportFileSuffix();
    canvas.SaveAs(file_name.c_str());
}

void Plotting::PlotProfile(Plot const& signal, Plot const& background, Point const& min, Point const& max) const
{
    Info();
    TCanvas canvas;
    Fill(canvas);
    canvas.SetRightMargin(0.15);
    int bin_number = 30;
    TProfile2D profile("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetProfile(profile, signal, background);
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    std::string file_name = Tagger().ExportFolderName() + "/" + "Prof-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y + ExportFileSuffix();
    canvas.SaveAs(file_name.c_str());
}

void Plotting::SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec) const
{
    Info();
    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (auto const & point : plot.points) histogram.Fill(point.x, point.y);
    histogram.SetContour(20);
    switch (color) {
    case kRed :
        exec.SetAction("boca::Color().Red();");
        break;
    case kBlue :
        exec.SetAction("boca::Color().Blue();");
        break;
    default:
        Error("unsupported color");
    }
    exec.Draw();
    CommonHist(histogram, plot, color);
    histogram.Draw(options.c_str());
}


void Plotting::SetProfile(TH2& histogram, Plot const& signal, Plot const& background) const
{
    Info();
    float max = (*std::max_element(signal.points.begin(), signal.points.end(), [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    float min = (*std::min_element(background.points.begin(), background.points.end(), [](Point const & a, Point const & b) {
        return a.z < b.z;
    })).z;
    for (auto const & point : signal.points) histogram.Fill(point.x, point.y, point.z);
    for (auto const & point : background.points) histogram.Fill(point.x, point.y, point.z);
    Color().Heat();
    CommonHist(histogram, signal, kRed);
    histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void Plotting::CommonHist(TH1& histogram, Plot const& plot, EColor color) const
{
    Info();
    histogram.SetXTitle(plot.nice_name_x.c_str());
    histogram.SetYTitle(plot.nice_name_y.c_str());
    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
}

std::vector<Plots> Plotting::Import(Stage stage, Tag tag) const
{
    Debug(Tagger().FileName(stage, tag), Tagger().TreeNames(tag).size());
    TFile file(Tagger().FileName(stage, tag).c_str(), "Read");
    std::vector<Plots> results;
    for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(PlotResult(file, tree_name, stage));
    return results;
}

Plots Plotting::PlotResult(TFile& file, std::string const& tree_name, Stage stage) const
{
    Debug(tree_name);
    Plots plots;
    plots.info_branch = InfoBranch(file, tree_name);
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(1);
    plots.plots = unordered_pairs(Tagger().Branch().Variables(), [&](Obs const & variable_1, Obs const & variable_2) {
        return ReadTree(tree, variable_1.name(), variable_2.name(), stage);
    });
    plots.name = tree_name;
    Debug(plots.plots.size(), Tagger().Branch().Variables().size());
    return plots;
}

Plot Plotting::ReadTree(TTree& tree, std::string const& leaf_1, std::string const& leaf_2, Stage stage) const
{
    Info();
    tree.SetBranchStatus("*", false);
    std::string branch_name = Tagger().BranchName(stage);
    Debug(branch_name);

    tree.SetBranchStatus(branch_name.c_str(), true);
    int branch_value = 0;
    tree.SetBranchAddress(branch_name.c_str(), &branch_value);
    Debug(branch_name.c_str());

    std::string size_name = branch_name + "_size";
    Debug(size_name.c_str());
    tree.SetBranchStatus(size_name.c_str(), true);
    int branch_size = 0;
    tree.SetBranchAddress(size_name.c_str(), &branch_size);

    //FIXME remove this magic number
    size_t max_value = 200;
    std::string leaf_name_1 = branch_name + "." + leaf_1;
    Debug(leaf_name_1.c_str());
    tree.SetBranchStatus(leaf_name_1.c_str(), true);
    std::vector<float> leaf_values_1(max_value);
    tree.SetBranchAddress(leaf_name_1.c_str(), &leaf_values_1.front());

    std::string leaf_name_2 = branch_name + "." + leaf_2;
    Debug(leaf_name_2.c_str());
    tree.SetBranchStatus(leaf_name_2.c_str(), true);
    std::vector<float> leaf_values_2(max_value);
    tree.SetBranchAddress(leaf_name_2.c_str(), &leaf_values_2.front());

    std::string bdt_name = branch_name + ".Bdt";
    Debug(bdt_name.c_str());
    tree.SetBranchStatus(bdt_name.c_str(), true);
    std::vector<float> bdt_values(max_value);
    tree.SetBranchAddress(bdt_name.c_str(), &bdt_values.front());

    Plot plot;
    for (auto const & entry : Range(tree.GetEntries())) {
        Detail(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (auto const & element : Range(branch_size)) {
            Point point;
            point.x = leaf_values_1.at(element);
            point.y = leaf_values_2.at(element);
            point.z = bdt_values.at(element);
            Detail(point.x, point.y, point.z);
            plot.points.emplace_back(point);
        }
    }
    return plot;
}

Plot Plotting::CoreVector(Plot& plot, std::function<bool (Point const&, Point const&)> const& function) const
{
    Info();
    // TODO sorting the whole vector when you just want to get rid of the extrem values might not be the fastest solution
    std::sort(plot.points.begin(), plot.points.end(), [&](Point const & a, Point const & b) {
        return function(a, b);
    });
    int cut_off = plot.points.size() / 25;
    plot.points.erase(plot.points.begin(), plot.points.begin() + cut_off);
    plot.points.erase(plot.points.end() - cut_off, plot.points.end());
    return plot;
}
Tagger& Plotting::Tagger() const
{
    return *tagger_;
}
std::string Plotting::ExportFileSuffix() const
{
    return ".png";
}

void Plotting::SetAxis(TAxis& axis, std::string const& title) const
{
    Info();
    axis.SetTitle(title.c_str());
    axis.CenterTitle();
    axis.SetTitleFont(FontCode());
    axis.SetTitleSize(TextSize());
    axis.SetLabelFont(FontCode());
    axis.SetLabelSize(LabelSize());
}

float Plotting::TextSize() const
{
    return 0.05;
    return 20;
}

float Plotting::LabelSize() const
{
    return 0.04;
    return 15;
}

}

