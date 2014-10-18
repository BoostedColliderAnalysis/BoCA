# include "HJetTag.hh"

HJetTag::HJetTag()
{

    Print(2,"Constructor");
}

HJetTag::~HJetTag()
{

    Print(2,"Destructor");
}

int HJetTag::GetBranchId(const int Value, int BranchId, int) const {

    Print(0, "No Jet Tagger defined", Value);
    
    return BranchId;

}
