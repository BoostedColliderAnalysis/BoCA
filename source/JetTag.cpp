# include "JetTag.hh"

analysis::JetTag::JetTag()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kInformation, "Constructor");
}

int analysis::JetTag::GetBranchId(const int particle_id, int branch_id)
{
    Print(kDebug, "Branch Id", Name(particle_id), Name(branch_id));
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
    Print(kDebug, "Branch Id", Name(branch_id));
    return branch_id;
}

analysis::Family analysis::JetTag::BranchFamily(const Family &node_family, Family &branch_family)
{
    Print(kDebug, "Branch Id", Name(node_family.particle().Id), Name(node_family.mother_1().Id), Name(branch_family.particle().Id));
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
    Print(kDebug, "Branch Id", Name(branch_family.particle().Id));
    return branch_family;
}
