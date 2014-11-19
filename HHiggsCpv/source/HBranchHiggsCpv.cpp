# include "HBranchHiggsCpv.hh"

ClassImp(hhiggscpv::HCandidateBranch)

hhiggscpv::HCandidateBranch::HCandidateBranch()
{

    reset();

}

hhiggscpv::HCandidateBranch::~HCandidateBranch() {}

void hhiggscpv::HCandidateBranch::reset()
{

    const int InitialValue = -10;

    InvMass1 = InitialValue;
    InvMass2 = InitialValue;
    InvMass3 = InitialValue;

    Pull1 = InitialValue;
    Pull2 = InitialValue;
    Pull3 = InitialValue;

    DeltaR1 = InitialValue;
    DeltaR2 = InitialValue;
    DeltaR3 = InitialValue;

    BTag1 = InitialValue;
    BTag2 = InitialValue;
    BTag3 = InitialValue;

    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;
    VertexNumber = InitialValue;

    HiggsTag = InitialValue;
    TopTag = InitialValue;

    TopBdtTag = InitialValue;
    JetBdtTag = InitialValue;

    TopCutSigEff = InitialValue;
    JetCutSigEff = InitialValue;

}



ClassImp(hhiggscpv::HBTaggerBranch)

hhiggscpv::HBTaggerBranch::HBTaggerBranch()
{

  reset();

}

hhiggscpv::HBTaggerBranch::~HBTaggerBranch() {}

void hhiggscpv::HBTaggerBranch::reset()
{

  const int InitialValue = -10;

  VertexMass = InitialValue;
  JetMass = InitialValue;
  Pull = InitialValue;
  DeltaR = InitialValue;
  Vertex = InitialValue;
  VertexNumber = InitialValue;

  BTag = InitialValue;

  BdtBTag = InitialValue;

  BCutSigEff = InitialValue;

}



// ClassImp(hhiggscpv::HConstituentBranch)
//
// hhiggscpv::HConstituentBranch::HConstituentBranch()
// {
//
//   reset();
//
// }
//
// hhiggscpv::HConstituentBranch::~HConstituentBranch() {}
//
// void hhiggscpv::HConstituentBranch::reset()
// {
//
//   int InitialValue = -100;
//
//   Eta = InitialValue;
//   Phi = InitialValue;
//   Pt = InitialValue;
//   Id = InitialValue;
//
// }


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
