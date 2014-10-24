# include "HJetTag.hh"

HJetTag::HJetTag()
{

    Print(2,"Constructor");
}

HJetTag::~HJetTag()
{

    Print(2,"Destructor");
}

int HJetTag::GetBranchId(const int ParticleId, int BranchId)
 {

     Print(0, "No Jet Tagger defined", ParticleId);
    
    return BranchId;

}
