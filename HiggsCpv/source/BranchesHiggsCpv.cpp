# include "BranchesHiggsCpv.hh"

ClassImp(analysis::higgscpv::SignatureLeptonicBranch)

analysis::higgscpv::SignatureLeptonicBranch::SignatureLeptonicBranch()
{
  HiggsMass = InitialValue();
  PairRap = InitialValue();
  BottomBdt = InitialValue();
  PairBottomBdt = InitialValue();
  HardTopPt = InitialValue();
  SoftTopPt = InitialValue();
}

ClassImp(analysis::higgscpv::OctetBranch)

analysis::higgscpv::OctetBranch::OctetBranch()
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


ClassImp(analysis::higgscpv::EventBranch)

analysis::higgscpv::EventBranch::EventBranch(){}

ClassImp(analysis::higgscpv::HLeptonBranch)

analysis::higgscpv::HLeptonBranch::HLeptonBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();
    Charge = int(InitialValue());
}

ClassImp(analysis::higgscpv::TopLeptonicPairBranch)

analysis::higgscpv::TopLeptonicPairBranch::TopLeptonicPairBranch(){}

ClassImp(analysis::higgscpv::TripletPairBranch)

analysis::higgscpv::TripletPairBranch::TripletPairBranch()
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

ClassImp(analysis::higgscpv::QuartetPairBranch)

analysis::higgscpv::QuartetPairBranch::QuartetPairBranch()
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
