# include "HBranchHeavyHiggs.hh"

using HeavyHiggs::HHeavyHiggsBranch;

ClassImp(HHeavyHiggsBranch)

HeavyHiggs::HHeavyHiggsBranch::HHeavyHiggsBranch()
{

    reset();

}

HeavyHiggs::HHeavyHiggsBranch::~HHeavyHiggsBranch() {}

void HeavyHiggs::HHeavyHiggsBranch::reset()
{

    int InitialValue = -10;

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

//     TopEta1 = InitialValue;
//     TopEta2 = InitialValue;
//     TopDeltaEta = InitialValue;
//
//     TopPhi1 = InitialValue;
//     TopPhi2 = InitialValue;
//     TopDeltaPhi = InitialValue;
//
//     TopPt1 = InitialValue;
//     TopPt2 = InitialValue;
//     TopInvMass = InitialValue;

}
