#include "TopLeptonicPairTagger.hh"
#include "multiplets/Quartet.hh"
#include "WimpMass.hh"
#include "generic/Types.hh"
#include "Event.hh"
#include "multiplets/Particles.hh"
#include "generic/Vector.hh"
#include "generic/DEBUG.hh"
#include "generic/Exception.hh"

namespace boca
{

namespace higgscpv
{

int TopLeptonicPairTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    INFO0;
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    DEBUG(triplets.size());
   std::vector<Particle> particles = event.Partons().GenParticles();
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
        //             Insert(sextets, wimp_mass.Sextet(quartet, event.Hadrons().MissingEt(), neutrinos, tag));
        return wimp_mass.Fake(quartet);
    });

    if (tag == Tag::signal && sextets.size() > 1) {
        DEBUG(sextets.size());
        sextets = BestRapidity(sextets);
    }
    return SaveEntries(sextets);
}

std::vector<Sextet> TopLeptonicPairTagger::TruthLevel(Event const& event, std::vector<Sextet> sextets, Tag tag) const
{
    switch (tag) {
    case Tag::signal : {
      std::vector<Particle> tops = CopyIfParticle(event.Partons().GenParticles(), Id::top);
        std::vector<Sextet> final_sextets;
        for (auto const& sextet : sextets) {
            bool truth_level = false;
            for (auto const& top : tops) {
                if (Close(top)(sextet.Triplet1())) truth_level = true;
                if (Close(top)(sextet.Triplet2())) truth_level = true;
            }
            if (truth_level) final_sextets.emplace_back(sextet);
        }
        return final_sextets;
    }
    case Tag::background : return sextets;
    DEFAULT(boca::Name(tag),{});
    }
}

std::vector<Sextet> TopLeptonicPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    INFO(triplets.size());
    std::vector<Sextet>  sextets = UnorderedPairs(triplets, [&](Triplet const& triplet_1, Triplet const& triplet_2) {
        Quartet22 quartet(Doublet(triplet_1.Singlet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet(), triplet_2.Doublet().Jet()));
        if (quartet.Overlap()) throw Overlap();
        quartet.Doublet1().SetBdt(triplet_1.Bdt());
        quartet.Doublet2().SetBdt(triplet_2.Bdt());
        WimpMass wimp_mass;
//             for (auto sextet : wimp_mass.Sextets(quartet, event.Hadrons().MissingEt())) {
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
