# include "HMvaHiggsTagger.hh"

hdelphes::HMvaHiggsTagger::HMvaHiggsTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    AnalysisName = "HiggsCpv";
    TaggerName = "Higgs";
    SignalNames = {"Higgs"};
    BackgroundNames = {"NotHiggs"};
    TestName = "Test";
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};
    SignalTreeNames = {"pp-x0tt-bblvlv-even"};
    BackgroundTreeNames = TestTreeNames;
    CandidateBranchName = "Higgs";
    Higgs = new HHiggsBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();
}

hdelphes::HMvaHiggsTagger::~HMvaHiggsTagger()
{
    Print(HNotification, "Destructor");
    delete Higgs;
}


std::vector<HHiggsBranch *> hdelphes::HMvaHiggsTagger::GetHiggsTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, HBottomTagger *BottomTagger)
{

    Print(HInformation, "Get Higgs Tags");

    JetTag->SetHeavyParticles( {CpvHiggsId, HiggsId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
//     if (Jets.size() < 2) return 0;

    HJets HiggsJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {

      Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));

      hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
      if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == CpvHiggsId) {
        JetInfo->SetHiggsTag(1);
      } else {
        JetInfo->SetHiggsTag(0);
      }

      const float Bdt = BottomTagger->GetBottomBdt(Jet);
      JetInfo->SetBTag(Bdt);
      Jet.set_user_info(JetInfo);
      Print(HInformation, "Bottom Bdt", Bdt);

      if (JetInfo->GetHiggsTag()) {
        HiggsJets.push_back(Jet);
      } else {
        OtherJets.push_back(Jet);
      }
    }

//     Print(HInformation, "Higgsness", Jets[0].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId), Jets[1].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId));

    std::vector<hdelphes::HSuperStructure> JetPairs;

    if (State == HSignal) {
//       if (HiggsJets.size() < 2) return 0;
      Print(HInformation, "Higgs Jets", HiggsJets.size());
      for (HJets::iterator Jet1 = HiggsJets.begin(); Jet1 != HiggsJets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != HiggsJets.end(); ++Jet2) {
          hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
          JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
          JetPair.Tag = 1;
          JetPairs.push_back(JetPair);
        }
      }
    }

    if (State == HBackground) {
//       if (OtherJets.size() < 2 || (OtherJets.size() < 1 && HiggsJets.size() < 1)) return 0;
      for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
          hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
          JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
          JetPairs.push_back(JetPair);
        }
      }
      for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = HiggsJets.begin(); Jet2 != HiggsJets.end(); ++Jet2) {
          hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
          JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
          JetPairs.push_back(JetPair);
        }
      }
    }

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());
//     if (JetPairs.size() <= 1) return 0;

//     for (const auto & Pair : JetPairs) {
//       HHiggsBranch *HiggsTagger = static_cast<HHiggsBranch *>(HiggsBranch->NewEntry());
//       FillHiggsBranch(Pair, HiggsTagger);
//     }

    std::vector<HHiggsBranch *> HiggsBranches;
    for (const auto & JetPair : JetPairs) {
      HHiggsBranch *HiggsBranch = new HHiggsBranch();
        FillHiggsBranch(JetPair, HiggsBranch);
        HiggsBranches.push_back(HiggsBranch);
    }


    return HiggsBranches;

}

void hdelphes::HMvaHiggsTagger::FillHiggsBranch(const hdelphes::HSuperStructure &Pair, HHiggsBranch *HiggsTagger)
{
  Print(HInformation, "FillPairTagger", Pair.GetBTag());

  HiggsTagger->Mass = Pair.GetInvariantMass();
  HiggsTagger->Pt = Pair.GetPtSum();
  HiggsTagger->DeltaR = Pair.GetDeltaR();
  HiggsTagger->DeltaEta = Pair.GetDeltaEta();
  HiggsTagger->DeltaPhi = Pair.GetPhiDelta();
  HiggsTagger->BottomTag = Pair.GetBTag();
  HiggsTagger->Pull1 = Pair.GetPullAngle1();
  HiggsTagger->Pull2 = Pair.GetPullAngle2();
  HiggsTagger->Pull = Pair.GetPullAngle();
  if (Pair.Tag == 1) {
    HiggsTagger->HiggsTag = 1;
  } else {
    HiggsTagger->HiggsTag = 0;
  }


}

float hdelphes::HMvaHiggsTagger::GetHiggsBdt(const hdelphes::HSuperStructure &Higgs)
{

  HHiggsBranch *HiggsTagger = new HHiggsBranch();
  FillHiggsBranch(Higgs, HiggsTagger);
  const float Bdt = GetBdt(HiggsTagger, Reader->Reader);
  delete HiggsTagger;
  return Bdt;
}

void hdelphes::HMvaHiggsTagger::DefineVariables()
{

  Print(HNotification , "Define Variables");

  Observables.push_back(NewObservable(&Higgs->Mass, "Mass"));
  Observables.push_back(NewObservable(&Higgs->Pt, "Pt"));
  Observables.push_back(NewObservable(&Higgs->DeltaPhi, "DeltaPhi"));
  Observables.push_back(NewObservable(&Higgs->DeltaEta, "DeltaEta"));
  Observables.push_back(NewObservable(&Higgs->DeltaR, "DeltaR"));
  Observables.push_back(NewObservable(&Higgs->Pull1, "Pull1"));
  Observables.push_back(NewObservable(&Higgs->Pull2,"Pull2"));
  Observables.push_back(NewObservable(&Higgs->Pull, "Pull"));
  Observables.push_back(NewObservable(&Higgs->BottomTag, "BottomTag"));

  Spectators.push_back(NewObservable(&Higgs->HiggsTag, "HiggsTag"));

  Print(HNotification, "Variables defined");

}

float hdelphes::HMvaHiggsTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader)
{

  Print(HInformation, "Get Bdt",BdtMethodName);

  *Higgs = *static_cast<HHiggsBranch*>(Branch);
  const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
  Print(HInformation,"BTagger Bdt",BdtEvaluation);

  return ((BdtEvaluation+1)/2);

}
