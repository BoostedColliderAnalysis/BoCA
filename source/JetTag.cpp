# include "JetTag.hh"

analysis::JetTag::JetTag()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kInformation, "Constructor");
}

int analysis::JetTag::GetBranchId(const int particle_id, int branch_id)
{
    Print(kDebug, "Get Branch Id", GetParticleName(particle_id), GetParticleName(branch_id));
    if (
        HeavyParticles.find(static_cast<ParticleId>(std::abs(particle_id))) != end(HeavyParticles)
//         && HeavyParticles.find(static_cast<ParticleId>(std::abs(BranchId))) == end(HeavyParticles)
    ) {
        branch_id = particle_id;
    } else if (
        RadiationParticles.find(static_cast<ParticleId>(std::abs(particle_id))) != end(RadiationParticles)
    ) {
        branch_id = IsrId;
    }
    Print(kDebug, "Branch Id", GetParticleName(branch_id));
    return branch_id;
}

analysis::Family analysis::JetTag::GetBranchFamily(const Family &node_family, Family &branch_family)
{
    Print(kDebug, "Get Branch Id", GetParticleName(node_family.particle().Id), GetParticleName(node_family.mother_1().Id), GetParticleName(branch_family.particle().Id));
    if (
        HeavyParticles.find(static_cast<ParticleId>(std::abs(node_family.particle().Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<ParticleId>(std::abs(branch_family.particle().Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<ParticleId>(std::abs(branch_family.mother_1().Id))) == end(HeavyParticles)
    ) {
        branch_family = node_family;
    } else if (
        HeavyParticles.find(static_cast<ParticleId>(std::abs(node_family.mother_1().Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<ParticleId>(std::abs(branch_family.mother_1().Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<ParticleId>(std::abs(branch_family.particle().Id))) == end(HeavyParticles)
    ) {
        branch_family = node_family;
    } else if (
        RadiationParticles.find(static_cast<ParticleId>(std::abs(node_family.mother_1().Id))) != end(RadiationParticles)
        || RadiationParticles.find(static_cast<ParticleId>(std::abs(node_family.particle().Id))) != end(RadiationParticles)
    ) {
        branch_family = Family(node_family.particle().Position,IsrId,node_family.mother_1().Position,IsrId);
    }
    Print(kDebug, "Branch Id", GetParticleName(branch_family.particle().Id));
    return branch_family;
}
