#include "HeavyHiggsLeptonicTagger.hh"

#include "WimpMass.hh"
#include "multiplets/Quartet.hh"
#include "Types.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace heavyhiggs {

int HeavyHiggsLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info0;
//     Mass mass = event.mass();
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    Jet missing_et = event.Hadrons().MissingEt();
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> neutrinos = CopyIfNeutrino(particles);
    INFO(triplets.size());
    std::vector<Sextet> sextets;
    for (auto const& triplet_1 : triplets) {
        for (auto const& triplet_2 : triplets) {
            Quartet22 quartet(Doublet(triplet_1.Singlet().Jet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet().Jet(), triplet_2.Doublet().Jet()));
            if (quartet.Overlap())
                continue;
            std::vector<Sextet> Presextets;
            WimpMass wimp_mass;
            Presextets = wimp_mass.Sextet(quartet, missing_et, neutrinos, tag);
            for (auto const& sextet : Presextets) {
//                 if (tag == Tag::signal && sextet.Mass() < mass / 2.) continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    INFO(sextets.size());
//     if (tag == Tag::signal) sextets = BestMass(sextets, mass);
    return SaveEntries(sextets);
}

std::vector<Sextet>  HeavyHiggsLeptonicTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    Jet missing_et = event.Hadrons().MissingEt();
    std::vector<Sextet> sextets;
    for (auto const& triplet_1 : triplets) {
        for (auto const& triplet_2 : triplets) {
            Quartet22 quartet(Doublet(triplet_1.Singlet().Jet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet().Jet(), triplet_2.Doublet().Jet()));
            if (quartet.Overlap())
                continue;
            std::vector<Sextet> pre_sextets;
            WimpMass wimp_mass;
            pre_sextets = wimp_mass.Sextets(quartet, missing_et);
            for (auto& sextet : pre_sextets) {
                sextet.SetBdt(Bdt(sextet, reader));
                sextets.emplace_back(sextet);
            }
        }
    }
    return ReduceResult(sextets);
}
std::string HeavyHiggsLeptonicTagger::Name() const
{
    return "HeavyHiggsLeptonic";
}

}

}
