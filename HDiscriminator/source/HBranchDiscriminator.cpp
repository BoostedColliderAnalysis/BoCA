# include "HBranchDiscriminator.hh"

using HiggsCPV::HCandidateBranch;

ClassImp(HCandidateBranch)

HiggsCPV::HCandidateBranch::HCandidateBranch()
{

    reset();

}

HiggsCPV::HCandidateBranch::~HCandidateBranch() {}

void HiggsCPV::HCandidateBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;

    DeltaR = InitialValue;
    SubJetsDeltaR = InitialValue;
    Asymmetry = InitialValue;
    DiPolarity = InitialValue;

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

ClassImp(HiggsCPV::HLeptonBranch)

HiggsCPV::HLeptonBranch::HLeptonBranch()
{

    reset();

}

HiggsCPV::HLeptonBranch::~HLeptonBranch() {}

void HiggsCPV::HLeptonBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
    Charge = InitialValue;

}


ClassImp(HiggsCPV::HConstituentBranch)

HiggsCPV::HConstituentBranch::HConstituentBranch()
{

  reset();

}

HiggsCPV::HConstituentBranch::~HConstituentBranch() {}

void HiggsCPV::HConstituentBranch::reset()
{

  int InitialValue = -100;

  Eta = InitialValue;
  Phi = InitialValue;
  Pt = InitialValue;
  Id = InitialValue;

}

ClassImp(HiggsCPV::HJetPropertiesBranch)

HiggsCPV::HJetPropertiesBranch::HJetPropertiesBranch()
{

    reset();

}

HiggsCPV::HJetPropertiesBranch::~HJetPropertiesBranch() {}

void HiggsCPV::HJetPropertiesBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;

    Eta = InitialValue;
    Phi = InitialValue;
    Radius = InitialValue;

}


ClassImp(HiggsCPV::HConstituentBranch)
