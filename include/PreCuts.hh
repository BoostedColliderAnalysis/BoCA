/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Jet.hh"

#include "PreCut.hh"

namespace boca
{

enum class Bosstness
{
    unboosted,
};

class PreCuts
{

public:

    template <typename Multiplet>
    bool PtTooSmall(Id id, Multiplet const& multiplet) const {
        return pt_lower_cut_.IsSet(id) && pt_lower_cut_.Get(id) > multiplet.Pt();
    }

    bool PtTooSmall(Id id, Jet const& jet) const {
        return pt_lower_cut_.IsSet(id) && pt_lower_cut_.Get(id) > jet.Pt();
    }

    template <typename Multiplet>
    bool PtTooLarge(Id id, Multiplet const& multiplet) const {
        return pt_upper_cut_.IsSet(id) && pt_upper_cut_.Get(id) < multiplet.Pt();
    }

    bool PtTooLarge(Id id, Jet const& jet) const {
        return pt_upper_cut_.IsSet(id) && pt_upper_cut_.Get(id) < jet.Pt();
    }

    template <typename Multiplet>
    bool MassTooSmall(Id id, Multiplet const& multiplet) const {
        return mass_lower_cut_.IsSet(id) && mass_lower_cut_.Get(id) > multiplet.Mass();
    }

    bool MassTooSmall(Id id, Jet const& jet) const {
        return mass_lower_cut_.IsSet(id) && mass_lower_cut_.Get(id) > jet.Mass();
    }

    template <typename Multiplet>
    bool MassTooLarge(Id id, Multiplet const& multiplet) const {
        return mass_upper_cut_.IsSet(id) && mass_upper_cut_.Get(id) < multiplet.Mass();
    }

    bool MassTooLarge(Id id, Jet const& jet) const {
        return mass_upper_cut_.IsSet(id) && mass_upper_cut_.Get(id) < jet.Mass();
    }

    template <typename Multiplet>
    bool OutsideTracker(Id id, Multiplet const& multiplet) const {
        return tracker_eta_upper_cut_.IsSet(id) && tracker_eta_upper_cut_.Get(id) < boost::units::abs(multiplet.Rap());
    }

    bool OutsideTracker(Id id, Jet const& jet) const {
        return tracker_eta_upper_cut_.IsSet(id) && tracker_eta_upper_cut_.Get(id) < std::abs(jet.rap()) * rad;
    }

    template <typename Multiplet>
    bool ApplyCuts(Id id, Multiplet const& multiplet) const {
        return PtTooSmall(id, multiplet) || PtTooLarge(id, multiplet) || MassTooSmall(id, multiplet) || MassTooLarge(id, multiplet) || OutsideTracker(id, multiplet);
    }

    bool DoSubJets(Id id) const {
        bool set = consider_building_block_.IsSet(id);
        if (!set) return true;
        return consider_building_block_.Get(id);
    }

//     bool DoSubJets() const;
//
//     void SetSubJets(bool do_sub_jets);

    bool SemiLeptonic() const;

    void SetSemiLeptonic(bool semi_leptonic);

    template <typename Multiplet>
    bool NotParticleRho(Multiplet const& multiplet, float min = 0.5, float max = 2) const {
        return multiplet.Rho() > 0 && (multiplet.Rho() < min || multiplet.Rho() > max);
    }

    template<typename Multiplet>
    bool OutSideMassWindow(Multiplet const& multiplet, Mass mass_window, Id id) const {
        return boost::units::abs(multiplet.Mass() - MassOf(id)) > mass_window;
    }

    PreCut<Momentum>& PtLowerCut() {
        return pt_lower_cut_;
    }

    PreCut<Momentum>& PtUpperCut() {
        return pt_upper_cut_;
    }

    PreCut<Mass>& MassLowerCut() {
        return mass_lower_cut_;
    }

    PreCut<Mass>& MassUpperCut() {
        return mass_upper_cut_;
    }

    PreCut<Angle>& TrackerMaxEta() {
        return tracker_eta_upper_cut_;
    }

    PreCut<bool>& ConsiderBuildingBlock() {
        return consider_building_block_;
    }

private:

    PreCut<Momentum> pt_lower_cut_;

    PreCut<Momentum> pt_upper_cut_;

    PreCut<Mass> mass_lower_cut_;

    PreCut<Mass> mass_upper_cut_;

    PreCut<Angle> tracker_eta_upper_cut_;

    PreCut<bool> consider_building_block_;

    bool semi_leptonic_ = true;

};

}
