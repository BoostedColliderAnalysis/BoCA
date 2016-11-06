#include "boca/multiplets/Quartet.hh"
#include "boca/WimpMass.hh"
#include "boca/generic/Types.hh"
#include "boca/event/Event.hh"
#include "boca/fastjet/Particles.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/Exception.hh"

#include "higgscpv/tagger/TopLeptonicPair.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace higgscpv
{

namespace tagger
{

int TopLeptonicPair::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto triplets = top_leptonic_reader_.Multiplets(event);
    DEBUG(triplets.size());
    auto particles = event.GenParticles();
    auto top_particles = CopyIfParticle(particles, Id::top);
    CHECK(top_particles.size() == 2, top_particles.size());
//    std::vector<Jet>neutrinos = CopyIfNeutrino(particles);
    if (top_particles.size() != 2 && tag == Tag::signal) DEBUG(particles.size());
    auto final_triplets = BestMatches(triplets, top_particles, tag);
//     CHECK(final_triplets.size()==2, final_triplets.size());
    auto sextets = UnorderedPairs(final_triplets, [](Triplet const & triplet_1, Triplet const & triplet_2) {
        Quartet22 quartet(Doublet(triplet_1.Singlet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet(), triplet_2.Doublet().Jet()));
        if (quartet.Overlap()) throw Overlap();
        quartet.Doublet1().SetBdt(triplet_1.Bdt());
        quartet.Doublet2().SetBdt(triplet_2.Bdt());
        WimpMass wimp_mass;
        //             Insert(sextets, wimp_mass.Sextet(quartet, event.MissingEt(), neutrinos, tag));
        return wimp_mass.Fake(quartet);
    });

    if (tag == Tag::signal && sextets.size() > 1) {
        DEBUG(sextets.size());
        sextets = BestRapidity(sextets);
    }
    return SaveEntries(sextets);
}

std::vector<Sextet33> TopLeptonicPair::Truth(boca::Event const& event, std::vector<Sextet33> sextets, Tag tag) const
{
    switch (tag) {
    case Tag::signal : {
        auto tops = CopyIfParticle(event.GenParticles(), Id::top);
        std::vector<Sextet33> final_sextets;
        for (auto const & sextet : sextets) {
            auto truth_level = false;
            for (auto const & top : tops) {
                if (Close<boca::Jet>(top)(sextet.Triplet1())) truth_level = true;
                if (Close<boca::Jet>(top)(sextet.Triplet2())) truth_level = true;
            }
            if (truth_level) final_sextets.emplace_back(sextet);
        }
        return final_sextets;
    }
    case Tag::background : return sextets;
        DEFAULT(boca::Name(tag), {});
    }
}

std::vector<Sextet33> TopLeptonicPair::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    auto triplets = top_leptonic_reader_.Multiplets(event);
    INFO(triplets.size());
    auto  sextets = UnorderedPairs(triplets, [&](Triplet const & triplet_1, Triplet const & triplet_2) {
        Quartet22 quartet(Doublet(triplet_1.Singlet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet(), triplet_2.Doublet().Jet()));
        if (quartet.Overlap()) throw Overlap();
        quartet.Doublet1().SetBdt(triplet_1.Bdt());
        quartet.Doublet2().SetBdt(triplet_2.Bdt());
        WimpMass wimp_mass;
//             for (auto sextet : wimp_mass.Sextets(quartet, event.MissingEt())) {
        Sextet33 sextet = wimp_mass.Fake(quartet);
        sextet.SetBdt(Bdt(sextet, reader));
        return sextet;
//             }
    });
    INFO(sextets.size());
    return sextets;
}
std::string TopLeptonicPair::Name() const
{
    return "TopLeptonicPair";
}

}

}
