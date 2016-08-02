#include "boca/TopLeptonicPairTagger.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/WimpMass.hh"
#include "boca/generic/Types.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG.hh"
#include "boca/generic/Exception.hh"

namespace boca
{

namespace higgscpv
{

int TopLeptonicPairTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    DEBUG(triplets.size());
   std::vector<Particle> particles = event.GenParticles();
   std::vector<Particle> top_particles = CopyIfParticle(particles, Id::top);
    CHECK(top_particles.size() == 2, top_particles.size());
//    std::vector<Jet>neutrinos = CopyIfNeutrino(particles);
    if (top_particles.size() != 2 && tag == Tag::signal) DEBUG(particles.size());
    std::vector<Triplet> final_triplets = BestMatches(triplets, top_particles, tag);
//     CHECK(final_triplets.size()==2, final_triplets.size());
    std::vector<Sextet> sextets = UnorderedPairs(final_triplets, [](Triplet const& triplet_1, Triplet const& triplet_2) {
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

std::vector<Sextet> TopLeptonicPairTagger::Truth(boca::Event const& event, std::vector<Sextet> sextets, Tag tag) const
{
    switch (tag) {
    case Tag::signal : {
      std::vector<Particle> tops = CopyIfParticle(event.GenParticles(), Id::top);
        std::vector<Sextet> final_sextets;
        for (auto const& sextet : sextets) {
            bool truth_level = false;
            for (auto const& top : tops) {
                if (Close<Jet>(top)(sextet.Triplet1())) truth_level = true;
                if (Close<Jet>(top)(sextet.Triplet2())) truth_level = true;
            }
            if (truth_level) final_sextets.emplace_back(sextet);
        }
        return final_sextets;
    }
    case Tag::background : return sextets;
    DEFAULT(boca::Name(tag),{});
    }
}

std::vector<Sextet> TopLeptonicPairTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    INFO(triplets.size());
    std::vector<Sextet>  sextets = UnorderedPairs(triplets, [&](Triplet const& triplet_1, Triplet const& triplet_2) {
        Quartet22 quartet(Doublet(triplet_1.Singlet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet(), triplet_2.Doublet().Jet()));
        if (quartet.Overlap()) throw Overlap();
        quartet.Doublet1().SetBdt(triplet_1.Bdt());
        quartet.Doublet2().SetBdt(triplet_2.Bdt());
        WimpMass wimp_mass;
//             for (auto sextet : wimp_mass.Sextets(quartet, event.MissingEt())) {
        Sextet sextet = wimp_mass.Fake(quartet);
        sextet.SetBdt(Bdt(sextet, reader));
        return sextet;
//             }
    });
    INFO(sextets.size());
    return sextets;
}
std::string TopLeptonicPairTagger::Name() const
{
    return "TopLeptonicPair";
}

}

}
