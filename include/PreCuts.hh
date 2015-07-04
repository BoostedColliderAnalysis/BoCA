#pragma once

#include <map>
#include "Global.hh"


namespace analysis
{

class PreCuts
{
public:
    void SetPtLowerCut(const Id id, const float value) {
        pt_lower_cut_[id] = value;
    }

    float PtLowerCut(const Id id) {
        return pt_lower_cut_[id];
    }

    void SetPtUpperCut(const Id id, const float value) {
        pt_upper_cut_[id] = value;
    }

    float PtUpperCut(const Id id) {
        return pt_upper_cut_[id];
    }

    void SetMassLowerCut(const Id id, const float value) {
        mass_lower_cut_[id] = value;
    }

    float MassLowerCut(const Id id) {
        return mass_lower_cut_[id];
    }

    void SetMassUpperCut(const Id id, const float value) {
        mass_upper_cut_[id] = value;
    }

    float MassUpperCut(const Id id) {
        return mass_upper_cut_[id];
    }

    void SetTrackerMaxEta(const Id id, const float value) {
        tracker_eta_upper_cut_[id] = value;
    }

    float TrackerMaxEta(const Id id) {
        return tracker_eta_upper_cut_[id];
    }

    bool DoSubJets()const {
        return do_sub_jets_;
    }

    void SetSubJets(const bool do_sub_jets) {
        do_sub_jets_ = do_sub_jets;
    }

private:

    std::map<Id, float> pt_lower_cut_;

    std::map<Id, float> pt_upper_cut_;

    std::map<Id, float> mass_lower_cut_;

    std::map<Id, float> mass_upper_cut_;

    std::map<Id, float> tracker_eta_upper_cut_;

    bool do_sub_jets_ = true;

};


}
