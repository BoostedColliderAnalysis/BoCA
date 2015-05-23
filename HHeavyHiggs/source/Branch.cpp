# include "Branch.hh"

ClassImp(heavyhiggs::BranchHeavyHiggs)

heavyhiggs::BranchHeavyHiggs::BranchHeavyHiggs()
{
    JetNumber = int(InitialValue());
    BTag = int(InitialValue());

    BottomRap1 = InitialValue();
    BottomRap2 = InitialValue();
    BottomDeltaRap = InitialValue();
    BottomSumRap = InitialValue();

    BottomPhi1 = InitialValue();
    BottomPhi2 = InitialValue();
    BottomDeltaPhi = InitialValue();
    BottomSumPhi = InitialValue();

    BottomPt1 = InitialValue();
    BottomPt2 = InitialValue();
    BottomInvMass = InitialValue();
    BottomDeltaPt = InitialValue();
}


ClassImp(heavyhiggs::EventLeptonicBranch)

heavyhiggs::EventLeptonicBranch::EventLeptonicBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();

    DeltaPt = InitialValue();
    DeltaRap = InitialValue();
    DeltaPhi = InitialValue();
    DeltaR = InitialValue();

    Bdt = InitialValue();
    Tag = int(InitialValue());

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());

    ScalarHt = InitialValue();

    HiggsMass = InitialValue();
    PairRap = InitialValue();

    RestM = InitialValue();
    RestPt = InitialValue();
    RestHt = InitialValue();
    RestRap = InitialValue();
    RestPhi = InitialValue();
    RestBBdt = InitialValue();
    MaxBBdt = InitialValue();
    TotalBBdt = InitialValue();
    RestBTag = int(InitialValue());
    ThirdBBdt = InitialValue();

    DeltaPt1 = InitialValue();
    DeltaRap1 = InitialValue();
    DeltaPhi1 = InitialValue();
    DeltaR1 = InitialValue();

    DeltaPt2 = InitialValue();
    DeltaRap2 = InitialValue();
    DeltaPhi2 = InitialValue();
    DeltaR2 = InitialValue();

}


ClassImp(heavyhiggs::EventHadronicBranch)

heavyhiggs::EventHadronicBranch::EventHadronicBranch()
{

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());

    ScalarHt = InitialValue();
    HeavyParticleBdt = InitialValue();

    HeavyHiggsBdt = InitialValue();
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();

    BottomSumPt = InitialValue();
    BottomDeltaPt = InitialValue();

    BottomDeltaRap = InitialValue();
    BottomDeltaPhi = InitialValue();
    BottomDeltaR = InitialValue();

    HbSumDeltaRap = InitialValue();
    HbSumDeltaPhi = InitialValue();
    HbSumDeltaR = InitialValue();

    HbDeltaDeltaRap = InitialValue();
    HbDeltaDeltaPhi = InitialValue();
    HbDeltaDeltaR = InitialValue();

    eventTag = int(InitialValue());
}


ClassImp(heavyhiggs::EventSemiBranch)

heavyhiggs::EventSemiBranch::EventSemiBranch()
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



ClassImp(heavyhiggs::EventTtSemiBranch)

heavyhiggs::EventTtSemiBranch::EventTtSemiBranch()
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


ClassImp(heavyhiggs::HBdtBranch)

heavyhiggs::HBdtBranch::HBdtBranch()
{

    eventTag = InitialValue();

    Mass = InitialValue();
    Bdt = InitialValue();
    Error = InitialValue();
    Rarity = InitialValue();

    Probability01 = InitialValue();
    Probability02 = InitialValue();
    Probability03 = InitialValue();
    Probability04 = InitialValue();
    Probability05 = InitialValue();
    Probability06 = InitialValue();
    Probability07 = InitialValue();
    Probability08 = InitialValue();
    Probability09 = InitialValue();
    Probability10 = InitialValue();

}


ClassImp(heavyhiggs::HOctetBranch)

heavyhiggs::HOctetBranch::HOctetBranch()
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


ClassImp(heavyhiggs::HChargedOctetBranch)

heavyhiggs::HChargedOctetBranch::HChargedOctetBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
}

ClassImp(heavyhiggs::HChargedSemiBranch)

heavyhiggs::HChargedSemiBranch::HChargedSemiBranch()
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


ClassImp(heavyhiggs::HChargedLeptonicBranch)

heavyhiggs::HChargedLeptonicBranch::HChargedLeptonicBranch()
{

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());

    ScalarHt = InitialValue();
    HeavyParticleBdt = InitialValue();

    HeavyHiggsBdt = InitialValue();
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();

    BottomSumPt = InitialValue();
    BottomDeltaPt = InitialValue();

    BottomDeltaRap = InitialValue();
    BottomDeltaPhi = InitialValue();
    BottomDeltaR = InitialValue();

    HbSumDeltaRap = InitialValue();
    HbSumDeltaPhi = InitialValue();
    HbSumDeltaR = InitialValue();

    HbDeltaDeltaRap = InitialValue();
    HbDeltaDeltaPhi = InitialValue();
    HbDeltaDeltaR = InitialValue();

    eventTag = int(InitialValue());

}


ClassImp(heavyhiggs::HChargedHadronicBranch)

heavyhiggs::HChargedHadronicBranch::HChargedHadronicBranch()
{

    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());

    ScalarHt = InitialValue();
    HeavyParticleBdt = InitialValue();

    HeavyHiggsBdt = InitialValue();
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();

    BottomSumPt = InitialValue();
    BottomDeltaPt = InitialValue();

    BottomDeltaRap = InitialValue();
    BottomDeltaPhi = InitialValue();
    BottomDeltaR = InitialValue();

    HbSumDeltaRap = InitialValue();
    HbSumDeltaPhi = InitialValue();
    HbSumDeltaR = InitialValue();

    HbDeltaDeltaRap = InitialValue();
    HbDeltaDeltaPhi = InitialValue();
    HbDeltaDeltaR = InitialValue();

    eventTag = int(InitialValue());

}
