# include "HBranchTest.hh"

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
