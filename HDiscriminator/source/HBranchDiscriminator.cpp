#include "HBranchDiscriminator.hh"

ClassImp(hcpvhiggs::HCandidateBranch)

hcpvhiggs::HCandidateBranch::HCandidateBranch()
{

    reset();

}

hcpvhiggs::HCandidateBranch::~HCandidateBranch() {}

void hcpvhiggs::HCandidateBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;
    Rap = InitialValue;
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

    ConstRap = InitialValue;
    ConstPhi = InitialValue;
    ConstDeltaR = InitialValue;
    ConstAngle = InitialValue;

    IsolationRap = InitialValue;
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

ClassImp(hcpvhiggs::HLeptonBranch)

hcpvhiggs::HLeptonBranch::HLeptonBranch()
{

    reset();

}

hcpvhiggs::HLeptonBranch::~HLeptonBranch() {}

void hcpvhiggs::HLeptonBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;
    Rap = InitialValue;
    Phi = InitialValue;
    Charge = InitialValue;

}


ClassImp(hcpvhiggs::ConstituentBranch)

hcpvhiggs::ConstituentBranch::ConstituentBranch()
{

  reset();

}

hcpvhiggs::ConstituentBranch::~ConstituentBranch() {}

void hcpvhiggs::ConstituentBranch::reset()
{

  int InitialValue = -100;

  Rap = InitialValue;
  Phi = InitialValue;
  Pt = InitialValue;
  Id = InitialValue;

}

ClassImp(hcpvhiggs::HJetPropertiesBranch)

hcpvhiggs::HJetPropertiesBranch::HJetPropertiesBranch()
{

    reset();

}

hcpvhiggs::HJetPropertiesBranch::~HJetPropertiesBranch() {}

void hcpvhiggs::HJetPropertiesBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;

    Rap = InitialValue;
    Phi = InitialValue;
    Radius = InitialValue;

}


ClassImp(hcpvhiggs::ConstituentBranch)
