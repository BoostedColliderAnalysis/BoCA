/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <map>
#include "Particles.hh"

namespace boca
{

enum class Bosstness
{
    unboosted,
};

template<typename Value>
class PreCut
{

public:

    void Set(Id id, Value value) {
        pre_cut_.emplace(id, value);
    }

    bool IsSet(Id id) const {
        return pre_cut_.find(id) != pre_cut_.end();
    }

    Value Get(Id id) const {
        try {
            return pre_cut_.at(id);
        } catch (std::out_of_range const&) {
            pre_cut_.emplace(id, Value(0.));
            return Value(0.);
        }
    }

private:

    mutable std::map<Id, Value> pre_cut_;

};

class PreCuts
{
public:
    void SetPtLowerCut(Id id, Momentum momentum);

    bool PtLowerCutIsSet(Id id) const;

    Momentum PtLowerCut(Id id) const;

    template <typename Multiplet>
    bool PtTooSmall(Id id, Multiplet const& multiplet) const {
        return PtLowerCutIsSet(id) && PtLowerCut(id) > multiplet.Pt();
    }

    void SetPtUpperCut(Id id, Momentum momentum);

    bool PtUpperCutIsSet(Id id) const;

    Momentum PtUpperCut(Id id) const;

    template <typename Multiplet>
    bool PtTooLarge(Id id, Multiplet const& multiplet) const {
        return PtUpperCutIsSet(id) && PtUpperCut(id) < multiplet.Pt();
    }

    void SetMassLowerCut(Id id, Mass mass);

    bool MassLowerCutIsSet(Id id) const;

    Mass MassLowerCut(Id id) const;

    template <typename Multiplet>
    bool MassTooSmall(Id id, Multiplet const& multiplet) const {
        return MassLowerCutIsSet(id) && MassLowerCut(id) > multiplet.Mass();
    }

    void SetMassUpperCut(Id id, Mass mass);

    bool MassUpperCutIsSet(Id id) const;

    Mass MassUpperCut(Id id) const;

    template <typename Multiplet>
    bool MassTooLarge(Id id, Multiplet const& multiplet) const {
        return MassUpperCutIsSet(id) && MassUpperCut(id) < multiplet.Mass();
    }

    void SetTrackerMaxEta(Id id, float eta);

    bool TrackerEtaMaxIsSet(Id id) const;

    float TrackerMaxEta(Id id) const;

    template <typename Multiplet>
    bool OutsideTracker(Id id, Multiplet const& multiplet) const {
        return TrackerEtaMaxIsSet(id) && TrackerMaxEta(id) < multiplet.Jet().rap();
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

private:

    // these members are mutable as the try/catch blocks are called way too often without stroring the negative results
    // TODO replace all problematic checks with unproblematic ones and remove mutable
    mutable std::map<Id, Momentum> pt_lower_cut_;

    mutable std::map<Id, Momentum> pt_upper_cut_;

    mutable std::map<Id, Mass> mass_lower_cut_;

    mutable std::map<Id, Mass> mass_upper_cut_;

    mutable std::map<Id, float> tracker_eta_upper_cut_;

    bool do_sub_jets_ = true;

    bool semi_leptonic_ = true;

};


}
