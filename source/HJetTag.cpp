# include "HJetTag.hh"

HJetTag::HJetTag()
{

    Print(2,"Constructor");
}

HJetTag::~HJetTag()
{

    Print(2,"Destructor");
}

HBranchStruct HJetTag::GetBranchId(const int Value, HBranchStruct BranchStruct) const {
    
    Print(0, "No Jet Tagger defined");
    
    return BranchStruct;
    
}