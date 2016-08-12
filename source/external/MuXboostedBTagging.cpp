#include <boost/range/algorithm/max_element.hpp>

#include "boca/external/MuXboostedBTagging.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "boca/physics/Id.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/Types.hh"
#include "boca/Settings.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"


namespace boca
{

Jet MuXboostedBTagging::Process(Jet const& jet, std::vector<Lepton> const& delphes_muons)
{
    INFO0;
    std::vector<Jet> muons;
    for (auto const & muon : delphes_muons) if (Close<Lepton>(jet)(muon)) muons.emplace_back(muon);
    if (muons.empty()) return jet;
    boost::sort(muons, [](Jet const & one, Jet const & two) {
        return one.Pt() < two.Pt();
    });

    auto recluster_input = muons;
    for (auto const & consituent : jet.Constituents()) {
        if (consituent.Info().ContainsDetectorPart(DetectorPart::tower) && consituent.Pt() < min_tower_pt_ratio_ * jet.Pt()) continue; // Don't use
        recluster_input.emplace_back(consituent);
    }
    // Recluster the jet, to find core candidates
    boca::ClusterSequence cluster_sequence(recluster_input, fastjet::JetDefinition(fastjet::antikt_algorithm, core_jet_radius / rad, &Settings::Recombiner()));
    // Get the core candidates (NOT sorted by pT until we remove muons)
    auto core_candidates = cluster_sequence.InclusiveJets();
    if (core_candidates.empty()) return jet;
    cluster_sequence.NoLongerNeeded();

    // If a taggable muon is inside a core candidate, remove the muon p4
    for (auto const & muon : muons) for (auto & core_candidate : core_candidates) if (muon.DeltaRTo(core_candidate) < core_jet_radius) {
                core_candidate -= muon;
                break;
            }

    // Sort the core candidates by pT (highest to lowest)
    core_candidates = SortedByPt(core_candidates);

    auto hardest_muon = *boost::range::max_element(muons, [](Lepton const & muon_1, Lepton const & muon_2) {
        return muon_1.Pt() > muon_2.Pt();
    });

    auto min_delta_mass = std::numeric_limits<Mass>::max(); // Default to infinity
    auto core = core_candidates.front();  // Default to hardest core

    for (auto const & core_candidate : core_candidates) {
        auto g = sqr(MassOf(Id::Dpm) / core_candidate.Energy());
        // Make sure we still have sufficient boost after muon subtraction
        if (g * sqr(core_min_boost_) > 1.) continue;
        auto y = core_candidate.Vector3().Tan2(hardest_muon.Vector3());

        // The core has the mass closest to fSubjetMassHypothesis
        auto delta_mass = abs(sqrt(sqr(MassOf(Id::Dpm)) + (4. * hardest_muon.Energy() * core_candidate.Energy() * (g + y)) / (1. + y + sqrt(1. - ((g - y) + g * y)))) - MassOf(Id::B0));

        if (delta_mass > min_delta_mass) continue;
        min_delta_mass = delta_mass;
        core = core_candidate;
    }

    // The current mass depends more on the granularity of the CAL more than anything else
    // To fix the mass, We need to scale the momentum of the core (but not the energy)
    core.ScaleMomentum(sqrt((core.Energy() - MassOf(Id::Dpm)) * (core.Energy() + MassOf(Id::Dpm)) / core.ModP2()));

    // Keep track of the smallest x for any muon
    auto min_x = std::numeric_limits<double>::max(); // Large enough, simple significand
    // Iterate through each muon, add it to the core, and calculate the resulting boost invariant
    Jet p4_neutrino_correction;
    for (auto const & muon : muons) {
        // Add back the muon and the neutrino
        core += 2 * muon;
        // Set a hard ceiling on subjet mass, for poor reconstruction
        double x_core = core.Energy() * muon.Vector3().Cross(core.Vector3()).Mag() / muon.Vector3().Dot(core.Vector3()) / std::min(core.Mass(), max_sub_jet_mass_);
        CHECK(x_core >= 0, x_core);
        if (x_core < 0) return jet;
        // Add the neutrino to original jet IFF the muon passes the boosted test
        if (x_core <= x_max_) p4_neutrino_correction += muon;
        min_x = std::min(min_x, x_core);
    }

    Jet result = jet + p4_neutrino_correction;
    CHECK(result.Pt() > 0_eV, result.Pt());
    CHECK(!(result.Pt() != result.Pt()), result.Pt())
    CHECK(!(core.Pt() != core.Pt()), core.Pt())
    CHECK(!(min_x != min_x), min_x)
    if (result.Pt() <= 0_eV) return jet;
    result.SetInfo(jet.Info());
    result.Info().SetMuBTag(min_x, core.Pt() / result.Pt());
    return result;
}

}
