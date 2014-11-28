# include "HBranchHiggsCpv.hh"

ClassImp(hhiggscpv::HEventBranch)

hhiggscpv::HEventBranch::HEventBranch()
{

    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;
    LeptonNumber = InitialValue;
    HeavyParticleTag = InitialValue;
    TopDeltaRap = InitialValue;
    TopDeltaPhi = InitialValue;
    TopDeltaR = InitialValue;

    Signal = InitialValue;

}

ClassImp(hhiggscpv::HLeptonBranch)

hhiggscpv::HLeptonBranch::HLeptonBranch()
{

    Mass = InitialValue;
    Pt = InitialValue;
    Rap = InitialValue;
    Phi = InitialValue;
    Charge = InitialValue;

}
