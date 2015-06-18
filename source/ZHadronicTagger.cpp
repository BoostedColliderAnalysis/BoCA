# include "ZHadronicTagger.hh"

namespace analysis
{

ZHadronicTagger::ZHadronicTagger()
{
    //         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("ZHadronic");
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

int ZHadronicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "ZHadronic Tag");
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
    Jets particles = event.Partons().GenParticles();
    Jets higgses = copy_if_abs_particle(particles, ZId);
    switch (tag) {
    case kSignal :
        doublets = BestMatch(doublets, higgses);
        break;
    case kBackground  :
        doublets = RemoveBestMatch(doublets, higgses);
        break;
    }
    return SaveEntries(doublets);
}

bool ZHadronicTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag)
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case kSignal :
        if (std::abs(doublet.Jet().m() - Mass(ZId)) > z_mass_window) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5)) return true;
        break;
    case kBackground :
        break;
    }
    return false;
}

bool ZHadronicTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts)
{
    if (pre_cuts.PtLowerCut(ZId) > 0 && pre_cuts.PtLowerCut(ZId) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(ZId) > 0 && pre_cuts.PtUpperCut(ZId) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(ZId) > 0 && pre_cuts.MassUpperCut(ZId) < doublet.Jet().m()) return true;
    return false;
}


std::vector<Doublet>  ZHadronicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "ZHadronic Bdt");
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
    return ReduceResult(doublets);
}

}

