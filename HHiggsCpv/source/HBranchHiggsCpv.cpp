# include "HBranchHiggsCpv.hh"

ClassImp(hhiggscpv::HEventBranch)

hhiggscpv::HEventBranch::HEventBranch()
{

    ScalarHt = InitialValue;
    JetNumber = int(InitialValue);
    BottomNumber = int(InitialValue);
    LeptonNumber = int(InitialValue);
    HeavyParticleTag = int(InitialValue);
    TopDeltaRap = InitialValue;
    TopDeltaPhi = InitialValue;
    TopDeltaR = InitialValue;

    Signal = int(InitialValue);

}

ClassImp(hhiggscpv::HLeptonBranch)

hhiggscpv::HLeptonBranch::HLeptonBranch()
{

    Mass = InitialValue;
    Pt = InitialValue;
    Rap = InitialValue;
    Phi = InitialValue;
    Charge = int(InitialValue);

}
