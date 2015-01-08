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
//         && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchId))) == end(HeavyParticles)
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

// HFamily hanalysis::HJetTag::GetBranchId(const HFamily &Family, HFamily &BranchId)
// {
//
//     Print(HDebug, "Get Branch Id", GetParticleName(Family.ParticleId), GetParticleName(Family.Mother1Id), GetParticleName(Family.Mother2Id), GetParticleName(BranchId.ParticleId));
//
//     if (
// //       HeavyParticles.find(static_cast<HParticleId>(std::abs(Family.ParticleId))) != end(HeavyParticles)
//         HeavyFamily.find(Family.Abs()) != end(HeavyFamily)
// //         && HeavyFamily.find((BranchId))) == end(HeavyParticles)
//     ) {
//         BranchId = Family;
// //         Print(HError, "Family", Family.ParticleId, BranchId.ParticleId);
//     } else if (
//         RadiationParticles.find(static_cast<HParticleId>(std::abs(Family.ParticleId))) != end(RadiationParticles)
//     ) {
//         BranchId = HFamily(IsrId, EmptyId, EmptyId);
//     }
//
//     Print(HDebug, "Branch Id", GetParticleName(BranchId.ParticleId));
//
//     return BranchId;
//
// }


hanalysis::HFamily hanalysis::HJetTag::GetBranchFamily(const HFamily &NodeFamily, HFamily &BranchFamily)
{

    Print(HDebug, "Get Branch Id", GetParticleName(NodeFamily.ParticleId), GetParticleName(NodeFamily.Mother1Id), GetParticleName(BranchFamily.ParticleId));

    if (
        HeavyParticles.find(static_cast<HParticleId>(std::abs(NodeFamily.ParticleId))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) == end(HeavyParticles)
    ) {
        BranchFamily = NodeFamily;
    } else if (
        HeavyParticles.find(static_cast<HParticleId>(std::abs(NodeFamily.Mother1Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) == end(HeavyParticles)
    ) {
        BranchFamily = NodeFamily;
    } else if (
        RadiationParticles.find(static_cast<HParticleId>(std::abs(NodeFamily.Mother1Id))) != end(RadiationParticles)
       || RadiationParticles.find(static_cast<HParticleId>(std::abs(NodeFamily.ParticleId))) != end(RadiationParticles)
    ) {
        BranchFamily = HFamily(NodeFamily.ParticlePosition,IsrId,NodeFamily.Mother1Position,IsrId);
    }

    Print(HDebug, "Branch Id", GetParticleName(BranchFamily.ParticleId));

    return BranchFamily;

}
