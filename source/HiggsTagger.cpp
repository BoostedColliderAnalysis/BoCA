# include "HiggsTagger.hh"

namespace analysis
{

HiggsTagger::HiggsTagger()
{
    //         DebugLevel = Severity::detailed;
    Print(Severity::notification, "Constructor");
    set_tagger_name("Higgs");
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

int HiggsTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Higgs Tag");
    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (Problematic(doublet, pre_cuts, tag)) continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    for (const auto jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts, tag)) continue;
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    for (const auto jet : jets) {
      Doublet doublet(jet);
      if (Problematic(doublet, pre_cuts, tag)) continue;
      doublet.SetTag(tag);
      doublets.emplace_back(doublet);
    }
    Jets particles = event.Partons().GenParticles();
    Jets higgses = copy_if_abs_particle(particles, Id::higgs, Id::CP_violating_higgs);
    return SaveEntries(BestMatches(doublets, higgses,tag));
}

bool HiggsTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag)
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - Mass(Id::higgs)) > higgs_mass_window) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5)) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts)
{
    if (pre_cuts.PtLowerCut(Id::higgs) > 0 && pre_cuts.PtLowerCut(Id::higgs) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(Id::higgs) > 0 && pre_cuts.PtUpperCut(Id::higgs) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(Id::higgs) > 0 && pre_cuts.MassUpperCut(Id::higgs) < doublet.Jet().m()) return true;
    return false;
}

std::vector<Doublet>  HiggsTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(Severity::information, "Higgs Bdt");
    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (Problematic(doublet, pre_cuts)) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    for (const auto jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts)) continue;
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    for (const auto jet : jets) {
      Doublet doublet(jet);
      if (Problematic(doublet, pre_cuts)) continue;
      doublet.SetBdt(Bdt(doublet, reader));
      doublets.emplace_back(doublet);
    }
    return ReduceResult(doublets);
}

}
