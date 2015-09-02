/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "ZHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

ZHadronicTagger::ZHadronicTagger()
{
    Info();
    DefineVariables();
}

int ZHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets,[&](fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
      return CheckDoublet(Doublet(jet_1, jet_2), pre_cuts, tag);
    });

    for (auto const& jet : jets) {
        try {
          doublets.emplace_back(CheckDoublet(Doublet(jet), pre_cuts, tag));
        } catch (...) {}
        try {
            Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
            doublets.emplace_back(CheckDoublet(Doublet(pieces.at(0), pieces.at(1)), pre_cuts, tag));
        } catch (...) {}
    }
    Jets particles = event.Partons().GenParticles();
    Jets z_particles = CopyIfParticle(particles, Id::Z);
    return SaveEntries(doublets, z_particles, tag, Id::Z);
}

Doublet ZHadronicTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts, tag)) throw "problematic";
    doublet.SetTag(tag);
    return doublet;
}

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts))return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - Mass(Id::Z)) > z_mass_window) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5)) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::Z) > 0 && pre_cuts.PtLowerCut(Id::Z) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(Id::Z) > 0 && pre_cuts.PtUpperCut(Id::Z) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(Id::Z) > 0 && pre_cuts.MassUpperCut(Id::Z) < doublet.Jet().m()) return true;
    return false;
}

std::vector<Doublet> ZHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets,[&](fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
        Doublet doublet(jet_1, jet_2);
        return Multiplet(doublet,pre_cuts,reader);
    });
    for (auto const& jet : jets) {
        try {
            Doublet doublet(jet);
            doublets.emplace_back(Multiplet(doublet,pre_cuts,reader));
        } catch (...) {}
        try {
            Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
            Doublet doublet(pieces.at(0), pieces.at(1));
            doublets.emplace_back(Multiplet(doublet,pre_cuts,reader));
        } catch (...) {}
    }
    return ReduceResult(doublets);
}

Doublet ZHadronicTagger::Multiplet(Doublet & doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    if (Problematic(doublet, pre_cuts)) throw "problematic";
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

}

