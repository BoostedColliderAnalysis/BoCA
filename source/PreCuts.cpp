/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/PreCuts.hh"
#include "boca/DetectorGeometry.hh"

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
