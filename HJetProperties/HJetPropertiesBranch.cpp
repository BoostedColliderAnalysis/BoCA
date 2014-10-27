# include "HJetPropertiesBranch.hh"

ClassImp(hjetproperties::HCandidateBranch)

hjetproperties::HCandidateBranch::HCandidateBranch()
{

    reset();

}

hjetproperties::HCandidateBranch::~HCandidateBranch() {}

void hjetproperties::HCandidateBranch::reset()
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


ClassImp(hjetproperties::HConstituentBranch)

hjetproperties::HConstituentBranch::HConstituentBranch()
{

  reset();

}

hjetproperties::HConstituentBranch::~HConstituentBranch() {}

void hjetproperties::HConstituentBranch::reset()
{

  int InitialValue = -100;

  Eta = InitialValue;
  Phi = InitialValue;
  Pt = InitialValue;
  Id = InitialValue;

}

ClassImp(hjetproperties::HLeptonBranch)

hjetproperties::HLeptonBranch::HLeptonBranch()
{
    
    reset();
    
}

hjetproperties::HLeptonBranch::~HLeptonBranch() {}

void hjetproperties::HLeptonBranch::reset()
{
    
    int InitialValue = -10;
    
    Mass = InitialValue;
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
    Charge = InitialValue;
    
}


