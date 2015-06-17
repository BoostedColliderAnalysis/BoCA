# pragma once

# include <map>
# include "Object.hh"

namespace analysis
{

class PreCuts : public analysis::Object
{
public:
    void SetPtLowerCut(const ParticleId particle_id, const float value) {
        pt_lower_cut_[particle_id] = value;
    }

    float PtLowerCut(const ParticleId particle_id) {
        return pt_lower_cut_[particle_id];
    }

    void SetPtUpperCut(const ParticleId particle_id, const float value) {
        pt_upper_cut_[particle_id] = value;
    }

    float PtUpperCut(const ParticleId particle_id) {
        return pt_upper_cut_[particle_id];
    }

    void SetMassLowerCut(const ParticleId particle_id, const float value) {
      mass_lower_cut_[particle_id] = value;
    }   

    float MassLowerCut(const ParticleId particle_id) {
      return mass_lower_cut_[particle_id];
    }

    void SetMassUpperCut(const ParticleId particle_id, const float value) {
      mass_upper_cut_[particle_id] = value;
    }

    float MassUpperCut(const ParticleId particle_id) {
      return mass_upper_cut_[particle_id];
    }

    void SetTrackerMaxEta(const ParticleId particle_id, const float value) {
        tracker_eta_upper_cut_[particle_id] = value;
    }

    float TrackerMaxEta(const ParticleId particle_id) {
        return tracker_eta_upper_cut_[particle_id];
    }

    bool DoSubJets()const {
        return do_sub_jets_;
    }

    void SetSubJets(const bool do_sub_jets) {
        do_sub_jets_ = do_sub_jets;
    }

private:
    std::map<ParticleId, float> pt_lower_cut_;
    std::map<ParticleId, float> pt_upper_cut_;
    std::map<ParticleId, float> mass_lower_cut_;
    std::map<ParticleId, float> mass_upper_cut_;
    std::map<ParticleId, float> tracker_eta_upper_cut_;
    bool do_sub_jets_ = true;
};


}
