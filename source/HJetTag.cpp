# include "HJetTag.hh"

hanalysis::HJetTag::HJetTag()
{

    Print(HInformation, "Constructor");
}

hanalysis::HJetTag::~HJetTag()
{

    Print(HInformation, "Destructor");
}

int hanalysis::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(HDebug, "Get Branch Id", ParticleId, BranchId);

    if (
        HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles) &&
        HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    } else if (
        RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles)
    ) {
        BranchId = IsrId;
    }

    Print(HDebug, "Branch Id", BranchId);

    return BranchId;

}
