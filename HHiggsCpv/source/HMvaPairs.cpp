# include "HMvaPairs.hh"

hhiggscpv::HMvaPair::HMvaPair()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";
    
    TaggerName = "EventTagger";

    SignalNames = {"Higgs"};

    BackgroundNames = {"Pair"};

    TestName = "JetPair";

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};

    BackgroundTreeNames = TestTreeNames;

    CandidateBranchName = "Higgs";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Pair = new HPairBranch();

    DefineVariables();

//     Cut = "abs(Pair.Pull11)<3.2&&abs(Pair.Pull12)<3.2&&abs(Pair.Pull21)<3.2&&/*/*abs*/*/(Pair.Pull22)<3.2&&abs(Pair.Pull31)<3.2&&abs(Pair.Pull32)<3.2&&abs(Pair.Pull41)<3.2&&abs(Pair.Pull42)<3.2";

}

hhiggscpv::HMvaPair::~HMvaPair()
{

    Print(HNotification , "Constructor");

    delete Pair;

}

float hhiggscpv::HMvaPair::GetBdt(TObject *Branch, TMVA::Reader *Reader){
    
    Print(HInformation, "Get Bdt",BdtMethodName);
    
    //     *Pair = *Branch;
    
    HPairBranch *TempBranch = static_cast<HPairBranch*>(Branch);
    *Pair = *TempBranch;
    
    Print(HInformation, "Mass", Pair->InvMass);
    
    
    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
    
    Print(HInformation,"BTagger Bdt",BdtEvaluation);
    
    return ((BdtEvaluation+1)/2);
    
}

void hhiggscpv::HMvaPair::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Pair->InvMass, "Pair.InvMass", "InvMass", "GeV"));
    Observables.push_back(NewObservable(&Pair->DeltaR, "Pair.DeltaR", "DeltaR1"));
    Observables.push_back(NewObservable(&Pair->Pull1, "Pair.Pull1", "Pull1"));
    Observables.push_back(NewObservable(&Pair->Pull2, "Pair.Pull2", "Pull2"));
    Observables.push_back(NewObservable(&Pair->Pull, "Pair.Pull", "Pull"));
    Observables.push_back(NewObservable(&Pair->BTag, "Pair.BTag", "BTag3"));

    Spectators.push_back(NewObservable(&Pair->HiggsTag, "Pair.HiggsTag", "Higgs Tag"));
    Spectators.push_back(NewObservable(&Pair->TopTag, "Pair.TopTag", "Top Tag"));

    Print(HNotification, "Variables defined");

}

void hhiggscpv::HMvaPair::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt");

    const TClonesArray *const PairClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *PairBranch = TreeWriter->NewBranch(CandidateBranchName.c_str(), HPairBranch::Class());
//   ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

    const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (int PairNumber = 0; PairNumber < PairClonesArray->GetEntriesFast(); ++PairNumber) {

            (*Pair) = *((HPairBranch *) PairClonesArray->At(PairNumber));

            HPairBranch *ExportPair = static_cast<HPairBranch *>(PairBranch->NewEntry());

            (*ExportPair) = *Pair;

            const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

            float SigEff;
            const int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

                bool CutEvaluation = Reader->EvaluateMVA(CutMethodName, SigEff / StepSize);

                if (CutEvaluation) break;

            }

//             ExportPair->JetBdtTag = BdtEvaluation;
//             ExportPair->JetCutSigEff = SigEff / StepSize;

//             ExportPair->TopBdtTag = BdtEvaluation;
//             ExportPair->TopCutSigEff = SigEff / StepSize;

        }

//     for (int PairNumber = 0; PairNumber < SpectatorClonesArray->GetEntriesFast(); ++PairNumber) {

//       HLeptonBranch *Lepton = (HLeptonBranch *) SpectatorClonesArray->At(PairNumber);

//       HLeptonBranch *ExportLepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
//       (*ExportLepton) = *Lepton;

//     }

        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

}


HReaderStruct hhiggscpv::HMvaPair::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
{

    Print(HNotification, "Cut Loop");

    int ObservableSum = Observables.size();

    Print(HNotification, "Observables", Observables.size());

    ReaderStruct.HiggsSum = 0;
    ReaderStruct.TopSum = 0;
    ReaderStruct.FatJetSum = 0;

    ReaderStruct.TopEventSum = 0;
    ReaderStruct.HiggsEventSum = 0;

    ReaderStruct.EventVector.assign(ObservableSum, 0);
    ReaderStruct.TopEventVector.assign(ObservableSum, 0);
    ReaderStruct.HiggsEventVector.assign(ObservableSum, 0);
    ReaderStruct.CutFlowVector.assign(ObservableSum, 0);
    ReaderStruct.FatJetVector.assign(ObservableSum, 0);
    ReaderStruct.HiggsVector.assign(ObservableSum, 0);
    ReaderStruct.TopVector.assign(ObservableSum, 0);

    Print(HInformation, "Vectors assigned");

    const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());


    const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();
    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {
        Print(HDebug, "Event Loop");

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        std::vector<bool> PairEventCut(ObservableSum, 1);
        std::vector<bool> TopEventCut(ObservableSum, 1);
        std::vector<bool> HiggsEventCut(ObservableSum, 1);
        bool HasHiggs = 0;;
        bool HasTop = 0;

        for (int PairNumber = 0; PairNumber < ClonesArray->GetEntriesFast(); ++PairNumber) {

            Print(HDebug, "Pair Loop");
            ++ReaderStruct.FatJetSum;

            if (Pair->TopTag) {

                ++ReaderStruct.TopSum;
                HasTop = 1;

            }

            if (Pair->HiggsTag) {

                ++ReaderStruct.HiggsSum;
                HasHiggs = 1;

            }

            (*Pair) = *((HPairBranch *) ClonesArray->At(PairNumber));

            bool ParticleCut = 0;
            for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

                Print(HDebug, "Observable Loop");

                Print(HDebug, "Error", ReaderStruct.CutsMin[ObservableNumber]);

                if (*Observables[ObservableNumber].Value < ReaderStruct.CutsMin[ObservableNumber]
                        || *Observables[ObservableNumber].Value > ReaderStruct.CutsMax[ObservableNumber]) {

                    Print(HDebug, "we are here", 1);

                    ParticleCut = 1;

                } else {

                    Print(HDebug, "we are here", 2);
                    ++ReaderStruct.CutFlowVector[ObservableNumber];

                }
                Print(HDebug, "Struct filled");

                if (!ParticleCut) {

                    ++ReaderStruct.FatJetVector[ObservableNumber];
                    PairEventCut[ObservableNumber] = 0;

                    if (Pair->TopTag) {

                        ++ReaderStruct.TopVector[ObservableNumber];
                        TopEventCut[ObservableNumber] = 0;

                    }

                    if (Pair->HiggsTag) {

                        ++ReaderStruct.HiggsVector[ObservableNumber];
                        HiggsEventCut[ObservableNumber] = 0;

                    }

                }

            }

        }

        if (HasHiggs) ++ReaderStruct.HiggsEventSum;
        if (HasTop) ++ReaderStruct.TopEventSum;

        for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

            if (!PairEventCut[ObservableNumber]) {

                ++ReaderStruct.EventVector[ObservableNumber];
                if (!HiggsEventCut[ObservableNumber]) ++ReaderStruct.HiggsEventVector[ObservableNumber];
                if (!TopEventCut[ObservableNumber]) ++ReaderStruct.TopEventVector[ObservableNumber];

            }

        }

    }

    return ReaderStruct;

}
