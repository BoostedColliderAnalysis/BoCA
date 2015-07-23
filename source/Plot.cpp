#include "Plot.hh"

#include<fstream>
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
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TGraph.h"
#include "TColor.h"
#include "TExec.h"

#include "exroot/ExRootAnalysis.hh"
#include "Predicate.hh"
#include "Branches.hh"
#define DEBUG
#include "Debug.hh"



namespace analysis {

Result::Result()
{
    steps = 20000;
    events.resize(steps, 0);
    efficiency.resize(steps, 0);
    analysis_event_number.resize(steps, 0);
    bins.resize(steps, 0);
}

std::vector<int> Result::Integral() const
{
    std::vector<int> integrals(steps, 0);
    integrals.at(steps - 1) = bins.at(steps - 1);
    for (int step = steps - 2; step >= 0; --step) integrals.at(step) = integrals.at(step + 1) + bins.at(step);
    return integrals;
}

Results::Results()
{
    significances.resize(Result().steps, 0);
    x_values.resize(Result().steps, 0);
}

void Results::BestBin()
{
    std::vector<float> background_efficiencies(background.size(), 0);
    int counter = 0;
    for (const auto& background_number : Range(background.size())) {
        while (background_efficiencies.at(background_number) == 0 && counter < Result().steps) {
            best_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
            background_efficiencies.at(background_number) = background.at(background_number).efficiency.at(best_bin);
            ++counter;
        }
    }
}

void Results::Significances()
{
    for (const auto& signal_results : signal) {
        for (int step : Range(Result().steps)) {
            float background_events = 0;
            for (const auto& background_result : background) background_events += background_result.events[step];
            if (signal_results.events[step] + background_events > 0) significances.at(step) = signal_results.events[step] / std::sqrt(signal_results.events[step] + background_events);
            else significances.at(step) = 0;
            x_values.at(step) = XValue(step);
        }
    }
}

// Plot::Plot()
// {
// Debug();
// }

Plot::Plot(Tagger& tagger)
{
    Debug("Constructor with tagger");
    tagger_ = &tagger;
    gStyle->SetOptStat("");
}

Results Plot::ExportFile() const
{
    std::string export_file_name = ExportName() + ".root";
    TFile export_file(export_file_name.c_str(), "Recreate");
    Results results;
    std::string signal_file_name = tagger().analysis_name() + "/" + tagger().signal_name() + "Reader.root";
    results.signal = Export(export_file, signal_file_name, tagger().signal_tree_names());
    std::string background_file_name = tagger().analysis_name() + "/" + tagger().background_name() + "Reader.root";
    results.background = Export(export_file, background_file_name, tagger().background_tree_names());
    export_file.Close();
    return results;
}

std::vector<Result> Plot::Export(TFile& export_file, const std::string& file_name, const Strings& treename) const
{
    TFile file(file_name.c_str(), "Read");
    Debug(file_name, treename.size());
    std::vector<Result> results;
    for (const auto& tree_name : treename)
        results.emplace_back(BdtResult(file, tree_name, export_file));
    return results;
}

TLegend Plot::Legend(float x_min, float y_max, float width, float height, const std::string& name) const
{
    TLegend legend(x_min, y_max - height, x_min + width, y_max);
    if (name != "") legend.SetHeader(name.c_str());
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
    return legend;
}

std::string Plot::PlotHistograms(const analysis::Results& results) const
{
    Debug();
    TCanvas canvas;
    std::vector<TH1F> histograms;
    TLegend legend = Legend(0.15, 0.85, 0.2, 0.4);
    float x_min = 0;
    for (const auto& result : results.background) {
        float min = *std::min_element(result.bdt.begin(), result.bdt.end());
        min -= 1;
        if (min < x_min) x_min = min;
    }
    float x_max = 0;
    for (const auto& result : results.signal) {
        float max = *std::max_element(result.bdt.begin(), result.bdt.end());
        max -= 1;
        if (max > x_max) x_max = max;
    }
    float y_max = 0;
    for (const auto& result : results.signal) {
        TH1F histogram(result.info_branch.Name.c_str(), "", 50, FloorToDigits(x_min,1), CeilToDigits(x_max,1));
        for (const float& bdt : result.bdt) histogram.Fill(bdt - 1);
        if (histogram.Integral() != 0)  histogram.Scale(1 / histogram.Integral());
        float max = histogram.GetBinContent(histogram.GetMaximumBin());
        if (max > y_max) y_max = max;
        histograms.emplace_back(histogram);
    }
    for (const auto& result : results.background) {
        TH1F histogram(result.info_branch.Name.c_str(), "", 50, FloorToDigits(x_min,1), CeilToDigits(x_max,1));
        for (const float& bdt : result.bdt) histogram.Fill(bdt - 1);
        if (histogram.Integral() != 0)  histogram.Scale(1 / histogram.Integral());
        SetPlotStyle(histogram, &result - &results.background[0] + 1);
        // histogram.SetLineColor(ColorCode(&result - &results.background[0] + 1));
        // histogram.SetLineStyle(&result - &results.background[0] + 2);
        histograms.emplace_back(histogram);
        float max = histogram.GetBinContent(histogram.GetMaximumBin());
        if (max > y_max)
            y_max = max;
    }
    Strings nice_names;
    for (const auto& result : results.signal)
        nice_names.emplace_back(result.info_branch.Name);
    for (const auto& result : results.background)
        nice_names.emplace_back(result.info_branch.Name);
    for (auto& histogram : histograms) {
        histogram.SetAxisRange(0, CeilToDigits(y_max), "Y");
        histogram.GetXaxis()->SetTitle("BDT");
        histogram.GetYaxis()->SetTitle("N");
        std::string name = nice_names.at(&histogram - &histograms[0]);
        legend.AddEntry(&histogram, name.c_str(), "l");
        histogram.Draw("same");
    }
    legend.Draw();
    const std::string efficiency_file_name = ExportName() + "-Bdt" + ExportFileSuffix();
    canvas.Print(efficiency_file_name.c_str());
    return efficiency_file_name;
}

void Plot::PlotAcceptanceGraph(const Results& results) const
{
    Debug();
    for (const auto& signal_result : results.signal) {
        TCanvas canvas;
        TMultiGraph multi_graph;
        std::vector<TGraph> graphs;
        for (const auto& result : results.background)
            graphs.emplace_back(TGraph(result.steps, &signal_result.efficiency[0], &result.efficiency[0]));
        Strings nice_names;
        for (const auto& result : results.background)
            nice_names.emplace_back(result.info_branch.Name);
        canvas.SetLogy();
        TLegend legend = Legend(0.15, 0.85, 0.2, 0.4, signal_result.info_branch.Name);
        for (auto& graph : graphs) {
            SetPlotStyle(graph, &graph - &graphs[0]);
            // graph.SetLineColor(ColorCode(&graph - &graphs[0]));
            // graph.SetLineStyle(&graph - &graphs[0] + 1);
            multi_graph.Add(&graph);
            std::string name = nice_names.at(&graph - &graphs[0]);
            legend.AddEntry(&graph, name.c_str(), "l");
        }
        SetMultiGraph(multi_graph);
        legend.Draw();
        std::string efficiency_file_name = ExportName() + "-Acceptance" + ExportFileSuffix();
        canvas.Print(efficiency_file_name.c_str());
    }
}

void Plot::SetPlotStyle(TAttLine& att_line, int index) const
{
    att_line.SetLineColor(ColorCode(index));
    att_line.SetLineStyle(index + 1);
}

void Plot::SetMultiGraph(TMultiGraph& multi_graph) const
{
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(0.2, 0.9);
    multi_graph.GetXaxis()->SetTitle("Signal acceptance");
    multi_graph.GetYaxis()->SetTitle("Background acceptance");
    multi_graph.SetMaximum(1);
    multi_graph.SetMinimum(0.001);
    // multi_graph.SetMinimum(0.01);
}

void Plot::TaggingEfficiency() const
{
    Debug();
    Results results = ExportFile();
    PlotHistograms(results);
    PlotAcceptanceGraph(results);
}

void Plot::OptimalSignificance() const
{
    Debug();
    std::stringstream table_header;
    table_header << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rlll}\n\\toprule\n";
    Results results = ExportFile();
    results.Significances();
    results.BestBin();
    int best_bin = results.best_bin;
    std::vector<float> significances = results.significances;
    std::vector<float> x_values = results.x_values;
    std::stringstream table;
    table << table_header.str();
    table << " Mass\n" << " & " << results.signal.front().info_branch.Mass;
    table << "\n \\\\ \\midrule\n";
    table << " BDT-cut\n" << " & " << results.XValue(best_bin);
    table << "\n \\\\ $p$-value\n & " << significances.at(best_bin);
    table << "\n \\\\ Efficiency\n & " << results.signal.front().efficiency.at(best_bin) << "\n & " << results.signal.front().analysis_event_number.at(best_bin) << "\n & " << results.signal.front().event_sum() << "\n";
    for (const auto& background : results.background)
        table << " \\\\ \\verb|" << tagger().background_tree_names().at(&background - &results.background[0]) << "|\n & " << background.efficiency.at(best_bin) << "\n & " << background.analysis_event_number.at(best_bin) << "\n & " << background.event_sum() << "\n";
    std::string efficiency_file_name = PlotEfficiencyGraph(results, x_values, best_bin);
    std::string significance_file_name = PlotSignificanceGraph(results, x_values, significances, best_bin);
    std::string bdt_file_name = PlotHistograms(results);
    std::stringstream table_footer;
    table_footer << " \\\\ \\bottomrule\n\\end{tabular}\n\\caption{Significance and efficiencies.}\n\\end{table}\n";
    table << table_footer.str();
    std::ofstream latex_file;
    LatexHeader(latex_file);
    latex_file << table.str();
    // latex_file << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << bdt_file_name << "}}\n\\caption{BDT Distribution.}\n\\end{figure}\n";
    // latex_file << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << efficiency_file_name << "}}\n\\caption{Efficiency.}\n\\end{figure}\n";
    // latex_file << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << significance_file_name << "}}\n\\caption{Significance.}\n\\end{figure}\n";
    latex_file << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" << bdt_file_name << "}\n\\caption{BDT Distribution.}\n\\end{figure}\n";
    latex_file << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" << efficiency_file_name << "}\n\\caption{Efficiency.}\n\\end{figure}\n";
    latex_file << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" << significance_file_name << "}\n\\caption{Significance.}\n\\end{figure}\n";
    LatexFooter(latex_file);
}

std::string Plot::PlotEfficiencyGraph(const Results& results, const std::vector<float>& x_values, int best_bin) const
{
    Result signal_results = results.signal.front();
    TCanvas canvas;
    canvas.SetLogy();
    TMultiGraph multi_graph;
    std::vector<TGraph> rejection_graphs;
    for (const auto& background_result : results.background)
        rejection_graphs.emplace_back(TGraph(background_result.steps, &x_values[0], &background_result.efficiency[0]));
    for (auto& rejection_graph : rejection_graphs)
        multi_graph.Add(&rejection_graph);
    TGraph graph(signal_results.steps, &x_values[0], &signal_results.efficiency[0]);
    graph.SetLineColor(kRed);
    multi_graph.Add(&graph);
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(-1,1);
    TLine line(results.XValue(best_bin), multi_graph.GetYaxis()->GetXmin(), results.XValue(best_bin), multi_graph.GetYaxis()->GetXmax());
    line.SetLineStyle(2);
    line.Draw();
    const std::string file_name = ExportName() + "-Efficiency" + ExportFileSuffix();
    canvas.Print(file_name.c_str());
    return file_name;
}

std::string Plot::PlotSignificanceGraph(const Results& results, const std::vector<float>& x_values, const std::vector<float>& significances, int best_bin) const
{
    Result signal_results = results.signal.front();
    TCanvas canvas;
    TGraph graph(signal_results.steps, &x_values[0], &significances[0]);
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(-1,1);
    canvas.Update();
    TLine line(results.XValue(best_bin), gPad->GetUymin(), results.XValue(best_bin), gPad->GetUymax());
    line.SetLineStyle(2);
    line.Draw();
    const std::string file_name = ExportName() + "-Significance" + ExportFileSuffix();
    canvas.Print(file_name.c_str());
    return file_name;
}


Result Plot::BdtResult(TFile& file, const std::string& tree_name, TFile& export_file) const
{
    Debug(tree_name);
    const float Luminosity = 3000; // 3000 fb-1
    Debug(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Result result = BdtDistribution(tree_reader, tree_name, export_file);
    result.info_branch = InfoBranch(file, tree_name);
    std::vector<int> integral = result.Integral();
    for (const auto& step : Range(result.steps)) {
        result.events[step] = float(integral[step]) / float(result.info_branch.EventNumber) * result.info_branch.Crosssection * Luminosity;
        result.efficiency[step] = float(integral[step]) / float(result.info_branch.EventNumber);
        result.analysis_event_number[step] = integral[step];
        Debug(result.efficiency[step], result.events[step]);
    }
    return result;
}

Result Plot::BdtDistribution(exroot::TreeReader& tree_reader, const std::string& tree_name, TFile& export_file) const
{
    Debug(tagger().branch_name());
    std::string branch_name = tagger().branch_name() + "Reader";
    Result result;
    TClonesArray& event_clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& result_branch = *tree_writer.NewBranch(branch_name.c_str(), ResultBranch::Class());
    long entries = 0;
    for (int event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (const auto& entry : Range(event_clones_array.GetEntriesFast())) {
            float bdt_value = tagger().ReadBdt(event_clones_array, entry);
            result.bdt.emplace_back(bdt_value);
            Check(bdt_value > 0 && bdt_value < 2, "Bdt Value" , bdt_value);
            static_cast<ResultBranch&>(*result_branch.NewEntry()).Bdt = bdt_value;
            int bin = std::floor(bdt_value * result.steps / 2) - 1;
            if (bin == -1) {
                bin = 0;    // FIXME clean this up
            }
            ++result.bins.at(bin);
            ++entries;
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    result.set_event_sum(entries);
    tree_writer.Write();
    return result;
}

InfoBranch Plot::InfoBranch(TFile& file, const std::string& tree_name) const
{
    Debug(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Debug(tree_name, tagger().weight_branch_name());
    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().weight_branch_name().c_str());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    return dynamic_cast<analysis::InfoBranch &>(*clones_array.At(clones_array.GetEntriesFast() - 1));
}


void Plot::LatexHeader(std::ofstream& latex_file) const
{
    Debug();
    const std::string file_name = tagger().analysis_name() + "/" + tagger().analysis_name() + ".tex";
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


void Plot::LatexFooter(std::ofstream& latex_file) const
{
    Debug();
    latex_file << "\n\\end{document}\n";
    latex_file.close();
}

// float Plot::GetRatio(const float Nominator, const float Denummertor) const
// {
// float Ratio;
// if (Denummertor > 0) {
// Ratio = float(Nominator) / Denummertor;
// } else {
// Ratio = 0;
// }
// return Ratio;
// }
//
//
// float Plot::GetScaling(const float events, int Particles) const
// {
// Debug("Scaling");
// float Scaling;
// if (Particles == 0) {
// Scaling = 0;
// } else {
// Scaling = events / Particles;
// }
// return Scaling;
// }
//
// float Plot::GetLuminosity(const float Number) const
// {
// Debug("Luminosity");
// float Luminosity = Number / CrosssectionScaled;
// return Luminosity;
// }
//
// float Plot::GetLuminosityError(const float Number) const
// {
// Debug("Luminosity Error");
// float LuminosityError = GetError(Number) / CrosssectionScaled + Number / CrosssectionNorm * LuminosityScalingError + GetLuminosity(Number) * CrosssectionNormRelError;
// return LuminosityError;
// }
//
// float Plot::GetError(const float Value) const
// {
// Debug("Error");
// float Error;
// if (Value == 0) {
// Error = 0;
// } else {
// Error = 1 / sqrt(Value);
// }
// return Error;
// }

// float Plot::RoundToDigits(const float Value) const
// {
// return RoundToDigits(Value, 3);
// }
//
// float Plot::RoundError(const float Value) const
// {
// return RoundToDigits(Value, 2);
// }
//
//
// float Plot::RoundToDigits(const float Value, int Digits) const
// {
// Debug();
// if (Value == 0 || Value != Value) {
// return 0;
// } else {
// const float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
// return (round(Value * Factor) / Factor);
// }
// }
//
// float Plot::RoundToError(const float Value, const float Error) const
// {
// Debug();
// if (Value == 0) {
// return 0;
// } else {
// const float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));
// return (round(Value * Factor) / Factor);
// }
// }


float Plot::FloorToDigits(const float value, int digits) const
{
  if (value == 0 || value != value) {
    return 0;
  } else {
    const float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
    return std::floor(value * factor) / factor;
  }
}

float Plot::CeilToDigits(const float value, int digits) const
{
  if (value == 0 || value != value) {
    return 0;
  } else {
    const float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
    return std::ceil(value * factor) / factor;
  }
}

int Plot::ColorCode(int number) const
{
    switch (number) {
    case 0 :
        return kBlack;
    case 1 :
        return kRed;
    case 2 :
        return kBlue;
    case 3 :
        return kTeal - 5;
    case 4 :
        return kPink + 1;
    case 5 :
        return kViolet;
    case 6 :
        return kOrange;
    case 7 :
        return kAzure;
    case 8 :
        return kSpring - 5;
    case 9 :
        return kGreen + 3;
    case 10 :
        return kCyan - 3;
    case 11 :
        return kMagenta - 3;
    case 12 :
        return kYellow - 9;
    case 13 :
        return kGray;
    default :
        return kBlack;
    }
}

std::string Plot::ExportName() const
{
    return tagger().analysis_name() + "/" + tagger().export_name();
}

long Result::event_sum() const
{
    // return info_branch.EventNumber;
    return event_sum_;
}
void Result::set_event_sum(const long event_sum)
{
    event_sum_ = event_sum;
}

void Plot::RunPlots() const
{
    std::string signal_file_name = tagger().analysis_name() + "/" + tagger().signal_name() + "Reader.root";
    Debug(signal_file_name, tagger().signal_tree_names().size());
    std::vector<Plots> signals = Import(signal_file_name, tagger().signal_tree_names());
    std::string background_file_name = tagger().analysis_name() + "/" + tagger().background_name() + "Reader.root";
    Debug(background_file_name, tagger().background_tree_names().size());
    std::vector<Plots> backgrounds = Import(background_file_name, tagger().background_tree_names());
    Plots bg = backgrounds.front();
    if (backgrounds.size() > 1) {
        bg = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), bg, [](Plots & sum, const Plots & elem) {
            for (const auto& plot : elem.plots)
                sum.plots.at(&plot - &elem.plots[0]).points = Join(sum.plots.at(&plot - &elem.plots[0]).points, plot.points);
            return sum;
        });
        bg.name = "background";
    }
    for (auto& signal : signals)
        DoPlot(signal, bg);
}

void Plot::DoPlot(Plots& signals, Plots& backgrounds) const
{
    std::vector<std::pair<std::string, std::string>> nice_names;
    unordered_pairs(tagger().branch().Variables(), nice_names, [&](const Obs & variable_1, const Obs & variable_2) {
        return std::make_pair(variable_1.nice_name(), variable_2.nice_name());
    });
    std::vector<std::pair<std::string, std::string>> names;
    unordered_pairs(tagger().branch().Variables(), names, [&](const Obs & variable_1, const Obs & variable_2) {
        return std::make_pair(variable_1.name(), variable_2.name());
    });
    for (auto& signal : signals.plots) {
        int index = &signal - &signals.plots[0];
        auto background = backgrounds.plots.at(index);
        signal.name_x = names.at(index).first;
        signal.name_y = names.at(index).second;
        signal.name = signals.info_branch.Name;
        signal.nice_name_x = nice_names.at(index).first;
        signal.nice_name_y = nice_names.at(index).second;
        signal.tree_name = signals.name;
        background.nice_name_x = nice_names.at(index).first;
        background.nice_name_y = nice_names.at(index).second;
        background.name = backgrounds.info_branch.Name;
        background.name_x = names.at(index).first;
        background.name_y = names.at(index).second;
        background.tree_name = backgrounds.name;
        Plotting(signal, background);
    }
}

void Plot::Plotting(const Plot2d& signal, const Plot2d& background) const
{
    Plot2d signal_x = CoreVector(signal, [](Point2d & a, Point2d & b) {
        return a.x < b.x;
    });
    Plot2d signal_y = CoreVector(signal, [](Point2d & a, Point2d & b) {
        return a.y < b.y;
    });
    Plot2d background_x = CoreVector(background, [](Point2d & a, Point2d & b) {
        return a.x < b.x;
    });
    Plot2d background_y = CoreVector(background, [](Point2d & a, Point2d & b) {
        return a.y < b.y;
    });
    float x_min = std::min(signal_x.points.front().x, background_x.points.front().x);
    float x_max = std::max(signal_x.points.back().x, background_x.points.back().x);
    float y_min = std::min(signal_y.points.front().y, background_y.points.front().y);
    float y_max = std::max(signal_y.points.back().y, background_y.points.back().y);
    PlotHistogram(signal, background, x_min, x_max, y_min, y_max);
    PlotProfile(signal, background, x_min, x_max, y_min, y_max);
}

void Plot::PlotHistogram(const Plot2d& signal, const Plot2d& background, const float x_min, const float x_max, const float y_min, const float y_max)const
{
    TCanvas canvas;
    canvas.SetBottomMargin(0.15);
    TLegend legend = Legend(0.3, 0.1, 0.3, 0.1);
    legend.SetNColumns(2);
    legend.SetColumnSeparation(0.2);
    int bin_number = 20;
    TExec exec_1;
    TH2F background_histogram("", tagger().NiceName().c_str(), bin_number, x_min, x_max, bin_number, y_min, y_max);
    SetHistogram(background_histogram, background, kRed, exec_1);
    legend.AddEntry(&background_histogram, background.name.c_str(), "l");
    TExec exec_2;
    TH2F signal_histogram("", tagger().NiceName().c_str(), bin_number, x_min, x_max, bin_number, y_min, y_max);
    SetHistogram(signal_histogram, signal, kBlue, exec_2);
    legend.AddEntry(&signal_histogram, signal.name.c_str(), "l");
    legend.Draw();
    mkdir(ExportName().c_str(), 0700);
    std::string file_name = ExportName() + "/" + "Hist-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y + ExportFileSuffix();
    canvas.Print(file_name.c_str());
}

void Plot::PlotProfile(const Plot2d& signal, const Plot2d& background, const float x_min, const float x_max, const float y_min, const float y_max)const
{
    TCanvas canvas;
    canvas.SetRightMargin(0.15);
    int bin_number = 30;
    TProfile2D test("", tagger().NiceName().c_str(), bin_number, x_min, x_max, bin_number, y_min, y_max);
    SetProfile(test, signal, background);
    mkdir(ExportName().c_str(), 0700);
    std::string file_name = ExportName() + "/" + "Prof-" + background.tree_name + "-" + signal.name_x + "-" + signal.name_y + ExportFileSuffix();
    canvas.Print(file_name.c_str());
}

void Plot::SetHistogram(TH2& histogram, const Plot2d& plot, const EColor color, TExec& exec) const
{
    std::string options = "cont1 same";
    histogram.Draw(options.c_str());
    for (const auto& point : plot.points)
        histogram.Fill(point.x, point.y);
    histogram.SetXTitle(plot.nice_name_x.c_str());
    histogram.SetYTitle(plot.nice_name_y.c_str());
    histogram.SetContour(20);
    switch (color) {
    case kRed :
        // FIXME why do these function have to be reversed?
        exec.SetAction("analysis::Color().Blue();");
        break;
    case kBlue :
        exec.SetAction("analysis::Color().Red();");
        break;
    default:
        Error("unsupported color");
    }
    exec.Draw();
    histogram.SetMarkerColor(color);
    histogram.SetLineColor(color);
    histogram.Draw(options.c_str());
}


void Plot::SetProfile(TProfile2D& histogram, const Plot2d& signal, const Plot2d& background) const
{
    float max = (*std::max_element(signal.points.begin(), signal.points.end(), [](Point2d  a, Point2d  b) {
        return a.z < b.z;
    })).z;
    float min = (*std::min_element(background.points.begin(), background.points.end(), [](Point2d  a, Point2d  b) {
        return a.z < b.z;
    })).z;
    for (const auto& point : signal.points)
        histogram.Fill(point.x, point.y, point.z);
    for (const auto& point : background.points)
        histogram.Fill(point.x, point.y, point.z);
    Color().Heat();
    histogram.SetXTitle(signal.nice_name_x.c_str());
    histogram.SetYTitle(signal.nice_name_y.c_str());
    histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.SetMarkerColor(kRed);
    histogram.SetLineColor(kRed);
    histogram.Draw("colz");
}

std::vector<Plots> Plot::Import(const std::string& file_name, const Strings& treename) const
{
    TFile file(file_name.c_str(), "Read");
    Debug(file_name, treename.size());
    std::vector<Plots> results;
    for (const auto& tree_name : treename)
        results.emplace_back(PlotResult(file, tree_name));
    return results;
}

Plots Plot::PlotResult(TFile& file, const std::string& tree_name) const
{
    Debug(tree_name);
    Plots plots;
    plots.info_branch = InfoBranch(file, tree_name);
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(1);
    unordered_pairs(tagger().branch().Variables(), plots.plots, [&](const Obs & variable_1, const Obs & variable_2) {
        return ReadTree(tree, variable_1.name(), variable_2.name());
    });
    plots.name = tree_name;
    Debug(plots.plots.size(), tagger().branch().Variables().size());
    return plots;
}

Plot2d Plot::ReadTree(TTree& tree, const std::string& leaf_1, const std::string& leaf_2) const
{
    tree.SetBranchStatus("*", 0);
    std::string branch_name = tagger().branch_name() + "Reader";
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
    int branch_size_max = 200; // TODO is there a cleaner way?
    std::string leaf_name_1 = branch_name + "." + leaf_1;
    Debug(leaf_name_1.c_str());
    tree.SetBranchStatus(leaf_name_1.c_str(), 1);
    float leaf_values_1[branch_size_max];
    tree.SetBranchAddress(leaf_name_1.c_str(), leaf_values_1);
    std::string leaf_name_2 = branch_name + "." + leaf_2;
    Debug(leaf_name_2.c_str());
    tree.SetBranchStatus(leaf_name_2.c_str(), 1);
    float leaf_values_2[branch_size_max];
    tree.SetBranchAddress(leaf_name_2.c_str(), leaf_values_2);
    std::string bdt_name = branch_name + ".Bdt";
    Debug(bdt_name.c_str());
    tree.SetBranchStatus(bdt_name.c_str(), 1);
    float bdt_values[branch_size_max];
    tree.SetBranchAddress(bdt_name.c_str(), bdt_values);
    Plot2d points;
    for (const auto& entry : Range(tree.GetEntries())) {
        Debug(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (const auto& element : Range(branch_size)) {
            Point2d point;
            point.x = leaf_values_1[element];
            point.y = leaf_values_2[element];
            point.z = bdt_values[element];
            Debug(point.x, point.y);
            points.points.emplace_back(point);
        }
    }
    return points;
}

Plot2d Plot::CoreVector(const Plot2d& points, std::function<bool (Point2d&, Point2d&)> function) const
{
    Plot2d plot = points;
    // TODO sorting the whole vector if you just want to get rid of the extrem values might not be the fastest solution
    std::sort(plot.points.begin(), plot.points.end(), [&](Point2d & a, Point2d & b) {
        return function(a, b);
    });
    int cut_off = plot.points.size() / 25;
    plot.points.erase(plot.points.begin(), plot.points.begin() + cut_off);
    plot.points.erase(plot.points.end() - cut_off, plot.points.end());
    return plot;
}

}
