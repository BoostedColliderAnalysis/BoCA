#include "TopLeptonicPairTagger.hh"
#include "Quartet.hh"
#include "WimpMass.hh"
#include "Predicate.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace higgscpv
{

TopLeptonicPairTagger::TopLeptonicPairTagger()
{
    Note();
    DefineVariables();
}

int TopLeptonicPairTagger::Train(const Event& event, const analysis::PreCuts&, Tag tag) const
{
    Info();
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    Debug(triplets.size());
    Jets particles = event.Partons().GenParticles();
    Jets top_particles = CopyIfParticle(particles, Id::top);
    Check(top_particles.size() == 2, top_particles.size());
//     Jets neutrinos = CopyIfNeutrino(particles);
    if (top_particles.size() != 2 && tag == Tag::signal) Debug(particles.size());
    std::vector<Triplet> final_triplets = BestMatches(triplets, top_particles, tag);
//     Check(final_triplets.size()==2, final_triplets.size());
    std::vector<Sextet> sextets = unordered_pairs(final_triplets, [](const Triplet & triplet_1, const Triplet & triplet_2) {
        Quartet22 quartet(Doublet(triplet_1.Singlet().Jet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet().Jet(), triplet_2.Doublet().Jet()));
        if (quartet.Overlap()) throw "overlap";
        WimpMass wimp_mass;
        //             sextets = Join(sextets, wimp_mass.Sextet(quartet, event.Hadrons().MissingEt(), neutrinos, tag));
        return wimp_mass.Fake(quartet);
    });

    if (tag == Tag::signal && sextets.size() > 1) {
        Debug(sextets.size());
        sextets = BestRapidity(sextets);
    }
    return SaveEntries(sextets);
}

std::vector<Sextet> TopLeptonicPairTagger::TruthLevel(const Event& event, std::vector<Sextet> sextets, Tag tag) const
{
    switch (tag) {
    case Tag::signal : {
        Jets tops = CopyIfParticle(event.Partons().GenParticles(), Id::top);
        std::vector<Sextet> final_sextets;
        for (const auto & sextet : sextets) {
            bool truth_level = false;
            for (const auto & top : tops) {
                if (Close(top)(sextet.Triplet1())) truth_level = true;
                if (Close(top)(sextet.Triplet2())) truth_level = true;
            }
            if (truth_level) final_sextets.emplace_back(sextet);
        }
        return final_sextets;
    }
    case Tag::background : return sextets;
    }
}

std::vector<Sextet> TopLeptonicPairTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    Info(triplets.size());
    std::vector<Sextet>  sextets = unordered_pairs(triplets, [&](const Triplet & triplet_1, const Triplet & triplet_2) {
        Quartet22 quartet(Doublet(triplet_1.Singlet().Jet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet().Jet(), triplet_2.Doublet().Jet()));
        if (quartet.Overlap()) throw "overlap";
        WimpMass wimp_mass;
//             for (auto sextet : wimp_mass.Sextets(quartet, event.Hadrons().MissingEt())) {
        Sextet sextet = wimp_mass.Fake(quartet);
        sextet.SetBdt(Bdt(sextet, reader));
        return sextet;
//             }
    });
    Info(sextets.size());
    return ReduceResult(sextets);
}

}

}
