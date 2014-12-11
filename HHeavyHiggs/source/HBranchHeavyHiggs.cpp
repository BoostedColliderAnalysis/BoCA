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


ClassImp(hheavyhiggs::HLeptonicEventBranch)

hheavyhiggs::HLeptonicEventBranch::HLeptonicEventBranch()
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


ClassImp(hheavyhiggs::HHadronicEventBranch)

hheavyhiggs::HHadronicEventBranch::HHadronicEventBranch()
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


ClassImp(hheavyhiggs::HMixedEventBranch)

hheavyhiggs::HMixedEventBranch::HMixedEventBranch()
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
