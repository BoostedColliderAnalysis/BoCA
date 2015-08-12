#include "HeavyHiggsLeptonicTagger.hh"

#include "WimpMass.hh"
#include "Quartet.hh"
#include "Types.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

HeavyHiggsLeptonicTagger::HeavyHiggsLeptonicTagger()
{
  Info();
    DefineVariables();
}

int HeavyHiggsLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    float mass = event.mass();
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    Jets particles = event.Partons().GenParticles();
    Jets neutrinos = CopyIfNeutrino(particles);
    Info(triplets.size());
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
                if (tag == Tag::signal && sextet.Jet().m() < mass / 2)
                    continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    Info(sextets.size());
    if (tag == Tag::signal)
        sextets = BestMass(sextets, mass);
    return SaveEntries(sextets);
}

std::vector<Sextet>  HeavyHiggsLeptonicTagger::Multiplets(Event const& event, TMVA::Reader const& reader) const
{
    Info();
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
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

}

}
