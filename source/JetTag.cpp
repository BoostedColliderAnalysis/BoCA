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
    Debug(Name(node_family.particle().id()), Name(node_family.mother_1().id()), Name(branch_family.particle().id()));
    if (
        HeavyParticles.find(static_cast<Id>(std::abs(node_family.particle().id()))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.particle().id()))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.mother_1().id()))) == end(HeavyParticles)
    )
        branch_family = node_family;
    else if (
        HeavyParticles.find(static_cast<Id>(std::abs(node_family.mother_1().id()))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.mother_1().id()))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.particle().id()))) == end(HeavyParticles)
    )
        branch_family = node_family;
    else if (
        RadiationParticles.find(static_cast<Id>(std::abs(node_family.mother_1().id()))) != end(RadiationParticles)
        || RadiationParticles.find(static_cast<Id>(std::abs(node_family.particle().id()))) != end(RadiationParticles)
    )
        branch_family = Family(node_family.particle().position(), Id::isr, node_family.mother_1().position(), Id::isr);
    Debug(Name(branch_family.particle().id()));
    return branch_family;
}

}
