/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "ZHadronicTagger.hh"
#include "MomentumRange.hh"
#include "Event.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

ZHadronicTagger::ZHadronicTagger()
{
    Info0;
    z_mass_window = 50. * GeV;
}

int ZHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return SetTag(doublet, pre_cuts, tag);
    }), Particles(event), tag, Id::Z);
}

std::vector<Doublet> ZHadronicTagger::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> function) const
{
    Info0;
    Jets jets = bottom_reader_.Jets(event);
    MomentumRange jet_range(Id::Z, Id::Z);
    std::vector<Doublet> doublets = unordered_pairs(jet_range.SofterThanMax(jets), [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (boost::optional<Doublet> optional_doublet = function(doublet)) return *optional_doublet;
        throw boca::Problematic();
    });

    for (auto const & jet : jet_range.HarderThanMin(jets)) {
        MomentumRange sub_jet_range((SubJet(Id::Z)), (SubJet(Id::Z)));
        if (sub_jet_range.BelowUpperBound(jet)) try {
                Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
                Doublet doublet(pieces.at(0), pieces.at(1));
                if (boost::optional<Doublet> optional_doublet = function(doublet)) doublets.emplace_back(*optional_doublet);
            } catch (std::exception&) {}
        if (sub_jet_range.AboveLowerBound(jet)) {
            Doublet doublet(jet);
            if (boost::optional<Doublet> optional_doublet = function(doublet)) doublets.emplace_back(*optional_doublet);
        }
    }
    return doublets;
}

boost::optional<Doublet> ZHadronicTagger::SetTag(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

Jets ZHadronicTagger::Particles(Event const& event) const
{
    Info0;
    return CopyIfParticle(event.Partons().GenParticles(), Id::Z);
}

bool ZHadronicTagger::Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
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
    Info0;
    if (pre_cuts.ApplyCuts(Id::Z, doublet)) return true;
    return false;
}

std::vector<Doublet> ZHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    }));
}

boost::optional<Doublet> ZHadronicTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::string ZHadronicTagger::Name() const
{
    Info0;
    return "ZHadronic";
}

std::string ZHadronicTagger::NiceName() const
{
    Info0;
    return "Z";
}

}

}
