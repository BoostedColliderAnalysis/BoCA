#pragma once

#include <map>
#include "Global.hh"


namespace analysis
{

class PreCuts
{
public:
    void SetPtLowerCut(Id id, float value);

    float PtLowerCut(Id id) const;

    void SetPtUpperCut(Id id, float value);

    float PtUpperCut(Id id) const;

    void SetMassLowerCut(Id id, float value);

    float MassLowerCut(Id id) const;

    void SetMassUpperCut(Id id, float value);

    float MassUpperCut(Id id) const;

    void SetTrackerMaxEta(Id id, float value);

    float TrackerMaxEta(Id id) const;

    bool DoSubJets() const;

    void SetSubJets(bool do_sub_jets);

    bool SemiLeptonic() const;

    void SetSemiLeptonic(bool semi_leptonic);

private:

    std::map<Id, float> pt_lower_cut_;

    std::map<Id, float> pt_upper_cut_;

    std::map<Id, float> mass_lower_cut_;

    std::map<Id, float> mass_upper_cut_;

    std::map<Id, float> tracker_eta_upper_cut_;

    bool do_sub_jets_ = true;

    bool semi_leptonic_ = true;

};


}
