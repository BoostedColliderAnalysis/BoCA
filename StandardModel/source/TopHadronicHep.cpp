/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "fastjet/ClusterSequence.hh"

#include "external/TopTagger.hh"
#include "generic/Exception.hh"
#include "delphes/Hadrons.hh"
#include "plotting/Font.hh"
#include "multiplets/Particles.hh"
#include "multiplets/Sort.hh"
#include "ClusterSequence.hh"
#include "DetectorGeometry.hh"
#include "PreCuts.hh"
#include "TopHadronicHep.hh"
#include "Event.hh"
// #define DEBUGGING
#include "generic/DEBUG.hh"

namespace boca
{

namespace standardmodel
{

TopHadronicHep::TopHadronicHep()
{
//     top_mass_window_ = 25_GeV;
    top_mass_window_ = MassOf(Id::top);
}

int TopHadronicHep::Train(const Event& event, const PreCuts& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Triplets(event, pre_cuts, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    }), Particles(event), tag);
}

std::vector<Particle>TopHadronicHep::Particles(Event const& event) const
{
    INFO0;
    auto particles = event.Partons().GenParticles();
    auto quarks = CopyIfGrandMother(CopyIfQuark(particles), Id::top);
    return CopyIfGrandDaughter(particles, quarks);
}

bool TopHadronicHep::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
//         if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > top_mass_window_) return true;
//         if (pre_cuts.NotParticleRho(triplet)) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopHadronicHep::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
    return false;
}

std::vector<Triplet> TopHadronicHep::Multiplets(const Event& event, const boca::PreCuts& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Triplets(event, pre_cuts, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
}

std::vector<Triplet> TopHadronicHep::Triplets(Event const& event, PreCuts const& pre_cuts, std::function<Triplet(Triplet&)> const& function) const
{
    INFO0;
    auto jets = static_cast<delphes::Hadrons const&>(event.Hadrons()).EFlow(JetDetail::structure | JetDetail::isolation);
    if (jets.empty()) return {};
    INFO(jets.size(), pre_cuts.JetConeMax(Id::top));
//     if(jets.size() == 209 || jets.size() == 115) return {}; /// FIXME remove this nasty hack which seems to be necessary for a specific gluon file
    boca::ClusterSequence cluster_sequence(jets, DetectorGeometry::JetDefinition(pre_cuts.JetConeMax(Id::top)));
    jets = SortedByPt(cluster_sequence.InclusiveJets(pre_cuts.PtLowerCut().Get(Id::top)));
    INFO(jets.size());
    std::vector<Triplet> triplets;
    for (auto const & jet : jets) {
        hep::TopTagger tagger(cluster_sequence.Get(), jet, MassOf(Id::top) / GeV, MassOf(Id::W) / GeV);
        tagger.set_top_range((MassOf(Id::top) - top_mass_window_) / GeV, (MassOf(Id::top) + top_mass_window_) / GeV);
        tagger.run_tagger();
        if (tagger.top_subjets().size() < 3) continue;
        Triplet triplet(Doublet(tagger.top_subjets().at(1), tagger.top_subjets().at(2)), tagger.top_subjets().at(0));
        DEBUG(triplet.Mass());
        try {
            triplet = function(triplet);
        } catch (std::exception const& exception) {
            continue;
        }
        triplet.SetTag(Tag(tagger.is_masscut_passed()));
        triplets.emplace_back(triplet);
    }
    return triplets;
}

std::string TopHadronicHep::Name() const
{
    INFO0;
    return "TopHadronicHep";
}

std::string TopHadronicHep::LatexName() const
{
    INFO0;
    return Formula("t_{h}") + "^{hep}";
}

}

}

