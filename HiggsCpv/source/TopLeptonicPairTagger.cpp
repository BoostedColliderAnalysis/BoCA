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

int TopLeptonicPairTagger::Train(const Event &event, analysis::PreCuts &, const analysis::Tag tag) const
{
    Info();
    std::vector<Triplet> triplet = top_leptonic_reader_.Multiplets(event);
    Debug(triplet.size());

    Jets particles = event.Partons().GenParticles();
    Jets top_particles = CopyIfAbsParticle(particles, Id::top);
    Jets neutrinos = copy_if_neutrino(particles);
    if (top_particles.size() != 2 && tag == Tag::signal) Error("Number of Tops?", particles.size());

    std::vector<Triplet> final_triplets;
    switch (tag) {
    case Tag::signal :
        for (const auto & doublet : triplet) for (const auto top : top_particles) if (doublet.Coincides(top)) final_triplets.emplace_back(doublet);
        break;
    case Tag::background :
        final_triplets = triplet;
    }
    Debug(final_triplets.size());

    std::vector<Sextet> sextets;
    for (auto triplet_1 = triplet.begin(); triplet_1 != triplet.end(); ++triplet_1)
        for (auto triplet_2 = triplet_1 + 1; triplet_2 != triplet.end(); ++triplet_2) {
          Quartet22 quartet(Doublet((*triplet_1).Singlet().Jet(),(*triplet_1).Doublet().Jet()), Doublet((*triplet_2).Singlet().Jet(),(*triplet_2).Doublet().Jet()));
            if (quartet.Overlap()) continue;
            WimpMass wimp_mass;
//             sextets = Join(sextets, wimp_mass.Sextet(quartet, event.Hadrons().MissingEt(), neutrinos, tag));
            sextets.emplace_back(wimp_mass.Fake(quartet));
        }
    Debug("Number of Sextets", sextets.size());
    if (tag == Tag::signal) sextets = BestRapidity(sextets);
    return SaveEntries(sextets);
}

std::vector< Sextet > TopLeptonicPairTagger::Multiplets(const Event &event, analysis::PreCuts &, const TMVA::Reader &reader) const
{
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    Info(triplets.size());
    std::vector<Sextet>  sextets;
    for (auto triplet_1 = triplets.begin(); triplet_1 != triplets.end(); ++triplet_1)
        for (auto triplet_2 = triplet_1 + 1; triplet_2 != triplets.end(); ++triplet_2) {
          Quartet22 quartet(Doublet((*triplet_1).Singlet().Jet(),(*triplet_1).Doublet().Jet()), Doublet((*triplet_2).Singlet().Jet(),(*triplet_2).Doublet().Jet()));
            if (quartet.Overlap()) continue;
            Info("Quartet");
            WimpMass wimp_mass;
//             for (auto sextet : wimp_mass.Sextets(quartet, event.Hadrons().MissingEt())) {
                Sextet sextet = wimp_mass.Fake(quartet);
                Info("Sextet");
                sextet.SetBdt(Bdt(sextet,reader));
                sextets.emplace_back(sextet);
//             }
        }
    Info(sextets.size());
    return ReduceResult(sextets);
}

}

}
