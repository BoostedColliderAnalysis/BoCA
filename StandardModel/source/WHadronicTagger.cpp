/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/range/algorithm/adjacent_find.hpp>

#include "WHadronicTagger.hh"
#include "ParticleInfo.hh"
#include "MomentumRange.hh"
#include "Event.hh"
#include "Math.hh"
#include "Exception.hh"
// #define NOTIFICATION
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

WHadronicTagger::WHadronicTagger()
{
    Info0;
    w_mass_window_ = 40. * GeV;
}

int WHadronicTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    std::vector<Doublet> doublets = Doublets(event, pre_cuts, [&](Doublet & doublet) {
        return CheckDoublet(doublet, pre_cuts, tag);
    });
    std::vector<Particle> w_particles = Particles(event);
    return SaveEntries(BestMatches(doublets, w_particles, tag, Id::W));
}

std::vector<Doublet> WHadronicTagger::Doublets(Event const& event, PreCuts const& pre_cuts, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    Info0;
    std::vector<Jet> jets = bottom_reader_.Jets(event);
    MomentumRange jet_range(Id::W, Id::W);
    std::vector<Doublet> doublets = Doublets(jet_range.SofterThanMax(jets), function);
    for (auto const & jet : jet_range.HarderThanMin(jets)) {
        MomentumRange w_jet_range(Id::W, SubJet(Id::W));
        if (w_jet_range.InsideBounds(jet)) {
            std::vector<Jet> pieces = bottom_reader_.SubMultiplet(jet, 2);
            if (pieces.size() == 2) {
                Doublet doublet(pieces.at(0), pieces.at(1));
                if (boost::optional<Doublet> optional = function(doublet)) doublets.emplace_back(*optional);
            }
        }
        MomentumRange top_jet_range(Id::top, SubJet(Id::W));
        if (pre_cuts.DoSubJets(Id::W) && top_jet_range.InsideBounds(jet)) {
            std::vector<Jet> pieces = bottom_reader_.SubMultiplet(jet, 3);
            doublets = Join(doublets, Doublets(pieces, function));
        }
        MomentumRange boosted_range(SubJet(Id::W), SubJet(Id::top));
        if (pre_cuts.DoSubJets(Id::W) && boosted_range.InsideBounds(jet)) {
            std::vector<Jet> pieces = bottom_reader_.SubMultiplet(jet, 2);
            for (auto const & piece : pieces) {
                Doublet doublet(piece);
                if (boost::optional<Doublet> optional = function(doublet)) doublets.emplace_back(*optional);
            }
        }
        if (boosted_range.AboveLowerBound(jet)) {
            Doublet doublet(jet);
            if (boost::optional<Doublet> optional = function(doublet)) doublets.emplace_back(*optional);
        }
    }
    return doublets;
}

std::vector<Particle> WHadronicTagger::Particles(Event const& event) const
{
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> quarks = CopyIfMother(CopyIfQuark(particles), Id::W);
    if (quarks.empty()) return {};
    std::vector<int> ids;
    for (auto const & quark : quarks) ids.emplace_back(quark.Info().Family().Mother().Id());
    if (boost::range::adjacent_find(ids, std::not_equal_to<int>()) == ids.end()) return CopyIfExactParticle(particles, ids.front());
    else return CopyIfParticle(particles, Id::W);
}

boost::optional<Doublet> WHadronicTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

std::vector<Doublet> WHadronicTagger::Doublets(std::vector<Jet> const& jets, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    return unordered_pairs(jets, [&](Jet const & jet_1, Jet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (boost::optional<Doublet> optional = function(doublet)) return *optional;
        throw boca::Problematic();
    });
}

bool WHadronicTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
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

bool WHadronicTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.ApplyCuts(Id::W, doublet)) return true;
//     if (double(doublet.DeltaR()) * rad < DetectorGeometry::MinCellResolution() && doublet.DeltaR() > 0) return true;
    return false;
}

std::vector<Doublet> WHadronicTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Doublet> doublets = Doublets(event, pre_cuts, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
    return ReduceResult(doublets);
}

boost::optional<Doublet> WHadronicTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

std::vector<Doublet> WHadronicTagger::Multiplets(std::vector<Jet> const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    return Doublets(jets, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> WHadronicTagger::Multiplet(Jet const& jet, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    Doublet doublet(jet);
    return Multiplet(doublet, pre_cuts, reader);
}

boost::optional<Doublet> WHadronicTagger::SubMultiplet(Jet const& jet, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    return SubDoublet(jet, [&](Doublet & doublet) {
        return Multiplet(doublet, pre_cuts, reader);
    });
}

boost::optional<Doublet> WHadronicTagger::SubDoublet(Jet const& jet, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    Info0;
    std::vector<Jet> pieces = bottom_reader_.SubMultiplet(jet, 2);
    if (pieces.empty()) return boost::none;
    Doublet doublet;
    if (pieces.size() == 1) doublet.SetJet(pieces.front());
    else doublet.SetMultiplets(pieces.at(0), pieces.at(1));
    return function(doublet);
}

boost::optional<Doublet> WHadronicTagger::Multiplet(Jet const& jet_1, Jet const& jet_2, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    Doublet doublet(jet_1, jet_2);
    return Multiplet(doublet, pre_cuts, reader);
}

std::string WHadronicTagger::Name() const
{
    return "WHadronic";
}

std::string WHadronicTagger::NiceName() const
{
    return "W_{h}";
}

}

}



