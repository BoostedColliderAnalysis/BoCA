# include "Branch.hh"


ClassImp(heavyhiggs::HeavyHiggsLeptonicBranch)

heavyhiggs::HeavyHiggsLeptonicBranch::HeavyHiggsLeptonicBranch()
{
  LargerWDeltaRap = InitialValue();
  LargerWDeltaPhi = InitialValue();
  LargerWDeltaR = InitialValue();
  SmallerWDeltaRap = InitialValue();
  SmallerWDeltaPhi = InitialValue();
  SmallerWDeltaR = InitialValue();
  LargerNeutrinoDeltaRap = InitialValue();
  LargerNeutrinoDeltaPhi = InitialValue();
  LargerNeutrinoDeltaR = InitialValue();
  SmallerNeutrinoDeltaRap = InitialValue();
  SmallerNeutrinoDeltaPhi = InitialValue();
  SmallerNeutrinoDeltaR = InitialValue();
}

ClassImp(heavyhiggs::HHeavyHiggsHadronicBranch)

heavyhiggs::HHeavyHiggsHadronicBranch::HHeavyHiggsHadronicBranch()
{
  HeavyHiggsMass = InitialValue();
  HeavyHiggsPt = InitialValue();
  TopDeltaRap = InitialValue();
  TopDeltaPhi = InitialValue();
  TopDeltaR = InitialValue();
  TopBdt = InitialValue();
  HeavyHiggsTag = int(InitialValue());
}

ClassImp(heavyhiggs::HeavyHiggsSemiBranch)

heavyhiggs::HeavyHiggsSemiBranch::HeavyHiggsSemiBranch() {}

ClassImp(heavyhiggs::ChargedHiggsSemiBranch)

heavyhiggs::ChargedHiggsSemiBranch::ChargedHiggsSemiBranch()
{
  Flag = int(InitialValue());
}

ClassImp(heavyhiggs::HChargedHiggsHadronicBranch)

heavyhiggs::HChargedHiggsHadronicBranch::HChargedHiggsHadronicBranch()
{
  HeavyHiggsMass = InitialValue();
  HeavyHiggsPt = InitialValue();
  TopDeltaRap = InitialValue();
  TopDeltaPhi = InitialValue();
  TopDeltaR = InitialValue();
  TopBdt = InitialValue();
  HeavyHiggsTag = int(InitialValue());
}


ClassImp(heavyhiggs::ChargedHiggsLeptonicBranch)

heavyhiggs::ChargedHiggsLeptonicBranch::ChargedHiggsLeptonicBranch()
{
  HeavyHiggsMass = InitialValue();
  HeavyHiggsPt = InitialValue();
  TopDeltaRap = InitialValue();
  TopDeltaPhi = InitialValue();
  TopDeltaR = InitialValue();
  LargerWDeltaRap = InitialValue();
  LargerWDeltaPhi = InitialValue();
  LargerWDeltaR = InitialValue();
  SmallerWDeltaRap = InitialValue();
  SmallerWDeltaPhi = InitialValue();
  SmallerWDeltaR = InitialValue();
  LargerNeutrinoDeltaRap = InitialValue();
  LargerNeutrinoDeltaPhi = InitialValue();
  LargerNeutrinoDeltaR = InitialValue();
  SmallerNeutrinoDeltaRap = InitialValue();
  SmallerNeutrinoDeltaPhi = InitialValue();
  SmallerNeutrinoDeltaR = InitialValue();
  TopBdt = InitialValue();
  HeavyHiggsTag = int(InitialValue());
}


ClassImp(heavyhiggs::HeavyHiggsTauBranch)

heavyhiggs::HeavyHiggsTauBranch::HeavyHiggsTauBranch()
{
  NeutrinoPt = InitialValue();
  LeptonPt = InitialValue();
}

ClassImp(heavyhiggs::EventNeutralBranch)

heavyhiggs::EventNeutralBranch::EventNeutralBranch()
{

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());
    ScalarHt = InitialValue();

    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();

    RestNumber = int(InitialValue());
    RestM = InitialValue();
    RestPt = InitialValue();
    RestHt = InitialValue();
    RestRap = InitialValue();
    RestPhi = InitialValue();
    RestBdt = InitialValue();
    LeptonHt = InitialValue();

    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    MissingEt = InitialValue();

    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();

    SubBottomBdt1 = InitialValue();
    SubBottomBdt2 = InitialValue();
    SubBottomBdt3 = InitialValue();
    SubBottomBdt4 = InitialValue();
    SubBottomBdt5 = InitialValue();
    SubBottomBdt6 = InitialValue();
    SubBottomBdt7 = InitialValue();
    SubBottomBdt8 = InitialValue();
    SubBottomBdt12 = InitialValue();
    SubBottomBdt34 = InitialValue();
    SubBottomBdt56 = InitialValue();
    SubBottomBdt78 = InitialValue();

}

ClassImp(heavyhiggs::EventFusionBranch)

heavyhiggs::EventFusionBranch::EventFusionBranch()
{

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());
    ScalarHt = InitialValue();

    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();

    RestNumber = int(InitialValue());
    RestM = InitialValue();
    RestPt = InitialValue();
    RestHt = InitialValue();
    RestRap = InitialValue();
    RestPhi = InitialValue();
    RestBdt = InitialValue();
    LeptonHt = InitialValue();

}


ClassImp(heavyhiggs::OctetNeutralBranch)

heavyhiggs::OctetNeutralBranch::OctetNeutralBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}


ClassImp(heavyhiggs::OctetChargedBranch)

heavyhiggs::OctetChargedBranch::OctetChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
}

ClassImp(heavyhiggs::EventChargedBranch)

heavyhiggs::EventChargedBranch::EventChargedBranch()
{

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());

    ScalarHt = InitialValue();

    HiggsMass = InitialValue();
    PairRap = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();

    RestM = InitialValue();
    RestPt = InitialValue();
    RestHt = InitialValue();
    RestRap = InitialValue();
    RestPhi = InitialValue();
    RestNumber = int(InitialValue());
    LeptonHt = InitialValue();
    MissingEt = InitialValue();

    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();

    SubBottomBdt1 = InitialValue();
    SubBottomBdt2 = InitialValue();
    SubBottomBdt3 = InitialValue();
    SubBottomBdt4 = InitialValue();
    SubBottomBdt5 = InitialValue();
    SubBottomBdt6 = InitialValue();
    SubBottomBdt7 = InitialValue();
    SubBottomBdt8 = InitialValue();
    SubBottomBdt12 = InitialValue();
    SubBottomBdt34 = InitialValue();
    SubBottomBdt56 = InitialValue();
    SubBottomBdt78 = InitialValue();
}
