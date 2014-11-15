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
//     InvMass4 = InitialValue;

    Pull11 = InitialValue;
    Pull12 = InitialValue;
    Pull21 = InitialValue;
    Pull22 = InitialValue;
    Pull31 = InitialValue;
    Pull32 = InitialValue;
//     Pull41 = InitialValue;
//     Pull42 = InitialValue;

    DeltaR1 = InitialValue;
    DeltaR2 = InitialValue;
    DeltaR3 = InitialValue;

    Vertex11 = InitialValue;
    Vertex12 = InitialValue;
    Vertex21 = InitialValue;
    Vertex22 = InitialValue;
    Vertex31 = InitialValue;
    Vertex32 = InitialValue;

    Mass11 = InitialValue;
    Mass12 = InitialValue;
    Mass21 = InitialValue;
    Mass22 = InitialValue;
    Mass31 = InitialValue;
    Mass32 = InitialValue;

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
