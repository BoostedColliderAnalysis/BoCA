/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "BosonTagger.hh"
#include "Event.hh"
#include "Doublet.hh"
#include "Exeption.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

BosonTagger::BosonTagger()
{
    Info();
    boson_mass_window = 80. * GeV;
}

int BosonTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    Info(boca::Name(tag));
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        return CheckDoublet(Doublet(jet_1, jet_2), pre_cuts, tag);
    });

    for (auto const & jet : jets) {
        try {
            doublets.emplace_back(CheckDoublet(Doublet(jet), pre_cuts, tag));
        } catch (...) {}
        try {
            Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
            doublets.emplace_back(CheckDoublet(Doublet(pieces.at(0), pieces.at(1)), pre_cuts, tag));
        } catch (...) {}
    }
    Jets bosons = Particles(event);
    return SaveEntries(doublets, bosons, tag);
}

Jets BosonTagger::Particles(Event const& event) const {
  Jets particles = event.Partons().GenParticles();
  Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
//   Jets vectors = CopyIfParticles(particles, Id::W, Id::Z);
  Jets vectors = CopyIfParticle(particles, Id::Z);
  return Join(higgses, vectors);
}

Doublet BosonTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts, tag)) throw boca::Problematic();
    doublet.SetTag(tag);
    return doublet;
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
//         if (boost::units::abs(doublet.Mass() - (MassOf(Id::higgs) + MassOf(Id::W)) / 2.) > boson_mass_window) return true;
//         if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::higgs) > at_rest && pre_cuts.PtLowerCut(Id::higgs) > doublet.Pt()) return true;
    if (pre_cuts.PtUpperCut(Id::higgs) > at_rest && pre_cuts.PtUpperCut(Id::higgs) < doublet.Pt()) return true;
    if (pre_cuts.MassLowerCut(Id::higgs) > massless && doublet.Mass() < pre_cuts.MassLowerCut(Id::higgs)) return true;
    if (pre_cuts.MassUpperCut(Id::higgs) > massless && pre_cuts.MassUpperCut(Id::higgs) < doublet.Mass()) return true;
    if (doublet.Jet().user_info<JetInfo>().VertexNumber() < 1) return true;
    if (doublet.Rho() > 2.5 || doublet.Rho() < 0.5) return true;
    if (doublet.Singlet1().Bdt() < 0 || doublet.Singlet2().Bdt() < 0) return true;
    return false;
}

std::vector<Doublet>  BosonTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        return Multiplet(doublet, pre_cuts, reader);
    });
    for (auto const & jet : jets) {
        try {
            Doublet doublet(jet);
            doublets.emplace_back(Multiplet(doublet, pre_cuts, reader));
        } catch (...) {}
        try {
            Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
            Doublet doublet(pieces.at(0), pieces.at(1));
            doublets.emplace_back(Multiplet(doublet, pre_cuts, reader));
        } catch (...) {}
    }
    return ReduceResult(doublets);
}

Doublet BosonTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
  if (Problematic(doublet, pre_cuts)) throw boca::Problematic();
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

int BosonTagger::SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
}

}
