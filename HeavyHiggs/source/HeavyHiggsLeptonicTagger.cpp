# include "HeavyHiggsLeptonicTagger.hh"
# include "WimpMass.hh"
# include "Predicate.hh"

heavyhiggs::HeavyHiggsLeptonicTagger::HeavyHiggsLeptonicTagger()
{
    //     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsLeptonic");
    top_leptonic_reader_.set_tagger(top_leptonic_tagger_);
    DefineVariables();
}

void heavyhiggs::HeavyHiggsLeptonicTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");

    AddVariable(branch_.LargerWDeltaR, "LargerWDeltaR");
    AddVariable(branch_.LargerWDeltaRap, "LargerWDeltaRap");
    AddVariable(branch_.LargerWDeltaPhi, "LargerWDeltaPhi");

    AddVariable(branch_.SmallerWDeltaR, "SmallerWDeltaR");
    AddVariable(branch_.SmallerWDeltaRap, "SmallerWDeltaRap");
    AddVariable(branch_.SmallerWDeltaPhi, "SmallerWDeltaPhi");

    AddVariable(branch_.LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
    AddVariable(branch_.LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
    AddVariable(branch_.LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");

    AddVariable(branch_.SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
    AddVariable(branch_.SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
    AddVariable(branch_.SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int heavyhiggs::HeavyHiggsLeptonicTagger::Train(analysis::Event &event, const Object::Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float mass = event.mass();

    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);

    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    analysis::Jets particles = event.Partons().GenParticles();
    analysis::Jets neutrinos = analysis::copy_if_neutrino(particles);

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<analysis::Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            analysis::Quartet22 quartet(doublet1, doublet2);
            if (quartet.Overlap())continue;
            std::vector<analysis::Sextet> Presextets;
            analysis::WimpMass wimp_mass;
            Presextets = wimp_mass.Sextet(quartet, missing_et, neutrinos, tag);
            for (const auto & sextet : Presextets) {
                if (tag == kSignal && sextet.Jet().m() < mass / 2)continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    Print(kInformation, "Numeber of sextets", sextets.size());

    if (tag == kSignal) sextets = BestMass(sextets,mass);
    return SaveEntries(sextets);
}

std::vector<analysis::Sextet>  heavyhiggs::HeavyHiggsLeptonicTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");
    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);
    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();

    std::vector<analysis::Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            analysis::Quartet22 quartet(doublet1, doublet2);
            if(quartet.Overlap()) continue;
            std::vector<analysis::Sextet> pre_sextets;
            analysis::WimpMass wimp_mass;
            pre_sextets = wimp_mass.Sextets(quartet, missing_et);
            for (auto & sextet : pre_sextets) {
                branch_ = branch(sextet);
                sextet.SetBdt(Bdt(reader));
                sextets.emplace_back(sextet);
            }
        }
    }
    return ReduceResult(sextets);
}
