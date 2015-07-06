#include "HeavyHiggsLeptonicTagger.hh"
#include "WimpMass.hh"
#include "Predicate.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

HeavyHiggsLeptonicTagger::HeavyHiggsLeptonicTagger()
{
    Note();
    set_tagger_name("HeavyHiggsLeptonic");
    DefineVariables();
}

int HeavyHiggsLeptonicTagger::Train(const Event &event, const Tag tag)
{
    Info("Higgs Tags");

    float mass = event.mass();

    std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets(event);

    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    Jets particles = event.Partons().GenParticles();
    Jets neutrinos = copy_if_neutrino(particles);

    Info("Number of doublets", doublets.size());

    std::vector<Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            Quartet22 quartet(doublet1, doublet2);
            if (quartet.Overlap())continue;
            std::vector<Sextet> Presextets;
            WimpMass wimp_mass;
            Presextets = wimp_mass.Sextet(quartet, missing_et, neutrinos, tag);
            for (const auto & sextet : Presextets) {
                if (tag == Tag::signal && sextet.Jet().m() < mass / 2)continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    Info("Numeber of sextets", sextets.size());

    if (tag == Tag::signal) sextets = BestMass(sextets, mass);
    return SaveEntries(sextets);
}

std::vector<Sextet>  HeavyHiggsLeptonicTagger::Multiplets(const Event &event, const TMVA::Reader &reader) const
{
    Info("Bdt");
    std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets(event);
    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();

    std::vector<Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            Quartet22 quartet(doublet1, doublet2);
            if (quartet.Overlap()) continue;
            std::vector<Sextet> pre_sextets;
            WimpMass wimp_mass;
            pre_sextets = wimp_mass.Sextets(quartet, missing_et);
            for (auto & sextet : pre_sextets) {
                sextet.SetBdt(Bdt(sextet, reader));
                sextets.emplace_back(sextet);
            }
        }
    }
    return ReduceResult(sextets);
}

}

}
