# include "HMvaDiscriminator.hh"
# include  "exroot/ExRootAnalysis.hh"
# include "TClonesArray.h"

hcpvhiggs::HMva::HMva()
{

  Print(analysis::Severity::Notification , "Constructor");

//     DebugLevel = 4;

    set_tagger_name("Higgs");

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

  Print(analysis::Severity::Notification , "Constructor");

    delete Candidate;

}

void hcpvhiggs::HMva::DefineVariables()
{

  Print(analysis::Severity::Notification , "Define Variables");

    AddVariable(Candidate->Mass, "Mass", "m_j");
    AddVariable(Candidate->Pt, "Pt", "p^T_j");
    AddVariable(Candidate->Rap, "Rap","\\eta_j");
    AddVariable(Candidate->Phi, "Phi","\\phi_j");

    AddVariable(Candidate->DeltaR, "DeltaR","Delta R");
    AddVariable(Candidate->SubJetsDeltaR, "SubJetsDeltaR","\\Delta R(j_1,j_2)");
    AddVariable(Candidate->Asymmetry, "Asymmetry","A");
    AddVariable(Candidate->DiPolarity, "DiPolarity","P");

    AddVariable(Candidate->SubJet1Mass, "SubJet1Mass", "m_{j_1}");
    AddVariable(Candidate->SubJet1Pt, "SubJet1Pt");
    AddVariable(Candidate->SubJet1DeltaR,"SubJet1DeltaR");

    AddVariable(Candidate->SubJet2Mass, "SubJet2Mass");
    AddVariable(Candidate->SubJet2Pt, "SubJet2Pt");
    AddVariable(Candidate->SubJet2DeltaR,"SubJet2DeltaR");

    AddVariable(Candidate->ConstRap,  "ConstRap");
    AddVariable(Candidate->ConstPhi,  "ConstPhi");
    AddVariable(Candidate->ConstDeltaR, "ConstDeltaR");
    AddVariable(Candidate->ConstAngle, "ConstAngle");

    AddVariable(Candidate->IsolationRap, "IsolationRap");
    AddVariable(Candidate->IsolationPhi, "IsolationPhi");
    AddVariable(Candidate->IsolationDeltaR, "IsolationDeltaR");
    AddVariable(Candidate->IsolationAngle, "IsolationAngle");
    AddVariable(Candidate->IsolationPt, "IsolationPt");

    AddSpectator(Candidate->HiggsTag, "HiggsTag");
    AddSpectator(Candidate->TopTag, "TopTag");

    Print(analysis::Severity::Notification,"Variables defined");

}


void hcpvhiggs::HMva::ApplyBdt(const exroot::TreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
{
  Print(analysis::Severity::Notification, "Apply Bdt");

  const TClonesArray *const CandidateClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(branch_name().c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

  exroot::TreeWriter *TreeWriter = new exroot::TreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
  exroot::TreeBranch *CandidateBranch = TreeWriter->NewBranch(branch_name().c_str(), HCandidateBranch::Class());
//   exroot::TreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

  const int eventSum = const_cast<exroot::TreeReader *>(TreeReader)->GetEntries();

  for (int eventNumber = 0; eventNumber < eventSum; ++eventNumber) {

    const_cast<exroot::TreeReader *>(TreeReader)->ReadEntry(eventNumber);

    for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

      (*Candidate) = *((HCandidateBranch *) CandidateClonesArray->At(CandidateNumber));

      HCandidateBranch *ExportCandidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

      (*ExportCandidate) = *Candidate;

      const float BdtEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name());

      float SigEff;
      const int StepSize = 50;
      for (SigEff = 0; SigEff < StepSize; ++SigEff) {

//         bool CutEvaluation = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(GetCutMethodName(), SigEff / StepSize);

//         if (CutEvaluation) break;

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


// ReaderStruct hcpvhiggs::HMva::CutLoop(const exroot::TreeReader *const TreeReader, ReaderStruct &ReaderStruct)
// {
//
//   Print(Severity::Notification, "Cut Loop");
//
//   int ObservableSum = Observables.size();
//
//   Print(Severity::Notification,"Observables",Observables.size());
//
//   ReaderStruct.HiggsSum = 0;
//   ReaderStruct.TopSum = 0;
//   ReaderStruct.FatJetSum = 0;
//
//   ReaderStruct.TopeventSum = 0;
//   ReaderStruct.HiggseventSum = 0;
//
//   ReaderStruct.eventVector.assign(ObservableSum, 0);
//   ReaderStruct.TopeventVector.assign(ObservableSum, 0);
//   ReaderStruct.HiggseventVector.assign(ObservableSum, 0);
//   ReaderStruct.CutFlowVector.assign(ObservableSum, 0);
//   ReaderStruct.FatJetVector.assign(ObservableSum, 0);
//   ReaderStruct.HiggsVector.assign(ObservableSum, 0);
//   ReaderStruct.TopVector.assign(ObservableSum, 0);
//
//   Print(Severity::Information,"Vectors assigned");
//
//   const TClonesArray *const ClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(eventBranchName.c_str());
//
//
//   const int eventSum = const_cast<exroot::TreeReader *>(TreeReader)->GetEntries();
//   for (int eventNumber = 0; eventNumber < eventSum; ++eventNumber) {
//       Print(Severity::Debug,"event Loop");
//
//     const_cast<exroot::TreeReader *>(TreeReader)->ReadEntry(eventNumber);
//
//     std::vector<bool> CandidateeventCut(ObservableSum, 1);
//     std::vector<bool> TopeventCut(ObservableSum, 1);
//     std::vector<bool> HiggseventCut(ObservableSum, 1);
//     bool HasHiggs = 0;;
//     bool HasTop = 0;
//
//     for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {
//
//         Print(Severity::Debug,"Candidate Loop");
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
//           Print(Severity::Debug,"Observable Loop");
//
//           Print(Severity::Debug,"Error",ReaderStruct.CutsMin[ObservableNumber]);
//
//         if (*Observables[ObservableNumber].GetValue() < ReaderStruct.CutsMin[ObservableNumber]
//             || *Observables[ObservableNumber].GetValue() > ReaderStruct.CutsMax[ObservableNumber]) {
//
//             Print(Severity::Debug,"we are here",1);
//
//             ParticleCut = 1;
//
//           } else {
//
//               Print(Severity::Debug,"we are here",2);
//             ++ReaderStruct.CutFlowVector[ObservableNumber];
//
//           }
//             Print(Severity::Debug,"Struct filled");
//
//           if (!ParticleCut) {
//
//             ++ReaderStruct.FatJetVector[ObservableNumber];
//             CandidateeventCut[ObservableNumber] = 0;
//
//             if (Candidate->TopTag) {
//
//               ++ReaderStruct.TopVector[ObservableNumber];
//               TopeventCut[ObservableNumber] = 0;
//
//             }
//
//             if (Candidate->HiggsTag) {
//
//               ++ReaderStruct.HiggsVector[ObservableNumber];
//               HiggseventCut[ObservableNumber] = 0;
//
//             }
//
//           }
//
//       }
//
//     }
//
//     if (HasHiggs) ++ReaderStruct.HiggseventSum;
//     if (HasTop) ++ReaderStruct.TopeventSum;
//
//     for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
//
//       if (!CandidateeventCut[ObservableNumber]) {
//
//         ++ReaderStruct.eventVector[ObservableNumber];
//         if (!HiggseventCut[ObservableNumber]) ++ReaderStruct.HiggseventVector[ObservableNumber];
//         if (!TopeventCut[ObservableNumber]) ++ReaderStruct.TopeventVector[ObservableNumber];
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
