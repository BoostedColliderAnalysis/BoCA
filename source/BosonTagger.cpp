/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "BosonTagger.hh"
#include "Event.hh"
#include "Doublet.hh"
#include "MomentumRange.hh"
#include "Exception.hh"
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
    Info();
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return CheckDoublet(doublet, pre_cuts, tag);
    }), Particles(event), tag);
}

Doublet BosonTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    if (Problematic(doublet, pre_cuts, tag)) throw boca::Problematic();
    doublet.SetTag(tag);
    return doublet;
}

std::vector<Doublet> BosonTagger::Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const
{
    Info();
    Jets jets =  bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (doublet.Pt() > MomentumRange::PtMax(Id::higgs)) throw boca::Problematic();
        return function(doublet);
    });
    for (auto const & jet : RemoveIfSoft(jets, MomentumRange::PtMin(Id::Z))) {
        if (jet.pt() * GeV < MomentumRange::PtMax((SubJet(Id::higgs)))) try {
                Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
                Doublet doublet(pieces.at(0), pieces.at(1));
                doublets.emplace_back(function(doublet));
            } catch (std::exception const&) {}
        if (jet.pt() * GeV > MomentumRange::PtMin((SubJet(Id::Z)))) try {
                Doublet doublet(jet);
                doublets.emplace_back(function(doublet));
            } catch (std::exception const&) {}
    }
    return doublets;
}

Jets BosonTagger::Particles(Event const& event) const
{
    Info();
    Jets particles = event.Partons().GenParticles();
    return CopyIfParticles(particles, MultiId(Id::neutral_boson));
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.NotParticleRho(doublet)) return true;
        if (boost::units::abs(doublet.Mass() - (MassOf(Id::Z) + MassOf(Id::higgs)) / 2.) > boson_mass_window) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    Info();
    if (pre_cuts.ApplyCuts(Id::neutral_boson, doublet)) return true;
    return false;
}

std::vector<Doublet> BosonTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    }));
}

Doublet BosonTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    if (Problematic(doublet, pre_cuts)) throw boca::Problematic();
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

int BosonTagger::SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
}

std::string BosonTagger::Name() const
{
    return "Boson";
}

std::string BosonTagger::NiceName() const
{
    return "B";
}

}

