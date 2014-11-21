# include "HBranchHiggsCpv.hh"

ClassImp(hhiggscpv::HEventBranch)

hhiggscpv::HEventBranch::HEventBranch()
{

    reset();

}

hhiggscpv::HEventBranch::~HEventBranch() {}

void hhiggscpv::HEventBranch::reset()
{

    const int InitialValue = -10;

    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;

    HiggsTag = InitialValue;
//     TopTag = InitialValue;

//     TopBdtTag = InitialValue;
//     JetBdtTag = InitialValue;

//     TopCutSigEff = InitialValue;
//     JetCutSigEff = InitialValue;

}



ClassImp(hhiggscpv::HPairBranch)

hhiggscpv::HPairBranch::HPairBranch()
{

    reset();

}

hhiggscpv::HPairBranch::~HPairBranch() {}

void hhiggscpv::HPairBranch::reset()
{

    const int InitialValue = -10;

    InvMass = InitialValue;

    Pull1 = InitialValue;
    Pull2 = InitialValue;
    Pull = InitialValue;

    DeltaR = InitialValue;

    BTag = InitialValue;

//     HiggsTag = InitialValue;
//     TopTag = InitialValue;

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
//   JetMass = InitialValue;
//   Pull = InitialValue;
//   DeltaR = InitialValue;
  Vertex = InitialValue;
  VertexNumber = InitialValue;

//   BTag = InitialValue;

//   BdtBTag = InitialValue;

//   BCutSigEff = InitialValue;

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
