#include "Plotting.hh"

#include <fstream>
#include <algorithm>
#include <sys/stat.h>

#include "TFile.h"
#include "TClonesArray.h"
#include "TPad.h"
#include "TDirectoryFile.h"
#include "TTree.h"
#include "TCanvas.h"
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

#include "exroot/ExRootAnalysis.hh"
#include "Vector.hh"
#include "Types.hh"
#include "Math.hh"
#include "Branches.hh"
// #define DEBUG
#include "Debug.hh"

namespace analysis
{

Plotting::Plotting(analysis::Tagger& tagger)
{
    Debug();
    tagger_ = &tagger;
    gStyle->SetOptStat("");
}

void Plotting::TaggingEfficiency() const
{
    Debug();
    Results results = ReadBdtFiles();
    PlotHistograms(results);
    PlotEfficiencyGraph(results);
    PlotAcceptanceGraph(results);
}

void Plotting::OptimalSignificance() const
{
    Debug();
    Results results = ReadBdtFiles();
    results.Significances();
    results.BestBin();
    std::string efficiency_file_name = PlotEfficiencyGraph(results);
    std::string significance_file_name = PlotSignificanceGraph(results);
    std::string bdt_file_name = PlotHistograms(results);
    std::ofstream latex_file;
    LatexHeader(latex_file);
    latex_file << Table(results);
    latex_file << IncludeGraphic(bdt_file_name, "BDT Distribution");
    latex_file << IncludeGraphic(efficiency_file_name, "Efficiency");
    latex_file << IncludeGraphic(significance_file_name, "Significance");
    LatexFooter(latex_file);
}

Results Plotting::ReadBdtFiles() const
{
    TFile export_file(Tagger().ExportFileName().c_str(), "Recreate");
    Results results;
    results.signal = ReadBdtFile(export_file, Tag::signal);
    results.background = ReadBdtFile(export_file, Tag::background);
    export_file.Close();
    results.ExtremeXValues();
    return results;
}

std::vector<Result> Plotting::ReadBdtFile(TFile& export_file, Tag tag) const
{
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    Debug(file_name);
    if (!Exists(file_name)) Error("non existent", file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<Result> results;
    for (const auto & tree_name : Tagger().TreeNames(tag)) results.emplace_back(BdtDistribution(file, tree_name, export_file));
    return results;
}

Result Plotting::BdtDistribution(TFile& file, const std::string& tree_name, TFile& export_file) const
{
    std::string branch_name = Tagger().BranchName(Stage::reader);
    Debug(branch_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Result result(InfoBranch(file, tree_name));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& result_branch = *tree_writer.NewBranch(branch_name.c_str(), ResultBranch::Class());
    long entries = 0;
    for (const auto & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (const auto & entry : Range(clones_array.GetEntriesFast())) {
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

InfoBranch Plotting::InfoBranch(TFile& file, const std::string& tree_name) const
{
    Debug(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Debug(tree_name, Tagger().WeightBranchName());
    TClonesArray& clones_array = *tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    return static_cast<analysis::InfoBranch&>(*clones_array.At(clones_array.GetEntriesFast() - 1));
}

std::string Plotting::PlotHistograms(analysis::Results& results) const
{
    Debug();
    TCanvas canvas;
    THStack stack("", Tagger().NiceName().c_str());
    std::vector<TH1F> histograms;
    Strings nice_names;
    for (const auto & result : results.signal) {
        histograms.emplace_back(Histogram(result, results.max, results.min, &result - &results.signal[0]));
        nice_names.emplace_back(result.info_branch_.Name);
    }
    for (const auto & result : results.background) {
        histograms.emplace_back(Histogram(result, results.max, results.min, &result - &results.background[0] + results.signal.size()));
        nice_names.emplace_back(result.info_branch_.Name);
    }
    TLegend legend = Legend(Orientation::top, nice_names);
    for (auto & histogram : histograms) AddHistogram(stack, histogram, legend);
    stack.Draw("nostack");
    stack.GetXaxis()->SetTitle("BDT");
    stack.GetYaxis()->SetTitle("N");
    canvas.Update();
    TLine line = Line(results, stack.GetMinimum(), results.max.y * 1.05);
    std::string efficiency_file_name = Tagger().ExportFolderName() + "-Bdt" + ExportFileSuffix();
    legend.Draw();
    canvas.Print(efficiency_file_name.c_str());
    return efficiency_file_name;
}

TH1F Plotting::Histogram(const Result& result, Point& max, Point& min, int index) const
{
    TH1F histogram(result.info_branch_.Name.c_str(), "", 50, FloorToDigits(min.x, 1), CeilToDigits(max.x, 1));
    for (const auto & bdt : result.bdt) histogram.Fill(bdt);
    if (histogram.Integral() != 0)  histogram.Scale(1. / histogram.Integral());
    SetPlotStyle(histogram, index);
    float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
    if (max_0 > max.y) max.y = max_0;
    return histogram;
}

void Plotting::AddHistogram(THStack& stack, TH1F& histogram, TLegend& legend) const
{
    stack.Add(&histogram);
    legend.AddEntry(&histogram, histogram.GetName(), "l");
}

TLegend Plotting::Legend(float x_min, float y_min, float width, float height, const std::string& title) const
{
    TLegend legend(x_min, y_min, x_min + width, y_min + height);
    if (title != "") legend.SetHeader(title.c_str());
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
    return legend;
}

TLegend Plotting::Legend(Orientation orientation, const Strings& entries, const std::string& title) const
{
    int letters = std::max_element(entries.begin(), entries.end(), [](const std::string & entry_1, const std::string & entry_2) {
        return entry_1.size() < entry_2.size();
    })->size();
    float letter_width = 0.01;
    float letter_height = 0.05;
    float image_width = 0.1;
    float width = letter_width * letters + image_width;
    float height = entries.size() * letter_height;
    if (title != "") height += letter_height;
    // default values for Orientation::center
    float x_shift = 0.5;
    float y_shift = 0.5;
    float x_offset = width / 8;
    float y_offset = height / 2;
    FlagSwitch(orientation, [&](Orientation orientation) {
        switch (orientation) {
        case Orientation::left:
            x_shift = 0;
            x_offset = 0;
            break;
        case Orientation::right:
            x_shift = 1;
            x_offset = width / 4;
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
    float y_unit = 1 - gPad->GetTopMargin() - gPad->GetBottomMargin() - 2 * margin;
    float x_min = gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset;
    float y_min = gPad->GetTopMargin() + margin + y_shift * y_unit - y_offset;
    return Legend(x_min, y_min, width, height, title);
}

std::string Plotting::PlotEfficiencyGraph(const Results& results) const
{
    TCanvas canvas;
    canvas.SetLogy();
    TMultiGraph multi_graph("", Tagger().NiceName().c_str());
    Strings nice_names;
    std::vector<TGraph> graphs;
    for (const auto & result : results.signal) {
        nice_names.emplace_back(result.info_branch_.Name);
        graphs.emplace_back(TGraph(result.steps, &results.x_values[0], &result.efficiency[0]));
    }
    for (const auto & result : results.background) {
        nice_names.emplace_back(result.info_branch_.Name);
        graphs.emplace_back(TGraph(result.steps, &results.x_values[0], &result.efficiency[0]));
    }
    TLegend legend = Legend(Orientation::bottom | Orientation::left, nice_names);
    for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names.at(&graph - &graphs[0]), &graph - &graphs[0]);
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    legend.Draw();
    TLine line = Line(results, multi_graph.GetYaxis()->GetXmin(), multi_graph.GetYaxis()->GetXmax());
    std::string file_name = Tagger().ExportFolderName() + "-Efficiency" + ExportFileSuffix();
    canvas.Print(file_name.c_str());
    return file_name;
}

TLine Plotting::Line(Results results, float y_min, float y_max) const
{
    TLine line(results.BestXValue(), y_min, results.BestXValue(), y_max);
    line.SetLineStyle(2);
    if (results.best_bin != 0)line.Draw();
    return line;
}

void Plotting::AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, const std::string& name, int index) const
{
    SetPlotStyle(graph, index);
    multi_graph.Add(&graph);
    legend.AddEntry(&graph, name.c_str(), "l");
}

void Plotting::PlotAcceptanceGraph(const Results& results) const
{
    Debug();
    for (const auto & signal_result : results.signal) {
        TCanvas canvas;
        TMultiGraph multi_graph("", Tagger().NiceName().c_str());
        std::vector<TGraph> graphs;
        Strings nice_names;
        for (const auto & result : results.background) {
            graphs.emplace_back(TGraph(result.steps, &signal_result.pure_efficiency[0], &result.pure_efficiency[0]));
            nice_names.emplace_back(result.info_branch_.Name);
        }
        canvas.SetLogy();
        TLegend legend = Legend(Orientation::left | Orientation::top, nice_names, signal_result.info_branch_.Name);
        for (auto & graph : graphs) AddGraph(graph, multi_graph, legend, nice_names.at(&graph - &graphs[0]), &graph - &graphs[0]);
        SetMultiGraph(multi_graph);
        legend.Draw();
        std::string efficiency_file_name = Tagger().ExportFolderName() + "-Acceptance" + ExportFileSuffix();
        canvas.Print(efficiency_file_name.c_str());
    }
}

void Plotting::SetPlotStyle(TAttLine& att_line, int index) const
{
    att_line.SetLineColor(ColorCode(index));
    att_line.SetLineStyle(index + 1);
}

void Plotting::SetMultiGraph(TMultiGraph& multi_graph) const
{
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(0.2, 0.9);
    multi_graph.GetXaxis()->SetTitle("Signal acceptance");
    multi_graph.GetYaxis()->SetTitle("Background acceptance");
    multi_graph.SetMaximum(1);
//     multi_graph.SetMinimum(0.001);
    multi_graph.SetMinimum(0.01);
}

std::string Plotting::PlotSignificanceGraph(const Results& results) const
{
    TCanvas canvas;
    TGraph graph(Result::steps, &results.x_values[0], &results.significances[0]);
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    canvas.Update();
    TLine line  = Line(results, gPad->GetUymin(), gPad->GetUymax());
    std::string file_name = Tagger().ExportFolderName() + "-Significance" + ExportFileSuffix();
    canvas.Print(file_name.c_str());
    return file_name;
}

void Plotting::LatexHeader(std::ofstream& latex_file) const
{
    Debug();
    std::string file_name = Tagger().ExportFolderName() + ".tex";
    latex_file.open(file_name);
    latex_file << "\\documentclass[a4paper,10pt]{article}\n\n"
               << "\\usepackage{booktabs}\n"
               << "\\usepackage{graphicx}\n"
               // << "\\usepackage[landscape]{geometry}\n"
               << "\\usepackage[cm]{fullpage}\n"
               // << "\\usepackage{units}\n"
               // << "\\usepackage{siunitx}\n\n"
               // << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}\n"
               // << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}\n"
               // << "\\newcolumntype{E}{R@{$\\pm$}L}\n"
               << "\\usepackage{tikz}\n"
               << "\\usetikzlibrary{patterns}\n"
               << "\\usetikzlibrary{plotmarks}\n"
               << "\n\\begin{document}\n";
}

std::string Plotting::Table(const Results& results) const
{
    std::stringstream table_header;
    table_header << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rlll}\n\\toprule\n";
    std::stringstream table;
    table << table_header.str();
    table << " Mass\n" << " & " << results.signal.front().info_branch_.Mass;
    table << "\n \\\\ \\midrule\n";
    table << " BDT-cut\n" << " & " << results.BestXValue();
    table << "\n \\\\ $p$-value\n & " << results.significances.at(results.best_bin);
    for (const auto & result : results.signal) table << " \\\\ \\verb|" << Tagger().TreeNames(Tag::signal).at(&result - &results.signal[0]) << "|\n & " << result.efficiency.at(results.best_bin) << "\n & " << result.event_sums.at(results.best_bin) << "\n & " << result.info_branch_.EventNumber << "\n";
    for (const auto & result : results.background) table << " \\\\ \\verb|" << Tagger().TreeNames(Tag::background).at(&result - &results.background[0]) << "|\n & " << result.efficiency.at(results.best_bin) << "\n & " << result.event_sums.at(results.best_bin) << "\n & " << result.info_branch_.EventNumber << "\n";
    std::stringstream table_footer;
    table_footer << " \\\\ \\bottomrule\n\\end{tabular}\n\\caption{Significance and efficiencies.}\n\\end{table}\n";
    table << table_footer.str();
    return table.str();
}

std::string Plotting::IncludeGraphic(std::string& file_name, std::string caption) const
{
    return "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" + file_name + "}\n\\caption{" + caption + "}\n\\end{figure}\n";
    return "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" + file_name + "}}\n\\caption{" + caption + ".}\n\\end{figure}\n";
}

void Plotting::LatexFooter(std::ofstream& latex_file) const
{
    Debug();
    latex_file << "\n\\end{document}\n";
    latex_file.close();
}

void Plotting::RunPlots() const
{
    for (const auto & stage : std::vector<Stage> {Stage::trainer, Stage::reader}) {
        Debug(Tagger().FileName(stage, Tag::signal), Tagger().TreeNames(Tag::signal).size());
        std::vector<Plots> signals = Import(stage, Tag::signal);
        Debug(Tagger().FileName(stage, Tag::background), Tagger().TreeNames(Tag::background).size());
        std::vector<Plots> backgrounds = Import(stage, Tag::background);
        Plots background = backgrounds.front();
        if (backgrounds.size() > 1) {
            background = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), background, [](Plots & sum, const Plots & elem) {
                for (const auto & plot : elem.plots) sum.plots.at(&plot - &elem.plots[0]).points = Join(sum.plots.at(&plot - &elem.plots[0]).points, plot.points);
                return sum;
            });
            background.name = "background";
        }
        for (auto & signal : signals) DoPlot(signal, background, stage);
    }
}

void Plotting::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    std::vector<std::pair<std::string, std::string>> nice_names = unordered_pairs(Tagger().Branch().Variables(), [&](const Obs & variable_1, const Obs & variable_2) {
        return std::make_pair(variable_1.nice_name(), variable_2.nice_name());
    });
    std::vector<std::pair<std::string, std::string>> names = unordered_pairs(Tagger().Branch().Variables(), [&](const Obs & variable_1, const Obs & variable_2) {
        return std::make_pair(variable_1.name(), variable_2.name());
    });
    signals.SetNames(names, nice_names);
    backgrounds.SetNames(names, nice_names);
    for (auto & signal : signals.plots) PlotDetails(signal, backgrounds.plots.at(&signal - &signals.plots[0]), stage);
}

void Plotting::PlotDetails(Plot& signal, Plot& background, Stage stage) const
{
    Plot signal_x = CoreVector(signal, [](Point & a, Point & b) {
        return a.x < b.x;
    });
    Plot signal_y = CoreVector(signal, [](Point & a, Point & b) {
        return a.y < b.y;
    });
    Plot background_x = CoreVector(background, [](Point & a, Point & b) {
        return a.x < b.x;
    });
    Plot background_y = CoreVector(background, [](Point & a, Point & b) {
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

void Plotting::PlotHistogram(const Plot& signal, const Plot& background, const Point& min, const Point& max) const
{
    TCanvas canvas;
    canvas.SetBottomMargin(0.15);
    TLegend legend = Legend(0.35, 0, 0.3, 0.1);
    legend.SetNColumns(2);
    legend.SetColumnSeparation(0.2);
    int bin_number = 20;
    TExec exec_1;
    TH2F background_histogram("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetHistogram(background_histogram, background, kBlue, exec_1);
//     legend.AddEntry(&background_histogram, background.name.c_str(), "l");
    TExec exec_2;
    TH2F signal_histogram("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetHistogram(signal_histogram, signal, kRed, exec_2);
//     legend.AddEntry(&signal_histogram, signal.name.c_str(), "l");
    legend.AddEntry(&signal_histogram, "Signal", "l");
    legend.AddEntry(&background_histogram, "Background", "l");
    legend.Draw();
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    std::string file_name = Tagger().ExportFolderName() + "/" + "Hist-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y + ExportFileSuffix();
    canvas.Print(file_name.c_str());
}

void Plotting::PlotProfile(const Plot& signal, const Plot& background, const Point& min, const Point& max) const
{
    TCanvas canvas;
    canvas.SetRightMargin(0.15);
    int bin_number = 30;
    TProfile2D test("", Tagger().NiceName().c_str(), bin_number, min.x, max.x, bin_number, min.y, max.y);
    SetProfile(test, signal, background);
    mkdir(Tagger().ExportFolderName().c_str(), 0700);
    std::string file_name = Tagger().ExportFolderName() + "/" + "Prof-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y + ExportFileSuffix();
    canvas.Print(file_name.c_str());
}

void Plotting::SetHistogram(TH2& histogram, const Plot& plot, EColor color, TExec& exec) const
{
    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (const auto & point : plot.points) histogram.Fill(point.x, point.y);
    histogram.SetContour(20);
    switch (color) {
    case kRed :
        exec.SetAction("analysis::Color().Red();");
        break;
    case kBlue :
        exec.SetAction("analysis::Color().Blue();");
        break;
    default:
        Error("unsupported color");
    }
    exec.Draw();
    CommmonHist(histogram, plot, color);
    histogram.Draw(options.c_str());
}


void Plotting::SetProfile(TProfile2D& histogram, const Plot& signal, const Plot& background) const
{
    float max = (*std::max_element(signal.points.begin(), signal.points.end(), [](Point  a, Point  b) {
        return a.z < b.z;
    })).z;
    float min = (*std::min_element(background.points.begin(), background.points.end(), [](Point  a, Point  b) {
        return a.z < b.z;
    })).z;
    for (const auto & point : signal.points) histogram.Fill(point.x, point.y, point.z);
    for (const auto & point : background.points) histogram.Fill(point.x, point.y, point.z);
    Color().Heat();
    CommmonHist(histogram, signal, kRed);
    histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void Plotting::CommmonHist(TH2& histogram, const Plot& plot, EColor color) const
{
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
    for (const auto & tree_name : Tagger().TreeNames(tag)) results.emplace_back(PlotResult(file, tree_name, stage));
    return results;
}

Plots Plotting::PlotResult(TFile& file, const std::string& tree_name, Stage stage) const
{
    Debug(tree_name);
    Plots plots;
    plots.info_branch = InfoBranch(file, tree_name);
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(1);
    plots.plots = unordered_pairs(Tagger().Branch().Variables(), [&](const Obs & variable_1, const Obs & variable_2) {
        return ReadTree(tree, variable_1.name(), variable_2.name(), stage);
    });
    plots.name = tree_name;
    Debug(plots.plots.size(), Tagger().Branch().Variables().size());
    return plots;
}

Plot Plotting::ReadTree(TTree& tree, const std::string& leaf_1, const std::string& leaf_2, Stage stage) const
{
    tree.SetBranchStatus("*", 0);
    std::string branch_name = Tagger().BranchName(stage);
    Debug(branch_name);

    tree.SetBranchStatus(branch_name.c_str(), 1);
    int branch_value = 0;
    tree.SetBranchAddress(branch_name.c_str(), &branch_value);
    Debug(branch_name.c_str());

    std::string size_name = branch_name + "_size";
    Debug(size_name.c_str());
    tree.SetBranchStatus(size_name.c_str(), 1);
    int branch_size = 0;
    tree.SetBranchAddress(size_name.c_str(), &branch_size);

    //FIXME remove this magic number
    size_t max_value = 200;
    std::string leaf_name_1 = branch_name + "." + leaf_1;
    Debug(leaf_name_1.c_str());
    tree.SetBranchStatus(leaf_name_1.c_str(), 1);
    std::vector<float> leaf_values_1(max_value);
    tree.SetBranchAddress(leaf_name_1.c_str(), &leaf_values_1[0]);

    std::string leaf_name_2 = branch_name + "." + leaf_2;
    Debug(leaf_name_2.c_str());
    tree.SetBranchStatus(leaf_name_2.c_str(), 1);
    std::vector<float> leaf_values_2(max_value);
    tree.SetBranchAddress(leaf_name_2.c_str(), &leaf_values_2[0]);

    std::string bdt_name = branch_name + ".Bdt";
    Debug(bdt_name.c_str());
    tree.SetBranchStatus(bdt_name.c_str(), 1);
    std::vector<float> bdt_values(max_value);
    tree.SetBranchAddress(bdt_name.c_str(), &bdt_values[0]);

    Plot plot;
    for (const auto & entry : Range(tree.GetEntries())) {
        Debug(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (const auto & element : Range(branch_size)) {
            Point point;
            point.x = leaf_values_1.at(element);
            point.y = leaf_values_2.at(element);
            point.z = bdt_values.at(element);
            Debug(point.x, point.y, point.z);
            plot.points.emplace_back(point);
        }
    }
    return plot;
}

Plot Plotting::CoreVector(Plot& plot, const std::function<bool (Point&, Point&)>& function) const
{
    // TODO sorting the whole vector if you just want to get rid of the extrem values might not be the fastest solution
    std::sort(plot.points.begin(), plot.points.end(), [&](Point & a, Point & b) {
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


}

