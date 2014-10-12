# include "HJetPropertiesBranch.hh"

ClassImp(HJetPropertiesBranch)

HJetPropertiesBranch::HJetPropertiesBranch()
{

    reset();

}

HJetPropertiesBranch::~HJetPropertiesBranch() {}

void HJetPropertiesBranch::reset()
{

    int InitialValue = -10;

    Mass = InitialValue;
    Pt = InitialValue;

    Eta = InitialValue;
    Phi = InitialValue;
    Radius = InitialValue;
    JetPtSum = InitialValue;
    PtSum = InitialValue;

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

