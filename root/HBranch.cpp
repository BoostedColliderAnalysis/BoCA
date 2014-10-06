# include "HBranch.hh"

ClassImp(HCandidateBranch)

HCandidateBranch::HCandidateBranch()
{

    reset();

}

HCandidateBranch::~HCandidateBranch() {}

void HCandidateBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
    Area = InitialValue;

    SubJetsDeltaR = InitialValue;

    SubJet1Mass = InitialValue;
    SubJet1Pt = InitialValue;
    SubJet1DeltaR = InitialValue;

    SubJet2Mass = InitialValue;
    SubJet2Pt = InitialValue;
    SubJet2DeltaR = InitialValue;

    ConstEta = InitialValue;
    ConstPhi = InitialValue;
    ConstDeltaR = InitialValue;
    ConstAngle = InitialValue;

    IsolationEta = InitialValue;
    IsolationPhi = InitialValue;
    IsolationDeltaR = InitialValue;
    IsolationAngle = InitialValue;
    IsolationPt = InitialValue;

    HiggsTag = InitialValue;
    TopTag = InitialValue;

    TopBdtTag = InitialValue;
    JetBdtTag = InitialValue;

    TopCutSigEff = InitialValue;
    JetCutSigEff = InitialValue;

}

ClassImp(HLeptonBranch)

HLeptonBranch::HLeptonBranch()
{

    reset();

}

HLeptonBranch::~HLeptonBranch() {}

void HLeptonBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
    Charge = InitialValue;

}

ClassImp(HInfoBranch)

HInfoBranch::HInfoBranch()
{

    reset();

}

HInfoBranch::~HInfoBranch() {}

void HInfoBranch::reset()
{

    int InitialValue = -10;

    Crosssection = InitialValue;
    Error = InitialValue;
    EventNumber = InitialValue;

}

ClassImp(HConstituentBranch)

HConstituentBranch::HConstituentBranch()
{

    reset();

}

HConstituentBranch::~HConstituentBranch() {}

void HConstituentBranch::reset()
{

    int InitialValue = -100;

    Eta = InitialValue;
    Phi = InitialValue;
    Pt = InitialValue;
    Id = InitialValue;

}

ClassImp(HHeavyHiggsBranch)

HHeavyHiggsBranch::HHeavyHiggsBranch()
{

    reset();

}

HHeavyHiggsBranch::~HHeavyHiggsBranch() {}

void HHeavyHiggsBranch::reset()
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
