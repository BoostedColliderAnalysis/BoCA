/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/algorithm/adjacent_find.hpp>

#include "boca/generic/Exception.hh"
#include "boca/math/Math.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/standardmodel/tagger/WHadronic.hh"
#include "boca/Event.hh"
#include "boca/MomentumRange.hh"
// #define NOTIFICATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace standardmodel
{

  namespace tagger {

WHadronic::WHadronic()
{
    INFO0;
    w_mass_window_ = 40_GeV;
}

int WHadronic::Train(Event const& event, PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Doublets(event, pre_cuts, [&](Doublet & doublet) {
        return CheckDoublet(doublet, pre_cuts, tag);
    }), Particles(event), tag, Id::W);
}

std::vector<Doublet> WHadronic::Doublets(Event const& event, PreCuts const& pre_cuts, Function const& function)
{
    INFO0;
    auto jets = event.Jets();
    MomentumRange two_jet_range(Id::W);
    std::vector<Jet> soft;
    for (auto & jet : two_jet_range.SofterThanMax(jets)) soft.emplace_back(bottom_reader_.Multiplet(jet));
    auto doublets = Doublets(soft, function);

    MomentumRange w_jet_range(Id::W, SubJet(Id::W));
    for (auto const & jet : w_jet_range.HarderThanMin(jets)) {

        MomentumRange top_jet_range(Id::top, SubJet(Id::W));
        if (pre_cuts.DoSubJets(Id::W) && top_jet_range.InsideRange(jet)) Insert(doublets, Doublets(bottom_reader_.SubMultiplet(jet, 3), function));

        MomentumRange boosted_range((SubJet(Id::W)), (SubJet(Id::top)));
        if (pre_cuts.DoSubJets(Id::W) && boosted_range.InsideRange(jet)) {
            auto pieces = bottom_reader_.SubMultiplet(jet, 2);
            for (auto const& piece : pieces) {
                Doublet doublet;
                doublet.Enforce(piece);
                if (auto optional = function(doublet)) doublets.emplace_back(*optional);
            }
        }

        Doublet doublet;
        doublet.Enforce(bottom_reader_.SubMultiplet(jet, 2));
        if (auto optional = function(doublet)) doublets.emplace_back(*optional);

    }
    return doublets;
}

std::vector<Particle> WHadronic::Particles(Event const& event) const
{
    auto particles = event.GenParticles();
    auto quarks = CopyIfMother(CopyIfQuark(particles), Id::W);
    if (quarks.empty()) return {};
    auto ids = Transform(quarks, [](Particle const & quark) {
        return quark.Info().Family().Member(Relative::mother).Id();
    });
    return boost::range::adjacent_find(ids, std::not_equal_to<int>()) == ids.end() ? CopyIfExactParticle(particles, ids.front()) : CopyIfParticle(particles, Id::W);
}

boost::optional<Doublet> WHadronic::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

std::vector<Doublet> WHadronic::Doublets(std::vector<Jet> const& jets, Function const& function) const
{
    return UnorderedPairs(jets, [&](Jet const & jet_1, Jet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (auto optional = function(doublet)) return *optional;
        throw boca::Problematic();
    });
}

bool WHadronic::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.OutSideMassWindow(doublet, w_mass_window_, Id::W)) return true;
        if (pre_cuts.NotParticleRho(doublet)) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool WHadronic::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.ApplyCuts(Id::W, doublet)) return true;
//     if (doublet.DeltaR() < Settings::MinCellResolution() && doublet.DeltaR() > 0) return true;
    return false;
}

std::vector<Doublet> WHadronic::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Doublets(event, pre_cuts, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> WHadronic::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::vector<Doublet> WHadronic::Multiplets(std::vector<Jet> const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Doublets(jets, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> WHadronic::Multiplet(Jet const& jet, TMVA::Reader const& reader) {
    PreCuts pre_cuts;
    Doublet doublet;
    doublet.Enforce(jet);
    return Multiplet(doublet, pre_cuts, reader);
}

boost::optional<Doublet> WHadronic::SubMultiplet(Jet const& jet, TMVA::Reader const& reader)
{
    PreCuts pre_cuts;
    return SubDoublet(jet, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> WHadronic::SubDoublet(Jet const& jet, Function const& function)
{
    INFO0;
    auto pieces = bottom_reader_.SubMultiplet(jet, 2);
    if (pieces.empty()) return boost::none;
    Doublet doublet;
    if (pieces.size() == 1) doublet.Enforce(pieces.front());
    else doublet = Doublet(pieces.at(0), pieces.at(1));
    return function(doublet);
}

boost::optional<Doublet> WHadronic::Multiplet(Jet const& jet_1, Jet const& jet_2, TMVA::Reader const& reader)
{
    PreCuts pre_cuts;
    Doublet doublet(jet_1, jet_2);
    return Multiplet(doublet, pre_cuts, reader);
}

std::string WHadronic::Name() const
{
    return "WHadronic";
}

latex::String WHadronic::LatexName() const
{
    return {"W_{h}^{#pm}", true};
}

}

}

}


