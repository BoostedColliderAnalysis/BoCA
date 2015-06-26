# include "TopLeptonicTagger.hh"

namespace analysis {

TopLeptonicTagger::TopLeptonicTagger()
{
    //     debug_level_ = Severity::debug;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_mass_window = std::abs(Mass(Id::top) - Mass(Id::higgs));
    DefineVariables();
}

int TopLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Train");
    std::size_t number_of_tops = 2;
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(Severity::information, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    Print(Severity::information, "Lepton Number", leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons)
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
//             if (tag == Tag::signal && std::abs(doublet.Jet().m() - Mass(Id::top)) > top_mass_window) continue;
            if (tag == Tag::signal && doublet.Jet().m() < 20) continue;
            doublets.emplace_back(doublet);
        }
    Print(Severity::information, "Number JetPairs", doublets.size());

    Jets particles = event.Partons().GenParticles();
    Jets tops = copy_if_abs_particle(particles, Id::top);
    switch (tag) {
    case Tag::signal :
        doublets = BestMatch(doublets, tops);
        break;
    case Tag::background  :
        doublets = RemoveBestMatch(doublets, tops);
        break;
    }
    return SaveEntries(doublets);
}

std::vector<Doublet> TopLeptonicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();
    Print(Severity::information, "Bdt");
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
