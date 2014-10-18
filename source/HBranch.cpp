# include "HBranch.hh"

ClassImp(HInfoBranch)

HInfoBranch::HInfoBranch()
{

    reset();

}

HInfoBranch::~HInfoBranch() {}

void HInfoBranch::reset()
{

    int InitialValue = -10;

    Crosssection = InitialValue;
    Error = InitialValue;
    EventNumber = InitialValue;

}


ClassImp(HEventBranch)

HEventBranch::HEventBranch()
{
    
    reset();
    
}

HEventBranch::~HEventBranch() {}

void HEventBranch::reset()
{
    
    int InitialValue = -10;
    
    ScalarPtSum = InitialValue;
    
}

ClassImp(HParticleBranch)

HParticleBranch::HParticleBranch()
{
    
    reset();
    
}

HParticleBranch::~HParticleBranch() {}

void HParticleBranch::reset()
{
    
    int InitialValue = -10;
    
    Pt = InitialValue; 
    Eta = InitialValue; 
    Phi = InitialValue; 
    
}
