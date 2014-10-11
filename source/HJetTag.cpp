# include "HJetTag.hh"

HJetTag::HJetTag()
{

    Print(2,"Constructor");
}

HJetTag::~HJetTag()
{

    Print(2,"Destructor");
}

int HJetTag::GetBranchId(int, int) const {
    
    Print(0, "No Jet Tagger defined");
    
    return 0;
    
};