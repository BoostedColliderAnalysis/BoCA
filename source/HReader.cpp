# include "HReader.hh"

HReader::HReader()
{

    if (Debug > 0)Print("HReader", "Constructor");

    Mva = new HMva();

    AddVariable();

    BookMVA();

    MVALoop();

}

HReader::~HReader()
{
    if (Debug > 0)Print("HReader", "Destructor");

    delete Reader;

}


void HReader::AddVariable()
{

    if (Debug > 0)Print("HReader", "Add Variable");

    TString DefaultOptions = "";
    Reader = new TMVA::Reader(DefaultOptions);

    int ObservableSum = Mva->ObservableVector.size();
    for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

        Reader->AddVariable(Mva->ObservableVector[ObservableNumber].Expression, Mva->ObservableVector[ObservableNumber].Value);

    }

    int SpectatorSum = Mva->SpectatorVector.size();
    for (int SpectatorNumber = 0; SpectatorNumber < SpectatorSum; ++SpectatorNumber) {

        Reader->AddSpectator(Mva->SpectatorVector[SpectatorNumber].Expression, Mva->SpectatorVector[SpectatorNumber].Value);

    }

}

void HReader::BookMVA()
{
    if (Debug > 0)Print("HReader", "Book Mva");

    TString XmlName = ".weights.xml";

    TString CutWeightFile = Mva->AnalysisName + "/" + Mva->AnalysisName + "_" + Mva->CutMethodName + "_" + Mva->BackgroundName + XmlName;
    cout << "Opening Weight File: " << CutWeightFile << endl;
    Reader->BookMVA(Mva->CutMethodName, CutWeightFile);

//     TString BdtWeightFile = Mva->AnalysisName + "/" + Mva->AnalysisName + "_" + Mva->BdtMethodName + "_" + Mva->BackgroundName + XmlName;
//     cout << "Opening Weight File: " << BdtWeightFile << endl;
//     Reader->BookMVA(Mva->BdtMethodName, BdtWeightFile);

}

void HReader::MVALoop()
{

    if (Debug > 0)Print("HReader", "Mva Loop");

    // Export File
//     TString ExportFileName = Mva->AnalysisName + "/" + Mva->BdtMethodName + ".root";
//     TFile *ExportFile = TFile::Open(ExportFileName, "Recreate");

    // Input File
    TString InputFileName = Mva->AnalysisName + "/" + Mva->TestName + TString(".root");
    TFile *InputFile = TFile::Open(InputFileName);

    cout << "SignalEfficiency:\t" << Mva->SignalEfficiency << endl;
    if (Mva->Latex) LatexHeader();

    GetCuts();
    
    int TreeSum = Mva->TestTreeVector.size();
    for (int TreeNumber = 0; TreeNumber < TreeSum; ++TreeNumber) {

        TString TreeName = Mva->TestTreeVector[TreeNumber];

        TTree *InputTree = (TTree *)InputFile->Get(TreeName);
        ExRootTreeReader *TreeReader = new ExRootTreeReader(InputTree);

        TClonesArray *ClonesArray = TreeReader->UseBranch(Mva->WeightBranchName);
        TreeReader->ReadEntry(0);
        HInfoBranch *Info = (HInfoBranch *) ClonesArray->At(0);
//         Crosssection = Info->Crosssection * TreeReader->GetEntries() / Info->EventNumber;
//         CrosssectionError = Info->Error * TreeReader->GetEntries() / Info->EventNumber;
        Crosssection = Info->Crosssection;
        CrosssectionError = Info->Error;
        EventGenerated = Info->EventNumber;

        EventSum = TreeReader->GetEntries();

//         ApplyBdt(TreeReader, TreeName, ExportFile);

        ApplyCuts(TreeReader, TreeName);

        delete TreeReader;

    }

//     ExportFile->Close();

    if (Mva->Latex) LatexFooter();

}


void HReader::ApplyBdt(ExRootTreeReader *TreeReader, TString TreeName, TFile *ExportFile)
{
    if (Debug > 0)Print("HReader", "Apply Bdt");

    TClonesArray *CandidateClonesArray = TreeReader->UseBranch(Mva->CandidateBranchName);
    TClonesArray *LeptonClonesArray = TreeReader->UseBranch(Mva->LeptonBranchName);

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(ExportFile, TreeName);
    ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(Mva->CandidateBranchName, HCandidateBranch::Class());
    ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(Mva->LeptonBranchName, HLeptonBranch::Class());


    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

        TreeReader->ReadEntry(EventNumber);

        int CandidateSum = CandidateClonesArray->GetEntriesFast();
        for (int CandidateNumber = 0; CandidateNumber < CandidateSum; ++CandidateNumber) {

            (*Mva->Candidate) = *((HCandidateBranch *) CandidateClonesArray->At(CandidateNumber));

            HCandidateBranch *ExportCandidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

            (*ExportCandidate) = *Mva->Candidate;

//             float BdtEvaluation = Reader->EvaluateMVA(Mva->BdtMethodName);

            float SigEff;
            int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

                bool CutEvaluation = Reader->EvaluateMVA(Mva->CutMethodName, SigEff / StepSize);

                if (CutEvaluation) break;

            }

            //             ExportCandidate->JetBdtTag = BdtEvaluation;
            ExportCandidate->JetCutSigEff = SigEff / StepSize;

            //             ExportCandidate->TopBdtTag = BdtEvaluation;
            ExportCandidate->TopCutSigEff = SigEff / StepSize;

        }



        CandidateSum = LeptonClonesArray->GetEntriesFast();
        for (int CandidateNumber = 0; CandidateNumber < CandidateSum; ++CandidateNumber) {

            HLeptonBranch *Lepton = (HLeptonBranch *) LeptonClonesArray->At(CandidateNumber);

            HLeptonBranch *ExportLepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
            (*ExportLepton) = *Lepton;

        }

        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

}

void HReader::GetCuts()
{
    if (Debug > 0)Print("HReader", "Get Cuts");

    TMVA::MethodCuts *MethodCuts;

    CutsMin.clear();
    CutsMax.clear();
    MethodCuts = Reader->FindCutsMVA(Mva->CutMethodName) ;
    MethodCuts->GetCuts(Mva->SignalEfficiency, CutsMin, CutsMax);
    
}

void HReader::LatexHeader()
{

    if (Debug > 0)Print("HReader", "LaTeX Header");

    TString TexFileName = Mva->AnalysisName + "/" + "Cutflow" + TString(".tex");

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


void HReader::ApplyCuts(ExRootTreeReader *TreeReader, TString TreeName)
{

    if (Debug > 0)Print("HReader", "Apply Cuts");

    CutLoop(TreeReader);

    vector<pair<size_t, VectorIterator> > OrderVector(CutFlowVector.size());

    size_t OrderNumber = 0;
    for (VectorIterator Iterator = CutFlowVector.begin(); Iterator != CutFlowVector.end(); ++Iterator, ++OrderNumber)
        OrderVector[OrderNumber] = std::make_pair(OrderNumber, Iterator);

    sort(OrderVector.begin(), OrderVector.end(), PairOrder());

    CutFlowVector = CutFlowOrder(CutFlowVector, OrderVector);
    Mva->ObservableVector = CutFlowOrder(Mva->ObservableVector, OrderVector);
//     InputVarVector = CutFlowOrder(InputVarVector, OrderVector);
    CutsMin = CutFlowOrder(CutsMin, OrderVector);
    CutsMax = CutFlowOrder(CutsMax, OrderVector);
    EventVector = CutFlowOrder(EventVector, OrderVector);
    TopEventVector = CutFlowOrder(TopEventVector, OrderVector);
    HiggsEventVector = CutFlowOrder(HiggsEventVector, OrderVector);

    CutLoop(TreeReader);

    TabularOutput();

    if (Mva->Latex) LatexContent(TreeName);

}


void HReader::CutLoop(ExRootTreeReader *TreeReader)
{

    if (Debug > 0)Print("HReader", "Cut Loop");

    int ObservableSum = Mva->ObservableVector.size();
    HiggsSum = 0;
    TopSum = 0;
    FatJetSum = 0;
    
    TopEventSum = 0;
    HiggsEventSum = 0;

    EventVector.assign(ObservableSum, 0);
    TopEventVector.assign(ObservableSum, 0);
    HiggsEventVector.assign(ObservableSum, 0);
    CutFlowVector.assign(ObservableSum, 0);
    FatJetVector.assign(ObservableSum, 0);
    HiggsVector.assign(ObservableSum, 0);
    TopVector.assign(ObservableSum, 0);

    TClonesArray *ClonesArray = TreeReader->UseBranch(Mva->CandidateBranchName);

    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

        TreeReader->ReadEntry(EventNumber);

        vector<bool> CandidateEventCut(ObservableSum, 1);
        vector<bool> TopEventCut(ObservableSum, 1);
        vector<bool> HiggsEventCut(ObservableSum, 1);
        bool HasHiggs = 0;;
        bool HasTop = 0;

        int CandidateSum = ClonesArray->GetEntriesFast();
        for (int CandidateNumber = 0; CandidateNumber < CandidateSum; ++CandidateNumber) {

            ++FatJetSum;
            
            if (Mva->Candidate->TopTag) {

                ++TopSum;
                HasTop = 1;

            }

            if (Mva->Candidate->HiggsTag) {

                ++HiggsSum;
                HasHiggs = 1;

            }

            (*Mva->Candidate) = *((HCandidateBranch *) ClonesArray->At(CandidateNumber));

            bool ParticleCut = 0;
            for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

                if (*Mva->ObservableVector[ObservableNumber].Value < CutsMin[ObservableNumber]
                        || *Mva->ObservableVector[ObservableNumber].Value > CutsMax[ObservableNumber]) {

                    ParticleCut = 1;

                } else {

                    ++CutFlowVector[ObservableNumber];

                }

                if (!ParticleCut) {

                    ++FatJetVector[ObservableNumber];
                    CandidateEventCut[ObservableNumber] = 0;

                    if (Mva->Candidate->TopTag) {

                        ++TopVector[ObservableNumber];
                        TopEventCut[ObservableNumber] = 0;

                    }

                    if (Mva->Candidate->HiggsTag) {

                        ++HiggsVector[ObservableNumber];
                        HiggsEventCut[ObservableNumber] = 0;

                    }

                }

            }

        }

        if (HasHiggs) ++HiggsEventSum;
        if (HasTop) ++TopEventSum;

        for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

            if (!CandidateEventCut[ObservableNumber]) {

                ++EventVector[ObservableNumber];
                if (!HiggsEventCut[ObservableNumber]) ++HiggsEventVector[ObservableNumber];
                if (!TopEventCut[ObservableNumber]) ++TopEventVector[ObservableNumber];

            }

        }

    }

}

void HReader::TabularOutput()
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


    float CandidatsPerEvent = Ratio(FatJetSum, EventSum);

    PrintText("Precut", NameWidth);
    PrintText("", DataWidth);
    PrintUnit("", UnitWidth);
    PrintText("", DataWidth);
    PrintUnit("", UnitWidth);
    PrintData(FatJetSum, DataWidth);
    PrintData(TopSum, DataWidth);
    PrintData(HiggsSum, DataWidth);
    PrintData(EventSum, DataWidth);
    PrintData(TopEventSum, DataWidth);
    PrintData(HiggsEventSum, DataWidth);
    PrintData(RoundToDigits(CandidatsPerEvent), DataWidth);
    cout << endl;

    int ObservableSum = Mva->ObservableVector.size();
    for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

        CandidatsPerEvent = Ratio(FatJetVector[ObservableNumber], EventVector[ObservableNumber]);

        PrintText(Mva->ObservableVector[ObservableNumber].Title, NameWidth);
        PrintData(RoundToDigits(CutsMin[ObservableNumber]), DataWidth);
        PrintUnit(Mva->ObservableVector[ObservableNumber].Unit, UnitWidth);
        PrintData(RoundToDigits(CutsMax[ObservableNumber]), DataWidth);
        PrintUnit(Mva->ObservableVector[ObservableNumber].Unit, UnitWidth);
        PrintData(FatJetVector[ObservableNumber], DataWidth);
        PrintData(TopVector[ObservableNumber], DataWidth);
        PrintData(HiggsVector[ObservableNumber], DataWidth);
        PrintData(EventVector[ObservableNumber], DataWidth);
        PrintData(TopEventVector[ObservableNumber], DataWidth);
        PrintData(HiggsEventVector[ObservableNumber], DataWidth);
        PrintData(RoundToDigits(CandidatsPerEvent), DataWidth);
        cout << endl;


    }

}

void HReader::LatexContent(TString TreeName)
{

    if (Debug > 0)Print("HReader", "LaTeX Content");

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
    float CrosssectionNormError = CrosssectionError * 1000;
//     CrosssectionNormRelError =  CrosssectionNormError / CrosssectionNorm;
    
    
//     float EventNorm = Mva->Luminosity * CrosssectionNorm; // both are in fb
//     float EventNormError = EventNorm * CrosssectionNormRelError;
    
             
//               float EventRatio = EventNorm / EventGenerated;
//     float EvenRatioError = EventNormError / EventGenerated;
//     float EventRatioNormError = EvenRatioError / EventRatio;
    
              
              float Lumi = Mva->Luminosity / EventGenerated;

              float EventLuminosity = EventSum * Lumi;
//               float EventLuminosityError = EventLuminosity * EventRatioNormError;
              float EventLuminosityError = Error(EventLuminosity);

              float HiggsEventLuminosity = HiggsEventSum * Lumi;
              //     float HiggsEventLuminosityError = HiggsEventLuminosity * EventRatioNormError;              
    float HiggsEventLuminosityError = Error(HiggsEventLuminosity);

    float TopEventLuminosity = TopEventSum * Lumi;
    //     float TopEventLuminosityError = TopEventLuminosity * EventRatioNormError;
    float TopEventLuminosityError = Error(TopEventLuminosity);

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

    int ObservableSum = Mva->ObservableVector.size();
    for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

        EventLuminosity = EventVector[ObservableNumber] * Lumi;
        EventLuminosityError = Error(EventLuminosity);
//         EventLuminosityError = EventLuminosity * EventRatioNormError;

        HiggsEventLuminosity = HiggsEventVector[ObservableNumber] * Lumi;            
        HiggsEventLuminosityError = Error(HiggsEventLuminosity);
//         HiggsEventLuminosityError = HiggsEventLuminosity * EventRatioNormError;

        TopEventLuminosity = TopEventVector[ObservableNumber] * Lumi;
        TopEventLuminosityError = Error(TopEventLuminosity);
//         TopEventLuminosityError = TopEventLuminosity * EventRatioNormError;

        LatexFile << " " /*<< "$"*/ << Mva->ObservableVector[ObservableNumber].Title /*<< "$"*/ << endl
                  << "  & " << RoundToDigits(CutsMin[ObservableNumber]) << endl
                  << "  & " << RoundToDigits(CutsMax[ObservableNumber]) << endl
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
              << "\\caption{Cutflow for data sample \"" << TreeName << "\" with a crosssection of $\\sigma= \\unit["<< RoundToError(CrosssectionNorm,CrosssectionNormError) << " \\pm " << RoundToDigits(CrosssectionNormError,2) << "]{fb}$, a signal efficiency of " << Mva->SignalEfficiency << " and a integrated Luminosity of $\\unit[" << Mva->Luminosity << "]{fb^{-1}}$.}" << endl
              //         << "\\label{tab:}" << Mva->BackgroundVector[BackgroundNumber] << endl;
              << "\\end{table}" << endl;

}

void HReader::LatexFooter()
{

    if (Debug > 0)Print("HReader", "LaTeX Footer");


    LatexFile << endl << "\\end{document}" << endl;

    LatexFile.close();

}

float HReader::Ratio(float Nominator, float Denummertor)
{


    float Ratio;

    if (Denummertor > 0) {

        Ratio = float(Nominator) / Denummertor;

    } else {

        Ratio = 0;

    }

    return Ratio;

}


float HReader::Scaling(float Events, int Particles)
{

    if (Debug > 1)Print("HReader", "Scaling");

    float Scaling;

    if (Particles == 0) {

        Scaling = 0;

    } else {

        Scaling = Events / Particles;

    }

    return Scaling;

}



float HReader::Luminosity(float Number)
{

    if (Debug > 1)Print("HReader", "Luminosity");

    float Luminosity = Number / CrosssectionScaled;

    return Luminosity;

}

float HReader::LuminosityError(float Number)
{

    if (Debug > 1)Print("HReader", "Luminosity Error");

    float LuminosityError = Error(Number) / CrosssectionScaled
                            + Number / CrosssectionNorm * LuminosityScalingError
                            + Luminosity(Number) * CrosssectionNormRelError;

    return LuminosityError;

}


float HReader::Error(float Value)
{
    if (Debug > 1)Print("HReader", "Error");

    float Error;

    if (Value == 0) {

        Error = 0;

    } else {

        Error = 1 / sqrt(Value);

    }

    return (Error);

}


float HReader::RoundToDigits(float Value)
{

    return RoundToDigits(Value, 3);

}


float HReader::RoundError(float Value)
{
    
    return RoundToDigits(Value, 2);
    
}


float HReader::RoundToDigits(float Value, int Digits)
{

    if (Debug > 1)Print("HReader", "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {

        float Factor = pow(10.0, Digits - ceil(log10(fabs(Value))));
        return (round(Value * Factor) / Factor);

    }
}


float HReader::RoundToError(float Value, float Error)
{

    if (Debug > 1)Print("HReader", "Round To Digits");

    if (Value == 0) {

        return 0;

    } else {


        float Factor = pow(10.0, 2 - ceil(log10(fabs(Error))));
        return (round(Value * Factor) / Factor);

    }
}

