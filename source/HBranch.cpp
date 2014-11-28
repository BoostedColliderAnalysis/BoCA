# include "HBranch.hh"

ClassImp(HInfoBranch)

HInfoBranch::HInfoBranch()
{
    Crosssection = InitialValue;
    CrosssectionError = InitialValue;
    EventNumber = InitialValue;
}

ClassImp(HEventBranch)

HEventBranch::HEventBranch()
{
    ScalarPtSum = InitialValue;
}

ClassImp(HParticleBranch)

HParticleBranch::HParticleBranch()
{
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
}


ClassImp(HBottomBranch)

HBottomBranch::HBottomBranch()
{

    Mass = InitialValue;
    VertexMass = InitialValue;
    Pt = InitialValue;
    Displacement = InitialValue;
    Multipliticity = InitialValue;
    DeltaR = InitialValue;

    BottomTag = InitialValue;

}

ClassImp(HLeptonicTopBranch)

HLeptonicTopBranch::HLeptonicTopBranch()
{

    Mass = InitialValue;
    JetPt = InitialValue;
    LeptonPt = InitialValue;

    DeltaEta = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    BottomTag = InitialValue;

    TopTag = InitialValue;

}


ClassImp(HHiggsBranch)

HHiggsBranch::HHiggsBranch()
{

  Mass = InitialValue;
  PtSum = InitialValue;
  PtDiff = InitialValue;

  DeltaEta = InitialValue;
  DeltaPhi = InitialValue;
  DeltaR = InitialValue;

  BottomTag = InitialValue;

  Pull1 = InitialValue;
  Pull2 = InitialValue;
  Pull = InitialValue;

  HiggsTag = InitialValue;

}


ClassImp(HMvaHeavyHiggsBranch)

HMvaHeavyHiggsBranch::HMvaHeavyHiggsBranch()
{

  Mass = InitialValue;
  Pt = InitialValue;

  DeltaEta = InitialValue;
  DeltaPhi = InitialValue;
  DeltaR = InitialValue;

  TopTag = InitialValue;

  Pull1 = InitialValue;
  Pull2 = InitialValue;
  Pull = InitialValue;

  HeavyHiggsTag = InitialValue;

}
