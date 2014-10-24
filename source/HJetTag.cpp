# include "HJetTag.hh"

Analysis::HJetTag::HJetTag()
{

    Print(2,"Constructor");
}

Analysis::HJetTag::~HJetTag()
{

    Print(2,"Destructor");
}

int Analysis::HJetTag::GetBranchId(const int ParticleId, int BranchId)
 {

     Print(0, "No Jet Tagger defined", ParticleId);

    return BranchId;

}
