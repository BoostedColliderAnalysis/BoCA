# include "HJetTag.hh"

hanalysis::HJetTag::HJetTag()
{

    Print(HInformation,"Constructor");
}

hanalysis::HJetTag::~HJetTag()
{

    Print(HInformation,"Destructor");
}

int hanalysis::HJetTag::GetBranchId(const int ParticleId, int BranchId)
 {

     Print(HError, "No Jet Tagger defined", ParticleId);

    return BranchId;

}
