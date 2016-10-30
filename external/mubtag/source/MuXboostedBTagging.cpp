#include <boost/range/algorithm/max_element.hpp>

#include "mubtag/MuXboostedBTagging.hh"

#include "boca/generic/Types.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "boca/identification/Id.hh"
#include "boca/fastjet/Vector.hh"
#include "boca/fastjet/Sort.hh"
#include "boca/Settings.hh"

#define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

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

Jet MuXboostedBTagging::Process(Jet const &jet, std::vector<Lepton> const &delphes_muons)
{
    INFO0;
    auto muons = Muons(delphes_muons,  jet);
    if (muons.empty()) return jet;

    auto core_candidates = CoreCandidates(muons,  jet);
    if (core_candidates.empty()) return jet;

    auto core = Core(core_candidates,  muons);

    return Result(muons, jet, core);
}

std::vector<Lepton> MuXboostedBTagging::Muons(std::vector<Lepton> const &delphes_muons, Jet const &jet) const
{
    INFO0;
    auto muons = std::vector<Lepton> {};
    for (auto const &muon : delphes_muons) if (Close<Lepton>(jet, Settings::JetConeSize())(muon)) muons.emplace_back(muon);
    boost::sort(muons, [](Jet const & one, Jet const & two) {
        return one.Pt() < two.Pt();
    });
    return muons;
}

std::vector<Jet> MuXboostedBTagging::CoreCandidates(std::vector<Lepton> const &muons, Jet const &jet) const
{
    INFO0;
    auto recluster_input = muons;
    for (auto const &consituent : jet.Constituents()) {
        if (consituent.Info().ContainsDetectorPart(DetectorPart::tower) && consituent.Pt() < min_tower_pt_ratio_ * jet.Pt()) continue; // Don't use
        recluster_input.emplace_back(consituent);
    }
    // Recluster the jet, to find core candidates
    auto cluster_sequence = boca::ClusterSequence {recluster_input, fastjet::JetDefinition(fastjet::antikt_algorithm, core_jet_radius / rad, &Settings::Recombiner())};
    // Get the core candidates (NOT sorted by pT until we remove muons)
    auto core_candidates = cluster_sequence.InclusiveJets();
    if (core_candidates.empty()) return core_candidates;
    cluster_sequence.NoLongerNeeded();

    // If a taggable muon is inside a core candidate, remove the muon p4
    for (auto const &muon : muons) for (auto &core_candidate : core_candidates) if (muon.DeltaRTo(core_candidate) < core_jet_radius) {
                core_candidate -= muon;
                break;
            }

    // Sort the core candidates by pT (highest to lowest)
    core_candidates = SortedByPt(core_candidates);
    return core_candidates;
}

Jet MuXboostedBTagging::Core(std::vector<Jet> const &core_candidates,  std::vector<Lepton> const &muons) const
{
    INFO0;
    auto hardest_muon = *boost::range::max_element(muons, [](Lepton const & muon_1, Lepton const & muon_2) {
        return muon_1.Pt() > muon_2.Pt();
    });
    auto min_delta_mass = std::numeric_limits<Mass>::max(); // Default to infinity
    auto core = core_candidates.front();  // Default to hardest core

    for (auto const &core_candidate : core_candidates) {
        if (core_candidate.Energy() == 0_eV) continue;
        auto g = sqr(MassOf(Id::Dpm) / core_candidate.Energy());
        // Make sure we still have sufficient boost after muon subtraction
        if (g * sqr(core_min_boost_) > 1.) continue;
        auto y = core_candidate.Spatial().Tan2(hardest_muon.Spatial());

        // The core has the mass closest to fSubjetMassHypothesis
        auto radicant = 1. - ((g - y) + g * y);
        if (radicant < 0) continue;
        auto denom = 1. + y + sqrt(radicant);
        if (denom == 0) continue;
        auto radicant2 = sqr(MassOf(Id::Dpm)) + (4. * hardest_muon.Energy() * core_candidate.Energy() * (g + y)) / denom;
        if (radicant2 < 0_eV * eV) continue;
        auto delta_mass = abs(sqrt(radicant2) - MassOf(Id::B0));

        if (delta_mass > min_delta_mass) continue;
        min_delta_mass = delta_mass;
        core = core_candidate;
    }

    if (core.ModP2() ==  0_eV * eV) return core;
    // The current mass depends more on the granularity of the CAL more than anything else
    // To fix the mass, We need to scale the momentum of the core (but not the energy)
    core.ScaleMomentum(sqrt((core.Energy() - MassOf(Id::Dpm)) * (core.Energy() + MassOf(Id::Dpm)) / core.ModP2()));
    return core;
}

Jet MuXboostedBTagging::Result(std::vector<Lepton> const &muons,  Jet const &jet, Jet &core) const
{
    INFO0;
    // Keep track of the smallest x for any muon
    auto min_x = std::numeric_limits<double>::max(); // Large enough, simple significand
    // Iterate through each muon, add it to the core, and calculate the resulting boost invariant
    auto p4_neutrino_correction = Jet {};
    for (auto const &muon : muons) {
        // Add back the muon and the neutrino
        core += 2 * muon;
        // Set a hard ceiling on subjet mass, for poor reconstruction
        auto dot = muon.Spatial().Dot(core.Spatial());
        auto min = std::min(core.Mass(), MaxSubJetMass());
        if (dot == 0_eV * eV || min == 0_eV) continue;
        auto cross = muon.Spatial().Cross(core.Spatial()).Mag();
        auto x_core = static_cast<double>(core.Energy() * cross / dot / min);
        CHECK(x_core >= 0, x_core);
        if (x_core < 0) return jet;
        // Add the neutrino to original jet IFF the muon passes the boosted test
        if (x_core <= XMax()) p4_neutrino_correction += muon;
        min_x = std::min(min_x, x_core);
    }

    auto result = jet + p4_neutrino_correction;
    CHECK(result.Pt() > 0_eV, result.Pt());
    CHECK(!(result.Pt() != result.Pt()), result.Pt())
    CHECK(!(core.Pt() != core.Pt()), core.Pt())
    CHECK(!(min_x != min_x), min_x)
    if (result.Pt() <= 0_eV) return jet;
    result.SetInfo(jet.Info());
    result.Info().SetMuBTag(min_x, core.Pt() / result.Pt());
    return result;
}

Mass MuXboostedBTagging::MaxSubJetMass() const
{
    INFO0;
    return 12_GeV;
}


double MuXboostedBTagging::XMax() const
{
    INFO0;
    return 3;
}

}
