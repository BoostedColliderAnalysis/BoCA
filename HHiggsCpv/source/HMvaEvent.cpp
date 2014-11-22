# include "HMvaEvent.hh"

hhiggscpv::HMvaEvent::HMvaEvent()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "EventTagger";

    SignalNames = {"Signal"};

    BackgroundNames = {"Background"};

    TestName = "Test";

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};

    BackgroundTreeNames = {"pp-bbtt-bblvlv-background"};

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

    CandidateBranchName = "Candidate";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    EventBranch = new HEventBranch();

    DefineVariables();

//     Cut = "abs(Candidate.Pull11)<3.2&&abs(Candidate.Pull12)<3.2&&abs(Candidate.Pull21)<3.2&&/*/*abs*/*/(Candidate.Pull22)<3.2&&abs(Candidate.Pull31)<3.2&&abs(Candidate.Pull32)<3.2&&abs(Candidate.Pull41)<3.2&&abs(Candidate.Pull42)<3.2";

}

hhiggscpv::HMvaEvent::~HMvaEvent()
{

    Print(HNotification , "Constructor");

    delete EventBranch;

}

void hhiggscpv::HMvaEvent::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&EventBranch->ScalarHt, "ScalarHt"));
    Observables.push_back(NewObservable(&EventBranch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&EventBranch->BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&EventBranch->HiggsTag, "HiggsTag"));

    Spectators.push_back(NewObservable(&EventBranch->HiggsTag, "HiggsTag"));
//     Spectators.push_back(NewObservable(&EventBranch->TopTag, "Candidate.TopTag", "Top Tag"));

    Print(HNotification, "Variables defined");

}

void hhiggscpv::HMvaEvent::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt");

    const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(CandidateBranchName.c_str(), HEventBranch::Class());
//   ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

    const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

            (*EventBranch) = *((HEventBranch *) CandidateClonesArray->At(CandidateNumber));

            HEventBranch *ExportCandidate = static_cast<HEventBranch *>(CandidateBranch->NewEntry());

            (*ExportCandidate) = *EventBranch;

            const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
            
            Print(HInformation,"Bdt",BdtEvaluation);

            float SigEff;
            const int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

                bool CutEvaluation = Reader->EvaluateMVA(CutMethodName, SigEff / StepSize);

                if (CutEvaluation) break;

            }

//             ExportCandidate->JetBdtTag = BdtEvaluation;
//             ExportCandidate->JetCutSigEff = SigEff / StepSize;

//             ExportCandidate->TopBdtTag = BdtEvaluation;
//             ExportCandidate->TopCutSigEff = SigEff / StepSize;

        }

//     for (int CandidateNumber = 0; CandidateNumber < SpectatorClonesArray->GetEntriesFast(); ++CandidateNumber) {

//       HLeptonBranch *Lepton = (HLeptonBranch *) SpectatorClonesArray->At(CandidateNumber);

//       HLeptonBranch *ExportLepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
//       (*ExportLepton) = *Lepton;

//     }

        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

}


HReaderStruct hhiggscpv::HMvaEvent::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
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

        std::vector<bool> CandidateEventCut(ObservableSum, 1);
        std::vector<bool> TopEventCut(ObservableSum, 1);
        std::vector<bool> HiggsEventCut(ObservableSum, 1);
        bool HasHiggs = 0;;
        bool HasTop = 0;

        for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {

            Print(HDebug, "Candidate Loop");
            ++ReaderStruct.FatJetSum;

//             if (EventBranch->TopTag) {

                ++ReaderStruct.TopSum;
                HasTop = 1;

//             }

//             if (EventBranch->HiggsTag) {

                ++ReaderStruct.HiggsSum;
                HasHiggs = 1;

//             }

            (*EventBranch) = *((HEventBranch *) ClonesArray->At(CandidateNumber));

            bool ParticleCut = 0;
            for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

                Print(HDebug, "Observable Loop");

                Print(HDebug, "Error", ReaderStruct.CutsMin[ObservableNumber]);

                if (*Observables[ObservableNumber].GetValue() < ReaderStruct.CutsMin[ObservableNumber]
                    || *Observables[ObservableNumber].GetValue() > ReaderStruct.CutsMax[ObservableNumber]) {

                    Print(HDebug, "we are here", 1);

                    ParticleCut = 1;

                } else {

                    Print(HDebug, "we are here", 2);
                    ++ReaderStruct.CutFlowVector[ObservableNumber];

                }
                Print(HDebug, "Struct filled");

                if (!ParticleCut) {

                    ++ReaderStruct.FatJetVector[ObservableNumber];
                    CandidateEventCut[ObservableNumber] = 0;

//                     if (EventBranch->TopTag) {

                        ++ReaderStruct.TopVector[ObservableNumber];
                        TopEventCut[ObservableNumber] = 0;

//                     }

//                     if (EventBranch->HiggsTag) {

                        ++ReaderStruct.HiggsVector[ObservableNumber];
                        HiggsEventCut[ObservableNumber] = 0;

//                     }

                }

            }

        }

        if (HasHiggs) ++ReaderStruct.HiggsEventSum;
        if (HasTop) ++ReaderStruct.TopEventSum;

        for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

            if (!CandidateEventCut[ObservableNumber]) {

                ++ReaderStruct.EventVector[ObservableNumber];
                if (!HiggsEventCut[ObservableNumber]) ++ReaderStruct.HiggsEventVector[ObservableNumber];
                if (!TopEventCut[ObservableNumber]) ++ReaderStruct.TopEventVector[ObservableNumber];

            }

        }

    }

    return ReaderStruct;

}
