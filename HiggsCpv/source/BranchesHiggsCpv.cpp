# include "BranchesHiggsCpv.hh"


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

higgscpv::EventBranch::EventBranch()
{
    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());
    ScalarHt = InitialValue();

    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();

    RestNumber = int(InitialValue());
    RestM = InitialValue();
    RestPt = InitialValue();
    RestHt = InitialValue();
    RestRap = InitialValue();
    RestPhi = InitialValue();
    RestBdt = InitialValue();
    LeptonHt = InitialValue();

    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    MissingEt = InitialValue();

    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();

    SubBottomBdt1 = InitialValue();
    SubBottomBdt2 = InitialValue();
    SubBottomBdt3 = InitialValue();
    SubBottomBdt4 = InitialValue();
    SubBottomBdt5 = InitialValue();
    SubBottomBdt6 = InitialValue();
    SubBottomBdt7 = InitialValue();
    SubBottomBdt8 = InitialValue();
    SubBottomBdt12 = InitialValue();
    SubBottomBdt34 = InitialValue();
    SubBottomBdt56 = InitialValue();
    SubBottomBdt78 = InitialValue();
}

ClassImp(higgscpv::HLeptonBranch)

higgscpv::HLeptonBranch::HLeptonBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();
    Charge = int(InitialValue());
}


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
