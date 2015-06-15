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
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");

    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaR, "DeltaR");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaPhi, "DeltaPhi");

    AddVariable(branch().LargerWDeltaR, "LargerWDeltaR");
    AddVariable(branch().LargerWDeltaRap, "LargerWDeltaRap");
    AddVariable(branch().LargerWDeltaPhi, "LargerWDeltaPhi");

    AddVariable(branch().SmallerWDeltaR, "SmallerWDeltaR");
    AddVariable(branch().SmallerWDeltaRap, "SmallerWDeltaRap");
    AddVariable(branch().SmallerWDeltaPhi, "SmallerWDeltaPhi");

    AddVariable(branch().LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
    AddVariable(branch().LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
    AddVariable(branch().LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");

    AddVariable(branch().SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
    AddVariable(branch().SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
    AddVariable(branch().SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
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
              sextet.SetBdt(Bdt(sextet,reader));
                sextets.emplace_back(sextet);
            }
        }
    }
    return ReduceResult(sextets);
}
