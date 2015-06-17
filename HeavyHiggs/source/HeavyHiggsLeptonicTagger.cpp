# include "HeavyHiggsLeptonicTagger.hh"
# include "WimpMass.hh"
# include "Predicate.hh"

namespace analysis
{

namespace heavyhiggs
{

HeavyHiggsLeptonicTagger::HeavyHiggsLeptonicTagger()
{
    //     DebugLevel = Object::kDebug;

    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsLeptonic");
    top_leptonic_reader_.SetTagger(top_leptonic_tagger_);
    DefineVariables();
}

int HeavyHiggsLeptonicTagger::Train(Event &event, const Object::Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float mass = event.mass();

    std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets<TopLeptonicTagger>(event);

    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    Jets particles = event.Partons().GenParticles();
    Jets neutrinos = copy_if_neutrino(particles);

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            Quartet22 quartet(doublet1, doublet2);
            if (quartet.Overlap())continue;
            std::vector<Sextet> Presextets;
            WimpMass wimp_mass;
            Presextets = wimp_mass.Sextet(quartet, missing_et, neutrinos, tag);
            for (const auto & sextet : Presextets) {
                if (tag == kSignal && sextet.Jet().m() < mass / 2)continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    Print(kInformation, "Numeber of sextets", sextets.size());

    if (tag == kSignal) sextets = BestMass(sextets, mass);
    return SaveEntries(sextets);
}

std::vector<Sextet>  HeavyHiggsLeptonicTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");
    std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets<TopLeptonicTagger>(event);
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
