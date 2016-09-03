/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/external/TopTagger2.hh"

#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "standardmodel/tagger/TopHadronicHep2.hh"

#include "boca/Settings.hh"
#include "boca/PreCuts.hh"
#include "boca/Event.hh"
#define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace standardmodel
{

namespace tagger
{

TopHadronicHep2::TopHadronicHep2()
{
//     top_mass_window_ = 25_GeV;
    top_mass_window_ = MassOf(Id::top);
}

int TopHadronicHep2::Train(boca::Event const& event, const PreCuts& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Triplets(event, pre_cuts, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    }), Particles(event), tag);
}

std::vector<Particle>TopHadronicHep2::Particles(boca::Event const& event) const
{
    INFO0;
    auto particles = event.GenParticles();
    auto quarks = CopyIfGrandMother(CopyIfQuark(particles), Id::top);
    return CopyIfGrandDaughter(particles, quarks);
}

bool TopHadronicHep2::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
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

bool TopHadronicHep2::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
    return false;
}

std::vector<Triplet> TopHadronicHep2::Multiplets(boca::Event const& event, const boca::PreCuts& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Triplets(event, pre_cuts, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
}

std::vector<Triplet> TopHadronicHep2::Triplets(boca::Event const& event, PreCuts const& pre_cuts, std::function<Triplet(Triplet&)> const& function) const
{
    INFO0;
    auto jets = event.EFlow(JetDetail::structure | JetDetail::isolation);
    if (jets.empty()) return {};
    INFO(jets.size(), pre_cuts.JetConeMax(Id::top));
    if(jets.size() == 306 /*|| jets.size() == 115*/) return {}; /// FIXME remove this nasty hack which seems to be necessary for a specific gluon file
    auto cluster_sequence = boca::ClusterSequence{jets, Settings::JetDefinition(pre_cuts.JetConeMax(Id::top))};
    jets = SortedByPt(cluster_sequence.InclusiveJets(pre_cuts.PtLowerCut().Get(Id::top)));
    INFO(jets.size());
    auto triplets = std::vector<Triplet>{};
    for (auto const & jet : jets) {
        auto tagger = hep::TopTagger2{jet, MassOf(Id::top) / GeV, MassOf(Id::W) / GeV};

        // Unclustering, Filtering & Subjet Settings
//         tagger.set_max_subjet_mass(30.);
//         tagger.set_mass_drop_threshold(0.8);
//         tagger.set_filtering_R(0.3);
//         tagger.set_filtering_n(5);
//         tagger.set_filtering_minpt_subjet(30.);

        // How to select among candidates
        tagger.set_mode(hep::TWO_STEP_FILTER);

        // Requirements to accept a candidate
        tagger.set_top_minpt(pre_cuts.PtLowerCut().Get(Id::top) / GeV);
        tagger.set_top_mass_range((MassOf(Id::top) - top_mass_window_) / GeV, (MassOf(Id::top) + top_mass_window_) / GeV);



        tagger.run();
        auto sub_jets = JetVector(tagger.top_subjets());
        if (sub_jets.size() < 3) continue;
        Triplet triplet(Doublet(sub_jets.at(1), sub_jets.at(2)), sub_jets.at(0));
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

std::string TopHadronicHep2::Name() const
{
    INFO0;
    return "TopHadronicHep2";
}

latex::String TopHadronicHep2::LatexName() const
{
    INFO0;
    return "t_{h}^{hep2}";
}

}

}
