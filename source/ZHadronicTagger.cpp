#include "ZHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

ZHadronicTagger::ZHadronicTagger()
{
  Info();
    DefineVariables();
}

int ZHadronicTagger::Train(const Event& event, const analysis::PreCuts& pre_cuts, Tag tag) const
{
    Info("ZHadronic Tag");
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (Problematic(doublet, pre_cuts, tag))
                continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    for (const auto& jet : jets) {
        size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number)
            continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts, tag))
            continue;
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    Jets particles = event.Partons().GenParticles();
    Jets z_particles = CopyIfParticle(particles, Id::Z);
    return SaveEntries(BestMatches(doublets, z_particles, tag));
}

bool ZHadronicTagger::Problematic(const analysis::Doublet& doublet, const analysis::PreCuts& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts))
        return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - Mass(Id::Z)) > z_mass_window)
            return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5))
            return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool ZHadronicTagger::Problematic(const analysis::Doublet& doublet, const analysis::PreCuts& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::Z) > 0 && pre_cuts.PtLowerCut(Id::Z) > doublet.Jet().pt())
        return true;
    if (pre_cuts.PtUpperCut(Id::Z) > 0 && pre_cuts.PtUpperCut(Id::Z) < doublet.Jet().pt())
        return true;
    if (pre_cuts.MassUpperCut(Id::Z) > 0 && pre_cuts.MassUpperCut(Id::Z) < doublet.Jet().m())
        return true;
    return false;
}


std::vector<Doublet>  ZHadronicTagger::Multiplets(const Event& event, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info("ZHadronic Bdt");
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (Problematic(doublet, pre_cuts))
                continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    for (const auto& jet : jets) {
        size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number)
            continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts))
            continue;
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    return ReduceResult(doublets);
}

}

