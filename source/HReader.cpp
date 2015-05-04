# include "HReader.hh"

# include "TPad.h"
# include "TDirectoryFile.h"
# include "TTree.h"
# include "TCanvas.h"
# include "TGraph.h"
# include "TMultiGraph.h"
# include "TLine.h"

# include "TMVA/Reader.h"
# include "TMVA/MethodCuts.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"


HMvaResult::HMvaResult()
{
    Steps = 20000;
    Events.resize(Steps, 0);
    Efficiency.resize(Steps, 0);
    AnalysisEventNumber.resize(Steps, 0);
    Bdt.resize(Steps, 0);
}

std::vector<int> HMvaResult::CutIntegral(const std::vector<int> &bins) const
{
    std::vector<int> integrals(Steps, 0);
    integrals.at(Steps - 1) = bins.at(Steps - 1);
    for (int step = Steps - 2; step >= 0; --step) integrals.at(step) = integrals.at(step + 1) + bins.at(step);
    return integrals;
}

hanalysis::HReader::HReader()
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
}

hanalysis::HReader::HReader(hanalysis::Tagger &tagger)
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
    SetMva(tagger);
}

void hanalysis::HReader::SetMva(hanalysis::Tagger &tagger)
{
    Print(HNotification, "SetMva");
    tagger_ = &tagger;
    AddVariable();
    BookMva();
}

void hanalysis::HReader::AddVariable()
{
    Print(HNotification, "Add Variable");
    const std::string default_options = "!Color:Silent";
    for (auto & observable : tagger().observables()) reader().AddVariable(observable.expression(), observable.value());
    for (auto & spectator : tagger().spectators()) reader().AddSpectator(spectator.expression(), spectator.value());

}

void hanalysis::HReader::BookMva()
{
    Print(HNotification, "Book Mva");
    const std::string xml_name = ".weights.xml";
    const std::string bdt_weight_file = tagger().analysis_name() + "/" + tagger().tagger_name() + "_" + tagger().BdtMethodName() + xml_name;
    Print(HNotification, "Opening Weight File", bdt_weight_file);
    reader().BookMVA(tagger().BdtMethodName(), bdt_weight_file);
}

float hanalysis::HReader::Bdt() const
{
    Print(HInformation, "Bdt");
    return const_cast<TMVA::Reader &>(reader_).EvaluateMVA(tagger().BdtMethodName()) + 1; // TODO get rid of the const cast
}

void hanalysis::HReader::SimpleMVALoop()
{
    Print(HNotification, "Mva Loop");
    std::stringstream TableHeader;
    TableHeader << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rlll}\n\\toprule\n";

    const std::string ExportFileName = tagger().analysis_name() + "/" + tagger().analysis_name() + ".root";
    TFile ExportFile(ExportFileName.c_str(), "Recreate");

    const std::string BackgroundFileName = tagger().analysis_name() + "/" + tagger().GetBackgroundName() + "Reader.root";
    TFile BackgroundFile(BackgroundFileName.c_str(), "Read");
    Print(HError, "Open Background File", BackgroundFileName, tagger().GetBackgroundTreeNames().size());


    std::vector<HMvaResult> BackgroundResults;
    for (const auto & BackgroundTreeName : tagger().GetBackgroundTreeNames()) BackgroundResults.push_back(BdtResult(BackgroundFile, BackgroundTreeName, ExportFile));

    const std::string SignalFileName = tagger().analysis_name() + "/" + tagger().GetSignalName() + "Reader.root";
    TFile SignalFile(SignalFileName.c_str(), "Read");
    Print(HError, "Open Signal File", SignalFileName, tagger().GetSignalTreeNames().size());

    HMvaResult SignalResults;
    std::vector<float> Significances(SignalResults.Steps, 0);
    std::vector<float> XValues(SignalResults.Steps, 0);
    for (const auto & SignalTreeName : tagger().GetSignalTreeNames()) {
        SignalResults = BdtResult(SignalFile, SignalTreeName, ExportFile);
        for (int Step = 0; Step < SignalResults.Steps; ++Step) {
            float BackgroundEvents = 0;
            for (const auto & BackgroundResult : BackgroundResults) BackgroundEvents += BackgroundResult.Events[Step];
            if (SignalResults.Events[Step] + BackgroundEvents > 0) Significances.at(Step) = SignalResults.Events[Step] / std::sqrt(SignalResults.Events[Step] + BackgroundEvents);
            else Significances.at(Step) = 0;
            XValues.at(Step) = float(Step) * 2 / SignalResults.Steps;
        }
    }
    ExportFile.Close();

    std::vector<float> BGs(BackgroundResults.size(), 0);
    int BestBin = 0;
    int Counter = 0;
    for (size_t BackgroundNumber = 0; BackgroundNumber < BackgroundResults.size(); ++BackgroundNumber) {
        while (BGs.at(BackgroundNumber) == 0 && Counter < SignalResults.Steps) {
            BestBin = std::distance(Significances.begin(), std::max_element(std::begin(Significances), std::end(Significances) - Counter));
            BGs.at(BackgroundNumber) = BackgroundResults.at(BackgroundNumber).Efficiency.at(BestBin);
            ++Counter;
        }
    }

    float MaxSignificance = Significances.at(BestBin);
    float SignalEfficiency = SignalResults.Efficiency.at(BestBin);
    const HInfoBranch SignalInfo = InfoBranch(SignalFile, tagger().GetSignalTreeNames().front());
    std::stringstream Table;
    Table << TableHeader.str();
    Table << "    Mass\n" << "  & " << SignalInfo.Mass;
    Table << "\n \\\\ \\midrule\n";
    Table << "    BDT-cut\n" << "  & " << float(BestBin) * 2 / SignalResults.Steps;
    Table << "\n \\\\ $p$-value\n  & " << MaxSignificance;
    Table << "\n \\\\ Efficiency\n  & " << SignalEfficiency << "\n  & " << SignalResults.AnalysisEventNumber.at(BestBin) << "\n  & " << SignalResults.TotalEventNumber << "\n";

    for (size_t BackgroundNumber = 0; BackgroundNumber < BackgroundResults.size(); ++BackgroundNumber) {
        Table << " \\\\ \\verb|" << tagger().GetBackgroundTreeNames().at(BackgroundNumber) << "|\n  & " << BackgroundResults.at(BackgroundNumber).Efficiency.at(BestBin) << "\n  & " << BackgroundResults.at(BackgroundNumber).AnalysisEventNumber.at(BestBin) << "\n  & " << BackgroundResults.at(BackgroundNumber).TotalEventNumber << "\n";
    }

    TCanvas EfficiencyCanvas;
    EfficiencyCanvas.SetLogy();
    TMultiGraph MultiGraph;
    std::vector<TGraph> RejectionGraphs;
    for (const auto & BackgroundResult : BackgroundResults) RejectionGraphs.push_back(TGraph(BackgroundResult.Steps, &XValues[0], &BackgroundResult.Efficiency[0]));
    for (auto & RejectionGraph : RejectionGraphs) MultiGraph.Add(&RejectionGraph);
    TGraph EfficiencyGraph(SignalResults.Steps, &XValues[0], &SignalResults.Efficiency[0]);
    EfficiencyGraph.SetLineColor(kRed);
    MultiGraph.Add(&EfficiencyGraph);
    MultiGraph.Draw("al");
    TLine EfficiencyLine(float(BestBin) * 2 / SignalResults.Steps, MultiGraph.GetYaxis()->GetXmin(), float(BestBin) * 2 / SignalResults.Steps, MultiGraph.GetYaxis()->GetXmax());
    EfficiencyLine.SetLineStyle(2);
    EfficiencyLine.Draw();
    const std::string EfficiencyFileName = tagger().analysis_name() + "-Efficiency.tex";
    const std::string EfficiencyFilePath = tagger().analysis_name() + "/" + EfficiencyFileName;
    EfficiencyCanvas.Print(EfficiencyFilePath.c_str());

    TCanvas SignificanceCanvas;
    TGraph SignificanceGraph(SignalResults.Steps, &XValues[0], &Significances[0]);
    SignificanceGraph.SetTitle("");
    SignificanceGraph.Draw("al");
    SignificanceCanvas.Update();
    TLine SignificanceLine(float(BestBin) * 2 / SignalResults.Steps, gPad->GetUymin(), float(BestBin) * 2 / SignalResults.Steps, gPad->GetUymax());
    SignificanceLine.SetLineStyle(2);
    SignificanceLine.Draw();
    const std::string SignificanceFileName = tagger().analysis_name() + "-Significance.tex";
    const std::string SignificanceFilePath = tagger().analysis_name() + "/" + SignificanceFileName;
    SignificanceCanvas.Print(SignificanceFilePath.c_str());

//     TCanvas BdtCanvas;
//     std::vector<TH1F> Histograms;
//     for (const auto & BackgroundResult : BackgroundResults) {
//       TH1F BackgroundHistogram("","",50,0,2);
//       for(const auto Bdt : BackgroundResult.Bdt) BackgroundHistogram.Fill(Bdt);
//       Histograms.push_back(BackgroundHistogram);
//     }
//     TH1F SignalHistogram("","",50,0,2);
//     for(const auto Bdt : SignalResults.Bdt) SignalHistogram.Fill(Bdt);
//     SignalHistogram.SetLineColor(kRed);
//     Histograms.push_back(SignalHistogram);
//     float YMax = 0;
//     for(const auto & Histogram : Histograms) if(Histogram.GetBinContent(Histogram.GetMaximumBin())> YMax) YMax = Histogram.GetBinContent(Histogram.GetMaximumBin());
//     for(auto & Histogram : Histograms) {
//       Histogram.SetAxisRange(0, 1.05 * YMax , "Y");
//     Histogram.Draw("same");
//     }
//     TLine BdtLine(float(BestBin) * 2 / SignalResults.Steps, 0, float(BestBin) * 2 / SignalResults.Steps, YMax);
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

    LatexFile << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << EfficiencyFileName << "}}\n\\caption{Efficiency.}\n\\end{figure}\n";
    LatexFile << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << SignificanceFileName << "}}\n\\caption{Significance.}\n\\end{figure}\n";
//     LatexFile << "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" << BdtFileName << "}}\n\\caption{Bdt.}\n\\end{figure}\n";

    LatexFooter(LatexFile);
}

HMvaResult hanalysis::HReader::BdtResult(TFile &file, const std::string &tree_name, TFile &export_file) const
{
    Print(HNotification, "Apply Bdt", tree_name);
    const float Luminosity = 3000; // 3000 fb-1

    Print(HError, "Open Tree", tree_name);
    ExRootTreeReader tree_reader(static_cast<TTree *>(file.Get(tree_name.c_str())));
    const HInfoBranch Info = InfoBranch(file, tree_name);

    HMvaResult Result;
    Result.TotalEventNumber = Info.EventNumber;
    std::vector<int> Bins = BdtDistribution(tree_reader, tree_name, export_file);
    std::vector<int> Integral = Result.CutIntegral(Bins);

    for (int Step = 0; Step < Result.Steps; ++Step) {
        Result.Events[Step] = float(Integral[Step]) / float(Info.EventNumber) * Info.Crosssection * Luminosity;
        Result.Efficiency[Step] = float(Integral[Step]) / float(Info.EventNumber);
        Result.AnalysisEventNumber[Step] = Integral[Step];
        Result.Bdt[Step] = Bins[Step];
        Print(HDebug, "Result", Result.Efficiency[Step], Result.Events[Step]);
    }
    return Result;
}

std::vector<int> hanalysis::HReader::BdtDistribution(ExRootTreeReader &tree_reader, const std::string &tree_name,  TFile &export_file) const
{
    Print(HNotification, "Bdt Distribution", tagger().GetBranchName());
    std::string NewEventBranchName = tagger().GetBranchName() + "Reader";

    HMvaResult Result;
    std::vector<int> Bins(Result.Steps, 0);

    TClonesArray &event_clones_array = *tree_reader.UseBranch(NewEventBranchName.c_str());
    ExRootTreeWriter tree_writer(&export_file, tree_name.c_str());
    ExRootTreeBranch &result_branch = *tree_writer.NewBranch(NewEventBranchName.c_str(), HResultBranch::Class());
    for (const int EventNumber : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(EventNumber);
        for (const int Entry : Range(event_clones_array.GetEntriesFast())) {
            const float BdtValue = tagger().ReadBdt(event_clones_array, Entry);
            if (BdtValue < 0 || BdtValue > 2) Print(HError, "Bdt Value" , BdtValue);
            static_cast<HResultBranch &>(*result_branch.NewEntry()).Bdt = BdtValue;
//             Print(HNotification, "Bdt Distribution", BdtValue,std::floor(BdtValue * Result.Steps / 2) - 1);
            int bin = std::floor(BdtValue * Result.Steps / 2) - 1;
            if (bin == -1) bin = 0; // FIXME clean this up
//             ++Bins.at(std::floor(BdtValue * Result.Steps / 2) - 1);
            ++Bins.at(bin);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    return Bins;
}

HInfoBranch hanalysis::HReader::InfoBranch(TFile &file, const std::string &tree_name) const
{
    ExRootTreeReader tree_reader(static_cast<TTree *>(file.Get(tree_name.c_str())));
//     Print(HError,"Info Branch",tagger().GetWeightBranchName().c_str());
    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().GetWeightBranchName().c_str());
//     tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    tree_reader.ReadEntry(0);
    return static_cast<HInfoBranch &>(*clones_array.At(0));
}


void hanalysis::HReader::LatexHeader(std::ofstream &latex_file) const
{
    Print(HNotification, "LaTeX Header");
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


void hanalysis::HReader::LatexFooter(ofstream &latex_file) const
{
    Print(HNotification, "LaTeX Footer");
    latex_file << "\n\\end{document}\n";
    latex_file.close();
}

// float hanalysis::HReader::GetRatio(const float Nominator, const float Denummertor) const
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
// float hanalysis::HReader::GetScaling(const float Events, const int Particles) const
// {
//     Print(HInformation , "Scaling");
//     float Scaling;
//     if (Particles == 0) {
//         Scaling = 0;
//     } else {
//         Scaling = Events / Particles;
//     }
//     return Scaling;
// }
//
// float hanalysis::HReader::GetLuminosity(const float Number) const
// {
//     Print(HInformation , "Luminosity");
//     float Luminosity = Number / CrosssectionScaled;
//     return Luminosity;
// }
//
// float hanalysis::HReader::GetLuminosityError(const float Number) const
// {
//     Print(HInformation , "Luminosity Error");
//     float LuminosityError = GetError(Number) / CrosssectionScaled + Number / CrosssectionNorm * LuminosityScalingError + GetLuminosity(Number) * CrosssectionNormRelError;
//     return LuminosityError;
// }
//
// float hanalysis::HReader::GetError(const float Value) const
// {
//     Print(HInformation , "Error");
//     float Error;
//     if (Value == 0) {
//         Error = 0;
//     } else {
//         Error = 1 / sqrt(Value);
//     }
//     return Error;
// }
//
// float hanalysis::HReader::RoundToDigits(const float Value) const
// {
//     return RoundToDigits(Value, 3);
// }
//
// float hanalysis::HReader::RoundError(const float Value) const
// {
//     return RoundToDigits(Value, 2);
// }
//
//
// float hanalysis::HReader::RoundToDigits(const float Value, const int Digits) const
// {
//     Print(HInformation , "Round To Digits");
//     if (Value == 0 || Value != Value) {
//         return 0;
//     } else {
//         const float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
//         return (round(Value * Factor) / Factor);
//     }
// }
//
// float hanalysis::HReader::RoundToError(const float Value, const float Error) const
// {
//     Print(HInformation , "Round To Digits");
//     if (Value == 0) {
//         return 0;
//     } else {
//         const float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));
//         return (round(Value * Factor) / Factor);
//     }
// }
