# include "HMvaEvent.hh"
# include  "exroot/ExRootAnalysis.hh"

hhiggscpv::HMvaevent::HMvaevent()
{

    Print(kNotification , "Constructor");

    set_tagger_name("eventTagger");

//     TaggerName = "eventTagger";

//     SignalNames = {"Signal"};

//     BackgroundNames = {"Background"};

//     TestName = "Test";

//     SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
//     SignalTreeNames = {"pp-x0tt-bblvlv-even"};

//     BackgroundTreeNames = {"pp-bbtt-bblvlv-background"};

//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};
//     TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};

//     SetBranchName("event");

//     SpectatorBranchName = "Lepton";

//     WeightBranchName = "Info";

//     SignalEfficiency = 0.5;

//     Luminosity = 3000; // fb

//     DoLatex = 1;

//     eventBranch = new EventBranch();

    DefineVariables();

//     Cut = "abs(Candidate.Pull11)<3.2&&abs(Candidate.Pull12)<3.2&&abs(Candidate.Pull21)<3.2&&/*/*abs*/*/(Candidate.Pull22)<3.2&&abs(Candidate.Pull31)<3.2&&abs(Candidate.Pull32)<3.2&&abs(Candidate.Pull41)<3.2&&abs(Candidate.Pull42)<3.2";

}

hhiggscpv::HMvaevent::~HMvaevent()
{

    Print(kNotification , "Constructor");

    delete eventBranch;

}

void hhiggscpv::HMvaevent::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(eventBranch->ScalarHt, "ScalarHt");
    AddVariable(eventBranch->JetNumber, "JetNumber");
    AddVariable(eventBranch->BottomNumber, "BottomNumber");
//     AddObservable(eventBranch->LeptonNumber, "LeptonNumber");
    AddVariable(eventBranch->HeavyParticleTag, "HeavyParticleTag");

    AddSpectator(eventBranch->Signal, "Signal");

    Print(kNotification, "Variables defined");

}

void hhiggscpv::HMvaevent::ApplyBdt(const exroot::TreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
{
    Print(kNotification, "Apply Bdt");

    const TClonesArray *const CandidateClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(branch_name().c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

    exroot::TreeWriter *TreeWriter = new exroot::TreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    exroot::TreeBranch *CandidateBranch = TreeWriter->NewBranch(branch_name().c_str(), EventBranch::Class());
//   exroot::TreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

    const int eventSum = const_cast<exroot::TreeReader *>(TreeReader)->GetEntries();

    for (int eventNumber = 0; eventNumber < eventSum; ++eventNumber) {

        const_cast<exroot::TreeReader *>(TreeReader)->ReadEntry(eventNumber);

        for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

            (*eventBranch) = *((EventBranch *) CandidateClonesArray->At(CandidateNumber));

            EventBranch *ExportCandidate = static_cast<EventBranch *>(CandidateBranch->NewEntry());

            (*ExportCandidate) = *eventBranch;

            const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());

            Print(kInformation,"Bdt",BdtEvaluation);

            float SigEff;
            const int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

//                 bool CutEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(CutMethodName, SigEff / StepSize);

//                 if (CutEvaluation) break;

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


// ReaderStruct hhiggscpv::HMvaevent::CutLoop(const exroot::TreeReader *const TreeReader, ReaderStruct &ReaderStruct)
// {
//
//     Print(kNotification, "Cut Loop");
//
//     int ObservableSum = Observables.size();
//
//     Print(kNotification, "Observables", Observables.size());
//
//     ReaderStruct.HiggsSum = 0;
//     ReaderStruct.TopSum = 0;
//     ReaderStruct.FatJetSum = 0;
//
//     ReaderStruct.TopeventSum = 0;
//     ReaderStruct.HiggseventSum = 0;
//
//     ReaderStruct.eventVector.assign(ObservableSum, 0);
//     ReaderStruct.TopeventVector.assign(ObservableSum, 0);
//     ReaderStruct.HiggseventVector.assign(ObservableSum, 0);
//     ReaderStruct.CutFlowVector.assign(ObservableSum, 0);
//     ReaderStruct.FatJetVector.assign(ObservableSum, 0);
//     ReaderStruct.HiggsVector.assign(ObservableSum, 0);
//     ReaderStruct.TopVector.assign(ObservableSum, 0);
//
//     Print(kInformation, "Vectors assigned");
//
//     const TClonesArray *const ClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(eventBranchName.c_str());
//
//
//     const int eventSum = const_cast<exroot::TreeReader *>(TreeReader)->GetEntries();
//     for (int eventNumber = 0; eventNumber < eventSum; ++eventNumber) {
//         Print(kDebug, "event Loop");
//
//         const_cast<exroot::TreeReader *>(TreeReader)->ReadEntry(eventNumber);
//
//         std::vector<bool> CandidateeventCut(ObservableSum, 1);
//         std::vector<bool> TopeventCut(ObservableSum, 1);
//         std::vector<bool> HiggseventCut(ObservableSum, 1);
//         bool HasHiggs = 0;;
//         bool HasTop = 0;
//
//         for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {
//
//             Print(kDebug, "Candidate Loop");
//             ++ReaderStruct.FatJetSum;
//
// //             if (eventBranch->TopTag) {
//
//                 ++ReaderStruct.TopSum;
//                 HasTop = 1;
//
// //             }
//
// //             if (eventBranch->HiggsTag) {
//
//                 ++ReaderStruct.HiggsSum;
//                 HasHiggs = 1;
//
// //             }
//
//             (*eventBranch) = *((EventBranch *) ClonesArray->At(CandidateNumber));
//
//             bool ParticleCut = 0;
//             for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
//
//                 Print(kDebug, "Observable Loop");
//
//                 Print(kDebug, "Error", ReaderStruct.CutsMin[ObservableNumber]);
//
//                 if (*Observables[ObservableNumber].GetValue() < ReaderStruct.CutsMin[ObservableNumber]
//                     || *Observables[ObservableNumber].GetValue() > ReaderStruct.CutsMax[ObservableNumber]) {
//
//                     Print(kDebug, "we are here", 1);
//
//                     ParticleCut = 1;
//
//                 } else {
//
//                     Print(kDebug, "we are here", 2);
//                     ++ReaderStruct.CutFlowVector[ObservableNumber];
//
//                 }
//                 Print(kDebug, "Struct filled");
//
//                 if (!ParticleCut) {
//
//                     ++ReaderStruct.FatJetVector[ObservableNumber];
//                     CandidateeventCut[ObservableNumber] = 0;
//
// //                     if (eventBranch->TopTag) {
//
//                         ++ReaderStruct.TopVector[ObservableNumber];
//                         TopeventCut[ObservableNumber] = 0;
//
// //                     }
//
// //                     if (eventBranch->HiggsTag) {
//
//                         ++ReaderStruct.HiggsVector[ObservableNumber];
//                         HiggseventCut[ObservableNumber] = 0;
//
// //                     }
//
//                 }
//
//             }
//
//         }
//
//         if (HasHiggs) ++ReaderStruct.HiggseventSum;
//         if (HasTop) ++ReaderStruct.TopeventSum;
//
//         for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
//
//             if (!CandidateeventCut[ObservableNumber]) {
//
//                 ++ReaderStruct.eventVector[ObservableNumber];
//                 if (!HiggseventCut[ObservableNumber]) ++ReaderStruct.HiggseventVector[ObservableNumber];
//                 if (!TopeventCut[ObservableNumber]) ++ReaderStruct.TopeventVector[ObservableNumber];
//
//             }
//
//         }
//
//     }
//
//     return ReaderStruct;
//
// }
