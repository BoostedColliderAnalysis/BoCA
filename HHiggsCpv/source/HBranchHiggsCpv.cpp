# include "HBranchHiggsCpv.hh"


ClassImp(hhiggscpv::HBTaggerBranch)

void hhiggscpv::HBTaggerBranch::reset()
{

  const int InitialValue = -10;
  Mass = InitialValue;
  Pt = InitialValue;
  Displacement = InitialValue;
  Multipliticity = InitialValue;

}

ClassImp(hhiggscpv::HPairBranch)

void hhiggscpv::HPairBranch::reset()
{

    const int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;

    DeltaEta = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    BTag = InitialValue;

    Pull1 = InitialValue;
    Pull2 = InitialValue;
    Pull = InitialValue;

}


ClassImp(hhiggscpv::HEventBranch)

void hhiggscpv::HEventBranch::reset()
{

  const int InitialValue = -10;

  ScalarHt = InitialValue;
  JetNumber = InitialValue;
  BottomNumber = InitialValue;

  HiggsTag = InitialValue;

}



ClassImp(hhiggscpv::HLeptonBranch)

hhiggscpv::HLeptonBranch::HLeptonBranch()
{

  reset();

}

hhiggscpv::HLeptonBranch::~HLeptonBranch() {}

void hhiggscpv::HLeptonBranch::reset()
{

  int InitialValue = -10;

  Mass = InitialValue;
  Pt = InitialValue;
  Eta = InitialValue;
  Phi = InitialValue;
  Charge = InitialValue;

}
