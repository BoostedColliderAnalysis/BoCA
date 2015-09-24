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
