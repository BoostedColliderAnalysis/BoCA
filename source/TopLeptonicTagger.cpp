# include "TopLeptonicTagger.hh"

namespace analysis {

TopLeptonicTagger::TopLeptonicTagger()
{
    //     debug_level_ = Severity::Debug;
    Print(Severity::Notification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_mass_window = std::abs(Mass(Id::Top) - Mass(Id::Higgs));
    DefineVariables();
}

int TopLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::Information, "Train");
    std::size_t number_of_tops = 2;
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(Severity::Information, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    Print(Severity::Information, "Lepton Number", leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons)
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
//             if (tag == Tag::Signal && std::abs(doublet.Jet().m() - Mass(Id::Top)) > top_mass_window) continue;
            if (tag == Tag::Signal && doublet.Jet().m() < 20) continue;
            doublets.emplace_back(doublet);
        }
    Print(Severity::Information, "Number JetPairs", doublets.size());

    Jets particles = event.Partons().GenParticles();
    Jets tops = copy_if_abs_particle(particles, Id::Top);
    switch (tag) {
    case Tag::Signal :
        doublets = BestMatch(doublets, tops);
        break;
    case Tag::Background  :
        doublets = RemoveBestMatch(doublets, tops);
        break;
    }
    return SaveEntries(doublets);
}

std::vector<Doublet> TopLeptonicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();
    Print(Severity::Information, "Bdt");
    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
            doublet.SetBdt(Bdt(doublet,reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

}
