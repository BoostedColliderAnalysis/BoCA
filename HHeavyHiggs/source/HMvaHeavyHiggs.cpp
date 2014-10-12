# include "HMvaHeavyHiggs.hh"

HMvaHeavyHiggs::HMvaHeavyHiggs()
{

    Print(1 , "Constructor");

    AnalysisName = "HeavyHiggs";

    SignalNameVector = {"Signal"};

    BackgroundNameVector = {"Background"};

    TestName = "Test";

    SignalTreeNameVector = {"Signal_5f"};

    BackgroundTreeNameVector = {"5k_Pt20"};

    TestTreeNameVector = {"Signal_5f","5k_Pt20"};

    CandidateBranchName = "HeavyHiggs";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    Latex = 0;

    HeavyHiggs = new HHeavyHiggsBranch();

    DefineVariables();

}

HMvaHeavyHiggs::~HMvaHeavyHiggs()
{

    Print(1 , "Constructor");

    delete HeavyHiggs;

}

void HMvaHeavyHiggs::DefineVariables()
{

    Print(1 , "Define Variables");

    ObservableVector.push_back(NewObservable(&HeavyHiggs->BottomDeltaEta, "HeavyHiggs.BottomDeltaEta", "BottomeDeltaEta"));
    ObservableVector.push_back(NewObservable(&HeavyHiggs->BottomDeltaPhi, "HeavyHiggs.BottomDeltaPhi", "BottomeDeltaPhi"));

    Print(1,"Variables defined");

}


void HMvaHeavyHiggs::ApplyBdt(const ExRootTreeReader *const TreeReader, const string TreeName, const TFile *const ExportFile, TMVA::Reader * Reader)
{
  Print(1, "Apply Bdt");

  const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

  ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
  ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(CandidateBranchName.c_str(), HHeavyHiggsBranch::Class());
//   ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLe::Class());

  const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

  for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

    for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

      (*HeavyHiggs) = *((HHeavyHiggsBranch *) CandidateClonesArray->At(CandidateNumber));

      HHeavyHiggsBranch *ExportCandidate = static_cast<HHeavyHiggsBranch *>(CandidateBranch->NewEntry());

      (*ExportCandidate) = *HeavyHiggs;

//       const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

      float SigEff;
      const int StepSize = 50;
      for (SigEff = 0; SigEff < StepSize; ++SigEff) {

        bool CutEvaluation = Reader->EvaluateMVA(CutMethodName, SigEff / StepSize);

        if (CutEvaluation) break;

      }

//       ExportCandidate->JetBdtTag = BdtEvaluation;
//       ExportCandidate->JetCutSigEff = SigEff / StepSize;

//       ExportCandidate->TopBdtTag = BdtEvaluation;
//       ExportCandidate->TopCutSigEff = SigEff / StepSize;

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


HReaderStruct HMvaHeavyHiggs::CutLoop(const ExRootTreeReader *const TreeReader)
{

  Print(1, "Cut Loop");

  HReaderStruct ReaderStruct;

  int ObservableSum = ObservableVector.size();
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

  const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());


  const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();
  for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

    vector<bool> CandidateEventCut(ObservableSum, 1);
    vector<bool> TopEventCut(ObservableSum, 1);
    vector<bool> HiggsEventCut(ObservableSum, 1);
    bool HasHiggs = 0;;
    bool HasTop = 0;

    for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {

      ++ReaderStruct.FatJetSum;

//       if (Candidate->TopTag) {

        ++ReaderStruct.TopSum;
        HasTop = 1;

//       }

//       if (Candidate->HiggsTag) {

        ++ReaderStruct.HiggsSum;
        HasHiggs = 1;

//       }

        (*HeavyHiggs) = *((HHeavyHiggsBranch *) ClonesArray->At(CandidateNumber));

      bool ParticleCut = 0;
      for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

        if (*ObservableVector[ObservableNumber].Value < ReaderStruct.CutsMin[ObservableNumber]
          || *ObservableVector[ObservableNumber].Value > ReaderStruct.CutsMax[ObservableNumber]) {

          ParticleCut = 1;

          } else {

            ++ReaderStruct.CutFlowVector[ObservableNumber];

          }

          if (!ParticleCut) {

            ++ReaderStruct.FatJetVector[ObservableNumber];
            CandidateEventCut[ObservableNumber] = 0;

//             if (Candidate->TopTag) {

              ++ReaderStruct.TopVector[ObservableNumber];
              TopEventCut[ObservableNumber] = 0;

//             }

//             if (Candidate->HiggsTag) {

              ++ReaderStruct.HiggsVector[ObservableNumber];
              HiggsEventCut[ObservableNumber] = 0;

//             }

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

