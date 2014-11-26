# include "HBranchHeavyHiggs.hh"

ClassImp(hheavyhiggs::HHeavyHiggsBranch)

hheavyhiggs::HHeavyHiggsBranch::HHeavyHiggsBranch()
{
    JetNumber = InitialValue;
    BTag = InitialValue;

    BottomEta1 = InitialValue;
    BottomEta2 = InitialValue;
    BottomDeltaEta = InitialValue;
    BottomSumEta = InitialValue;

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
