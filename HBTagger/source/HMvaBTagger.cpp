# include "HMvaBTagger.hh"
# include "ExRootAnalysis/ExRootTreeWriter.h"

hbtagger::HMva::HMva()
{

    Print(kNotification , "Constructor");

    set_tagger_name("BTagger");

//     SignalNames = {"Bottom"};

//     BackgroundNames = {"LightJet"};

//     TestName = "Test";

//     SignalTreeNames = {"pp-hjj-bbjj-run_01"};

//     BackgroundTreeNames = {"pp-hjj-bbjj-run_01"};

//     TestTreeNames = {"pp-hjj-bbjj-run_01"};

//     SetBranchName("Candidate");

//     SpectatorBranchName = "Lepton";

//     WeightBranchName = "Info";

//     SignalEfficiency = 0.5;

//     Luminosity = 3000; // fb

//     DoLatex = 1;

    Candidate = new HBTaggerBranch();

    DefineVariables();

//     Cut = "abs(Candidate.Pull11)<3.2&&abs(Candidate.Pull12)<3.2&&abs(Candidate.Pull21)<3.2&&/*/*abs*/*/(Candidate.Pull22)<3.2&&abs(Candidate.Pull31)<3.2&&abs(Candidate.Pull32)<3.2&&abs(Candidate.Pull41)<3.2&&abs(Candidate.Pull42)<3.2";

}

hbtagger::HMva::~HMva()
{

    Print(kNotification , "Constructor");

    delete Candidate;

}

void hbtagger::HMva::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Candidate->VertexMass, "VertexMass");
    AddVariable(Candidate->JetMass, "JetMass");
    AddVariable(Candidate->VertexNumber, "VertexNumber");
    AddVariable(Candidate->Vertex, "Vertex");

    AddSpectator(Candidate->BTag, "BTag");

    Print(kNotification, "Variables defined");

}


void hbtagger::HMva::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
{
    Print(kNotification, "Apply Bdt");

    const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(branch_name().c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(branch_name().c_str(), HBTaggerBranch::Class());

    const int eventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

    for (int eventNumber = 0; eventNumber < eventSum; ++eventNumber) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(eventNumber);

        for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

            (*Candidate) = *((HBTaggerBranch *) CandidateClonesArray->At(CandidateNumber));

            HBTaggerBranch *ExportCandidate = static_cast<HBTaggerBranch *>(CandidateBranch->NewEntry());

            (*ExportCandidate) = *Candidate;

            const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());

            float SigEff;
            const int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

//                 bool CutEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(GetCutMethodName(), SigEff / StepSize);

//                 if (CutEvaluation) break;

            }

            ExportCandidate->BdtBTag = BdtEvaluation;
            ExportCandidate->BCutSigEff = SigEff / StepSize;

        }


        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

}


// ReaderStruct hbtagger::HMva::CutLoop(const ExRootTreeReader *const TreeReader, ReaderStruct &ReaderStruct)
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
//     const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(eventBranchName.c_str());
//
//
//     const int eventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();
//     for (int eventNumber = 0; eventNumber < eventSum; ++eventNumber) {
//         Print(kDebug, "event Loop");
//
//         const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(eventNumber);
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
//             if (Candidate->BTag) {
//
//                 ++ReaderStruct.TopSum;
//                 HasTop = 1;
//
//             }
//
//             (*Candidate) = *((HBTaggerBranch *) ClonesArray->At(CandidateNumber));
//
//             bool ParticleCut = 0;
//             for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
//
//                 Print(kDebug, "Observable Loop");
//
//                 Print(kDebug, "Error", ReaderStruct.CutsMin[ObservableNumber]);
//
//                 if (*Observables[ObservableNumber].GetValue() < ReaderStruct.CutsMin[ObservableNumber]
//                         || *Observables[ObservableNumber].GetValue() > ReaderStruct.CutsMax[ObservableNumber]) {
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
//                     if (Candidate->BTag) {
//
//                         ++ReaderStruct.TopVector[ObservableNumber];
//                         TopeventCut[ObservableNumber] = 0;
//
//                     }
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
