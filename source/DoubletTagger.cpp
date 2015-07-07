#include "DoubletTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

DoubletTagger::DoubletTagger()
{
    Note();
    DefineVariables();
}

int DoubletTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info(Name(tag));
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (Problematic(doublet, pre_cuts, tag)) continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts, tag)) continue;
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    for (const auto & jet : jets) {
        Doublet doublet(jet);
        if (Problematic(doublet, pre_cuts, tag)) continue;
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    Jets particles = event.Partons().GenParticles();
    Jets higgses = copy_if_abs_particle(particles, Id::higgs, Id::CP_violating_higgs);
    return SaveEntries(BestMatches(doublets, higgses, tag));
}

bool DoubletTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - (Mass(Id::higgs) + Mass(Id::W))/2) > higgs_mass_window) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool DoubletTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::higgs) > 0 && pre_cuts.PtLowerCut(Id::higgs) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(Id::higgs) > 0 && pre_cuts.PtUpperCut(Id::higgs) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(Id::higgs) > 0 && pre_cuts.MassUpperCut(Id::higgs) < doublet.Jet().m()) return true;
    return false;
}

std::vector<Doublet>  DoubletTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info();
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (Problematic(doublet, pre_cuts)) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts)) continue;
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    for (const auto & jet : jets) {
        Doublet doublet(jet);
        if (Problematic(doublet, pre_cuts)) continue;
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    return ReduceResult(doublets);
}

}
