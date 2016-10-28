#pragma once
#include "boca/fastjet/Jet.hh"

namespace boca
{

/**
 * \brief  MuXboostedBTagging tags high-pT heavy flavor jets using a muonic tag
 *
 *  --> see [arXiv:1511.05990] for a full discussion of the physics.
 *  --> see <delphes/doc/MuXboostedBTagging/MuX_UserGuide.pdf> for a quick description of the module
 * <a href="https://github.com/keith-pedersen/delphes/tree/MuXboostedBTagging">Check for updates</a>
 *
 *  One of the crucial features of MuXboostedBTagging is that it
 *  ALTERS the pT of tagged jets, which come from semi-leptonic decay
 *  by construction, and thus are always missing neutrino energy.
 *
 *  MuXboostedBTagging accounts for this missing energy by ESTIMATING
 *  the neutrino's energy (currently using the simplest choice pNu=pMu,
 *  from the  shared boost). Thus, "taggable" muons are added a second
 *  time to jets that are tagged.
 *
 *  Therefore, in addition to altering the BTag bit of the original jet,
 *  (for which no neutrino estimation is performed), MuXboostedBTagging
 *  also clones the list of jets (adding neutrino energy when they
 *  pass the tag).
 *
 *  NOTE: This module gives more accurate light jet fake rates when
 *  used in conjunction with AllParticlePropagator (which simulates the
 *  initial bending of in-flight Pion/Kaon decays to muons).
 *
 */
class MuXboostedBTagging
{

public:

    Jet Process(boca::Jet const &jet, std::vector<Lepton> const &delphes_muons = {});

private:

   std::vector<Lepton> Muons(std::vector<Lepton> const& delphes_muons, Jet const& jet) const;

   std::vector<Jet> CoreCandidates(std::vector<Lepton> const& muons, Jet const& jet) const;

   Jet Core(std::vector<Jet> const& core_candidates, std::vector<Lepton> const& muons) const;

   Jet Result(std::vector<Lepton> const& muons,  Jet const& jet, Jet & core) const;

    //Main tagging parameters
    // xMax for the tag
    double XMax() const;

    Momentum min_muon_pt_ = 10_GeV; // Min muon pT to be a "taggable" muon

    // Parameters for subjet reconstruction
    double min_tower_pt_ratio_ = 0.05; // Min pT ratio of tower to entire jet, to qualify for reclustering. Helps reduce pileup sensitivity
    Angle core_jet_radius = 40_mrad; // Reculstering radius

    double core_min_boost_ = 1; // Minimum core boost during core selection (keep this low to reduce fake rate)

    /**
    * @brief Ceiling of reconstructe subjet mass, for sanity
    */
    Mass MaxSubJetMass() const;

};

}
