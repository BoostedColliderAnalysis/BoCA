#include "Plot.hh"

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
#include "TGraph.h"

#include "exroot/ExRootAnalysis.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

Result::Result()
{
    steps = 20000;
    events.resize(steps, 0);
    efficiency.resize(steps, 0);
    analysis_event_number.resize(steps, 0);
    bins.resize(steps, 0);
}

std::vector<int> Result::CutIntegral() const
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
  for (const auto & signal_results : signal) {
    for (const int step : Range(Result().steps)) {
      float background_events = 0;
      for (const auto & background_result : background) background_events += background_result.events[step];
      if (signal_results.events[step] + background_events > 0) significances.at(step) = signal_results.events[step] / std::sqrt(signal_results.events[step] + background_events);
      else significances.at(step) = 0;
      x_values.at(step) = float(step) * 2 / Result().steps;
    }
  }
}

// Plot::Plot()
// {
//     Debug();
// }

Plot::Plot(Tagger &tagger)
{
    Debug("Constructor with tagger");
    tagger_ = &tagger;
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

std::vector<Result> Plot::Export(TFile &export_file, const std::string &file_name, const Strings &treename) const
{
    TFile file(file_name.c_str(), "Read");
    Debug(file_name, treename.size());

    std::vector<Result> results;
    for (const auto & tree_name : treename) results.emplace_back(BdtResult(file, tree_name, export_file));

    return results;
}

TLegend Plot::Legend(float x_min, float y_max, float width, float height, const std::string &name) const
{
    TLegend legend(x_min, y_max - height, x_min + width, y_max);
    if (name != "") legend.SetHeader(name.c_str());
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
    return legend;
}

std::string Plot::PlotHistograms(const analysis::Results &results) const
{
    Debug();
    gStyle->SetOptStat("");

    TCanvas canvas;
    std::vector<TH1F> histograms;
    TLegend legend = Legend(0.15, 0.85, 0.2, 0.4);

    float x_min = 0;
    for (const auto & result : results.background)  {
        float min = *std::min_element(result.bdt.begin(), result.bdt.end());
        min -= 1;
        if (min < x_min) x_min = min;
    }

    float x_max = 0;
    for (const auto & result : results.signal)  {
        float max = *std::max_element(result.bdt.begin(), result.bdt.end());
        max -= 1;
        if (max > x_max) x_max = max;
    }

    float y_max = 0;
    for (const auto & result : results.signal)  {
        TH1F histogram(result.info_branch.Name.c_str(), "", 50, x_min * 1.1, x_max * 1.1);
        for (const float & bdt : result.bdt) histogram.Fill(bdt - 1);
        float max = histogram.GetBinContent(histogram.GetMaximumBin());
        if (max > y_max) y_max = max;
        histograms.emplace_back(histogram);
    }

    for (const auto & result : results.background)  {
        TH1F histogram(result.info_branch.Name.c_str(), "", 50, x_min * 1.1, x_max * 1.1);
        for (const float & bdt : result.bdt) histogram.Fill(bdt - 1);
        histogram.SetLineColor(ColorCode(&result - &results.background[0] + 1));
        histogram.SetLineStyle(&result - &results.background[0] + 2);
        histograms.emplace_back(histogram);
        float max = histogram.GetBinContent(histogram.GetMaximumBin());
        if (max > y_max) y_max = max;
    }

    Strings nice_names;
    for (const auto & result : results.signal) nice_names.emplace_back(result.info_branch.Name);
    for (const auto & result : results.background) nice_names.emplace_back(result.info_branch.Name);
    for (auto & histogram : histograms) {
        histogram.SetAxisRange(0, y_max * 1.05, "Y");
        histogram.GetXaxis()->SetTitle("BDT");
        histogram.GetYaxis()->SetTitle("N");
        std::string name = nice_names.at(&histogram - &histograms[0]);
        legend.AddEntry(&histogram, name.c_str(), "l");
        histogram.Draw("same");
    }
    legend.Draw();

    const std::string efficiency_file_name = ExportName() + "-Bdt.pdf";
    canvas.Print(efficiency_file_name.c_str());
    return efficiency_file_name;
}

void Plot::PlotMultiGraph(const Results &results) const
{
    Debug();
    TCanvas canvas;
    TMultiGraph multi_graph;
    std::vector<TGraph> graphs;
    for (const auto & result : results.background) graphs.emplace_back(TGraph(result.steps, &results.signal.front().efficiency[0], &result.efficiency[0]));
    Strings nice_names;
    for (const auto & result : results.background) nice_names.emplace_back(result.info_branch.Name);
    canvas.SetLogy();
    TLegend legend = Legend(0.15, 0.85, 0.2, 0.4, results.signal.front().info_branch.Name);
    for (auto & graph : graphs) {
        graph.SetLineColor(ColorCode(&graph - &graphs[0]));
        graph.SetLineStyle(&graph - &graphs[0] + 1);
        multi_graph.Add(&graph);
        std::string name = nice_names.at(&graph - &graphs[0]);
        legend.AddEntry(&graph, name.c_str(), "l");
    }
    multi_graph.Draw("al");
    multi_graph.GetXaxis()->SetLimits(0.2, 0.9);
    multi_graph.GetXaxis()->SetTitle("Signal acceptance");
    multi_graph.GetYaxis()->SetTitle("Background acceptance");
    multi_graph.SetMaximum(1);
    multi_graph.SetMinimum(0.001);
//     multi_graph.SetMinimum(0.01);
    legend.Draw();

    std::string efficiency_file_name = ExportName() + "-Acceptance.pdf";
    canvas.Print(efficiency_file_name.c_str());
}

void Plot::TaggingEfficiency() const
{
    Debug();

    Results results = ExportFile();

    PlotHistograms(results);
    PlotMultiGraph(results);

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
    table << "    Mass\n" << "  & " << results.signal.front().info_branch.Mass;
    table << "\n \\\\ \\midrule\n";
    table << "    BDT-cut\n" << "  & " << float(best_bin) * 2 / Result().steps;
    table << "\n \\\\ $p$-value\n  & " << significances.at(best_bin);
    table << "\n \\\\ Efficiency\n  & " << results.signal.front().efficiency.at(best_bin) << "\n  & " << results.signal.front().analysis_event_number.at(best_bin) << "\n  & " << results.signal.front().event_sum() << "\n";

    for (const auto& background : results.background) {
      table << " \\\\ \\verb|" << tagger().background_tree_names().at(&background - &results.background[0]) << "|\n  & " << background.efficiency.at(best_bin) << "\n  & " << background.analysis_event_number.at(best_bin) << "\n  & " << background.event_sum() << "\n";
    }

    std::string efficiency_file_name = PlotEfficiencyGraph(results, x_values, best_bin);

    std::string significance_file_name = PlotSignificanceGraph(results, x_values,significances, best_bin);

    std::string bdt_file_name = PlotHistograms(results);

    std::stringstream table_footer;
    table_footer << " \\\\ \\bottomrule\n\\end{tabular}\n\\caption{Significance and efficiencies.}\n\\end{table}\n";
    table << table_footer.str();

    std::ofstream latex_file;
    LatexHeader(latex_file);
    latex_file << table.str();

//     latex_file << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << bdt_file_name << "}}\n\\caption{BDT Distribution.}\n\\end{figure}\n";
//     latex_file << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << efficiency_file_name << "}}\n\\caption{Efficiency.}\n\\end{figure}\n";
//     latex_file << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << significance_file_name << "}}\n\\caption{Significance.}\n\\end{figure}\n";

    latex_file << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" << bdt_file_name << "}\n\\caption{BDT Distribution.}\n\\end{figure}\n";
    latex_file << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" << efficiency_file_name << "}\n\\caption{Efficiency.}\n\\end{figure}\n";
    latex_file << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" << significance_file_name << "}\n\\caption{Significance.}\n\\end{figure}\n";

    LatexFooter(latex_file);
}

std::string Plot::PlotEfficiencyGraph(const Results &results, const std::vector<float> &x_values, const int best_bin) const
{
    Result signal_results = results.signal.front();
    TCanvas canvas;
    canvas.SetLogy();
    TMultiGraph multi_graph;
    std::vector<TGraph> rejection_graphs;
    for (const auto & background_result : results.background) rejection_graphs.emplace_back(TGraph(background_result.steps, &x_values[0], &background_result.efficiency[0]));
    for (auto & rejection_graph : rejection_graphs) multi_graph.Add(&rejection_graph);
    TGraph graph(signal_results.steps, &x_values[0], &signal_results.efficiency[0]);
    graph.SetLineColor(kRed);
    multi_graph.Add(&graph);
    multi_graph.Draw("al");
    TLine line(float(best_bin) * 2 / signal_results.steps, multi_graph.GetYaxis()->GetXmin(), float(best_bin) * 2 / signal_results.steps, multi_graph.GetYaxis()->GetXmax());
    line.SetLineStyle(2);
    line.Draw();
    const std::string file_name = ExportName() + "-Efficiency.pdf";
    canvas.Print(file_name.c_str());
    return file_name;
}

std::string Plot::PlotSignificanceGraph(const Results &results, const std::vector<float> &x_values, const std::vector<float> &significances, const int best_bin) const
{
    Result signal_results = results.signal.front();
    TCanvas canvas;
    TGraph graph(signal_results.steps, &x_values[0], &significances[0]);
    graph.SetTitle("");
    graph.Draw("al");
    canvas.Update();
    TLine line(float(best_bin) * 2 / signal_results.steps, gPad->GetUymin(), float(best_bin) * 2 / signal_results.steps, gPad->GetUymax());
    line.SetLineStyle(2);
    line.Draw();
    const std::string file_name = ExportName() + "-Significance.pdf";
    canvas.Print(file_name.c_str());
    return file_name;
}


Result Plot::BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const
{
  Debug(tree_name);
    const float Luminosity = 3000; // 3000 fb-1

    Debug("Open Tree", tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree *>(file.Get(tree_name.c_str())));
    Result result = BdtDistribution(tree_reader, tree_name, export_file);
    result.info_branch = InfoBranch(file, tree_name);

    std::vector<int> Integral = result.CutIntegral();

    for (int step = 0; step < result.steps; ++step) {
        result.events[step] = float(Integral[step]) / float(result.event_sum()) * result.info_branch.Crosssection * Luminosity;
        result.efficiency[step] = float(Integral[step]) / float(result.event_sum());
        result.analysis_event_number[step] = Integral[step];
//         result.bdt[step] = bins[step];
        Debug("Result", result.efficiency[step], result.events[step]);
    }
    return result;
}

Result Plot::BdtDistribution(exroot::TreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const
{
  Debug("Bdt Distribution", tagger().branch_name());
    std::string branch_name = tagger().branch_name() + "Reader";

    Result result;
    TClonesArray &event_clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch &result_branch = *tree_writer.NewBranch(branch_name.c_str(), ResultBranch::Class());
    int entries = 0;
    for (const int event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (const int entry : Range(event_clones_array.GetEntriesFast())) {
            float bdt_value = tagger().ReadBdt(event_clones_array, entry);
            result.bdt.emplace_back(bdt_value);
            Check(bdt_value > 0 && bdt_value < 2, "Bdt Value" , bdt_value);
            static_cast<ResultBranch &>(*result_branch.NewEntry()).Bdt = bdt_value;
//             Note("Bdt Distribution", BdtValue,std::floor(BdtValue * result.steps / 2) - 1);
            int bin = std::floor(bdt_value * result.steps / 2) - 1;
            if (bin == -1) bin = 0; // FIXME clean this up
//             ++bins.at(std::floor(BdtValue * result.steps / 2) - 1);
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

InfoBranch Plot::InfoBranch(TFile &file, const std::string &tree_name) const
{
    Debug(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree *>(file.Get(tree_name.c_str())));
    Debug("Info Branch", tree_name, tagger().weight_branch_name());
    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().weight_branch_name().c_str());
//     tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    tree_reader.ReadEntry(0);
    return dynamic_cast<analysis::InfoBranch &>(*clones_array.At(0));
}


void Plot::LatexHeader(std::ofstream &latex_file) const
{
    Debug();
    const std::string file_name = tagger().analysis_name() + "/" + tagger().analysis_name() + ".tex";
    latex_file.open(file_name);
    latex_file << "\\documentclass[a4paper,10pt]{article}\n\n"
               << "\\usepackage{booktabs}\n"
               << "\\usepackage{graphicx}\n"
               //               << "\\usepackage[landscape]{geometry}\n"
               << "\\usepackage[cm]{fullpage}\n"
               //               << "\\usepackage{units}\n"
               //               << "\\usepackage{siunitx}\n\n"
               //               << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}\n"
               //               << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}\n"
               //               << "\\newcolumntype{E}{R@{$\\pm$}L}\n"
               << "\\usepackage{tikz}\n"
               << "\\usetikzlibrary{patterns}\n"
               << "\\usetikzlibrary{plotmarks}\n"
               << "\n\\begin{document}\n";
}


void Plot::LatexFooter(ofstream &latex_file) const
{
    Debug();
    latex_file << "\n\\end{document}\n";
    latex_file.close();
}

// float Plot::GetRatio(const float Nominator, const float Denummertor) const
// {
//     float Ratio;
//     if (Denummertor > 0) {
//         Ratio = float(Nominator) / Denummertor;
//     } else {
//         Ratio = 0;
//     }
//     return Ratio;
// }
//
//
// float Plot::GetScaling(const float events, const int Particles) const
// {
//     Debug("Scaling");
//     float Scaling;
//     if (Particles == 0) {
//         Scaling = 0;
//     } else {
//         Scaling = events / Particles;
//     }
//     return Scaling;
// }
//
// float Plot::GetLuminosity(const float Number) const
// {
//     Debug("Luminosity");
//     float Luminosity = Number / CrosssectionScaled;
//     return Luminosity;
// }
//
// float Plot::GetLuminosityError(const float Number) const
// {
//     Debug("Luminosity Error");
//     float LuminosityError = GetError(Number) / CrosssectionScaled + Number / CrosssectionNorm * LuminosityScalingError + GetLuminosity(Number) * CrosssectionNormRelError;
//     return LuminosityError;
// }
//
// float Plot::GetError(const float Value) const
// {
//     Debug("Error");
//     float Error;
//     if (Value == 0) {
//         Error = 0;
//     } else {
//         Error = 1 / sqrt(Value);
//     }
//     return Error;
// }
//
// float Plot::RoundToDigits(const float Value) const
// {
//     return RoundToDigits(Value, 3);
// }
//
// float Plot::RoundError(const float Value) const
// {
//     return RoundToDigits(Value, 2);
// }
//
//
// float Plot::RoundToDigits(const float Value, const int Digits) const
// {
//     Debug("Round To Digits");
//     if (Value == 0 || Value != Value) {
//         return 0;
//     } else {
//         const float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
//         return (round(Value * Factor) / Factor);
//     }
// }
//
// float Plot::RoundToError(const float Value, const float Error) const
// {
//     Debug("Round To Digits");
//     if (Value == 0) {
//         return 0;
//     } else {
//         const float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));
//         return (round(Value * Factor) / Factor);
//     }
// }

int Plot::ColorCode(const int number) const
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
int Result::event_sum() const
{
//         return info_branch.EventNumber;
    return event_sum_;
}
void Result::set_event_sum(const int event_sum)
{
    event_sum_ = event_sum;
}

}
