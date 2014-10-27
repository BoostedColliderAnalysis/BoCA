# include "HJetTag.hh"

hanalysis::HJetTag::HJetTag()
{

    Print(2,"Constructor");
}

hanalysis::HJetTag::~HJetTag()
{

    Print(2,"Destructor");
}

int hanalysis::HJetTag::GetBranchId(const int ParticleId, int BranchId)
 {

     Print(0, "No Jet Tagger defined", ParticleId);

    return BranchId;

}
