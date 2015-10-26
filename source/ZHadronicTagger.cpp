/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "ZHadronicTagger.hh"
#include "Event.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

ZHadronicTagger::ZHadronicTagger()
{
    Info();
    z_mass_window = 50. * GeV;
}

int ZHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return CheckDoublet(doublet, pre_cuts, tag);
    }), Particles(event), tag, Id::Z);
}

std::vector<Doublet> ZHadronicTagger::Doublets(Event const& event, std::function<Doublet(Doublet&)> function) const {
    Info();
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Doublet> doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        return function(doublet);
    });

    for (auto const & jet : jets) {
        try {
            Doublet doublet(jet);
            doublets.emplace_back(function(doublet));
        } catch (std::exception const&) {}
        try {
            Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
            Doublet doublet(pieces.at(0), pieces.at(1));
            doublets.emplace_back(function(doublet));
        } catch (std::exception const&) {}
    }
    return doublets;
}

Doublet ZHadronicTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    if (Problematic(doublet, pre_cuts, tag)) throw boca::Problematic();
    doublet.SetTag(tag);
    return doublet;
}

Jets ZHadronicTagger::Particles(Event const& event) const
{
    Info();
    return CopyIfParticle(event.Partons().GenParticles(), Id::Z);
}

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    if (Problematic(doublet, pre_cuts))return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.NotParticleRho(doublet)) return true;
        if (boost::units::abs(doublet.Mass() - MassOf(Id::Z)) > z_mass_window) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const
{
    Info();
    if (pre_cuts.ApplyCuts(Id::Z, doublet)) return true;
    return false;
}

std::vector<Doublet> ZHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    }));
}

Doublet ZHadronicTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    if (Problematic(doublet, pre_cuts)) throw boca::Problematic();
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::string ZHadronicTagger::Name() const
{
    Info();
    return "ZHadronic";
}

std::string ZHadronicTagger::NiceName() const
{
    Info();
    return "Z";
}

}

