# include "JetTag.hh"

namespace analysis {

JetTag::JetTag()
{
//     DebugLevel = Object::Severity::Debug;
    Print(Severity::Information, "Constructor");
}

int JetTag::GetBranchId(const int id, int branch_id)
{
    Print(Severity::Debug, "Branch Id", Name(id), Name(branch_id));
    if (
        HeavyParticles.find(static_cast<Id>(std::abs(id))) != end(HeavyParticles)
//         && HeavyParticles.find(static_cast<Id>(std::abs(BranchId))) == end(HeavyParticles)
    ) {
        branch_id = id;
    } else if (
        RadiationParticles.find(static_cast<Id>(std::abs(id))) != end(RadiationParticles)
    ) {
        branch_id = to_int(Id::Isr);
    }
    Print(Severity::Debug, "Branch Id", Name(branch_id));
    return branch_id;
}

Family JetTag::BranchFamily(const Family &node_family, Family &branch_family)
{
    Print(Severity::Debug, "Branch Id", Name(node_family.particle().Id), Name(node_family.mother_1().Id), Name(branch_family.particle().Id));
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
        branch_family = Family(node_family.particle().Position,Id::Isr,node_family.mother_1().Position,Id::Isr);
    }
    Print(Severity::Debug, "Branch Id", Name(branch_family.particle().Id));
    return branch_family;
}

}
