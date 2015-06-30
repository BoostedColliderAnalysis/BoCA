#include "JetTag.hh"
#include "Debug.hh"

namespace analysis {

JetTag::JetTag()
{
//     DebugLevel = Severity::debug;
    Info("Constructor");
}

int JetTag::GetBranchId(const int id, int branch_id)
{
    Debug("Branch Id", Name(id), Name(branch_id));
    if (
        HeavyParticles.find(static_cast<Id>(std::abs(id))) != end(HeavyParticles)
//         && HeavyParticles.find(static_cast<Id>(std::abs(BranchId))) == end(HeavyParticles)
    ) {
        branch_id = id;
    } else if (
        RadiationParticles.find(static_cast<Id>(std::abs(id))) != end(RadiationParticles)
    ) {
        branch_id = to_int(Id::isr);
    }
    Debug("Branch Id", Name(branch_id));
    return branch_id;
}

Family JetTag::BranchFamily(const Family &node_family, Family &branch_family)
{
    Debug("Branch Id", Name(node_family.particle().Id), Name(node_family.mother_1().Id), Name(branch_family.particle().Id));
    if (
        HeavyParticles.find(static_cast<Id>(std::abs(node_family.particle().Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.particle().Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.mother_1().Id))) == end(HeavyParticles)
    ) {
        branch_family = node_family;
    } else if (
        HeavyParticles.find(static_cast<Id>(std::abs(node_family.mother_1().Id))) != end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.mother_1().Id))) == end(HeavyParticles)
        && HeavyParticles.find(static_cast<Id>(std::abs(branch_family.particle().Id))) == end(HeavyParticles)
    ) {
        branch_family = node_family;
    } else if (
        RadiationParticles.find(static_cast<Id>(std::abs(node_family.mother_1().Id))) != end(RadiationParticles)
        || RadiationParticles.find(static_cast<Id>(std::abs(node_family.particle().Id))) != end(RadiationParticles)
    ) {
        branch_family = Family(node_family.particle().Position,Id::isr,node_family.mother_1().Position,Id::isr);
    }
    Debug("Branch Id", Name(branch_family.particle().Id));
    return branch_family;
}

}
