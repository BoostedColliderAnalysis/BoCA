# include "HBranchHiggsCpv.hh"

ClassImp(hhiggscpv::HCandidateBranch)

hhiggscpv::HCandidateBranch::HCandidateBranch()
{

    reset();

}

hhiggscpv::HCandidateBranch::~HCandidateBranch() {}

void hhiggscpv::HCandidateBranch::reset()
{

    int InitialValue = -10;

    InvMass1 = InitialValue;
    InvMass2 = InitialValue;
    InvMass3 = InitialValue;
    InvMass4 = InitialValue;

    Pull11 = InitialValue;
    Pull12 = InitialValue;
    Pull21 = InitialValue;
    Pull22 = InitialValue;
    Pull31 = InitialValue;
    Pull32 = InitialValue;
    Pull41 = InitialValue;
    Pull42 = InitialValue;

    ScalarHt = InitialValue;

    HiggsTag = InitialValue;
    TopTag = InitialValue;

    TopBdtTag = InitialValue;
    JetBdtTag = InitialValue;

    TopCutSigEff = InitialValue;
    JetCutSigEff = InitialValue;

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
