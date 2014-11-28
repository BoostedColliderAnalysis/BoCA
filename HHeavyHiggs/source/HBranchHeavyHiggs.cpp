# include "HBranchHeavyHiggs.hh"

ClassImp(hheavyhiggs::HHeavyHiggsBranch)

hheavyhiggs::HHeavyHiggsBranch::HHeavyHiggsBranch()
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


ClassImp(hheavyhiggs::HEventBranch)

hheavyhiggs::HEventBranch::HEventBranch()
{
    
    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;
    LeptonNumber = InitialValue;
    HeavyParticleTag = InitialValue;
    
    Signal = InitialValue;
    
}
