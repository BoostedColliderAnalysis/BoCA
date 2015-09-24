/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <map>
#include "Particles.hh"

namespace boca
{

enum class Bosstness {
  unboosted,
};

class PreCuts
{
public:
    void SetPtLowerCut(Id id, Momentum momentum);

    Momentum PtLowerCut(Id id) const;

    void SetPtUpperCut(Id id, Momentum momentum);

    Momentum PtUpperCut(Id id) const;

    void SetMassLowerCut(Id id, Mass mass);

    Mass MassLowerCut(Id id) const;

    void SetMassUpperCut(Id id, Mass mass);

    Mass MassUpperCut(Id id) const;

    void SetTrackerMaxEta(Id id, float eta);

    float TrackerMaxEta(Id id) const;

    bool DoSubJets() const;

    void SetSubJets(bool do_sub_jets);

    bool SemiLeptonic() const;

    void SetSemiLeptonic(bool semi_leptonic);

private:

    // these members are mutable as the try/catch blocks are called way too often without stroring these negative results
    mutable std::map<Id, Momentum> pt_lower_cut_;

    mutable std::map<Id, Momentum> pt_upper_cut_;

    mutable std::map<Id, Mass> mass_lower_cut_;

    mutable std::map<Id, Mass> mass_upper_cut_;

    mutable std::map<Id, float> tracker_eta_upper_cut_;

    bool do_sub_jets_ = true;

    bool semi_leptonic_ = true;

};


}
