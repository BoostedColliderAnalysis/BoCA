# include "HReader.hh"

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
    for (auto & Observable : Mva->GetObservables())Reader.AddVariable(Observable.Expression, Observable.GetValue());
    for (auto & Spectator : Mva->GetSpectators()) Reader.AddSpectator(Spectator.Expression, Spectator.GetValue());
}

void hanalysis::HReader::BookMva()
{
    Print(HNotification, "Book Mva");
    const std::string XmlName = ".weights.xml";
    //     const std::string CutWeightFile = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + "_" + Mva->GetCutMethodName() + XmlName;
    //     Print(HError, "Opening Weight File", CutWeightFile);
    //     Reader.BookMVA(Mva->GetCutMethodName(), CutWeightFile);
    const std::string BdtWeightFile = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + "_" + Mva->GetBdtMethodName() + XmlName;
    Print(HNotification, "Opening Weight File", BdtWeightFile);
    Reader.BookMVA(Mva->GetBdtMethodName(), BdtWeightFile);
}


void hanalysis::HReader::SimpleMVALoop()
{
    Print(HNotification, "Mva Loop");
    std::stringstream TableHeader;
    TableHeader << "\n\\begin{table}\n\\centering\n\\begin{tabular}{rl}\n\\toprule\n";

    const std::string ExportFileName = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + Mva->GetBdtMethodName() + ".root";
    TFile ExportFile(ExportFileName.c_str(), "Recreate");

    const std::string BackgroundFileName = Mva->GetAnalysisName() + "/" + Mva->GetBackgroundName() + "Reader.root";
    const TFile BackgroundFile(BackgroundFileName.c_str(),"Read");
    Print(HError, "Open Background File", BackgroundFileName, Mva->GetBackgroundTreeNames().size());


    std::vector<HMvaResult> BackgroundResults;
    for (const auto & BackgroundTreeName : Mva->GetBackgroundTreeNames()) BackgroundResults.push_back(BdtResult(BackgroundFile, BackgroundTreeName, ExportFile));

    const std::string SignalFileName = Mva->GetAnalysisName() + "/" + Mva->GetSignalName() + "Reader.root";
    const TFile SignalFile(SignalFileName.c_str(),"Read");
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

    auto MaxIt = std::max_element(std::begin(Significances), std::end(Significances));
    int MaxBin = std::distance(Significances.begin(), MaxIt);
    float MaxSignificance = Significances.at(MaxBin);
    float SignalEfficiency = SignalResults.Efficiency.at(MaxBin);
    std::stringstream Table;
    Table << TableHeader.str();
    Table << "    Mass\n" << "  & " << GetMass(SignalFile, Mva->GetSignalTreeNames().at(0));
    Table << "\n \\\\ \\midrule\n";
    Table << "    BDT-cut\n" << "  & " << float(MaxBin) * 2 / SignalResults.Steps;
    Table << "\n \\\\ $p$-value\n  & " << MaxSignificance;
    Table << "\n \\\\ Efficiency\n  & " << SignalEfficiency << std::endl;

    for (size_t BackgroundNumber = 0; BackgroundNumber < BackgroundResults.size(); ++BackgroundNumber) {
        Table << " \\\\ \\verb|" << Mva->GetBackgroundTreeNames().at(BackgroundNumber) << "|\n  & " << BackgroundResults.at(BackgroundNumber).Efficiency.at(MaxBin) << std::endl;
    }

    TCanvas EfficiencyCanvas;
    TMultiGraph MultiGraph;
    for (const auto & BackgroundResult : BackgroundResults) {
      TGraph RejectionGraph(BackgroundResult.Steps, &XValues[0], &BackgroundResult.Efficiency[0]);
        RejectionGraph.SetTitle("");
        MultiGraph.Add(&RejectionGraph);
    }
    TGraph EfficiencyGraph(SignalResults.Steps, &XValues[0], &SignalResults.Efficiency[0]);
    EfficiencyGraph.SetTitle("");
    MultiGraph.Add(&EfficiencyGraph);
    MultiGraph.Draw();
    const std::string EfficiencyFileName = Mva->GetAnalysisName() + "/" + "Efficiency.pdf";
    EfficiencyCanvas.Print(EfficiencyFileName.c_str());

    TCanvas SignificanceCanvas;
    TGraph SignificanceGraph(SignalResults.Steps, &XValues[0], &Significances[0]);
    SignificanceGraph.SetTitle("");
    SignificanceGraph.Draw();
    const std::string SignificanceFileName = Mva->GetAnalysisName() + "/" + "Significance.pdf";
    SignificanceCanvas.Print(SignificanceFileName.c_str());


    std::stringstream TableFooter;
    TableFooter << " \\\\ \\bottomrule\n\\end{tabular}\n\\caption{Significance and efficiencies.}\n\\end{table}\n";
    Table << TableFooter.str();

    std::ofstream LatexFile;
    LatexHeader(LatexFile);
    LatexFile << Table.str();

    LatexFile << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.7\\textwidth]{Efficiency.pdf}\n\\caption{Efficiency}\n\\end{figure}\n";

    LatexFile << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.7\\textwidth]{Significance.pdf}\n\\caption{Significance}\n\\end{figure}\n";

    LatexFooter(LatexFile);
}


float hanalysis::HReader::GetMass(const TFile &File, const std::string &TreeName) const
{
    Print(HNotification, "Get Mass", TreeName);
    const TTree *const Tree = (TTree *)const_cast<TFile *>(&File)->Get(TreeName.c_str());
    Print(HError, "Open Tree", TreeName);
    ExRootTreeReader TreeReader(const_cast<TTree *>(Tree));
    const TClonesArray *ClonesArray = TreeReader.UseBranch(Mva->GetWeightBranchName().c_str());
    TreeReader.ReadEntry(0);
    const HInfoBranch *const Info = (HInfoBranch *) ClonesArray->At(0);
    return Info->Mass;
}

HMvaResult hanalysis::HReader::BdtResult(const TFile &File, const std::string &TreeName, const TFile &ExportFile) const
{
    Print(HNotification, "Apply Bdt", TreeName);
    const float Luminosity = 3000; // 3000 fb-1

    Print(HError, "Open Tree", TreeName);
    const TTree *const Tree = (TTree *)const_cast<TFile *>(&File)->Get(TreeName.c_str());

    Print(HError, "Tree Reader", Tree->GetEntries());
    ExRootTreeReader TreeReader(const_cast<TTree *>(Tree));

    Print(HError, "Branch", Mva->GetWeightBranchName(), TreeReader.GetEntries());
    const TClonesArray *ClonesArray = TreeReader.UseBranch(Mva->GetWeightBranchName().c_str());
    TreeReader.ReadEntry(0);
    const HInfoBranch *const Info = (HInfoBranch *) ClonesArray->At(0);

    HMvaResult Result;
    std::vector<int> Bins = BdtDistribution(TreeReader, TreeName, ExportFile);
    std::vector<int> Integral = Result.CutIntegral(Bins);

    for (int Step = 0; Step < Result.Steps; ++Step) {
        Result.Events[Step] = float(Integral[Step]) / float(Info->EventNumber) * Info->Crosssection * Luminosity;
        Result.Efficiency[Step] = float(Integral[Step]) / float(Info->EventNumber);
        Print(HDebug, "Result", Result.Efficiency[Step], Result.Events[Step]);
    }
    return Result;
}

std::vector<int> hanalysis::HReader::BdtDistribution(const ExRootTreeReader &TreeReader, const std::string TreeName, const TFile &ExportFile) const
{
    Print(HNotification, "Apply Bdt", Mva->GetBranchName());
    std::string NewEventBranchName = Mva->GetBranchName() + "Reader";

    HMvaResult Result;
    std::vector<int> Bins(Result.Steps, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(&TreeReader)->UseBranch(NewEventBranchName.c_str());
    ExRootTreeWriter TreeWriter(const_cast<TFile *>(&ExportFile), TreeName.c_str());
//     ExRootTreeBranch *ResultBranch = TreeWriter.NewBranch(NewEventBranchName.c_str(), HResultBranch::Class());
    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(&TreeReader)->GetEntries())) {
        const_cast<ExRootTreeReader *>(&TreeReader)->ReadEntry(EventNumber);
        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
            const float BdtValue = Mva->ReadBdt(*EventClonesArray, Entry);
//             HResultBranch *Export = static_cast<HResultBranch *>(TreeWriter.NewBranch(NewEventBranchName.c_str(), HResultBranch::Class())->NewEntry());
//             Export->Bdt = BdtValue;
            static_cast<HResultBranch *>(TreeWriter.NewBranch(NewEventBranchName.c_str(), HResultBranch::Class())->NewEntry())->Bdt = BdtValue;
            ++Bins.at(floor(BdtValue * Result.Steps / 2));
        }
        TreeWriter.Fill();
        TreeWriter.Clear();
    }
    TreeWriter.Write();
    return Bins;
}


void hanalysis::HReader::LatexHeader(ofstream &LatexFile) const
{
    Print(HNotification, "LaTeX Header");
    const std::string TexFileName = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + ".tex";
    LatexFile.open(TexFileName);
    LatexFile << "\\documentclass[a4paper,10pt]{article}\n\n"
              << "\\usepackage{booktabs\n}"
              << "\\usepackage{graphicx}\n"
              //               << "\\usepackage[landscape]{geometry}\n"
              //               << "\\usepackage[cm]{fullpage}\n"
              //               << "\\usepackage{units}\n"
              //               << "\\usepackage{siunitx}\n\n"
              //               << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}\n"
              //               << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}\n"
              //               << "\\newcolumntype{E}{R@{$\\pm$}L}\n"
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
