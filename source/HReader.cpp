# include "HReader.hh"

hanalysis::HReader::HReader(HMva *NewMva)
{

    Print(HNotification, "Constructor");

//     DebugLevel = HDebug;

    Mva = NewMva;
    AddVariable();
    BookMVA();
}

hanalysis::HReader::~HReader()
{
    Print(HNotification, "Destructor");

    delete Reader;

}

void hanalysis::HReader::AddVariable()
{

    Print(HNotification, "Add Variable");

    const std::string DefaultOptions = "!Color:Silent";
    Reader = new TMVA::Reader(DefaultOptions);

    for (auto & Observable : Mva->GetObservables()) {
        Print(HDebug, "Expression", Observable.Expression);
        Print(HDebug, "Value", *(Observable.GetValue()));
        Reader->AddVariable(Observable.Expression, Observable.GetValue());
    }

    for (auto & Spectator : Mva->GetSpectators()) {
        Reader->AddSpectator(Spectator.Expression, Spectator.GetValue());
    }

}

void hanalysis::HReader::BookMVA()
{
    Print(HNotification, "Book Mva");

    const std::string XmlName = ".weights.xml";

//     const std::string CutWeightFile = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + "_" + Mva->GetCutMethodName() + XmlName;
//     Print(HError, "Opening Weight File", CutWeightFile);
//     Reader->BookMVA(Mva->GetCutMethodName(), CutWeightFile);

    const std::string BdtWeightFile = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + "_" + Mva->GetBdtMethodName() + XmlName;
    Print(HNotification, "Opening Weight File", BdtWeightFile);

    Reader->BookMVA(Mva->GetBdtMethodName(), BdtWeightFile);

}





// void hanalysis::HReader::SimpleMVALoop()
// {
//
//     float Luminosity = 3000; // 3000 fb-1
//     Luminosity *= 1000; //  * pb
//
//     Print(HNotification, "Mva Loop");
//     LatexHeader();
//
//     const std::string ExportFileName = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + Mva->GetBdtMethodName() + ".root";
//     const TFile *ExportFile = TFile::Open(ExportFileName.c_str(), "Recreate");
//
//     const std::string BackgroundFileName = Mva->GetAnalysisName() + "/" + Mva->GetBackgroundName() + ".root";
//     const TFile *BackgroundFile = TFile::Open(BackgroundFileName.c_str());
//     Print(HError, "Open Background File", BackgroundFileName);
//
//     const int Steps = 10;
//     std::vector<float> BackgroundResults(Steps, 0);
//     std::vector<float> SignalResults(Steps, 0);
//
//     for (const auto & BackgroundTreeName : Mva->GetBackgroundTreeNames()) {
//
//         std::vector<float> NewBackgroundResults = ApplyBdt(BackgroundFile, BackgroundTreeName, ExportFile);
//         for (int Step = 0; Step < Steps; ++Step) BackgroundResults[Step] += NewBackgroundResults[Step];
//
//     }
//
// //     for (int Step = 0; Step < Steps; ++Step) Print(HError, "BGR", BackgroundResults[Step]);
//
//     LatexFile << std::endl
//               << "\\begin{table}" << std::endl
//               << "\\centering" << std::endl
//               << "\\begin{tabular}{lrrrrrrrrrr}" << std::endl
//               << " \\\\ \\toprule" << std::endl
//               << "    Mass" << std::endl
//               << "  & \\multicolumn{10}{c}{BDT Cut}" << std::endl
//               << " \\\\ \\cmidrule(r){2-11}" << std::endl;
//
//     for (int Step = 0; Step < Steps; ++Step) {
//         const float Cut = float(Step) / Steps;
//         LatexFile << "  & " << Cut << std::endl;
//     }
//
//     LatexFile << " \\\\ \\midrule" << std::endl;
//
//     const std::string SignalFileName = Mva->GetAnalysisName() + "/" + Mva->GetSignalName() + ".root";
//     const TFile *SignalFile = TFile::Open(SignalFileName.c_str());
//     Print(HError, "Open Signal File", SignalFileName);
//
//     for (const auto & SignalTreeName : Mva->GetSignalTreeNames()) {
//
//         std::vector<float> SignalResults = ApplyBdt(SignalFile, SignalTreeName, ExportFile);
//
//         LatexFile << "\\verb|" << SignalTreeName << "|" << std::endl;
// //         Print(HError, "Signal", SignalTreeName);
//         for (int Step = 0; Step < Steps; ++Step) {
// //             const float Cut = float(Step) / Steps;
//             const float Significance = SignalResults[Step] / std::sqrt(SignalResults[Step] + BackgroundResults[Step]);
// //             Print(HError, "Numbers",SignalNumbers[Step], BackgroundNumbers[Step]);
// //             Print(HError, "Eff", Cut, RoundToDigits(Eff), RoundToDigits(Norm));
//             LatexFile << "  & " << RoundToDigits(Significance) << std::endl;
//         }
//         LatexFile << " \\\\ ";
//
//     }
//
//     const_cast<TFile *>(ExportFile)->Close();
//
//
//
//     LatexFile << "\\bottomrule" << std::endl
//               << "\\end{tabular}" << std::endl
//               << "\\caption{" << Mva->GetTaggerName() << " Significance.}" << std::endl
//               //         << "\\label{tab:}" << Mva->BackgroundVector[BackgroundNumber] << endl;
//               << "\\end{table}" << std::endl;
//     LatexFooter();
//
// }


void hanalysis::HReader::SimpleMVALoop()
{
    Print(HNotification, "Mva Loop");

    LatexHeader();
    ResultStruct BackgroundResults;

    std::stringstream TableHeader;
    TableHeader << std::endl
                << "\\begin{table}" << std::endl
                << "\\centering" << std::endl
                << "\\begin{tabular}{l@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r@{ }r}" << std::endl
                << " \\\\ \\toprule" << std::endl
                << "    Mass" << std::endl
                << "  & \\multicolumn{20}{c}{BDT Cut}" << std::endl
                << " \\\\ \\cmidrule(r){2-21}" << std::endl;

    std::stringstream PlotHeader;
    PlotHeader << std::endl
               << "\\begin{figure}" << std::endl
               << "\\centering" << std::endl
               << "\\begin{tikzpicture}" << std::endl
               << "\\begin{axis}[" << std::endl
               << ", ymin = 0" << std::endl
               << ", xlabel = {BDT}" << std::endl
               << ", ylabel = {Number of events per bin}" << std::endl
               << "]" << std::endl;

    std::stringstream PlotFooter;
    PlotFooter << "\\end{axis}" << std::endl
               << "\\end{tikzpicture};" << std::endl;

    for (int Step = 0; Step < BackgroundResults.Steps; ++Step) {
        const float Cut = float(Step) / BackgroundResults.Steps + 1;
        TableHeader << "  & " << Cut << std::endl;
    }
    TableHeader << " \\\\ \\midrule" << std::endl;

    std::stringstream TableFooter1;
    TableFooter1 << "\\bottomrule" << std::endl
                 << "\\end{tabular}" << std::endl
                 << "\\caption{" << Mva->GetTaggerName();

    std::stringstream TableFooter2;
    TableFooter2 << ".}" << std::endl << "\\end{table}" << std::endl;

    const std::string ExportFileName = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + Mva->GetBdtMethodName() + ".root";
    const TFile *ExportFile = TFile::Open(ExportFileName.c_str(), "Recreate");

    const std::string BackgroundFileName = Mva->GetAnalysisName() + "/" + Mva->GetBackgroundName() + "Reader.root";
    const TFile *BackgroundFile = TFile::Open(BackgroundFileName.c_str());
    Print(HError, "Open Background File", BackgroundFileName);

    std::stringstream EfficiencyTable;
    EfficiencyTable << TableHeader.str();

    std::stringstream BdtPlot;
    BdtPlot << PlotHeader.str();

    for (const auto & BackgroundTreeName : Mva->GetBackgroundTreeNames()) {
        EfficiencyTable << "\\verb|" << BackgroundTreeName << "|" << std::endl;

        ResultStruct NewBackgroundResults = ApplyBdt(BackgroundFile, BackgroundTreeName, ExportFile);
        for (int Step = 0; Step < BackgroundResults.Steps; ++Step) {
            BackgroundResults.Results[Step] += NewBackgroundResults.Results[Step];
            EfficiencyTable << "  & " << RoundToDigits(NewBackgroundResults.Hong[Step]) << std::endl;
        }
        EfficiencyTable << " \\\\ ";
    }

    std::stringstream SignificanceTable;
    SignificanceTable << TableHeader.str();

    const std::string SignalFileName = Mva->GetAnalysisName() + "/" + Mva->GetSignalName() + "Reader.root";
    const TFile *SignalFile = TFile::Open(SignalFileName.c_str());
    Print(HError, "Open Signal File", SignalFileName);

    for (const auto & SignalTreeName : Mva->GetSignalTreeNames()) {
        SignificanceTable << GetMass(SignalFile, SignalTreeName) << std::endl;
        EfficiencyTable << GetMass(SignalFile, SignalTreeName) << std::endl;

        ResultStruct SignalResults = ApplyBdt(SignalFile, SignalTreeName, ExportFile);

        for (int Step = 0; Step < SignalResults.Steps; ++Step) {
            const float Significance = SignalResults.Results[Step] / std::sqrt(SignalResults.Results[Step] + BackgroundResults.Results[Step] + 15);
            SignificanceTable << "  & " << RoundToDigits(Significance) << std::endl;
            EfficiencyTable << "  & " << RoundToDigits(SignalResults.Hong[Step]) << std::endl;
        }
        EfficiencyTable << " \\\\ ";
        SignificanceTable << " \\\\ ";

    }

    const_cast<TFile *>(ExportFile)->Close();

    SignificanceTable << TableFooter1.str();
    SignificanceTable << " Significance";
    SignificanceTable << TableFooter2.str();

    EfficiencyTable << TableFooter1.str();
    EfficiencyTable << " Efficiencies";
    EfficiencyTable << TableFooter2.str();

    LatexFile << EfficiencyTable.str();
    LatexFile << SignificanceTable.str();

    LatexFooter();

}



float hanalysis::HReader::GetMass(const TFile *File, const std::string &TreeName)
{

    const TTree *const Tree = (TTree *)const_cast<TFile *>(File)->Get(TreeName.c_str());
    Print(HError, "Open Tree", TreeName);
    const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));

    const TClonesArray *ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->GetWeightBranchName().c_str());
    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
    const HInfoBranch *const Info = (HInfoBranch *) ClonesArray->At(0);
    return Info->Mass;

}


ResultStruct hanalysis::HReader::ApplyBdt(const TFile *File, const std::string &TreeName, const TFile *ExportFile)
{
    float Luminosity = 3000; // 3000 fb-1
    Luminosity *= 1000; // * pb
    ResultStruct Result;

    const TTree *const Tree = (TTree *)const_cast<TFile *>(File)->Get(TreeName.c_str());
    Print(HError, "Open Tree", TreeName);
    const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));

    const TClonesArray *ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->GetWeightBranchName().c_str());
    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
    const HInfoBranch *const Info = (HInfoBranch *) ClonesArray->At(0);

    std::vector<int> Numbers = Mva->ApplyBdt2(TreeReader, TreeName, ExportFile);

    for (int Step = 0; Step < Result.Steps; ++Step) {
        Result.Results[Step] = float(Numbers[Step]) / float(Info->EventNumber) * Info->Crosssection * Luminosity;
        Result.Hong[Step] = float(Numbers[Step]) / float(Info->EventNumber);
    }

    return Result;
}



// std::vector<int> hanalysis::HReader::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
// {
//     Print(HNotification, "Apply Bdt", Mva->GetBranchName());
//     std::string Temp = Mva->GetBranchName(); // TODO remove this dirty trick
//     Mva->GetBranchName() += "Reader";
//
//     const int Steps = 10;
//     std::vector<int> EventNumbers(Steps);
//
//     const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->GetBranchName().c_str());
//
//     ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
//     ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(Mva->GetBranchName().c_str(), HResultBranch::Class());
//
//     for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
//
//         const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
//
//         for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
//
// //             HEventSemiBranch *Test = (HEventSemiBranch *) EventClonesArray->At(Entry);
//           Mva->GetBranch() =  (HBranch *) EventClonesArray->At(Entry);
//             const float Bdt = Mva->GetBranch()->Bdt;
//
//             HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
//             Export->Bdt = Bdt;
//
//
//             for (int Step = 0; Step < Steps; ++Step) {
//                 const float Cut = float(Step) / Steps;
//                 if (Bdt > Cut) ++EventNumbers.at(Step);
//             }
//
//         }
//
//         TreeWriter->Fill();
//         TreeWriter->Clear();
//     }
//
//     TreeWriter->Write();
//     delete TreeWriter;
//     Mva->GetBranchName() = Temp;
//
//     return EventNumbers;
// }





void hanalysis::HReader::MVALoop()
{

//     SetMva();

    AddVariable(); // TODO i dont nee dthese

    BookMVA(); // TODO i dont need these


    Print(HNotification, "Mva Loop");

    // Export File
    const std::string ExportFileName = Mva->GetAnalysisName() + "/" + Mva->GetBdtMethodName() + ".root";
    const TFile *ExportFile = TFile::Open(ExportFileName.c_str(), "Recreate");

    // Input File
    const std::string InputFileName = Mva->GetAnalysisName() + "/" + Mva->GetTestName() + ".root";
    const TFile *InputFile = TFile::Open(InputFileName.c_str());

    std::cout << "SignalSignificance:\t" << Mva->GetSignalEfficiency() << std::endl;
    if (Mva->LaTeX()) LatexHeader();

    GetCuts();

    for (const auto & TestTreeName : Mva->GetTestTreeNames()) {

        const TTree *const InputTree = (TTree *)const_cast<TFile *>(InputFile)->Get(TestTreeName.c_str());
        const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(InputTree));

        const TClonesArray *ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->GetWeightBranchName().c_str());
        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
        const HInfoBranch *const Info = (HInfoBranch *) ClonesArray->At(0);
        Crosssection = Info->Crosssection * TreeReader->GetEntries() / Info->EventNumber;
        CrosssectionError = Info->CrosssectionError * TreeReader->GetEntries() / Info->EventNumber;
//         Crosssection = Info->Crosssection;
//         CrosssectionError = Info->Error;
        EventGenerated = Info->EventNumber;

        EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

        Mva->ApplyBdt(TreeReader, TestTreeName, ExportFile, Reader);

        ApplyCuts(TreeReader, TestTreeName);

//         delete TreeReader; // FIXME why

    }

    const_cast<TFile *>(ExportFile)->Close();

    if (Mva->LaTeX()) LatexFooter();

}


void hanalysis::HReader::GetCuts()
{
    Print(HNotification, "Get Cuts");

    TMVA::MethodCuts *MethodCuts;

    ReaderStruct.CutsMin.clear();
    ReaderStruct.CutsMax.clear();
    MethodCuts = Reader->FindCutsMVA(Mva->GetCutMethodName()) ;
    MethodCuts->GetCuts(Mva->GetSignalEfficiency(), ReaderStruct.CutsMin, ReaderStruct.CutsMax);

}

void hanalysis::HReader::LatexHeader()
{

    Print(HNotification, "LaTeX Header");

    const std::string TexFileName = Mva->GetAnalysisName() + "/" + Mva->GetTaggerName() + ".tex";

    LatexFile.open(TexFileName);

    LatexFile << "\\documentclass[a4paper,10pt]{article}" << std::endl << std::endl
              << "\\usepackage{booktabs}" << std::endl
              << "\\usepackage[landscape]{geometry}" << std::endl
              << "\\usepackage{fullpage}" << std::endl
//               << "\\usepackage{units}" << std::endl
//               << "\\usepackage{siunitx}" << std::endl << std::endl
//               << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}" << std::endl
//               << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}" << std::endl
//               << "\\newcolumntype{E}{R@{$\\pm$}L}" << std::endl << std::endl
              << "\\begin{document}" << std::endl << std::endl;

}


void hanalysis::HReader::ApplyCuts(const ExRootTreeReader *const TreeReader, const std::string TreeName)
{

    Print(HNotification, "Apply Cuts");

    ReaderStruct = Mva->CutLoop(TreeReader, ReaderStruct);

    std::vector<std::pair<size_t, VectorIterator> > Priority(ReaderStruct.CutFlowVector.size());

    size_t OrderNumber = 0;
    for (VectorIterator Iterator = ReaderStruct.CutFlowVector.begin(); Iterator != ReaderStruct.CutFlowVector.end(); ++Iterator, ++OrderNumber)
        Priority[OrderNumber] = std::make_pair(OrderNumber, Iterator);

    std::sort(Priority.begin(), Priority.end(), PairOrder());

    ReaderStruct.CutFlowVector = SortByPriority(ReaderStruct.CutFlowVector, Priority);
    Mva->SetObservables(SortByPriority(Mva->GetObservables(), Priority));
//     InputVarVector = SortByPriority(InputVarVector, OrderVector);
    ReaderStruct.CutsMin = SortByPriority(ReaderStruct.CutsMin, Priority);
    ReaderStruct.CutsMax = SortByPriority(ReaderStruct.CutsMax, Priority);
    ReaderStruct.EventVector = SortByPriority(ReaderStruct.EventVector, Priority);
    ReaderStruct.TopEventVector = SortByPriority(ReaderStruct.TopEventVector, Priority);
    ReaderStruct.HiggsEventVector = SortByPriority(ReaderStruct.HiggsEventVector, Priority);

    ReaderStruct = Mva->CutLoop(TreeReader, ReaderStruct);

    TabularOutput();

    if (Mva->LaTeX()) LatexContent(TreeName);

}


void hanalysis::HReader::TabularOutput() const
{

    const int NameWidth = 15;
    const int DataWidth = 8;
    const int UnitWidth = 5;

    PrintText("Cut Name", NameWidth);
    PrintText("CutMin", DataWidth);
    PrintUnit("", UnitWidth);
    PrintText("CutMax", DataWidth);
    PrintUnit("", UnitWidth);
    PrintText("# Cand", DataWidth);
    PrintText("# Tops", DataWidth);
    PrintText("# Higgs", DataWidth);
    PrintText("# Event", DataWidth);
    PrintText("t Tag", DataWidth);
    PrintText("h Tag", DataWidth);
    PrintText("Per Event", DataWidth);
    std::cout << std::endl;


    float CandidatsPerEvent = GetRatio(ReaderStruct.FatJetSum, EventSum);

    PrintText("Precut", NameWidth);
    PrintText("", DataWidth);
    PrintUnit("", UnitWidth);
    PrintText("", DataWidth);
    PrintUnit("", UnitWidth);
    PrintData(ReaderStruct.FatJetSum, DataWidth);
    PrintData(ReaderStruct.TopSum, DataWidth);
    PrintData(ReaderStruct.HiggsSum, DataWidth);
    PrintData(EventSum, DataWidth);
    PrintData(ReaderStruct.TopEventSum, DataWidth);
    PrintData(ReaderStruct.HiggsEventSum, DataWidth);
    PrintData(RoundToDigits(CandidatsPerEvent), DataWidth);
    std::cout << std::endl;

    for (unsigned ObservableNumber = 0; ObservableNumber < Mva->GetObservables().size(); ++ObservableNumber) {

        CandidatsPerEvent = GetRatio(ReaderStruct.FatJetVector[ObservableNumber], ReaderStruct.EventVector[ObservableNumber]);

        PrintText(Mva->GetObservables()[ObservableNumber].Title, NameWidth);
        PrintData(RoundToDigits(ReaderStruct.CutsMin[ObservableNumber]), DataWidth);
        PrintUnit(Mva->GetObservables()[ObservableNumber].Unit, UnitWidth);
        PrintData(RoundToDigits(ReaderStruct.CutsMax[ObservableNumber]), DataWidth);
        PrintUnit(Mva->GetObservables()[ObservableNumber].Unit, UnitWidth);
        PrintData(ReaderStruct.FatJetVector[ObservableNumber], DataWidth);
        PrintData(ReaderStruct.TopVector[ObservableNumber], DataWidth);
        PrintData(ReaderStruct.HiggsVector[ObservableNumber], DataWidth);
        PrintData(ReaderStruct.EventVector[ObservableNumber], DataWidth);
        PrintData(ReaderStruct.TopEventVector[ObservableNumber], DataWidth);
        PrintData(ReaderStruct.HiggsEventVector[ObservableNumber], DataWidth);
        PrintData(RoundToDigits(CandidatsPerEvent), DataWidth);
        std::cout << std::endl;


    }

}

void hanalysis::HReader::LatexContent(const std::string &TreeName)
{

    Print(HNotification, "LaTeX Content");

    LatexFile << std::endl
              << "\\begin{table}" << std::endl
              << "\\centering" << std::endl
              << "\\begin{tabular}{lSSEEE}" << std::endl
              << " \\\\ \\toprule" << std::endl
              << "    Cut Name" << std::endl
              << "  & \\multicolumn{2}{c}{Cutvalues}" << std::endl
              << "  & \\multicolumn{6}{c}{Luminosity in fb$^{-1}$}" << std::endl
              << " \\\\ \\cmidrule(r){2-3} \\cmidrule(l){4-9}" << std::endl
              << "  & \\multicolumn{1}{c}{Minimum}" << std::endl
              << "  & \\multicolumn{1}{c}{Maximum}" << std::endl
              << "  & \\multicolumn{2}{c}{fat jets}" << std::endl
              << "  & \\multicolumn{2}{c}{Top}" << std::endl
              << "  & \\multicolumn{2}{c}{Higgs}" << std::endl
              << " \\\\ \\midrule" << std::endl << "   ";

    CrosssectionNorm = Crosssection * 1000; // conversion from pico to femto
    const float CrosssectionNormError = CrosssectionError * 1000;
//     CrosssectionNormRelError =  CrosssectionNormError / CrosssectionNorm;


//     float EventNorm = Mva->Luminosity * CrosssectionNorm; // both are in fb
//     float EventNormError = EventNorm * CrosssectionNormRelError;


//               float EventRatio = EventNorm / EventGenerated;
//     float EvenRatioError = EventNormError / EventGenerated;
//     float EventRatioNormError = EvenRatioError / EventRatio;


    const float Lumi = Mva->GetLuminosity() / EventGenerated;

    float EventLuminosity = EventSum * Lumi;
//               float EventLuminosityError = EventLuminosity * EventRatioNormError;
    float EventLuminosityError = GetError(EventLuminosity);

    float HiggsEventLuminosity = ReaderStruct.HiggsEventSum * Lumi;
    //     float HiggsEventLuminosityError = HiggsEventLuminosity * EventRatioNormError;
    float HiggsEventLuminosityError = GetError(HiggsEventLuminosity);

    float TopEventLuminosity = ReaderStruct.TopEventSum * Lumi;
    //     float TopEventLuminosityError = TopEventLuminosity * EventRatioNormError;
    float TopEventLuminosityError = GetError(TopEventLuminosity);

    LatexFile << " " << "Initial" << std::endl
              << "  & " <<  std::endl
              << "  & " <<  std::endl
              << "  & " << RoundToError(EventLuminosity, EventLuminosityError) << std::endl
              << "  & " << RoundError(EventLuminosityError) << std::endl
              << "  & " << RoundToError(TopEventLuminosity, TopEventLuminosityError) << std::endl
              << "  & " << RoundError(TopEventLuminosityError) << std::endl
              << "  & " << RoundToError(HiggsEventLuminosity, HiggsEventLuminosityError) << std::endl
              << "  & " << RoundError(HiggsEventLuminosityError) << std::endl
              << " \\\\ ";

    int ObservableSum = Mva->GetObservables().size();
    for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

        EventLuminosity = ReaderStruct.EventVector[ObservableNumber] * Lumi;
        EventLuminosityError = GetError(EventLuminosity);
//         EventLuminosityError = EventLuminosity * EventRatioNormError;

        HiggsEventLuminosity = ReaderStruct.HiggsEventVector[ObservableNumber] * Lumi;
        HiggsEventLuminosityError = GetError(HiggsEventLuminosity);
//         HiggsEventLuminosityError = HiggsEventLuminosity * EventRatioNormError;

        TopEventLuminosity = ReaderStruct.TopEventVector[ObservableNumber] * Lumi;
        TopEventLuminosityError = GetError(TopEventLuminosity);
//         TopEventLuminosityError = TopEventLuminosity * EventRatioNormError;

        LatexFile << " " /*<< "$"*/ << Mva->GetObservables()[ObservableNumber].Title /*<< "$"*/ << std::endl
                  << "  & " << RoundToDigits(ReaderStruct.CutsMin[ObservableNumber]) << std::endl
                  << "  & " << RoundToDigits(ReaderStruct.CutsMax[ObservableNumber]) << std::endl
                  << "  & " << RoundToError(EventLuminosity, EventLuminosityError) << std::endl
                  << "  & " << RoundError(EventLuminosityError) << std::endl
                  << "  & " << RoundToError(TopEventLuminosity, TopEventLuminosityError) << std::endl
                  << "  & " << RoundError(TopEventLuminosityError) << std::endl
                  << "  & " << RoundToError(HiggsEventLuminosity, HiggsEventLuminosityError) << std::endl
                  << "  & " << RoundError(HiggsEventLuminosityError) << std::endl
                  << " \\\\ ";

    }

    LatexFile << "\\bottomrule" << std::endl
              << "\\end{tabular}" << std::endl
              << "\\caption{Cutflow for data sample \"" << TreeName << "\" with a crosssection of $\\sigma= \\unit[" << RoundToError(CrosssectionNorm, CrosssectionNormError) << " \\pm " << RoundToDigits(CrosssectionNormError, 2) << "]{fb}$, a signal efficiency of " << Mva->GetSignalEfficiency() << " and a integrated Luminosity of $\\unit[" << Mva->GetLuminosity() << "]{fb^{-1}}$.}" << std::endl
              //         << "\\label{tab:}" << Mva->BackgroundVector[BackgroundNumber] << endl;
              << "\\end{table}" << std::endl;

}

void hanalysis::HReader::LatexFooter()
{

    Print(HNotification, "LaTeX Footer");

    LatexFile << std::endl << "\\end{document}" << std::endl;

    LatexFile.close();

}

float hanalysis::HReader::GetRatio(const float Nominator, const float Denummertor) const
{

    float Ratio;

    if (Denummertor > 0) {

        Ratio = float(Nominator) / Denummertor;

    } else {

        Ratio = 0;

    }

    return Ratio;

}


float hanalysis::HReader::GetScaling(const float Events, const int Particles) const
{

    Print(HInformation , "Scaling");

    float Scaling;

    if (Particles == 0) {

        Scaling = 0;

    } else {

        Scaling = Events / Particles;

    }

    return Scaling;

}



float hanalysis::HReader::GetLuminosity(const float Number) const
{

    Print(HInformation , "Luminosity");

    float Luminosity = Number / CrosssectionScaled;

    return Luminosity;

}

float hanalysis::HReader::GetLuminosityError(const float Number) const
{

    Print(HInformation , "Luminosity Error");

    float LuminosityError = GetError(Number) / CrosssectionScaled
                            + Number / CrosssectionNorm * LuminosityScalingError
                            + GetLuminosity(Number) * CrosssectionNormRelError;

    return LuminosityError;

}


float hanalysis::HReader::GetError(const float Value) const
{
    Print(HInformation , "Error");

    float Error;

    if (Value == 0) {

        Error = 0;

    } else {

        Error = 1 / sqrt(Value);

    }

    return Error;

}


float hanalysis::HReader::RoundToDigits(const float Value) const
{

    return RoundToDigits(Value, 3);

}


float hanalysis::HReader::RoundError(const float Value) const
{

    return RoundToDigits(Value, 2);

}


float hanalysis::HReader::RoundToDigits(const float Value, const int Digits) const
{

    Print(HInformation , "Round To Digits");

    if (Value == 0 || Value != Value) {

        return 0;

    } else {

        const float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
        return (round(Value * Factor) / Factor);

    }
}


float hanalysis::HReader::RoundToError(const float Value, const float Error) const
{

    Print(HInformation , "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {

        const float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));

        return (round(Value * Factor) / Factor);

    }
}



