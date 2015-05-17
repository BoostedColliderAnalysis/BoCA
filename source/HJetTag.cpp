# include "HJetTag.hh"

analysis::HJetTag::HJetTag()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kInformation, "Constructor");
}

analysis::HJetTag::~HJetTag()
{
    Print(kInformation, "Destructor");
}

int analysis::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(kDebug, "Get Branch Id", GetParticleName(ParticleId), GetParticleName(BranchId));

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

    Print(kDebug, "Branch Id", GetParticleName(BranchId));

    return BranchId;

}

analysis::Family analysis::HJetTag::GetBranchFamily(const Family &node_family, Family &branch_family)
{

    Print(kDebug, "Get Branch Id", GetParticleName(node_family.particle().Id), GetParticleName(node_family.mother_1().Id), GetParticleName(branch_family.particle().Id));

    if (
        HeavyParticles.find(static_cast<HParticleId>(std::abs(node_family.particle().Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(branch_family.particle().Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(branch_family.mother_1().Id))) == end(HeavyParticles)
    ) {
        branch_family = node_family;
    } else if (
        HeavyParticles.find(static_cast<HParticleId>(std::abs(node_family.mother_1().Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(branch_family.mother_1().Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<HParticleId>(std::abs(branch_family.particle().Id))) == end(HeavyParticles)
    ) {
        branch_family = node_family;
    } else if (
        RadiationParticles.find(static_cast<HParticleId>(std::abs(node_family.mother_1().Id))) != end(RadiationParticles)
        || RadiationParticles.find(static_cast<HParticleId>(std::abs(node_family.particle().Id))) != end(RadiationParticles)
    ) {
        branch_family = Family(node_family.particle().Position,IsrId,node_family.mother_1().Position,IsrId);
    }

    Print(kDebug, "Branch Id", GetParticleName(branch_family.particle().Id));

    return branch_family;

}
