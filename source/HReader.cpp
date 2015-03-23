# include "HReader.hh"
# include "TPad.h"

hanalysis::HReader::HReader()
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
}

hanalysis::HReader::HReader(hanalysis::HMva &NewMva)
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
    SetMva(NewMva);
}

void hanalysis::HReader::SetMva(hanalysis::HMva &NewMva)
{
    Print(HNotification, "SetMva");
    Mva = &NewMva;
    AddVariable();
    BookMva();
}

void hanalysis::HReader::AddVariable()
{
    Print(HNotification, "Add Variable");
    const std::string DefaultOptions = "!Color:Silent";
    //     Reader = TMVA::Reader(DefaultOptions);
    for (auto & Observable : Mva->GetObservables())reader_.AddVariable(Observable.Expression, Observable.GetValue());
    for (auto & Spectator : Mva->GetSpectators()) reader_.AddSpectator(Spectator.Expression, Spectator.GetValue());
}

void hanalysis::HReader::BookMva()
{
    Print(HNotification, "Book Mva");
    const std::string XmlName = ".weights.xml";
    //     const std::string CutWeightFile = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + "_" + Mva->GetCutMethodName() + XmlName;
    //     Print(HError, "Opening Weight File", CutWeightFile);
    //     Reader.BookMVA(Mva->GetCutMethodName(), CutWeightFile);
    const std::string BdtWeightFile = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + "_" + Mva->BdtMethodName() + XmlName;
    Print(HNotification, "Opening Weight File", BdtWeightFile);
    reader_.BookMVA(Mva->BdtMethodName(), BdtWeightFile);
}

void hanalysis::HReader::SimpleMVALoop()
{
    Print(HNotification, "Mva Loop");
    std::stringstream TableHeader;
    TableHeader << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rlll}\n\\toprule\n";

    const std::string ExportFileName = Mva->GetAnalysisName() + "/" + Mva->GetAnalysisName() + ".root";
    TFile ExportFile(ExportFileName.c_str(), "Recreate");

    const std::string BackgroundFileName = Mva->GetAnalysisName() + "/" + Mva->GetBackgroundName() + "Reader.root";
    const TFile BackgroundFile(BackgroundFileName.c_str(), "Read");
    Print(HError, "Open Background File", BackgroundFileName, Mva->GetBackgroundTreeNames().size());


    std::vector<HMvaResult> BackgroundResults;
    for (const auto & BackgroundTreeName : Mva->GetBackgroundTreeNames()) BackgroundResults.push_back(BdtResult(BackgroundFile, BackgroundTreeName, ExportFile));

    const std::string SignalFileName = Mva->GetAnalysisName() + "/" + Mva->GetSignalName() + "Reader.root";
    const TFile SignalFile(SignalFileName.c_str(), "Read");
    Print(HError, "Open Signal File", SignalFileName, Mva->GetSignalTreeNames().size());

    HMvaResult SignalResults;
    std::vector<float> Significances(SignalResults.Steps, 0);
    std::vector<float> XValues(SignalResults.Steps, 0);
    for (const auto & SignalTreeName : Mva->GetSignalTreeNames()) {
        SignalResults = BdtResult(SignalFile, SignalTreeName, ExportFile);
        for (int Step = 0; Step < SignalResults.Steps; ++Step) {
            float BackgroundEvents = 0;
            for (const auto & BackgroundResult : BackgroundResults) BackgroundEvents += BackgroundResult.Events[Step];
            Significances.at(Step) = SignalResults.Events[Step] / std::sqrt(SignalResults.Events[Step] + BackgroundEvents + 15);
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
    const HInfoBranch SignalInfo = InfoBranch(SignalFile, Mva->GetSignalTreeNames().front());
    std::stringstream Table;
    Table << TableHeader.str();
    Table << "    Mass\n" << "  & " << SignalInfo.Mass;
    Table << "\n \\\\ \\midrule\n";
    Table << "    BDT-cut\n" << "  & " << float(BestBin) * 2 / SignalResults.Steps;
    Table << "\n \\\\ $p$-value\n  & " << MaxSignificance;
    Table << "\n \\\\ Efficiency\n  & " << SignalEfficiency << "\n  & " << SignalResults.AnalysisEventNumber.at(BestBin) << "\n  & " << SignalResults.TotalEventNumber << "\n";

    for (size_t BackgroundNumber = 0; BackgroundNumber < BackgroundResults.size(); ++BackgroundNumber) {
        Table << " \\\\ \\verb|" << Mva->GetBackgroundTreeNames().at(BackgroundNumber) << "|\n  & " << BackgroundResults.at(BackgroundNumber).Efficiency.at(BestBin) << "\n  & " << BackgroundResults.at(BackgroundNumber).AnalysisEventNumber.at(BestBin) << "\n  & " << BackgroundResults.at(BackgroundNumber).TotalEventNumber << "\n";
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
    const std::string EfficiencyFileName = Mva->GetAnalysisName() + "-Efficiency.tex";
    const std::string EfficiencyFilePath = Mva->GetAnalysisName() + "/" + EfficiencyFileName;
    EfficiencyCanvas.Print(EfficiencyFilePath.c_str());

    TCanvas SignificanceCanvas;
    TGraph SignificanceGraph(SignalResults.Steps, &XValues[0], &Significances[0]);
    SignificanceGraph.SetTitle("");
    SignificanceGraph.Draw("al");
    SignificanceCanvas.Update();
    TLine SignificanceLine(float(BestBin) * 2 / SignalResults.Steps, gPad->GetUymin(), float(BestBin) * 2 / SignalResults.Steps, gPad->GetUymax());
    SignificanceLine.SetLineStyle(2);
    SignificanceLine.Draw();
    const std::string SignificanceFileName = Mva->GetAnalysisName() + "-Significance.tex";
    const std::string SignificanceFilePath = Mva->GetAnalysisName() + "/" + SignificanceFileName;
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
//     const std::string BdtFileName = Mva->GetAnalysisName() + "-Bdt.pdf";
//     const std::string BdtFilePath = Mva->GetAnalysisName() + "/" + BdtFileName;
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

HMvaResult hanalysis::HReader::BdtResult(const TFile &File, const std::string &TreeName, const TFile &ExportFile) const
{
    Print(HNotification, "Apply Bdt", TreeName);
    const float Luminosity = 3000; // 3000 fb-1

    Print(HError, "Open Tree", TreeName);
    ExRootTreeReader TreeReader((TTree *)const_cast<TFile *>(&File)->Get(TreeName.c_str()));
    const HInfoBranch Info = InfoBranch(File, TreeName);

    HMvaResult Result;
    Result.TotalEventNumber = Info.EventNumber;
    std::vector<int> Bins = BdtDistribution(TreeReader, TreeName, ExportFile);
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

std::vector<int> hanalysis::HReader::BdtDistribution(const ExRootTreeReader &TreeReader, const std::string &TreeName, const TFile &ExportFile) const
{
    Print(HNotification, "Bdt Distribution", Mva->GetBranchName());
    std::string NewEventBranchName = Mva->GetBranchName() + "Reader";

    HMvaResult Result;
    std::vector<int> Bins(Result.Steps, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(&TreeReader)->UseBranch(NewEventBranchName.c_str());
    ExRootTreeWriter TreeWriter(const_cast<TFile *>(&ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter.NewBranch(NewEventBranchName.c_str(), HResultBranch::Class());
    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(&TreeReader)->GetEntries())) {
        const_cast<ExRootTreeReader *>(&TreeReader)->ReadEntry(EventNumber);
        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
            const float BdtValue = Mva->ReadBdt(*EventClonesArray, Entry);
            if (BdtValue < 0 || BdtValue > 2) Print(HError, "Bdt Value" , BdtValue);
            static_cast<HResultBranch *>(ResultBranch->NewEntry())->Bdt = BdtValue;
            ++Bins.at(floor(BdtValue * Result.Steps / 2) - 1);
        }
        TreeWriter.Fill();
        TreeWriter.Clear();
    }
    TreeWriter.Write();
    return Bins;
}

HInfoBranch hanalysis::HReader::InfoBranch(const TFile &File, const std::string &TreeName) const
{
    ExRootTreeReader TreeReader((TTree *)const_cast<TFile *>(&File)->Get(TreeName.c_str()));
    const TClonesArray *ClonesArray = TreeReader.UseBranch(Mva->GetWeightBranchName().c_str());
    TreeReader.ReadEntry(0);
    return *(HInfoBranch *) ClonesArray->At(0);
}


void hanalysis::HReader::LatexHeader(std::ofstream &LatexFile) const
{
    Print(HNotification, "LaTeX Header");
    const std::string TexFileName = Mva->GetAnalysisName() + "/" + Mva->GetAnalysisName() + ".tex";
    LatexFile.open(TexFileName);
    LatexFile << "\\documentclass[a4paper,10pt]{article}\n\n"
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


void hanalysis::HReader::LatexFooter(ofstream &LatexFile) const
{
    Print(HNotification, "LaTeX Footer");
    LatexFile << "\n\\end{document}\n";
    LatexFile.close();
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
