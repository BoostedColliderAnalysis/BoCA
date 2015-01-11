# include "HBranchHeavyHiggs.hh"

ClassImp(hheavyhiggs::HBranchHeavyHiggs)

hheavyhiggs::HBranchHeavyHiggs::HBranchHeavyHiggs()
{
    JetNumber = InitialValue;
    BTag = InitialValue;

    BottomRap1 = InitialValue;
    BottomRap2 = InitialValue;
    BottomDeltaRap = InitialValue;
    BottomSumRap = InitialValue;

    BottomPhi1 = InitialValue;
    BottomPhi2 = InitialValue;
    BottomDeltaPhi = InitialValue;
    BottomSumPhi = InitialValue;

    BottomPt1 = InitialValue;
    BottomPt2 = InitialValue;
    BottomInvMass = InitialValue;
    BottomDeltaPt = InitialValue;
}


ClassImp(hheavyhiggs::HEventLeptonicBranch)

hheavyhiggs::HEventLeptonicBranch::HEventLeptonicBranch()
{

  LeptonNumber = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  ScalarHt = InitialValue;

}


ClassImp(hheavyhiggs::HEventHadronicBranch)

hheavyhiggs::HEventHadronicBranch::HEventHadronicBranch()
{

    LeptonNumber = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;

    ScalarHt = InitialValue;
    HeavyParticleBdt = InitialValue;

    HeavyHiggsBdt = InitialValue;
    HeavyHiggsMass = InitialValue;
    HeavyHiggsPt = InitialValue;

    BottomSumPt = InitialValue;
    BottomDeltaPt = InitialValue;

    BottomDeltaRap = InitialValue;
    BottomDeltaPhi = InitialValue;
    BottomDeltaR = InitialValue;

    HbSumDeltaRap = InitialValue;
    HbSumDeltaPhi = InitialValue;
    HbSumDeltaR = InitialValue;

    HbDeltaDeltaRap = InitialValue;
    HbDeltaDeltaPhi = InitialValue;
    HbDeltaDeltaR = InitialValue;

    EventTag = InitialValue;

}


ClassImp(hheavyhiggs::HEventSemiBranch)

hheavyhiggs::HEventSemiBranch::HEventSemiBranch()
{

  LeptonNumber = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  ScalarHt = InitialValue;

}



ClassImp(hheavyhiggs::HBdtBranch)

hheavyhiggs::HBdtBranch::HBdtBranch()
{

  EventTag = InitialValue;

  Mass = InitialValue;
  Bdt = InitialValue;
  Error = InitialValue;
  Rarity = InitialValue;

  Probability01 = InitialValue;
  Probability02 = InitialValue;
  Probability03 = InitialValue;
  Probability04 = InitialValue;
  Probability05 = InitialValue;
  Probability06 = InitialValue;
  Probability07 = InitialValue;
  Probability08 = InitialValue;
  Probability09 = InitialValue;
  Probability10 = InitialValue;

  EventTag = InitialValue;

}


ClassImp(hheavyhiggs::HChargedSemiBranch)

hheavyhiggs::HChargedSemiBranch::HChargedSemiBranch()
{

  LeptonNumber = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  ScalarHt = InitialValue;
  HeavyParticleBdt = InitialValue;

  HeavyHiggsBdt = InitialValue;
  HeavyHiggsMass = InitialValue;
  HeavyHiggsPt = InitialValue;

  BottomSumPt = InitialValue;
  BottomDeltaPt = InitialValue;

  BottomDeltaRap = InitialValue;
  BottomDeltaPhi = InitialValue;
  BottomDeltaR = InitialValue;

  HbSumDeltaRap = InitialValue;
  HbSumDeltaPhi = InitialValue;
  HbSumDeltaR = InitialValue;

  HbDeltaDeltaRap = InitialValue;
  HbDeltaDeltaPhi = InitialValue;
  HbDeltaDeltaR = InitialValue;

  EventTag = InitialValue;

}


ClassImp(hheavyhiggs::HChargedSemi2Branch)

hheavyhiggs::HChargedSemi2Branch::HChargedSemi2Branch()
{

  LeptonNumber = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  ScalarHt = InitialValue;
  HeavyParticleBdt = InitialValue;

  HeavyHiggsBdt = InitialValue;
  HeavyHiggsMass = InitialValue;
  HeavyHiggsPt = InitialValue;

  BottomSumPt = InitialValue;
  BottomDeltaPt = InitialValue;

  BottomDeltaRap = InitialValue;
  BottomDeltaPhi = InitialValue;
  BottomDeltaR = InitialValue;

  HbSumDeltaRap = InitialValue;
  HbSumDeltaPhi = InitialValue;
  HbSumDeltaR = InitialValue;

  HbDeltaDeltaRap = InitialValue;
  HbDeltaDeltaPhi = InitialValue;
  HbDeltaDeltaR = InitialValue;

  EventTag = InitialValue;

}


ClassImp(hheavyhiggs::HChargedLeptonicBranch)

hheavyhiggs::HChargedLeptonicBranch::HChargedLeptonicBranch()
{

  LeptonNumber = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  ScalarHt = InitialValue;
  HeavyParticleBdt = InitialValue;

  HeavyHiggsBdt = InitialValue;
  HeavyHiggsMass = InitialValue;
  HeavyHiggsPt = InitialValue;

  BottomSumPt = InitialValue;
  BottomDeltaPt = InitialValue;

  BottomDeltaRap = InitialValue;
  BottomDeltaPhi = InitialValue;
  BottomDeltaR = InitialValue;

  HbSumDeltaRap = InitialValue;
  HbSumDeltaPhi = InitialValue;
  HbSumDeltaR = InitialValue;

  HbDeltaDeltaRap = InitialValue;
  HbDeltaDeltaPhi = InitialValue;
  HbDeltaDeltaR = InitialValue;

  EventTag = InitialValue;

}


ClassImp(hheavyhiggs::HChargedHadronicBranch)

hheavyhiggs::HChargedHadronicBranch::HChargedHadronicBranch()
{

  LeptonNumber = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  ScalarHt = InitialValue;
  HeavyParticleBdt = InitialValue;

  HeavyHiggsBdt = InitialValue;
  HeavyHiggsMass = InitialValue;
  HeavyHiggsPt = InitialValue;

  BottomSumPt = InitialValue;
  BottomDeltaPt = InitialValue;

  BottomDeltaRap = InitialValue;
  BottomDeltaPhi = InitialValue;
  BottomDeltaR = InitialValue;

  HbSumDeltaRap = InitialValue;
  HbSumDeltaPhi = InitialValue;
  HbSumDeltaR = InitialValue;

  HbDeltaDeltaRap = InitialValue;
  HbDeltaDeltaPhi = InitialValue;
  HbDeltaDeltaR = InitialValue;

  EventTag = InitialValue;

}
