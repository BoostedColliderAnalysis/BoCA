# include "BranchesHiggsCpv.hh"

ClassImp(higgscpv::SignatureLeptonicBranch)

higgscpv::SignatureLeptonicBranch::SignatureLeptonicBranch()
{
  HiggsMass = InitialValue();
  PairRap = InitialValue();
  BottomBdt = InitialValue();
  PairBottomBdt = InitialValue();
  HardTopPt = InitialValue();
  SoftTopPt = InitialValue();
}

ClassImp(higgscpv::OctetBranch)

higgscpv::OctetBranch::OctetBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}


ClassImp(higgscpv::EventBranch)

higgscpv::EventBranch::EventBranch(){}

ClassImp(higgscpv::HLeptonBranch)

higgscpv::HLeptonBranch::HLeptonBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();
    Charge = int(InitialValue());
}

ClassImp(higgscpv::TopLeptonicPairBranch)

higgscpv::TopLeptonicPairBranch::TopLeptonicPairBranch(){}

ClassImp(higgscpv::TripletPairBranch)

higgscpv::TripletPairBranch::TripletPairBranch()
{
    BottomMass = InitialValue();
    BottomPt = InitialValue();
    BottomRap = InitialValue();
    BottomPhi = InitialValue();
    BottomBdt = InitialValue();
    BottomBTag = InitialValue();
    TopMass = InitialValue();
    TopPt = InitialValue();
    TopRap = InitialValue();
    TopPhi = InitialValue();
    TopBdt = InitialValue();
    TopBTag = InitialValue();
}

ClassImp(higgscpv::QuartetPairBranch)

higgscpv::QuartetPairBranch::QuartetPairBranch()
{
  BottomMass = InitialValue();
  BottomPt = InitialValue();
  BottomRap = InitialValue();
  BottomPhi = InitialValue();
  BottomBdt = InitialValue();
  BottomBTag = InitialValue();
  TopMass = InitialValue();
  TopPt = InitialValue();
  TopRap = InitialValue();
  TopPhi = InitialValue();
  TopBdt = InitialValue();
  TopBTag = InitialValue();
}
