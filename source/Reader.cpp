# include "Reader.hh"

# include "TClonesArray.h"
# include "TPad.h"
# include "TDirectoryFile.h"
# include "TTree.h"
# include "TCanvas.h"
# include "TGraph.h"
# include "TMultiGraph.h"
# include "TLine.h"
# include "TLegend.h"
# include "TStyle.h"

// # include "TMVA/Reader.h"
# include "TMVA/MethodCuts.h"

namespace analysis
{

MvaResult::MvaResult()
{
    steps = 20000;
    events.resize(steps, 0);
    efficiency.resize(steps, 0);
    analysis_event_number.resize(steps, 0);
    bdt.resize(steps, 0);
}

std::vector<int> MvaResult::CutIntegral(const std::vector<int> &bins) const
{
    std::vector<int> integrals(steps, 0);
    integrals.at(steps - 1) = bins.at(steps - 1);
    for (int step = steps - 2; step >= 0; --step) integrals.at(step) = integrals.at(step + 1) + bins.at(step);
    return integrals;
}

Reader::Reader()
{
//     debug_level_ = kDebug;
    Print(kInformation, "Constructor");
}

Reader::Reader(Tagger &tagger)
{
//     debug_level_ = kDebug;
    Print(kInformation, "Constructor with tagger");
    SetTagger(tagger);
}

void Reader::SetTagger(Tagger &tagger)
{
    Print(kNotification, "SetMva");
    tagger_ = &tagger;
    AddVariable();
    BookMva();
}

void Reader::AddVariable()
{
    Print(kNotification, "Add Variable");
    const std::string default_options = "!Color:Silent";
    for (auto & observable : tagger().observables()) reader().AddVariable(observable.expression(), observable.value());
    for (auto & spectator : tagger().spectators()) reader().AddSpectator(spectator.expression(), spectator.value());

}

void Reader::BookMva()
{
    Print(kNotification, "Book Mva");
    const std::string xml_name = ".weights.xml";
    const std::string bdt_weight_file = tagger().analysis_name() + "/" + tagger().tagger_name() + "_" + tagger().bdt_method_name() + xml_name;
    Print(kNotification, "Opening Weight File", bdt_weight_file);
    reader().BookMVA(tagger().bdt_method_name(), bdt_weight_file);
}

float Reader::Bdt() const
{
    Print(kInformation, "Bdt");
    return const_cast<TMVA::Reader &>(reader_).EvaluateMVA(tagger().bdt_method_name()) + 1;
}

// void Reader::Export(){
//   const std::string export_file_name = tagger().analysis_name() + "/" + tagger().analysis_name() + ".root";
//   TFile export_file(export_file_name.c_str(), "Recreate");
//
//   const std::string background_file_name = tagger().analysis_name() + "/" + tagger().background_name() + "Reader.root";
//   TFile background_file(background_file_name.c_str(), "Read");
//   Print(kError, "Open Background File", background_file_name, tagger().background_tree_names().size());
//
//   std::vector<MvaResult> background_results;
//   for (const auto & background_tree_name : tagger().background_tree_names()) background_results.emplace_back(BdtResult(background_file, background_tree_name, export_file));
//
//   const std::string signal_file_name = tagger().analysis_name() + "/" + tagger().signal_name() + "Reader.root";
//   TFile signal_file(signal_file_name.c_str(), "Read");
//   Print(kError, "Open Signal File", signal_file_name, tagger().signal_tree_names().size());
//
//   MvaResult signal_results;
//   std::vector<float> x_values(signal_results.steps, 0);
//   for (const auto & signal_tree_names : tagger().signal_tree_names()) {
//     signal_results = BdtResult(signal_file, signal_tree_names, export_file);
//     for (int step = 0; step < signal_results.steps; ++step) {
//       float background_events = 0;
//       for (const auto & background_result : background_results) background_events += background_result.events[step];
//       x_values.at(step) = float(step) * 2 / signal_results.steps;
//     }
//   }
//   export_file.Close();
// }

void Reader::TaggingEfficiency()
{
    Print(kNotification, "Tagging Efficiency");

    const std::string export_file_name = tagger().analysis_name() + "/" + tagger().analysis_name() + ".root";
    TFile export_file(export_file_name.c_str(), "Recreate");

    const std::string background_file_name = tagger().analysis_name() + "/" + tagger().background_name() + "Reader.root";
    TFile background_file(background_file_name.c_str(), "Read");
    Print(kError, "Open Background File", background_file_name, tagger().background_tree_names().size());

    std::vector<MvaResult> background_results;
    for (const auto & background_tree_name : tagger().background_tree_names()) background_results.emplace_back(BdtResult(background_file, background_tree_name, export_file));

    const std::string signal_file_name = tagger().analysis_name() + "/" + tagger().signal_name() + "Reader.root";
    TFile signal_file(signal_file_name.c_str(), "Read");
    Print(kError, "Open Signal File", signal_file_name, tagger().signal_tree_names().size());

    MvaResult signal_results;
    std::vector<float> x_values(signal_results.steps, 0);
    for (const auto & signal_tree_names : tagger().signal_tree_names()) {
        signal_results = BdtResult(signal_file, signal_tree_names, export_file);
        for (int step = 0; step < signal_results.steps; ++step) {
            float background_events = 0;
            for (const auto & background_result : background_results) background_events += background_result.events[step];
            x_values.at(step) = float(step) * 2 / signal_results.steps;
        }
    }
    export_file.Close();

    Strings nice_names;
    for (const auto & background_tree_name : tagger().background_tree_names()) {
        analysis::InfoBranch info_branch = InfoBranch(background_file, background_tree_name);
        nice_names.emplace_back(info_branch.Name);
    }

    analysis::InfoBranch info_branch2 = InfoBranch(signal_file, tagger().signal_tree_names().front());

    TCanvas canvas;
    canvas.SetLogy();
    TMultiGraph multi_graph;
    std::vector<TGraph> graphs;
    for (const auto & background_result : background_results) graphs.emplace_back(TGraph(background_result.steps, &signal_results.efficiency[0], &background_result.efficiency[0]));
    float x_min = 0.15;
    float y_max = 0.85;
    float width = 0.2;
    float height = 0.4;
    TLegend legend(x_min, y_max - height, x_min + width, y_max);
    legend.SetHeader(info_branch2.Name.c_str());
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
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
    multi_graph.SetMinimum(0.01);
    legend.Draw();


    const std::string efficiency_file_name = tagger().analysis_name() + "-Acceptance.pdf";
    const std::string efficiency_file_path = tagger().analysis_name() + "/" + efficiency_file_name;
    canvas.Print(efficiency_file_path.c_str());
}

void Reader::OptimalSignificance()
{
    Print(kNotification, "Mva Loop");
    std::stringstream TableHeader;
    TableHeader << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rlll}\n\\toprule\n";

    const std::string export_file_name = tagger().analysis_name() + "/" + tagger().analysis_name() + ".root";
    TFile export_file(export_file_name.c_str(), "Recreate");

    const std::string background_file_name = tagger().analysis_name() + "/" + tagger().background_name() + "Reader.root";
    TFile background_file(background_file_name.c_str(), "Read");
    Print(kError, "Open Background File", background_file_name, tagger().background_tree_names().size());


    std::vector<MvaResult> background_results;
    for (const auto & background_tree_name : tagger().background_tree_names()) background_results.emplace_back(BdtResult(background_file, background_tree_name, export_file));

    const std::string signal_file_name = tagger().analysis_name() + "/" + tagger().signal_name() + "Reader.root";
    TFile signal_file(signal_file_name.c_str(), "Read");
    Print(kError, "Open Signal File", signal_file_name, tagger().signal_tree_names().size());

    MvaResult signal_results;
    std::vector<float> Significances(signal_results.steps, 0);
    std::vector<float> x_values(signal_results.steps, 0);
    for (const auto & signal_tree_names : tagger().signal_tree_names()) {
        signal_results = BdtResult(signal_file, signal_tree_names, export_file);
        for (int step = 0; step < signal_results.steps; ++step) {
            float background_events = 0;
            for (const auto & background_result : background_results) background_events += background_result.events[step];
            if (signal_results.events[step] + background_events > 0) Significances.at(step) = signal_results.events[step] / std::sqrt(signal_results.events[step] + background_events);
            else Significances.at(step) = 0;
            x_values.at(step) = float(step) * 2 / signal_results.steps;
        }
    }
    export_file.Close();

    std::vector<float> background_efficiencies(background_results.size(), 0);
    int BestBin = 0;
    int counter = 0;
    for (std::size_t background_number = 0; background_number < background_results.size(); ++background_number) {
        while (background_efficiencies.at(background_number) == 0 && counter < signal_results.steps) {
            BestBin = std::distance(Significances.begin(), std::max_element(std::begin(Significances), std::end(Significances) - counter));
            background_efficiencies.at(background_number) = background_results.at(background_number).efficiency.at(BestBin);
            ++counter;
        }
    }

    float MaxSignificance = Significances.at(BestBin);
    float SignalEfficiency = signal_results.efficiency.at(BestBin);
    const analysis::InfoBranch info_branch = InfoBranch(signal_file, tagger().signal_tree_names().front());
    std::stringstream Table;
    Table << TableHeader.str();
    Table << "    Mass\n" << "  & " << info_branch.Mass;
    Table << "\n \\\\ \\midrule\n";
    Table << "    BDT-cut\n" << "  & " << float(BestBin) * 2 / signal_results.steps;
    Table << "\n \\\\ $p$-value\n  & " << MaxSignificance;
    Table << "\n \\\\ Efficiency\n  & " << SignalEfficiency << "\n  & " << signal_results.analysis_event_number.at(BestBin) << "\n  & " << signal_results.event_sum << "\n";

    for (std::size_t background_number = 0; background_number < background_results.size(); ++background_number) {
        Table << " \\\\ \\verb|" << tagger().background_tree_names().at(background_number) << "|\n  & " << background_results.at(background_number).efficiency.at(BestBin) << "\n  & " << background_results.at(background_number).analysis_event_number.at(BestBin) << "\n  & " << background_results.at(background_number).event_sum << "\n";
    }

    TCanvas efficiency_canvas;
    efficiency_canvas.SetLogy();
    TMultiGraph multi_graph;
    std::vector<TGraph> rejection_graphs;
    for (const auto & background_result : background_results) rejection_graphs.emplace_back(TGraph(background_result.steps, &x_values[0], &background_result.efficiency[0]));
    for (auto & rejection_graph : rejection_graphs) multi_graph.Add(&rejection_graph);
    TGraph EfficiencyGraph(signal_results.steps, &x_values[0], &signal_results.efficiency[0]);
    EfficiencyGraph.SetLineColor(kRed);
    multi_graph.Add(&EfficiencyGraph);
    multi_graph.Draw("al");
    TLine EfficiencyLine(float(BestBin) * 2 / signal_results.steps, multi_graph.GetYaxis()->GetXmin(), float(BestBin) * 2 / signal_results.steps, multi_graph.GetYaxis()->GetXmax());
    EfficiencyLine.SetLineStyle(2);
    EfficiencyLine.Draw();
    const std::string efficiency_file_name = tagger().analysis_name() + "-Efficiency.tex";
    const std::string efficiency_file_path = tagger().analysis_name() + "/" + efficiency_file_name;
    efficiency_canvas.Print(efficiency_file_path.c_str());

    TCanvas SignificanceCanvas;
    TGraph SignificanceGraph(signal_results.steps, &x_values[0], &Significances[0]);
    SignificanceGraph.SetTitle("");
    SignificanceGraph.Draw("al");
    SignificanceCanvas.Update();
    TLine SignificanceLine(float(BestBin) * 2 / signal_results.steps, gPad->GetUymin(), float(BestBin) * 2 / signal_results.steps, gPad->GetUymax());
    SignificanceLine.SetLineStyle(2);
    SignificanceLine.Draw();
    const std::string SignificanceFileName = tagger().analysis_name() + "-Significance.tex";
    const std::string SignificanceFilePath = tagger().analysis_name() + "/" + SignificanceFileName;
    SignificanceCanvas.Print(SignificanceFilePath.c_str());

//     TCanvas BdtCanvas;
//     std::vector<TH1F> Histograms;
//     for (const auto & background_result : background_results) {
//       TH1F BackgroundHistogram("","",50,0,2);
//       for(const auto Bdt : background_result.Bdt) BackgroundHistogram.Fill(Bdt);
//       Histograms.emplace_back(BackgroundHistogram);
//     }
//     TH1F SignalHistogram("","",50,0,2);
//     for(const auto Bdt : signal_results.Bdt) SignalHistogram.Fill(Bdt);
//     SignalHistogram.SetLineColor(kRed);
//     Histograms.emplace_back(SignalHistogram);
//     float YMax = 0;
//     for(const auto & Histogram : Histograms) if(Histogram.GetBinContent(Histogram.GetMaximumBin())> YMax) YMax = Histogram.GetBinContent(Histogram.GetMaximumBin());
//     for(auto & Histogram : Histograms) {
//       Histogram.SetAxisRange(0, 1.05 * YMax , "Y");
//     Histogram.Draw("same");
//     }
//     TLine BdtLine(float(BestBin) * 2 / signal_results.steps, 0, float(BestBin) * 2 / signal_results.steps, YMax);
//     BdtLine.SetLineStyle(2);
//     BdtLine.Draw();
//     const std::string BdtFileName = tagger().GetAnalysisName() + "-Bdt.pdf";
//     const std::string BdtFilePath = tagger().GetAnalysisName() + "/" + BdtFileName;
//     BdtCanvas.Print(BdtFilePath.c_str());


    std::stringstream TableFooter;
    TableFooter << " \\\\ \\bottomrule\n\\end{tabular}\n\\caption{Significance and efficiencies.}\n\\end{table}\n";
    Table << TableFooter.str();

    std::ofstream LatexFile;
    LatexHeader(LatexFile);
    LatexFile << Table.str();

    LatexFile << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << efficiency_file_name << "}}\n\\caption{Efficiency.}\n\\end{figure}\n";
    LatexFile << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << SignificanceFileName << "}}\n\\caption{Significance.}\n\\end{figure}\n";
//     LatexFile << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << BdtFileName << "}}\n\\caption{Bdt.}\n\\end{figure}\n";

    LatexFooter(LatexFile);
}

MvaResult Reader::BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const
{
    Print(kNotification, "Apply Bdt", tree_name);
    const float Luminosity = 3000; // 3000 fb-1

    Print(kError, "Open Tree", tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree *>(file.Get(tree_name.c_str())));
    const analysis::InfoBranch Info = InfoBranch(file, tree_name);

    MvaResult result;
    result.event_sum = Info.EventNumber;
    std::vector<int> bins = BdtDistribution(tree_reader, tree_name, export_file);
    std::vector<int> Integral = result.CutIntegral(bins);

    for (int step = 0; step < result.steps; ++step) {
        result.events[step] = float(Integral[step]) / float(Info.EventNumber) * Info.Crosssection * Luminosity;
        result.efficiency[step] = float(Integral[step]) / float(Info.EventNumber);
        result.analysis_event_number[step] = Integral[step];
        result.bdt[step] = bins[step];
        Print(kDebug, "Result", result.efficiency[step], result.events[step]);
    }
    return result;
}

std::vector<int> Reader::BdtDistribution(exroot::TreeReader &tree_reader, const std::string &tree_name, TFile &export_file) const
{
    Print(kNotification, "Bdt Distribution", tagger().branch_name());
    std::string NeweventBranchName = tagger().branch_name() + "Reader";

    MvaResult result;
    std::vector<int> bins(result.steps, 0);

    TClonesArray &event_clones_array = *tree_reader.UseBranch(NeweventBranchName.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch &result_branch = *tree_writer.NewBranch(NeweventBranchName.c_str(), ResultBranch::Class());
    for (const int eventNumber : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(eventNumber);
        for (const int Entry : Range(event_clones_array.GetEntriesFast())) {
            const float bdt_value = tagger().ReadBdt(event_clones_array, Entry);
            if (bdt_value < 0 || bdt_value > 2) Print(kError, "Bdt Value" , bdt_value);
            static_cast<ResultBranch &>(*result_branch.NewEntry()).Bdt = bdt_value;
//             Print(kNotification, "Bdt Distribution", BdtValue,std::floor(BdtValue * result.steps / 2) - 1);
            int bin = std::floor(bdt_value * result.steps / 2) - 1;
            if (bin == -1) bin = 0; // FIXME clean this up
//             ++bins.at(std::floor(BdtValue * result.steps / 2) - 1);
            ++bins.at(bin);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    return bins;
}

InfoBranch Reader::InfoBranch(TFile &file, const std::string &tree_name) const
{
    Print(kNotification, "Info Branch", tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree *>(file.Get(tree_name.c_str())));
    Print(kError, "Info Branch", tree_name, tagger().weight_branch_name());
    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().weight_branch_name().c_str());
//     tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    tree_reader.ReadEntry(0);
    return static_cast<analysis::InfoBranch &>(*clones_array.At(0));
}


void Reader::LatexHeader(std::ofstream &latex_file) const
{
    Print(kNotification, "LaTeX Header");
    const std::string TexFileName = tagger().analysis_name() + "/" + tagger().analysis_name() + ".tex";
    latex_file.open(TexFileName);
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


void Reader::LatexFooter(ofstream &latex_file) const
{
    Print(kNotification, "LaTeX Footer");
    latex_file << "\n\\end{document}\n";
    latex_file.close();
}

// float Reader::GetRatio(const float Nominator, const float Denummertor) const
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
// float Reader::GetScaling(const float events, const int Particles) const
// {
//     Print(kInformation , "Scaling");
//     float Scaling;
//     if (Particles == 0) {
//         Scaling = 0;
//     } else {
//         Scaling = events / Particles;
//     }
//     return Scaling;
// }
//
// float Reader::GetLuminosity(const float Number) const
// {
//     Print(kInformation , "Luminosity");
//     float Luminosity = Number / CrosssectionScaled;
//     return Luminosity;
// }
//
// float Reader::GetLuminosityError(const float Number) const
// {
//     Print(kInformation , "Luminosity Error");
//     float LuminosityError = GetError(Number) / CrosssectionScaled + Number / CrosssectionNorm * LuminosityScalingError + GetLuminosity(Number) * CrosssectionNormRelError;
//     return LuminosityError;
// }
//
// float Reader::GetError(const float Value) const
// {
//     Print(kInformation , "Error");
//     float Error;
//     if (Value == 0) {
//         Error = 0;
//     } else {
//         Error = 1 / sqrt(Value);
//     }
//     return Error;
// }
//
// float Reader::RoundToDigits(const float Value) const
// {
//     return RoundToDigits(Value, 3);
// }
//
// float Reader::RoundError(const float Value) const
// {
//     return RoundToDigits(Value, 2);
// }
//
//
// float Reader::RoundToDigits(const float Value, const int Digits) const
// {
//     Print(kInformation , "Round To Digits");
//     if (Value == 0 || Value != Value) {
//         return 0;
//     } else {
//         const float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
//         return (round(Value * Factor) / Factor);
//     }
// }
//
// float Reader::RoundToError(const float Value, const float Error) const
// {
//     Print(kInformation , "Round To Digits");
//     if (Value == 0) {
//         return 0;
//     } else {
//         const float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));
//         return (round(Value * Factor) / Factor);
//     }
// }

int Reader::ColorCode(const int number) const
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

}
