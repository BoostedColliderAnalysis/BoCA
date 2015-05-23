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
