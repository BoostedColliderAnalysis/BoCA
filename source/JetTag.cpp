/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "JetTag.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

int JetTag::GetBranchId(int id, int branch_id)
{
    Debug(Name(id), Name(branch_id));
    if (
        HeavyParticles.find(static_cast<Id>(std::abs(id))) != end(HeavyParticles)
//         && HeavyParticles.find(static_cast<Id>(std::abs(BranchId))) == end(HeavyParticles)
    )
        branch_id = id;
    else if (
        RadiationParticles.find(static_cast<Id>(std::abs(id))) != end(RadiationParticles)
    )
        branch_id = to_int(Id::isr);
    Debug(Name(branch_id));
    return branch_id;
}

Family JetTag::BranchFamily(Family const&node_family, Family& branch_family)
{
    Debug(Name(node_family.Particle().Id()), Name(node_family.Mother().Id()), Name(branch_family.Particle().Id()));
    if (
        HeavyParticles.find(static_cast<Id>(std::abs(node_family.Particle().Id()))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.Particle().Id()))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.Mother().Id()))) == end(HeavyParticles)
    )
        branch_family = node_family;
    else if (
        HeavyParticles.find(static_cast<Id>(std::abs(node_family.Mother().Id()))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.Mother().Id()))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.Particle().Id()))) == end(HeavyParticles)
    )
        branch_family = node_family;
    else if (
        RadiationParticles.find(static_cast<Id>(std::abs(node_family.Mother().Id()))) != end(RadiationParticles)
        || RadiationParticles.find(static_cast<Id>(std::abs(node_family.Particle().Id()))) != end(RadiationParticles)
    )
      branch_family = Family(node_family.Particle().Position(), to_int(Id::isr), node_family.Mother().Position(), to_int(Id::isr), to_int(Id::isr));
    Debug(Name(branch_family.Particle().Id()));
    return branch_family;
}

}
