# include "HMvaDiscriminator.hh"

HMvaDiscriminator::HMvaDiscriminator()
{

    Print(1 , "Constructor");

//     DebugLevel = 4;

    AnalysisName = "Discriminator";

//     SignalVector = {"Higgs","HiggsTop"};
    SignalNames = {"Higgs"};

//     BackgroundVector = {"Top", "Jet","TwoTop"};
    BackgroundNames = {"Top", "Jet"};
//         BackgroundVector = {"Top"};

    TestName = "Test";

    SignalTreeNames = {"even", "mix", "odd"};
//         SignalTreeVector = {"even"};

    BackgroundTreeNames = {"background", "even", "mix", "odd"};
//         BackgroundTreeVector = {"even"};

    TestTreeNames = {"background","even", "mix", "odd"};
//         TestTreeVector = {"even"};

    CandidateBranchName = "Candidate";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Candidate = new HCandidateBranch();

    DefineVariables();

    Cut = "Candidate.SubJet1Pt>0&&Candidate.SubJet2Pt>0&&Candidate.IsolationPt>0";

}

HMvaDiscriminator::~HMvaDiscriminator()
{

    Print(1 , "Constructor");

    delete Candidate;

}

void HMvaDiscriminator::DefineVariables()
{

    Print(1 , "Define Variables");

    Observables.push_back(NewObservable(&Candidate->Mass, "Candidate.Mass", "Mass", "GeV","m_j"));
    Observables.push_back(NewObservable(&Candidate->Pt, "Candidate.Pt","Pt", "GeV","p^T_j"));
    Observables.push_back(NewObservable(&Candidate->Eta, "Candidate.Eta", "Eta","","\\eta_j"));
    Observables.push_back(NewObservable(&Candidate->Phi, "Candidate.Phi", "Phi","","\\phi_j"));

    Observables.push_back(NewObservable(&Candidate->SubJetsDeltaR, "Candidate.SubJetsDeltaR", "SubJet DeltaR","","\\Delta R(j_1,j_2)"));

    Observables.push_back(NewObservable(&Candidate->SubJet1Mass, "Candidate.SubJet1Mass","SubJet1 Mass", "GeV","m_{j_1}"));
    Observables.push_back(NewObservable(&Candidate->SubJet1Pt, "Candidate.SubJet1Pt","SubJet1 Pt", "GeV"));
    Observables.push_back(NewObservable(&Candidate->SubJet1DeltaR,"Candidate.SubJet1DeltaR","SubJet1 DeltaR"));

    Observables.push_back(NewObservable(&Candidate->SubJet2Mass, "Candidate.SubJet2Mass","SubJet2 Mass", "GeV"));
    Observables.push_back(NewObservable(&Candidate->SubJet2Pt, "Candidate.SubJet2Pt","SubJet2 Pt", "GeV"));
    Observables.push_back(NewObservable(&Candidate->SubJet2DeltaR,"Candidate.SubJet2DeltaR","SubJet2 DeltaR"));

//     ObservableVector.push_back(NewObservable(&Candidate->ConstEta, "Candidate.ConstEta", "Const Eta"));
//     ObservableVector.push_back(NewObservable(&Candidate->ConstPhi, "Candidate.ConstPhi", "Const Phi"));
    Observables.push_back(NewObservable(&Candidate->ConstDeltaR, "Candidate.ConstDeltaR","Const DeltaR"));
    Observables.push_back(NewObservable(&Candidate->ConstAngle, "Candidate.ConstAngle","Const Angle"));

//     ObservableVector.push_back(NewObservable(&Candidate->IsolationEta, "Candidate.IsolationEta"));
//     ObservableVector.push_back(NewObservable(&Candidate->IsolationPhi, "Candidate.IsolationPhi"));
    Observables.push_back(NewObservable(&Candidate->IsolationDeltaR, "Candidate.IsolationDeltaR","Isol DeltaR"));
    Observables.push_back(NewObservable(&Candidate->IsolationAngle, "Candidate.IsolationAngle","Isol Angle"));
    Observables.push_back(NewObservable(&Candidate->IsolationPt, "Candidate.IsolationPt","Isol Pt", "GeV"));

    Spectators.push_back(NewObservable(&Candidate->HiggsTag, "Candidate.HiggsTag","Higgs Tag"));
    Spectators.push_back(NewObservable(&Candidate->TopTag, "Candidate.TopTag","Top Tag"));

    Print(1,"Variables defined");

}


void HMvaDiscriminator::ApplyBdt(const ExRootTreeReader *const TreeReader, const string TreeName, const TFile *const ExportFile, TMVA::Reader * Reader)
{
  Print(1, "Apply Bdt");

  const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());
  const TClonesArray *const SpectatorClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

  ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
  ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(CandidateBranchName.c_str(), HCandidateBranch::Class());
  ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

  const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

  for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

    for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

      (*Candidate) = *((HCandidateBranch *) CandidateClonesArray->At(CandidateNumber));

      HCandidateBranch *ExportCandidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

      (*ExportCandidate) = *Candidate;

      const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

      float SigEff;
      const int StepSize = 50;
      for (SigEff = 0; SigEff < StepSize; ++SigEff) {

        bool CutEvaluation = Reader->EvaluateMVA(CutMethodName, SigEff / StepSize);

        if (CutEvaluation) break;

      }

      ExportCandidate->JetBdtTag = BdtEvaluation;
      ExportCandidate->JetCutSigEff = SigEff / StepSize;

      ExportCandidate->TopBdtTag = BdtEvaluation;
      ExportCandidate->TopCutSigEff = SigEff / StepSize;

    }

    for (int CandidateNumber = 0; CandidateNumber < SpectatorClonesArray->GetEntriesFast(); ++CandidateNumber) {

      HLeptonBranch *Lepton = (HLeptonBranch *) SpectatorClonesArray->At(CandidateNumber);

      HLeptonBranch *ExportLepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
      (*ExportLepton) = *Lepton;

    }

    TreeWriter->Fill();
    TreeWriter->Clear();

  }

  TreeWriter->Write();
  delete TreeWriter;

}


HReaderStruct HMvaDiscriminator::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
{

  Print(1, "Cut Loop");

  int ObservableSum = Observables.size();
  
  Print(1,"Observables",Observables.size());
  
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
  
  Print(2,"Vectors assigned");

  const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());


  const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();
  for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {
      Print(3,"Event Loop");

    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

    vector<bool> CandidateEventCut(ObservableSum, 1);
    vector<bool> TopEventCut(ObservableSum, 1);
    vector<bool> HiggsEventCut(ObservableSum, 1);
    bool HasHiggs = 0;;
    bool HasTop = 0;

    for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {
        
        Print(3,"Candidate Loop");
      ++ReaderStruct.FatJetSum;

      if (Candidate->TopTag) {

        ++ReaderStruct.TopSum;
        HasTop = 1;

      }

      if (Candidate->HiggsTag) {

        ++ReaderStruct.HiggsSum;
        HasHiggs = 1;

      }

      (*Candidate) = *((HCandidateBranch *) ClonesArray->At(CandidateNumber));

      bool ParticleCut = 0;
      for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {
          
          Print(3,"Observable Loop");
          
          Print(3,"Error",ReaderStruct.CutsMin[ObservableNumber]);

        if (*Observables[ObservableNumber].Value < ReaderStruct.CutsMin[ObservableNumber]
          || *Observables[ObservableNumber].Value > ReaderStruct.CutsMax[ObservableNumber]) {

            Print(3,"we are here",1);
            
            ParticleCut = 1;

          } else {
              
              Print(3,"we are here",2);
            ++ReaderStruct.CutFlowVector[ObservableNumber];

          }
            Print(3,"Struct filled");

          if (!ParticleCut) {

            ++ReaderStruct.FatJetVector[ObservableNumber];
            CandidateEventCut[ObservableNumber] = 0;

            if (Candidate->TopTag) {

              ++ReaderStruct.TopVector[ObservableNumber];
              TopEventCut[ObservableNumber] = 0;

            }

            if (Candidate->HiggsTag) {

              ++ReaderStruct.HiggsVector[ObservableNumber];
              HiggsEventCut[ObservableNumber] = 0;

            }

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
