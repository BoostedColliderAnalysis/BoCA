# include "HJetTag.hh"

hanalysis::HJetTag::HJetTag()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HInformation, "Constructor");
}

hanalysis::HJetTag::~HJetTag()
{
    Print(HInformation, "Destructor");
}

int hanalysis::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(HDebug, "Get Branch Id", GetParticleName(ParticleId), GetParticleName(BranchId));

    if (
        HeavyParticles.find(static_cast<HParticleId>(std::abs(ParticleId))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchId))) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    } else if (
        RadiationParticles.find(static_cast<HParticleId>(std::abs(ParticleId))) != end(RadiationParticles)
    ) {
        BranchId = IsrId;
    }

    Print(HDebug, "Branch Id", GetParticleName(BranchId));

    return BranchId;

}

int hanalysis::HJetTag::GetBranchId(const HFamily Family, int BranchId)
{
  
  Print(HDebug, "Get Branch Id", GetParticleName(Family.ParticleId), GetParticleName(BranchId));

  if (
    HeavyParticles.find(static_cast<HParticleId>(std::abs(Family.ParticleId))) != end(HeavyParticles)
    && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchId))) == end(HeavyParticles)
  ) {
    BranchId = Family.ParticleId;
  } else if (
    RadiationParticles.find(static_cast<HParticleId>(std::abs(Family.ParticleId))) != end(RadiationParticles)
  ) {
    BranchId = IsrId;
  }

  Print(HDebug, "Branch Id", GetParticleName(BranchId));

  return BranchId;

}
