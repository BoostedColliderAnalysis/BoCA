# include "HBranch.hh"

ClassImp(HInfoBranch)

HInfoBranch::HInfoBranch()
{
    Crosssection = InitialValue;
    CrosssectionError = InitialValue;
    EventNumber = InitialValue;
}

ClassImp(HEventBranch)

HEventBranch::HEventBranch()
{
    ScalarPtSum = InitialValue;
}

ClassImp(HParticleBranch)

HParticleBranch::HParticleBranch()
{
    Pt = InitialValue;
    Eta = InitialValue;
    Phi = InitialValue;
}


ClassImp(hhiggscpv::HBottomBranch)

HBottomBranch::HBottomBranch()
{
    
    Mass = InitialValue;
    VertexMass = InitialValue;
    Pt = InitialValue;
    Displacement = InitialValue;
    Multipliticity = InitialValue;
    DeltaR = InitialValue;
    
    BottomTag = InitialValue;
    
}