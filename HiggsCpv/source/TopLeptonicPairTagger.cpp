# include "TopLeptonicPairTagger.hh"
# include "Quartet22.hh"
# include "WimpMass.hh"
# include "Predicate.hh"

namespace higgscpv
{

TopLeptonicPairTagger::TopLeptonicPairTagger()
{
//     debug_level_ = kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopLeptonicPair");
    top_leptonic_reader_.set_tagger(top_leptonic_tagger_);
    DefineVariables();
}

void TopLeptonicPairTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.Bdt1, "Bdt1");
    AddVariable(branch_.Bdt2, "Bdt2");
    AddSpectator(branch_.Tag, "Tag");
}

int TopLeptonicPairTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Top Leptonic Pair Tagger Tags");
    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);
    Print(kDebug, "Number of Doublets", doublets.size());

    analysis::Jets particles = event.Partons().GenParticles();
    analysis::Jets top_particles = analysis::copy_if_abs_particle(particles, TopId);
    analysis::Jets neutrinos = analysis::copy_if_neutrino(particles);
    if (top_particles.size() != 2 && tag == kSignal) Print(kError, "Number of Tops?", particles.size());

    std::vector<analysis::Doublet> final_doublets;
    switch (tag) {
    case kSignal :
        for (const auto & doublet : doublets) for (const auto top : top_particles) if (doublet.Coincides(top)) final_doublets.emplace_back(doublet);
        break;
    case kBackground :
        final_doublets = doublets;
    }
    Print(kDebug, "Number of Doublets", final_doublets.size());

    std::vector<analysis::Sextet> sextets;
    for (auto doublet1 = doublets.begin(); doublet1 != doublets.end(); ++doublet1)
        for (auto doublet2 = doublet1 + 1; doublet2 != doublets.end(); ++doublet2) {
            analysis::Quartet22 quartet(*doublet1, *doublet2);
            if (quartet.Overlap()) continue;
            analysis::WimpMass wimp_mass;
//             sextets = analysis::Join(sextets, wimp_mass.Sextet(quartet, event.Hadrons().MissingEt(), neutrinos, tag));
            sextets.emplace_back(wimp_mass.Fake(quartet));
        }
    Print(kDebug, "Number of Sextets", sextets.size());
    if (tag == kSignal) sextets = BestRapidity(sextets);
    return SaveEntries(sextets);
}

std::vector< analysis::Sextet > TopLeptonicPairTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);
    Print(kInformation, "Doublets", doublets.size());
    std::vector<analysis::Sextet>  sextets;
    for (auto doublet1 = doublets.begin(); doublet1 != doublets.end(); ++doublet1)
        for (auto doublet2 = doublet1 + 1; doublet2 != doublets.end(); ++doublet2) {
            analysis::Quartet22 quartet(*doublet1, *doublet2);
            if (quartet.Overlap()) continue;
            Print(kInformation, "Quartet");
            analysis::WimpMass wimp_mass;
//             for (auto sextet : wimp_mass.Sextets(quartet, event.Hadrons().MissingEt())) {
                analysis::Sextet sextet = wimp_mass.Fake(quartet);
                Print(kInformation, "Sextet");
                branch_ = branch(sextet);
                sextet.SetBdt(Bdt(reader));
                sextets.emplace_back(sextet);
//             }
        }
    Print(kInformation, "Sextets", sextets.size());
    return ReduceResult(sextets);
}

}
