# include "HMvaDiscriminator.hh"

hcpvhiggs::HMva::HMva()
{

    Print(HNotification , "Constructor");

//     DebugLevel = 4;

    SetTaggerName("Higgs");

//     SignalNames = {"Higgs"};

//     BackgroundNames = {"Top", "Jet"};
//         BackgroundNames = {"Top","Jet"};

//     TestName = "Test";

//     SignalTreeNames = {"even", "mix", "odd"};
//         SignalTreeVector = {"even"};

//     BackgroundTreeNames = {"background", "even", "mix", "odd"};
//         BackgroundTreeVector = {"even"};

//     TestTreeNames = {"background","even", "mix", "odd"};
//         TestTreeVector = {"even"};

//     SetBranchName("Candidate");

//     SpectatorBranchName = "Lepton";

//     WeightBranchName = "Info";

//     SignalEfficiency = 0.5;

//     Luminosity = 3000; // fb

//     DoLatex = 1;

    Candidate = new HCandidateBranch();

    DefineVariables();

//     Cut = "Candidate.SubJet1Pt>0&&Candidate.SubJet2Pt>0&&Candidate.IsolationPt>0";

}

hcpvhiggs::HMva::~HMva()
{

    Print(HNotification , "Constructor");

    delete Candidate;

}

void hcpvhiggs::HMva::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddObservable(Candidate->Mass, "Mass", "m_j");
    AddObservable(Candidate->Pt, "Pt", "p^T_j");
    AddObservable(Candidate->Rap, "Rap","\\eta_j");
    AddObservable(Candidate->Phi, "Phi","\\phi_j");

    AddObservable(Candidate->DeltaR, "DeltaR","Delta R");
    AddObservable(Candidate->SubJetsDeltaR, "SubJetsDeltaR","\\Delta R(j_1,j_2)");
    AddObservable(Candidate->Asymmetry, "Asymmetry","A");
    AddObservable(Candidate->DiPolarity, "DiPolarity","P");

    AddObservable(Candidate->SubJet1Mass, "SubJet1Mass", "m_{j_1}");
    AddObservable(Candidate->SubJet1Pt, "SubJet1Pt");
    AddObservable(Candidate->SubJet1DeltaR,"SubJet1DeltaR");

    AddObservable(Candidate->SubJet2Mass, "SubJet2Mass");
    AddObservable(Candidate->SubJet2Pt, "SubJet2Pt");
    AddObservable(Candidate->SubJet2DeltaR,"SubJet2DeltaR");

    AddObservable(Candidate->ConstRap,  "ConstRap");
    AddObservable(Candidate->ConstPhi,  "ConstPhi");
    AddObservable(Candidate->ConstDeltaR, "ConstDeltaR");
    AddObservable(Candidate->ConstAngle, "ConstAngle");

    AddObservable(Candidate->IsolationRap, "IsolationRap");
    AddObservable(Candidate->IsolationPhi, "IsolationPhi");
    AddObservable(Candidate->IsolationDeltaR, "IsolationDeltaR");
    AddObservable(Candidate->IsolationAngle, "IsolationAngle");
    AddObservable(Candidate->IsolationPt, "IsolationPt");

    AddSpectator(Candidate->HiggsTag, "HiggsTag");
    AddSpectator(Candidate->TopTag, "TopTag");

    Print(HNotification,"Variables defined");

}


void hcpvhiggs::HMva::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
{
  Print(HNotification, "Apply Bdt");

  const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(GetBranchName().c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

  ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
  ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(GetBranchName().c_str(), HCandidateBranch::Class());
//   ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

  const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

  for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

    for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

      (*Candidate) = *((HCandidateBranch *) CandidateClonesArray->At(CandidateNumber));

      HCandidateBranch *ExportCandidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

      (*ExportCandidate) = *Candidate;

      const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(BdtMethodName());

      float SigEff;
      const int StepSize = 50;
      for (SigEff = 0; SigEff < StepSize; ++SigEff) {

        bool CutEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(GetCutMethodName(), SigEff / StepSize);

        if (CutEvaluation) break;

      }

      ExportCandidate->JetBdtTag = BdtEvaluation;
      ExportCandidate->JetCutSigEff = SigEff / StepSize;

      ExportCandidate->TopBdtTag = BdtEvaluation;
      ExportCandidate->TopCutSigEff = SigEff / StepSize;

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


// HReaderStruct hcpvhiggs::HMva::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
// {
//
//   Print(HNotification, "Cut Loop");
//
//   int ObservableSum = Observables.size();
//
//   Print(HNotification,"Observables",Observables.size());
//
//   ReaderStruct.HiggsSum = 0;
//   ReaderStruct.TopSum = 0;
//   ReaderStruct.FatJetSum = 0;
//
//   ReaderStruct.TopEventSum = 0;
//   ReaderStruct.HiggsEventSum = 0;
//
//   ReaderStruct.EventVector.assign(ObservableSum, 0);
//   ReaderStruct.TopEventVector.assign(ObservableSum, 0);
//   ReaderStruct.HiggsEventVector.assign(ObservableSum, 0);
//   ReaderStruct.CutFlowVector.assign(ObservableSum, 0);
//   ReaderStruct.FatJetVector.assign(ObservableSum, 0);
//   ReaderStruct.HiggsVector.assign(ObservableSum, 0);
//   ReaderStruct.TopVector.assign(ObservableSum, 0);
//
//   Print(HInformation,"Vectors assigned");
//
//   const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());
//
//
//   const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();
//   for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {
//       Print(HDebug,"Event Loop");
//
//     const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
//
//     std::vector<bool> CandidateEventCut(ObservableSum, 1);
//     std::vector<bool> TopEventCut(ObservableSum, 1);
//     std::vector<bool> HiggsEventCut(ObservableSum, 1);
//     bool HasHiggs = 0;;
//     bool HasTop = 0;
//
//     for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {
//
//         Print(HDebug,"Candidate Loop");
//       ++ReaderStruct.FatJetSum;
//
//       if (Candidate->TopTag) {
//
//         ++ReaderStruct.TopSum;
//         HasTop = 1;
//
//       }
//
//       if (Candidate->HiggsTag) {
//
//         ++ReaderStruct.HiggsSum;
//         HasHiggs = 1;
//
//       }
//
//       (*Candidate) = *((HCandidateBranch *) ClonesArray->At(CandidateNumber));
//
//       bool ParticleCut = 0;
//       for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
//
//           Print(HDebug,"Observable Loop");
//
//           Print(HDebug,"Error",ReaderStruct.CutsMin[ObservableNumber]);
//
//         if (*Observables[ObservableNumber].GetValue() < ReaderStruct.CutsMin[ObservableNumber]
//             || *Observables[ObservableNumber].GetValue() > ReaderStruct.CutsMax[ObservableNumber]) {
//
//             Print(HDebug,"we are here",1);
//
//             ParticleCut = 1;
//
//           } else {
//
//               Print(HDebug,"we are here",2);
//             ++ReaderStruct.CutFlowVector[ObservableNumber];
//
//           }
//             Print(HDebug,"Struct filled");
//
//           if (!ParticleCut) {
//
//             ++ReaderStruct.FatJetVector[ObservableNumber];
//             CandidateEventCut[ObservableNumber] = 0;
//
//             if (Candidate->TopTag) {
//
//               ++ReaderStruct.TopVector[ObservableNumber];
//               TopEventCut[ObservableNumber] = 0;
//
//             }
//
//             if (Candidate->HiggsTag) {
//
//               ++ReaderStruct.HiggsVector[ObservableNumber];
//               HiggsEventCut[ObservableNumber] = 0;
//
//             }
//
//           }
//
//       }
//
//     }
//
//     if (HasHiggs) ++ReaderStruct.HiggsEventSum;
//     if (HasTop) ++ReaderStruct.TopEventSum;
//
//     for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
//
//       if (!CandidateEventCut[ObservableNumber]) {
//
//         ++ReaderStruct.EventVector[ObservableNumber];
//         if (!HiggsEventCut[ObservableNumber]) ++ReaderStruct.HiggsEventVector[ObservableNumber];
//         if (!TopEventCut[ObservableNumber]) ++ReaderStruct.TopEventVector[ObservableNumber];
//
//       }
//
//     }
//
//   }
//
//   return ReaderStruct;
//
// }
