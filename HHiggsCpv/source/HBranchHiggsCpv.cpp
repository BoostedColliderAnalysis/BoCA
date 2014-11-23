# include "HBranchHiggsCpv.hh"


ClassImp(hhiggscpv::HBottomBranch)

hhiggscpv::HBottomBranch::HBottomBranch()
{

    Mass = InitialValue;
    VertexMass = InitialValue;
    Pt = InitialValue;
    Displacement = InitialValue;
    Multipliticity = InitialValue;
    DeltaR = InitialValue;
    
    Bottom = InitialValue;

}

ClassImp(hhiggscpv::HHiggsBranch)

hhiggscpv::HHiggsBranch::HHiggsBranch()
{

    Mass = InitialValue;
    Pt = InitialValue;

    DeltaEta = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    BTag = InitialValue;

    Pull1 = InitialValue;
    Pull2 = InitialValue;
    Pull = InitialValue;
    
    Higgs = InitialValue;

}

ClassImp(hhiggscpv::HTopBranch)

hhiggscpv::HTopBranch::HTopBranch()
{
    
    Mass = InitialValue;
    Pt = InitialValue;
    
    DeltaEta = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;
    
    BTag = InitialValue;
    
    Top = InitialValue;
    
}


ClassImp(hhiggscpv::HEventBranch)

hhiggscpv::HEventBranch::HEventBranch()
{

    ScalarHt = InitialValue;
    JetNumber = InitialValue;
    BottomNumber = InitialValue;
    HiggsTag = InitialValue;
    
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
