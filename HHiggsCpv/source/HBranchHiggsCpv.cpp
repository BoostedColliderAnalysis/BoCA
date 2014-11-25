# include "HBranchHiggsCpv.hh"



ClassImp(hhiggscpv::HHiggsBranch)

hhiggscpv::HHiggsBranch::HHiggsBranch()
{

    Mass = InitialValue;
    Pt = InitialValue;

    DeltaEta = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    BottomTag = InitialValue;

    Pull1 = InitialValue;
    Pull2 = InitialValue;
    Pull = InitialValue;

    HiggsTag = InitialValue;

}

ClassImp(hhiggscpv::HEventBranch)

hhiggscpv::HEventBranch::HEventBranch()
{

    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;
    LeptonNumber = InitialValue;
    HeavyParticleTag = InitialValue;

    Signal = InitialValue;

}



ClassImp(hhiggscpv::HLeptonBranch)

hhiggscpv::HLeptonBranch::HLeptonBranch()
{

    Mass = InitialValue;
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
    Charge = InitialValue;

}
