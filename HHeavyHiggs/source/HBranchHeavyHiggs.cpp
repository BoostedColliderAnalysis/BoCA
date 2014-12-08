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


ClassImp(hheavyhiggs::HEventBranch)

hheavyhiggs::HEventBranch::HEventBranch()
{
    
    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;
    LeptonNumber = InitialValue;
    
    HeavyParticleBdt = InitialValue;
    HeavyHiggsBdt = InitialValue;
    
    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;
    
    DeltaRapSum = InitialValue;
    DeltaPhiSum = InitialValue;
    DeltaRSum = InitialValue;
    
    DeltaRapDiff = InitialValue;
    DeltaPhiDiff = InitialValue;
    DeltaRDiff = InitialValue;
    
    Signal = InitialValue;
    
}
