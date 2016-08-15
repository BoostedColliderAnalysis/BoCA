#pragma once
#include "boca/multiplets/Jet.hh"

/** \class MuXboostedBTagging
 *
 *  MuXboostedBTagging tags high-pT heavy flavor jets using a muonic tag
 *  --> see [arXiv:1511.05990] for a full discussion of the physics.
 *  --> see <delphes/doc/MuXboostedBTagging/MuX_UserGuide.pdf> for a quick description of the module
 *  --> check <https://github.com/keith-pedersen/delphes/tree/MuXboostedBTagging> for updates
 *
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
 *
 *
 *  NOTE: This module gives more accurate light jet fake rates when
 *  used in conjunction with AllParticlePropagator (which simulates the
 *  initial bending of in-flight Pion/Kaon decays to muons).
 *
 *
 *
 *  The algorithm synopsis
 *
 *  1. Clone each jet into the output array, regardless of whether it's tagged.
 *
 *  2. Look for jets passing a preliminary pT cut (no less than half
 *     the final cut, since neutrino estimation could potentially
 *     double a jet's pT)
 *       2a. (ptJet >= 0.5*fMinJetPt)
 *
 *  3. Look inside the jet for at least one "taggable" muon (muon pT >= fMinMuonPt).
 *     WARNING: This requires muons to be clustered into jets during
 *     the initial jet clustering; MuXboostedBTagging does not take a
 *     muon input array.
 *       3a. (ptMu >= fMinMuonPt)
 *       3b. After all "taggable" neutrinos are found, ensure that the
 *           final jet pT (with neutrino estimation) can possibly pass
 *           the pT cut (ptJet [with neutrinos] > fMinJetPt).
 *
 *  4. Reconstruct the subjet of the semi-leptonic decay
 *       4a. Recluster the jet (discarding towers whose pT ratio, to the
 *           original jet pT, is less than fMinTowerPtRatio), using
 *           anti-kt with radius fCoreAntiktR.
 *       4b. The mass of the core is poorly measured, constrain it
 *           to fCoreMassHypothesis.
 *       4c. Search through the list of candidate cores and, if their
 *           boost is greater than fCoreMinBoost, calculate the mass
 *           of the resulting subjet (using only the hardest muon).
 *       4d. The "correct" core is the one which produces mSubjet closest
 *           to fSubjetMassHypothesis.
 *
 *  5. Calculate x
 *       5a. x = tan(thetaLab)*Esubjet/mSubjet. However, restrict mSubjet
 *           to be no larger than fMaxSubjetMass (in case of a
 *           poorly reconstructed subjet).
 *
 *  6. Calculate fSubjet
 *       6a. fSubjet = pTsubjet/pTjet (account for neutrino estimation).
 *
 *  7. Tag the jet
 *       7a. If (x <= fMaxX) and (f >= fSubjet), tag both the original jet and
 *           the clone (using fBitNumber in the BTag field).
 *       7b. If the jet is tagged, add the neutrino pT to the clone.
 *
 *  \author K. Pedersen - Illinois Institute of Technology
 *
 */


namespace boca
{

class MuXboostedBTagging
{

public:

  Jet Process(boca::Jet const& jet, std::vector<Lepton> const& delphes_muons = {});

private:

    //Main tagging parameters
    double x_max_ = 3; // xMax for the tag
//     double min_core_pt_ratio_ = .5; // fMin for the tag

    Momentum min_muon_pt_ = 10_GeV; // Min muon pT to be a "taggable" muon

    // Parameters for subjet reconstruction
    double min_tower_pt_ratio_ = 0.05; // Min pT ratio of tower to entire jet, to qualify for reclustering. Helps reduce pileup sensitivity
    Angle core_jet_radius = 40_mrad; // Reculstering radius

    double core_min_boost_ = 1; // Minimum core boost during core selection (keep this low to reduce fake rate)

    Mass max_sub_jet_mass_ = 12_GeV; // Ceiling of reconstructe subjet mass, for sanity

};

}
