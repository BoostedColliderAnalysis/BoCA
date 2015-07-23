#pragma once

#include <map>
#include "Global.hh"


namespace analysis
{

class PreCuts
{
public:
    void SetPtLowerCut(const Id id, float value);

    float PtLowerCut(const Id id) const;

    void SetPtUpperCut(const Id id, float value);

    float PtUpperCut(const Id id) const;

    void SetMassLowerCut(const Id id, float value);

    float MassLowerCut(const Id id) const;

    void SetMassUpperCut(const Id id, float value);

    float MassUpperCut(const Id id) const;

    void SetTrackerMaxEta(const Id id, float value);

    float TrackerMaxEta(const Id id) const;

    bool DoSubJets() const;

    void SetSubJets(const bool do_sub_jets);

private:

    std::map<Id, float> pt_lower_cut_;

    std::map<Id, float> pt_upper_cut_;

    std::map<Id, float> mass_lower_cut_;

    std::map<Id, float> mass_upper_cut_;

    std::map<Id, float> tracker_eta_upper_cut_;

    bool do_sub_jets_ = true;

};


}
