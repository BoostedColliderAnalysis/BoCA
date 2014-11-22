# include "HReader.hh"

hmva::HReader::HReader(HMva *NewMva)
{

    Print(HNotification, "Constructor");

    DebugLevel = HDebug;

    Mva = NewMva;


}

hmva::HReader::~HReader()
{
    Print(HNotification, "Destructor");

    delete Reader;

}


void hmva::HReader::AddVariable()
{

    Print(HNotification, "Add Variable");

    const std::string DefaultOptions = "";
    Reader = new TMVA::Reader(DefaultOptions);

    for (auto & Observable : Mva->Observables) {
        Print(HDebug, "Expression", Observable.Expression);
        Print(HDebug, "Value", *(Observable.GetValue()));
        Reader->AddVariable(Observable.Expression, Observable.GetValue());
    }

    for (auto & Spectator : Mva->Spectators) {
        Reader->AddSpectator(Spectator.Expression, Spectator.GetValue());
    }

}

void hmva::HReader::BookMVA()
{
    Print(HNotification, "Book Mva");

    const std::string XmlName = ".weights.xml";

//     const std::string CutWeightFile = Mva->AnalysisName + "/" + Mva->AnalysisName + "_" + Mva->CutMethodName + "_" + Mva->BackgroundName + XmlName;
    const std::string CutWeightFile = Mva->AnalysisName + "/" + Mva->TaggerName + "_" + Mva->CutMethodName + "_" + Mva->BackgroundName + XmlName;
    Print(HError, "Opening Weight File", CutWeightFile);

    Reader->BookMVA(Mva->CutMethodName, CutWeightFile);

//     const std::string BdtWeightFile = Mva->AnalysisName + "/" + Mva->AnalysisName + "_" + Mva->BdtMethodName + "_" + Mva->BackgroundName + XmlName;
    const std::string BdtWeightFile = Mva->AnalysisName + "/" + Mva->TaggerName + "_" + Mva->BdtMethodName + "_" + Mva->BackgroundName + XmlName;
    Print(HError, "Opening Weight File", BdtWeightFile);
    Reader->BookMVA(Mva->BdtMethodName, BdtWeightFile);

}

void hmva::HReader::MVALoop()
{



    AddVariable();

    BookMVA();

    Print(HNotification, "Mva Loop");

    // Export File
    const std::string ExportFileName = Mva->AnalysisName + "/" + Mva->BdtMethodName + ".root";
    const TFile *ExportFile = TFile::Open(ExportFileName.c_str(), "Recreate");

    // Input File
    const std::string InputFileName = Mva->AnalysisName + "/" + Mva->TestName + ".root";
    const TFile *InputFile = TFile::Open(InputFileName.c_str());

    std::cout << "SignalEfficiency:\t" << Mva->SignalEfficiency << std::endl;
    if (Mva->DoLatex) LatexHeader();

    GetCuts();

    for (const auto & TestTreeName : Mva->TestTreeNames) {

        const TTree *const InputTree = (TTree *)const_cast<TFile *>(InputFile)->Get(TestTreeName.c_str());
        const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(InputTree));

        const TClonesArray *ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->WeightBranchName.c_str());
        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
        const HInfoBranch *const Info = (HInfoBranch *) ClonesArray->At(0);
        Crosssection = Info->Crosssection * TreeReader->GetEntries() / Info->EventNumber;
        CrosssectionError = Info->Error * TreeReader->GetEntries() / Info->EventNumber;
//         Crosssection = Info->Crosssection;
//         CrosssectionError = Info->Error;
        EventGenerated = Info->EventNumber;

        EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

        Mva->ApplyBdt(TreeReader, TestTreeName, ExportFile, Reader);

        ApplyCuts(TreeReader, TestTreeName);

//         delete TreeReader; // FIXME why

    }

    const_cast<TFile *>(ExportFile)->Close();

    if (Mva->DoLatex) LatexFooter();

}


void hmva::HReader::GetCuts()
{
    Print(HNotification, "Get Cuts");

    TMVA::MethodCuts *MethodCuts;

    ReaderStruct.CutsMin.clear();
    ReaderStruct.CutsMax.clear();
    MethodCuts = Reader->FindCutsMVA(Mva->CutMethodName) ;
    MethodCuts->GetCuts(Mva->SignalEfficiency, ReaderStruct.CutsMin, ReaderStruct.CutsMax);

}

void hmva::HReader::LatexHeader()
{

    Print(HNotification, "LaTeX Header");

    const std::string TexFileName = Mva->AnalysisName + "/" + "Cutflow" + ".tex";

    LatexFile.open(TexFileName);

    LatexFile << "\\documentclass[a4paper,11pt]{article}" << std::endl << std::endl
              << "\\usepackage{booktabs}" << std::endl
              << "\\usepackage{a4wide}" << std::endl
              << "\\usepackage{units}" << std::endl
              << "\\usepackage{siunitx}" << std::endl << std::endl
              << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}" << std::endl
              << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}" << std::endl
              << "\\newcolumntype{E}{R@{$\\pm$}L}" << std::endl << std::endl
              << "\\begin{document}" << std::endl << std::endl;

}


void hmva::HReader::ApplyCuts(const ExRootTreeReader *const TreeReader, const std::string TreeName)
{

    Print(HNotification, "Apply Cuts");

    ReaderStruct = Mva->CutLoop(TreeReader, ReaderStruct);

    std::vector<std::pair<size_t, VectorIterator> > Priority(ReaderStruct.CutFlowVector.size());

    size_t OrderNumber = 0;
    for (VectorIterator Iterator = ReaderStruct.CutFlowVector.begin(); Iterator != ReaderStruct.CutFlowVector.end(); ++Iterator, ++OrderNumber)
        Priority[OrderNumber] = std::make_pair(OrderNumber, Iterator);

    std::sort(Priority.begin(), Priority.end(), PairOrder());

    ReaderStruct.CutFlowVector = SortByPriority(ReaderStruct.CutFlowVector, Priority);
    Mva->Observables = SortByPriority(Mva->Observables, Priority);
//     InputVarVector = SortByPriority(InputVarVector, OrderVector);
    ReaderStruct.CutsMin = SortByPriority(ReaderStruct.CutsMin, Priority);
    ReaderStruct.CutsMax = SortByPriority(ReaderStruct.CutsMax, Priority);
    ReaderStruct.EventVector = SortByPriority(ReaderStruct.EventVector, Priority);
    ReaderStruct.TopEventVector = SortByPriority(ReaderStruct.TopEventVector, Priority);
    ReaderStruct.HiggsEventVector = SortByPriority(ReaderStruct.HiggsEventVector, Priority);

    ReaderStruct = Mva->CutLoop(TreeReader, ReaderStruct);

    TabularOutput();

    if (Mva->DoLatex) LatexContent(TreeName);

}


void hmva::HReader::TabularOutput() const
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

    for (unsigned ObservableNumber = 0; ObservableNumber < Mva->Observables.size(); ++ObservableNumber) {

        CandidatsPerEvent = GetRatio(ReaderStruct.FatJetVector[ObservableNumber], ReaderStruct.EventVector[ObservableNumber]);

        PrintText(Mva->Observables[ObservableNumber].Title, NameWidth);
        PrintData(RoundToDigits(ReaderStruct.CutsMin[ObservableNumber]), DataWidth);
        PrintUnit(Mva->Observables[ObservableNumber].Unit, UnitWidth);
        PrintData(RoundToDigits(ReaderStruct.CutsMax[ObservableNumber]), DataWidth);
        PrintUnit(Mva->Observables[ObservableNumber].Unit, UnitWidth);
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

void hmva::HReader::LatexContent(const std::string &TreeName)
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


    const float Lumi = Mva->Luminosity / EventGenerated;

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

    int ObservableSum = Mva->Observables.size();
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

        LatexFile << " " /*<< "$"*/ << Mva->Observables[ObservableNumber].Title /*<< "$"*/ << std::endl
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
              << "\\caption{Cutflow for data sample \"" << TreeName << "\" with a crosssection of $\\sigma= \\unit[" << RoundToError(CrosssectionNorm, CrosssectionNormError) << " \\pm " << RoundToDigits(CrosssectionNormError, 2) << "]{fb}$, a signal efficiency of " << Mva->SignalEfficiency << " and a integrated Luminosity of $\\unit[" << Mva->Luminosity << "]{fb^{-1}}$.}" << std::endl
              //         << "\\label{tab:}" << Mva->BackgroundVector[BackgroundNumber] << endl;
              << "\\end{table}" << std::endl;

}

void hmva::HReader::LatexFooter()
{

    Print(HNotification, "LaTeX Footer");

    LatexFile << std::endl << "\\end{document}" << std::endl;

    LatexFile.close();

}

float hmva::HReader::GetRatio(const float Nominator, const float Denummertor) const
{

    float Ratio;

    if (Denummertor > 0) {

        Ratio = float(Nominator) / Denummertor;

    } else {

        Ratio = 0;

    }

    return Ratio;

}


float hmva::HReader::GetScaling(const float Events, const int Particles) const
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



float hmva::HReader::GetLuminosity(const float Number) const
{

    Print(HInformation , "Luminosity");

    float Luminosity = Number / CrosssectionScaled;

    return Luminosity;

}

float hmva::HReader::GetLuminosityError(const float Number) const
{

    Print(HInformation , "Luminosity Error");

    float LuminosityError = GetError(Number) / CrosssectionScaled
                            + Number / CrosssectionNorm * LuminosityScalingError
                            + GetLuminosity(Number) * CrosssectionNormRelError;

    return LuminosityError;

}


float hmva::HReader::GetError(const float Value) const
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


float hmva::HReader::RoundToDigits(const float Value) const
{

    return RoundToDigits(Value, 3);

}


float hmva::HReader::RoundError(const float Value) const
{

    return RoundToDigits(Value, 2);

}


float hmva::HReader::RoundToDigits(const float Value, const int Digits) const
{

    Print(HInformation , "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {

        const float Factor = std::pow(10.0, Digits - ceil(log10(std::abs(Value))));
        return (round(Value * Factor) / Factor);

    }
}


float hmva::HReader::RoundToError(const float Value, const float Error) const
{

    Print(HInformation , "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {

        const float Factor = std::pow(10.0, 2 - ceil(log10(std::abs(Error))));

        return (round(Value * Factor) / Factor);

    }
}

float hmva::HReader::GetBdt() const
{


//     return Reader->EvaluateMVA(BdtMethodName);
    return 1;

}

