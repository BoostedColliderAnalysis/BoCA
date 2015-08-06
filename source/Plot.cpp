#include "Plot.hh"

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

#include "exroot/ExRootAnalysis.hh"
#include "Vector.hh"
#include "Types.hh"
#include "Branches.hh"
// #define DEBUG
#include "Debug.hh"

namespace analysis
{

Result::Result()
{
//     steps = 20000;
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
    significances.resize(Result::steps, 0);
    x_values.resize(Result::steps, 0);
}

void Results::BestBin()
{
    std::vector<float> efficiencies(background.size(), 0);
    int counter = 0;
    for (const auto & number : Range(background.size())) {
        while (efficiencies.at(number) == 0 && counter < Result::steps) {
            best_bin = std::distance(significances.begin(), std::max_element(std::begin(significances), std::end(significances) - counter));
            efficiencies.at(number) = background.at(number).efficiency.at(best_bin);
            ++counter;
        }
    }
}

void Results::Significances()
{
        for (const int step : Range(Result::steps)) {

          float signal_events = 0;
            for (const auto & signal_results : signal) signal_events += signal_results.events[step];

          float background_events = 0;
            for (const auto & background_result : background) background_events += background_result.events[step];

            if (signal_events + background_events > 0) significances.at(step) = signal_events / std::sqrt(signal_events + background_events);
            else significances.at(step) = 0;
            x_values.at(step) = XValue(step);
        }
}

Plot::Plot(analysis::Tagger& tagger)
{
    Debug();
    tagger_ = &tagger;
    gStyle->SetOptStat("");
}

void Plot::TaggingEfficiency() const
{
    Debug();
    Results results = ReadBdtFiles();
    results.ExtremeXValues();
    PlotHistograms(results);
    PlotAcceptanceGraph(results);
}

void Plot::OptimalSignificance() const
{
    Debug();
    Results results = ReadBdtFiles();
    results.Significances();
    results.BestBin();
    results.ExtremeXValues();
    std::string efficiency_file_name = PlotEfficiencyGraph(results);
    std::string significance_file_name = PlotSignificanceGraph(results);
    std::string bdt_file_name = PlotHistograms(results);
    std::ofstream latex_file;
    LatexHeader(latex_file);
    latex_file << Table(results);
    latex_file << IncludeGraphic(bdt_file_name,"BDT Distribution");
    latex_file << IncludeGraphic(efficiency_file_name, "Efficiency");
    latex_file << IncludeGraphic(significance_file_name,"Significance");
    LatexFooter(latex_file);
}

Results Plot::ReadBdtFiles() const
{
    TFile export_file(Tagger().ExportFileName().c_str(), "Recreate");
    Results results;
    results.signal = ReadBdtFile(export_file, Tag::signal);
    results.background = ReadBdtFile(export_file, Tag::background);
    export_file.Close();
    return results;
}

std::vector<Result> Plot::ReadBdtFile(TFile& export_file, Tag tag) const
{
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    Debug(file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<Result> results;
    for (const auto & tree_name : Tagger().TreeNames(tag)) results.emplace_back(BdtResult(file, tree_name, export_file));
    return results;
}

Result Plot::BdtResult(TFile& file, const std::string& tree_name, TFile& export_file) const
{
  Debug(tree_name);
  exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
  Result result = BdtDistribution(tree_reader, tree_name, export_file);
  result.info_branch = InfoBranch(file, tree_name);
  std::vector<int> integral = result.Integral();
  for (const auto & step : Range(result.steps)) {
    result.events.at(step) = float(integral.at(step)) / float(result.info_branch.EventNumber) * result.info_branch.Crosssection * DetectorGeometry::Luminosity();
    result.efficiency.at(step) = float(integral.at(step)) / float(result.info_branch.EventNumber);
    result.analysis_event_number.at(step) = integral.at(step);
    Debug(result.efficiency.at(step), result.events.at(step));
  }
  return result;
}

Result Plot::BdtDistribution(exroot::TreeReader& tree_reader, const std::string& tree_name, TFile& export_file) const
{
  std::string branch_name = Tagger().BranchName(Stage::reader);
  Debug(branch_name);
  Result result;
  TClonesArray& event_clones_array = *tree_reader.UseBranch(branch_name.c_str());
  exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
  exroot::TreeBranch& result_branch = *tree_writer.NewBranch(branch_name.c_str(), ResultBranch::Class());
  long entries = 0;
  for (const auto & event_number : Range(tree_reader.GetEntries())) {
    tree_reader.ReadEntry(event_number);
    for (const auto & entry : Range(event_clones_array.GetEntriesFast())) {
      float bdt_value = Tagger().ReadBdt(event_clones_array, entry);
      result.bdt.emplace_back(bdt_value);
      Check(bdt_value >= -1 && bdt_value <= 1, bdt_value);
      static_cast<ResultBranch &>(*result_branch.NewEntry()).Bdt = bdt_value;
      ++result.bins.at(Results().XBin(bdt_value));
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
  Debug(tree_name, Tagger().WeightBranchName());
  TClonesArray& clones_array = *tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
  tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
  return static_cast<analysis::InfoBranch&>(*clones_array.At(clones_array.GetEntriesFast() - 1));
}

std::string Plot::PlotHistograms(analysis::Results& results) const
{
  Debug();
  TCanvas canvas;
  std::vector<TH1F> histograms;
  Strings nice_names;
  for (const auto & result : results.signal) {
    histograms.emplace_back(Histogram(result, results.max, results.min, &result - &results.signal[0]));
    nice_names.emplace_back(result.info_branch.Name);
  }
  for (const auto & result : results.background) {
    histograms.emplace_back(Histogram(result, results.max, results.min, &result - &results.background[0] + results.signal.size()));
    nice_names.emplace_back(result.info_branch.Name);
  }
  TLegend legend = Legend(0.15, 0.85, 0.2, 0.4);
  for (auto & histogram : histograms) SetHistogram(histogram,legend, nice_names.at(&histogram - &histograms[0]), results.max);
  legend.Draw();
  std::string efficiency_file_name = Tagger().ExportFolderName() + "-Bdt" + ExportFileSuffix();
  canvas.Print(efficiency_file_name.c_str());
  return efficiency_file_name;
}

TH1F Plot::Histogram(const Result& result, Point& max, Point& min, int index) const
{
  TH1F histogram(result.info_branch.Name.c_str(), "", 50, FloorToDigits(min.x, 1), CeilToDigits(max.x, 1));
  for (const auto & bdt : result.bdt) histogram.Fill(bdt);
  if (histogram.Integral() != 0)  histogram.Scale(1. / histogram.Integral());
  SetPlotStyle(histogram, index);
  float max_0 = histogram.GetBinContent(histogram.GetMaximumBin());
  if (max_0 > max.y) max.y = max_0;
  return histogram;
}

void Plot::SetHistogram(TH1F& histogram, TLegend& legend, std::string& nice_name, const analysis::Point& max) const {
  histogram.SetAxisRange(0, CeilToDigits(max.y), "Y");
  histogram.GetXaxis()->SetTitle("BDT");
  histogram.GetYaxis()->SetTitle("N");
  legend.AddEntry(&histogram, nice_name.c_str(), "l");
  histogram.Draw("same");
}

TLegend Plot::Legend(float x_min, float y_max, float width, float height, const std::string& name) const
{
  TLegend legend(x_min, y_max - height, x_min + width, y_max);
  if (name != "") legend.SetHeader(name.c_str());
  legend.SetBorderSize(0);
  legend.SetFillStyle(0);
  return legend;
}

std::string Plot::PlotEfficiencyGraph(const Results& results) const
{
    TCanvas canvas;
    canvas.SetLogy();
    TMultiGraph multi_graph;
    TLegend legend = Legend(0.15, 0.65, 0.2, 0.4);
    Strings nice_names;
    std::vector<TGraph> graphs;
    for (const auto & background : results.background){
      nice_names.emplace_back(background.info_branch.Name);
      graphs.emplace_back(TGraph(background.steps, &results.x_values[0], &background.efficiency[0]));
    }

    for (const auto & signal : results.signal) {
      nice_names.emplace_back(signal.info_branch.Name);
      graphs.emplace_back(TGraph(signal.steps, &results.x_values[0], &signal.efficiency[0]));
    }

    for (auto & graph : graphs) {
      SetPlotStyle(graph, &graph - &graphs[0]);
      multi_graph.Add(&graph);
      std::string name = nice_names.at(&graph - &graphs[0]);
      legend.AddEntry(&graph, name.c_str(), "l");
    }
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    legend.Draw();
    TLine line(results.BestXValue(), multi_graph.GetYaxis()->GetXmin(), results.BestXValue(), multi_graph.GetYaxis()->GetXmax());
    line.SetLineStyle(2);
    line.Draw();
    std::string file_name = Tagger().ExportFolderName() + "-Efficiency" + ExportFileSuffix();
    canvas.Print(file_name.c_str());
    return file_name;
}

void Plot::PlotAcceptanceGraph(const Results& results) const
{
  Debug();
  for (const auto & signal_result : results.signal) {
    TCanvas canvas;
    TMultiGraph multi_graph;
    std::vector<TGraph> graphs;
    for (const auto & result : results.background)
      graphs.emplace_back(TGraph(result.steps, &signal_result.efficiency[0], &result.efficiency[0]));
    Strings nice_names;
    for (const auto & result : results.background)
      nice_names.emplace_back(result.info_branch.Name);
    canvas.SetLogy();
    TLegend legend = Legend(0.15, 0.85, 0.2, 0.4, signal_result.info_branch.Name);
    for (auto & graph : graphs) {
      SetPlotStyle(graph, &graph - &graphs[0]);
      multi_graph.Add(&graph);
      std::string name = nice_names.at(&graph - &graphs[0]);
      legend.AddEntry(&graph, name.c_str(), "l");
    }
    SetMultiGraph(multi_graph);
    legend.Draw();
    std::string efficiency_file_name = Tagger().ExportFolderName() + "-Acceptance" + ExportFileSuffix();
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

std::string Plot::PlotSignificanceGraph(const Results& results) const
{
    TCanvas canvas;
    TGraph graph(Result::steps, &results.x_values[0], &results.significances[0]);
    graph.SetTitle("");
    graph.Draw("al");
    graph.GetXaxis()->SetLimits(results.min.x, results.max.x);
    canvas.Update();
    TLine line(results.BestXValue(), gPad->GetUymin(), results.BestXValue(), gPad->GetUymax());
    line.SetLineStyle(2);
    line.Draw();
    std::string file_name = Tagger().ExportFolderName() + "-Significance" + ExportFileSuffix();
    canvas.Print(file_name.c_str());
    return file_name;
}

void Plot::LatexHeader(std::ofstream& latex_file) const
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

std::string Plot::Table(const Results& results) const {
  std::stringstream table_header;
  table_header << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rlll}\n\\toprule\n";
  std::stringstream table;
  table << table_header.str();
  table << " Mass\n" << " & " << results.signal.front().info_branch.Mass;
  table << "\n \\\\ \\midrule\n";
  table << " BDT-cut\n" << " & " << results.BestXValue();
  table << "\n \\\\ $p$-value\n & " << results.significances.at(results.best_bin);
  table << "\n \\\\ Efficiency\n & " << results.signal.front().efficiency.at(results.best_bin) << "\n & " << results.signal.front().analysis_event_number.at(results.best_bin) << "\n & " << results.signal.front().event_sum() << "\n";
  for (const auto & background : results.background)
    table << " \\\\ \\verb|" << Tagger().TreeNames(Tag::background).at(&background - &results.background[0]) << "|\n & " << background.efficiency.at(results.best_bin) << "\n & " << background.analysis_event_number.at(results.best_bin) << "\n & " << background.event_sum() << "\n";
  std::stringstream table_footer;
  table_footer << " \\\\ \\bottomrule\n\\end{tabular}\n\\caption{Significance and efficiencies.}\n\\end{table}\n";
  table << table_footer.str();
  return table.str();
}

std::string Plot::IncludeGraphic(std::string &file_name, std::string caption) const{
    return "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" + file_name + "}\n\\caption{" + caption + "}\n\\end{figure}\n";
    return "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" + file_name + "}}\n\\caption{" + caption + ".}\n\\end{figure}\n";
}

void Plot::LatexFooter(std::ofstream& latex_file) const
{
    Debug();
    latex_file << "\n\\end{document}\n";
    latex_file.close();
}

// float Plot::GetRatio(float Nominator, float Denummertor) const
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
// float Plot::GetScaling(float events, int Particles) const
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
// float Plot::GetLuminosity(float Number) const
// {
// Debug("Luminosity");
// float Luminosity = Number / CrosssectionScaled;
// return Luminosity;
// }
//
// float Plot::GetLuminosityError(float Number) const
// {
// Debug("Luminosity Error");
// float LuminosityError = GetError(Number) / CrosssectionScaled + Number / CrosssectionNorm * LuminosityScalingError + GetLuminosity(Number) * CrosssectionNormRelError;
// return LuminosityError;
// }
//
// float Plot::GetError(float Value) const
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

// float Plot::RoundToDigits(float Value) const
// {
// return RoundToDigits(Value, 3);
// }
//
// float Plot::RoundError(float Value) const
// {
// return RoundToDigits(Value, 2);
// }
//
//
// float Plot::RoundToDigits(float Value, int Digits) const
// {
// Debug();
// if (Value == 0 || Value != Value) {
// return 0;
// } else {
// float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
// return (round(Value * Factor) / Factor);
// }
// }
//
// float Plot::RoundToError(float Value, float Error) const
// {
// Debug();
// if (Value == 0) {
// return 0;
// } else {
// float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));
// return (round(Value * Factor) / Factor);
// }
// }


float Plot::FloorToDigits(float value, int digits) const
{
    if (value == 0 || value != value) {
        return 0;
    } else {
        float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
        return std::floor(value * factor) / factor;
    }
}

float Plot::CeilToDigits(float value, int digits) const
{
    if (value == 0 || value != value) {
        return 0;
    } else {
        float factor = std::pow(10.0, digits - std::ceil(std::log10(std::abs(value))));
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

long Result::event_sum() const
{
    // return info_branch.EventNumber;
    return event_sum_;
}
void Result::set_event_sum(long event_sum)
{
    event_sum_ = event_sum;
}

void Plot::RunPlots() const
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

void Plot::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    std::vector<std::pair<std::string, std::string>> nice_names = unordered_pairs(Tagger().Branch().Variables(), [&](const Obs & variable_1, const Obs & variable_2) {
        return std::make_pair(variable_1.nice_name(), variable_2.nice_name());
    });
    std::vector<std::pair<std::string, std::string>> names = unordered_pairs(Tagger().Branch().Variables(), [&](const Obs & variable_1, const Obs & variable_2) {
        return std::make_pair(variable_1.name(), variable_2.name());
    });
    for (auto & signal : signals.plots) {
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
        Plotting(signal, background, stage);
    }
}

void Plot::Plotting(const Plot3d& signal, const Plot3d& background, Stage stage) const
{
    Plot3d signal_x = CoreVector(signal, [](Point & a, Point & b) {
        return a.x < b.x;
    });
    Plot3d signal_y = CoreVector(signal, [](Point & a, Point & b) {
        return a.y < b.y;
    });
    Plot3d background_x = CoreVector(background, [](Point & a, Point & b) {
        return a.x < b.x;
    });
    Plot3d background_y = CoreVector(background, [](Point & a, Point & b) {
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

void Plot::PlotHistogram(const Plot3d& signal, const Plot3d& background, const Point& min, const Point& max) const
{
    TCanvas canvas;
    canvas.SetBottomMargin(0.15);
    TLegend legend = Legend(0.3, 0.1, 0.3, 0.1);
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

void Plot::PlotProfile(const Plot3d& signal, const Plot3d& background, const Point& min, const Point& max) const
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

void Plot::SetHistogram(TH2& histogram, const Plot3d& plot, EColor color, TExec& exec) const
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


void Plot::SetProfile(TProfile2D& histogram, const Plot3d& signal, const Plot3d& background) const
{
    float max = (*std::max_element(signal.points.begin(), signal.points.end(), [](Point  a, Point  b) {
        return a.z < b.z;
    })).z;
    float min = (*std::min_element(background.points.begin(), background.points.end(), [](Point  a, Point  b) {
        return a.z < b.z;
    })).z;
    for (const auto & point : signal.points)
        histogram.Fill(point.x, point.y, point.z);
    for (const auto & point : background.points)
        histogram.Fill(point.x, point.y, point.z);
    Color().Heat();
    CommmonHist(histogram, signal, kRed);
    histogram.SetZTitle("BDT");
    histogram.SetMaximum(max);
    histogram.SetMinimum(min);
    histogram.SetContour(30);
    histogram.Draw("colz");
}

void Plot::CommmonHist(TH2& histogram, const Plot3d& plot, EColor color) const {
  histogram.SetXTitle(plot.nice_name_x.c_str());
  histogram.SetYTitle(plot.nice_name_y.c_str());
  histogram.SetMarkerColor(color);
  histogram.SetLineColor(color);
}

std::vector<Plots> Plot::Import(Stage stage, Tag tag) const
{
    Debug(Tagger().FileName(stage, tag), Tagger().TreeNames(tag).size());
    TFile file(Tagger().FileName(stage, tag).c_str(), "Read");
    std::vector<Plots> results;
    for (const auto & tree_name : Tagger().TreeNames(tag)) results.emplace_back(PlotResult(file, tree_name, stage));
    return results;
}

Plots Plot::PlotResult(TFile& file, const std::string& tree_name, Stage stage) const
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

Plot3d Plot::ReadTree(TTree& tree, const std::string& leaf_1, const std::string& leaf_2, Stage stage) const
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

    Plot3d points;
    for (const auto & entry : Range(tree.GetEntries())) {
        Debug(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (const auto & element : Range(branch_size)) {
            Point point;
            point.x = leaf_values_1.at(element);
            point.y = leaf_values_2.at(element);
            point.z = bdt_values.at(element);
            Debug(point.x, point.y, point.z);
            points.points.emplace_back(point);
        }
    }
    return points;
}

Plot3d Plot::CoreVector(const Plot3d& points, const std::function<bool (Point&, Point&)>& function) const
{
    Plot3d plot = points;
    // TODO sorting the whole vector if you just want to get rid of the extrem values might not be the fastest solution
    std::sort(plot.points.begin(), plot.points.end(), [&](Point & a, Point & b) {
        return function(a, b);
    });
    int cut_off = plot.points.size() / 25;
    plot.points.erase(plot.points.begin(), plot.points.begin() + cut_off);
    plot.points.erase(plot.points.end() - cut_off, plot.points.end());
    return plot;
}
int Results::XBin(float value) const
{
    return std::floor((value + 1) * Result::steps / 2);
}
void Results::ExtremeXValues()
{
    for (const auto & result : background) {
        float min_0 = *std::min_element(result.bdt.begin(), result.bdt.end());
        if (min_0 < min.x) {
            min.x = min_0;
        }
    }
    for (const auto & result : signal) {
        float max_0 = *std::max_element(result.bdt.begin(), result.bdt.end());
        if (max_0 > max.x) {
            max.x = max_0;
        }
    }
}

}
