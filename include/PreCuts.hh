/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"

#include "PreCut.hh"
#include "Debug.hh"

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

    bool PtTooSmall(Id id, fastjet::PseudoJet const& jet) const {
        return pt_lower_cut_.IsSet(id) && pt_lower_cut_.Get(id) > jet.pt() * GeV;
    }

    template <typename Multiplet>
    bool PtTooLarge(Id id, Multiplet const& multiplet) const {
        return pt_upper_cut_.IsSet(id) && pt_upper_cut_.Get(id) < multiplet.Pt();
    }

    bool PtTooLarge(Id id, fastjet::PseudoJet const& jet) const {
        return pt_upper_cut_.IsSet(id) && pt_upper_cut_.Get(id) > jet.pt() * GeV;
    }

    template <typename Multiplet>
    bool MassTooSmall(Id id, Multiplet const& multiplet) const {
        return mass_lower_cut_.IsSet(id) && mass_lower_cut_.Get(id) > multiplet.Mass();
    }

    bool MassTooSmall(Id id, fastjet::PseudoJet const& jet) const {
        return mass_lower_cut_.IsSet(id) && mass_lower_cut_.Get(id) > jet.m() * GeV;
    }

    template <typename Multiplet>
    bool MassTooLarge(Id id, Multiplet const& multiplet) const {
        return mass_upper_cut_.IsSet(id) && mass_upper_cut_.Get(id) < multiplet.Mass();
    }

    bool MassTooLarge(Id id, fastjet::PseudoJet const& jet) const {
        return mass_upper_cut_.IsSet(id) && mass_upper_cut_.Get(id) > jet.m() * GeV;
    }

    template <typename Multiplet>
    bool OutsideTracker(Id id, Multiplet const& multiplet) const {
        return tracker_eta_upper_cut_.IsSet(id) && tracker_eta_upper_cut_.Get(id) < std::abs(multiplet.Jet().rap());
    }

    bool OutsideTracker(Id id, fastjet::PseudoJet const& jet) const {
        return tracker_eta_upper_cut_.IsSet(id) && tracker_eta_upper_cut_.Get(id) < std::abs(jet.rap());
    }

    template <typename Multiplet>
    bool ApplyCuts(Id id, Multiplet const& multiplet) const {
        return PtTooSmall(id, multiplet) || PtTooLarge(id, multiplet) || MassTooSmall(id, multiplet) || MassTooLarge(id, multiplet) || OutsideTracker(id, multiplet);
    }

    bool DoSubJets() const;

    void SetSubJets(bool do_sub_jets);

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

    PreCut<float>& TrackerMaxEta() {
        return tracker_eta_upper_cut_;
    }

private:

    PreCut<Momentum> pt_lower_cut_;

    PreCut<Momentum> pt_upper_cut_;

    PreCut<Mass> mass_lower_cut_;

    PreCut<Mass> mass_upper_cut_;

    PreCut<float> tracker_eta_upper_cut_;

    bool do_sub_jets_ = true;

    bool semi_leptonic_ = true;

};

}
