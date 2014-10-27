# include "HReader.hh"

hanalysis::HReader::HReader(HMva   *NewMva)
{

    Print(1, "Constructor");

//     DebugLevel = 4;

    Mva = NewMva;

    AddVariable();

    BookMVA();

    MVALoop();

}

hanalysis::HReader::~HReader()
{
    Print(1, "Destructor");

    delete Reader;

}


void hanalysis::HReader::AddVariable()
{

    Print(1, "Add Variable");

    const string DefaultOptions = "";
    Reader = new TMVA::Reader(DefaultOptions);

    for (const auto & Observable : Mva->Observables) {

        Reader->AddVariable(Observable.Expression, Observable.Value);

    }

    for (const auto & Spectator : Mva->Spectators) {

        Reader->AddSpectator(Spectator.Expression, Spectator.Value);

    }

}

void hanalysis::HReader::BookMVA()
{
    Print(1, "Book Mva");

    const string XmlName = ".weights.xml";

    const string CutWeightFile = Mva->AnalysisName + "/" + Mva->AnalysisName + "_" + Mva->CutMethodName + "_" + Mva->BackgroundName + XmlName;
    Print(0, "Opening Weight File", CutWeightFile);

    Reader->BookMVA(Mva->CutMethodName, CutWeightFile);

    const string BdtWeightFile = Mva->AnalysisName + "/" + Mva->AnalysisName + "_" + Mva->BdtMethodName + "_" + Mva->BackgroundName + XmlName;
    Print(0, "Opening Weight File", BdtWeightFile);
    Reader->BookMVA(Mva->BdtMethodName, BdtWeightFile);

}

void hanalysis::HReader::MVALoop()
{

    Print(1, "Mva Loop");

    // Export File
    const string ExportFileName = Mva->AnalysisName + "/" + Mva->BdtMethodName + ".root";
    const TFile *ExportFile = TFile::Open(ExportFileName.c_str(), "Recreate");

    // Input File
    const string InputFileName = Mva->AnalysisName + "/" + Mva->TestName + ".root";
    const TFile *InputFile = TFile::Open(InputFileName.c_str());

    cout << "SignalEfficiency:\t" << Mva->SignalEfficiency << endl;
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

        delete TreeReader;

    }

    const_cast<TFile *>(ExportFile)->Close();

    if (Mva->DoLatex) LatexFooter();

}


void hanalysis::HReader::GetCuts()
{
    Print(1, "Get Cuts");

    TMVA::MethodCuts *MethodCuts;

    ReaderStruct.CutsMin.clear();
    ReaderStruct.CutsMax.clear();
    MethodCuts = Reader->FindCutsMVA(Mva->CutMethodName) ;
    MethodCuts->GetCuts(Mva->SignalEfficiency, ReaderStruct.CutsMin, ReaderStruct.CutsMax);

}

void hanalysis::HReader::LatexHeader()
{

    Print(1, "LaTeX Header");

    const string TexFileName = Mva->AnalysisName + "/" + "Cutflow" + ".tex";

    LatexFile.open(TexFileName);

    LatexFile << "\\documentclass[a4paper,11pt]{article}" << endl << endl
              << "\\usepackage{booktabs}" << endl
              << "\\usepackage{a4wide}" << endl
              << "\\usepackage{units}" << endl
              << "\\usepackage{siunitx}" << endl << endl
              << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}" << endl
              << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}" << endl
              << "\\newcolumntype{E}{R@{$\\pm$}L}" << endl << endl
              << "\\begin{document}" << endl << endl;

}


void hanalysis::HReader::ApplyCuts(const ExRootTreeReader *const TreeReader, const string TreeName)
{

    Print(1, "Apply Cuts");

    ReaderStruct = Mva->CutLoop(TreeReader, ReaderStruct);

    vector<pair<size_t, VectorIterator> > Priority(ReaderStruct.CutFlowVector.size());

    size_t OrderNumber = 0;
    for (VectorIterator Iterator = ReaderStruct.CutFlowVector.begin(); Iterator != ReaderStruct.CutFlowVector.end(); ++Iterator, ++OrderNumber)
        Priority[OrderNumber] = std::make_pair(OrderNumber, Iterator);

    sort(Priority.begin(), Priority.end(), PairOrder());

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
    cout << endl;


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
    cout << endl;

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
        cout << endl;


    }

}

void hanalysis::HReader::LatexContent(const string TreeName)
{

    Print(1, "LaTeX Content");

    LatexFile << endl
              << "\\begin{table}" << endl
              << "\\centering" << endl
              << "\\begin{tabular}{lSSEEE}" << endl
              << " \\\\ \\toprule" << endl
              << "    Cut Name" << endl
              << "  & \\multicolumn{2}{c}{Cutvalues}" << endl
              << "  & \\multicolumn{6}{c}{Luminosity in fb$^{-1}$}" << endl
              << " \\\\ \\cmidrule(r){2-3} \\cmidrule(l){4-9}" << endl
              << "  & \\multicolumn{1}{c}{Minimum}" << endl
              << "  & \\multicolumn{1}{c}{Maximum}" << endl
              << "  & \\multicolumn{2}{c}{fat jets}" << endl
              << "  & \\multicolumn{2}{c}{Top}" << endl
              << "  & \\multicolumn{2}{c}{Higgs}" << endl
              << " \\\\ \\midrule" << endl << "   ";

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

    LatexFile << " " << "Initial" << endl
              << "  & " <<  endl
              << "  & " <<  endl
              << "  & " << RoundToError(EventLuminosity, EventLuminosityError) << endl
              << "  & " << RoundError(EventLuminosityError) << endl
              << "  & " << RoundToError(TopEventLuminosity, TopEventLuminosityError) << endl
              << "  & " << RoundError(TopEventLuminosityError) << endl
              << "  & " << RoundToError(HiggsEventLuminosity, HiggsEventLuminosityError) << endl
              << "  & " << RoundError(HiggsEventLuminosityError) << endl
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

        LatexFile << " " /*<< "$"*/ << Mva->Observables[ObservableNumber].Title /*<< "$"*/ << endl
        << "  & " << RoundToDigits(ReaderStruct.CutsMin[ObservableNumber]) << endl
        << "  & " << RoundToDigits(ReaderStruct.CutsMax[ObservableNumber]) << endl
                  << "  & " << RoundToError(EventLuminosity, EventLuminosityError) << endl
                  << "  & " << RoundError(EventLuminosityError) << endl
                  << "  & " << RoundToError(TopEventLuminosity, TopEventLuminosityError) << endl
                  << "  & " << RoundError(TopEventLuminosityError) << endl
                  << "  & " << RoundToError(HiggsEventLuminosity, HiggsEventLuminosityError) << endl
                  << "  & " << RoundError(HiggsEventLuminosityError) << endl
                  << " \\\\ ";

    }

    LatexFile << "\\bottomrule" << endl
              << "\\end{tabular}" << endl
              << "\\caption{Cutflow for data sample \"" << TreeName << "\" with a crosssection of $\\sigma= \\unit[" << RoundToError(CrosssectionNorm, CrosssectionNormError) << " \\pm " << RoundToDigits(CrosssectionNormError, 2) << "]{fb}$, a signal efficiency of " << Mva->SignalEfficiency << " and a integrated Luminosity of $\\unit[" << Mva->Luminosity << "]{fb^{-1}}$.}" << endl
              //         << "\\label{tab:}" << Mva->BackgroundVector[BackgroundNumber] << endl;
              << "\\end{table}" << endl;

}

void hanalysis::HReader::LatexFooter()
{

    Print(1, "LaTeX Footer");

    LatexFile << endl << "\\end{document}" << endl;

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

    Print(2 , "Scaling");

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

    Print(2 , "Luminosity");

    float Luminosity = Number / CrosssectionScaled;

    return Luminosity;

}

float hanalysis::HReader::GetLuminosityError(const float Number) const
{

    Print(2 , "Luminosity Error");

    float LuminosityError = GetError(Number) / CrosssectionScaled
                            + Number / CrosssectionNorm * LuminosityScalingError
                            + GetLuminosity(Number) * CrosssectionNormRelError;

    return LuminosityError;

}


float hanalysis::HReader::GetError(const float Value) const
{
    Print(2 , "Error");

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

    Print(2 , "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {

        const float Factor = pow(10.0, Digits - ceil(log10(fabs(Value))));
        return (round(Value * Factor) / Factor);

    }
}


float hanalysis::HReader::RoundToError(const float Value, const float Error) const
{

    Print(2 , "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {

        const float Factor = pow(10.0, 2 - ceil(log10(fabs(Error))));

        return (round(Value * Factor) / Factor);

    }
}

