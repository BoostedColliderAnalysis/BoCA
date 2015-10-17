/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "PreCuts.hh"

namespace boca
{

void PreCuts::SetPtLowerCut(Id id, Momentum momentum)
{
    pt_lower_cut_.emplace(id, momentum);
}

bool PreCuts::PtLowerCutIsSet(Id id) const {
  return pt_lower_cut_.find(id) != pt_lower_cut_.end();
}

Momentum PreCuts::PtLowerCut(Id id) const
{
    try {
        return pt_lower_cut_.at(id);
    } catch (std::out_of_range const&) {
        pt_lower_cut_.emplace(id, at_rest);
        return at_rest;
    }
}

void PreCuts::SetPtUpperCut(Id id, Momentum momentum)
{
    pt_upper_cut_.emplace(id, momentum);
}

bool PreCuts::PtUpperCutIsSet(Id id) const {
  return pt_upper_cut_.find(id) != pt_upper_cut_.end();
}

Momentum PreCuts::PtUpperCut(Id id) const
{
    try {
        return pt_upper_cut_.at(id);
    } catch (std::out_of_range const&) {
        pt_upper_cut_.emplace(id, at_rest);
        return at_rest;
    }
}

void PreCuts::SetMassLowerCut(Id id, Mass mass)
{
    mass_lower_cut_.emplace(id, mass);
}

bool PreCuts::MassLowerCutIsSet(Id id) const {
  return mass_lower_cut_.find(id) != mass_lower_cut_.end();
}

Mass PreCuts::MassLowerCut(Id id) const
{
    try {
        return mass_lower_cut_.at(id);
    } catch (std::out_of_range const&) {
        mass_lower_cut_.emplace(id, massless);
        return massless;
    }
}

void PreCuts::SetMassUpperCut(Id id, Mass mass)
{
    mass_upper_cut_.emplace(id, mass);
}

bool PreCuts::MassUpperCutIsSet(Id id) const {
  return mass_upper_cut_.find(id) != mass_upper_cut_.end();
}

Mass PreCuts::MassUpperCut(Id id) const
{
    try {
        return mass_upper_cut_.at(id);
    } catch (std::out_of_range const&) {
        mass_upper_cut_.emplace(id, massless);
        return massless;
    }
}

void PreCuts::SetTrackerMaxEta(Id id, float eta)
{
    tracker_eta_upper_cut_.emplace(id, eta);
}

bool PreCuts::TrackerEtaMaxIsSet(Id id) const {
  return tracker_eta_upper_cut_.find(id) != tracker_eta_upper_cut_.end();
}

float PreCuts::TrackerMaxEta(Id id) const
{
    try {
        return tracker_eta_upper_cut_.at(id);
    } catch (std::out_of_range const&) {
        tracker_eta_upper_cut_.emplace(id, 0);
        return 0;
    }
}

bool PreCuts::DoSubJets() const
{
    return do_sub_jets_;
}

void PreCuts::SetSubJets(bool do_sub_jets)
{
    do_sub_jets_ = do_sub_jets;
}

bool PreCuts::SemiLeptonic() const
{
    return semi_leptonic_;
}

void PreCuts::SetSemiLeptonic(bool semi_leptonic)
{
    semi_leptonic_ = semi_leptonic;
}

}
