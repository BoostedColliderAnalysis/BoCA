/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "PreCuts.hh"
#include "DetectorGeometry.hh"

namespace boca
{

bool PreCuts::SemiLeptonic() const
{
    return semi_leptonic_;
}

void PreCuts::SetSemiLeptonic(bool semi_leptonic)
{
    semi_leptonic_ = semi_leptonic;
}
bool PreCuts::PtTooSmall(Id id, const Jet& jet) const
{
    return pt_lower_cut_.IsSet(id) && pt_lower_cut_.Get(id) > jet.Pt();
}
bool PreCuts::PtTooLarge(Id id, const Jet& jet) const
{
    return pt_upper_cut_.IsSet(id) && pt_upper_cut_.Get(id) < jet.Pt();
}
bool PreCuts::MassTooSmall(Id id, const Jet& jet) const
{
    return mass_lower_cut_.IsSet(id) && mass_lower_cut_.Get(id) > jet.Mass();
}
bool PreCuts::MassTooLarge(Id id, const Jet& jet) const
{
    return mass_upper_cut_.IsSet(id) && mass_upper_cut_.Get(id) < jet.Mass();
}
bool PreCuts::OutsideTracker(Id id, const Jet& jet) const
{
    return tracker_eta_upper_cut_.IsSet(id) && tracker_eta_upper_cut_.Get(id) < boost::units::abs(jet.Rap());
}
bool PreCuts::DoSubJets(Id id) const
{
    return (consider_building_block_.IsSet(id)) ? consider_building_block_.Get(id) : true;
}
PreCut< Momentum >& PreCuts::PtLowerCut()
{
    return pt_lower_cut_;
}
PreCut< Momentum >& PreCuts::PtUpperCut()
{
    return pt_upper_cut_;
}
PreCut< Mass >& PreCuts::MassLowerCut()
{
    return mass_lower_cut_;
}
PreCut< Mass >& PreCuts::MassUpperCut()
{
    return mass_upper_cut_;
}
PreCut< Angle >& PreCuts::TrackerMaxEta()
{
    return tracker_eta_upper_cut_;
}
PreCut< bool >& PreCuts::ConsiderBuildingBlock()
{
    return consider_building_block_;
}
const PreCut< Momentum >& PreCuts::PtLowerCut() const
{
    return pt_lower_cut_;
}
const PreCut< Momentum >& PreCuts::PtUpperCut() const
{
    return pt_upper_cut_;
}
const PreCut< Mass >& PreCuts::MassLowerCut() const
{
    return mass_lower_cut_;
}
const PreCut< Mass >& PreCuts::MassUpperCut() const
{
    return mass_upper_cut_;
}
const PreCut< Angle >& PreCuts::TrackerMaxEta() const
{
    return tracker_eta_upper_cut_;
}
const PreCut< bool >& PreCuts::ConsiderBuildingBlock() const
{
    return consider_building_block_;
}
Angle PreCuts::JetConeMax(boca::Id id) const
{
    return (PtLowerCut().IsSet(id)) ? 2_rad * double(MassOf(id) / PtLowerCut().Get(id)) : DetectorGeometry::JetConeSize();
}

}
