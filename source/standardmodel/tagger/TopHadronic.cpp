/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/algorithm/adjacent_find.hpp>

#include "boca/generic/Exception.hh"
#include "boca/plotting/Font.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/standardmodel/tagger/TopHadronic.hh"

#include "boca/Event.hh"
#include "boca/MomentumRange.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace standardmodel
{

namespace tagger
{

namespace
{

// void TruthLevel(Event const& event, PreCuts const& pre_cuts, Id id)
// {
//     INFO0;
//     auto particle = event.GenParticles();
//     auto tops = CopyIfParticle(particle, id);
//     for (auto const & top : tops) {
//         if (pre_cuts.ApplyCuts(id, top)) continue;
// //         if (top.Pt() < pre_cuts.PtLowerCut().Get(id) || top.Pt() > pre_cuts.PtUpperCut().Get(id)) continue;
//         auto bottoms = CopyIfMother(CopyIfParticle(particle, Id::bottom), top);
//         if (bottoms.empty()) continue;
//         auto Ws = CopyIfMother(CopyIfParticle(particle, Id::W), top);
//         if (Ws.empty()) continue;
//         auto quarks = SortedByPt(CopyIfGrandMother(CopyIfQuark(particle), top));
//         if (quarks.size() < 2) continue;
//         DEBUG(top.Pt(), bottoms.front().Pt(), Ws.front().Pt(), quarks.at(0).Pt(), quarks.at(1).Pt());
//         auto delta_r_top = Ws.front().DeltaRTo(bottoms.front());
//         auto delat_r_w = quarks.at(0).DeltaRTo(quarks.at(1));
//         DEBUG(delta_r_top, delat_r_w);
//     }
// }

std::vector< Triplet > ordered_doublets(std::vector<Jet> const& jets, std::function< boost::optional<Triplet>(Jet const& piece_1, Jet const& piece_2)> const& function)
{
    INFO0;
    auto triplets = std::vector<Triplet>{};
    auto sub_jet_number = static_cast<unsigned>(2);
    if (jets.size() < sub_jet_number) return triplets;
    for (std::size_t i = 0; i < jets.size(); ++i) if (auto optional = function(jets.at(i), jets.at((i + 1) % sub_jet_number))) triplets.emplace_back(*optional);
    return triplets;
}

std::vector< Triplet > ordered_triplets(std::vector<Jet> const& jets, std::function< boost::optional<Triplet>(Jet const& piece_1, Jet const& piece_2, Jet const& piece_3)> const& function)
{
    INFO0;
    auto triplets = std::vector<Triplet>{};
    auto sub_jet_number = static_cast<unsigned>(3);
    if (jets.size() < sub_jet_number) return triplets;
    for (std::size_t i = 0; i < jets.size(); ++i) if (auto optional = function(jets.at(i), jets.at((i + 1) % sub_jet_number), jets.at((i + 2) % sub_jet_number))) triplets.emplace_back(*optional);
    return triplets;
}

}

TopHadronic::TopHadronic(Id id)
{
    INFO0;
    id_ = id;
    if (id_ == Id::top) top_mass_window_ = 2. * MassOf(id_);
}

int TopHadronic::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    auto number = SaveEntries(Triplets(event, [&](Triplet & triplet, std::vector<Jet>const & leptons) {
        return Tripple(triplet, leptons, pre_cuts, tag);
    }), pre_cuts.ApplyCuts(id_, Particles(event)), tag, id_);
    INFO(number);
//     if (number == 0) TruthLevel(event, pre_cuts);
    return number;
}

std::vector<Particle> TopHadronic::Particles(Event const& event) const
{
    INFO0;
    auto particles = event.GenParticles();
    DEBUG(particles.size());
    auto quarks = CopyIfGrandMother(CopyIfQuark(particles), id_);
    DEBUG(quarks.size());
    auto tops = CopyIfGrandDaughter(particles, quarks);
    DEBUG(tops.size());
    return tops;
}

std::vector<Triplet> TopHadronic::Triplets(Event const& event, Function const& function)
{
    INFO0;
    auto jets = SortedByPt(bottom_reader_.Jets(event));
    auto leptons = event.Leptons();

    auto three_jet_range = MomentumRange{Id::W};
    auto triplets = ThreeJets(three_jet_range.SofterThanMax(jets), leptons, function, three_jet_range);

    auto two_jet_range = MomentumRange{Id::W, id_};
    for (auto const & jet : two_jet_range.InsidePtWindow(jets)) Insert(triplets, TwoJets(two_jet_range.SofterThanMax(jets), jet, leptons, function, two_jet_range));

    auto three_sub_jet_range = MomentumRange{id_, SubJet{Id::W}};
    for (auto const & jet : three_sub_jet_range.HarderThanMin(jets)) {
        if (three_sub_jet_range.InsideRange(jet)) Insert(triplets, ThreeSubJets(jet, leptons, function, three_sub_jet_range));
        auto two_sub_jet_range = MomentumRange{SubJet{Id::W}, SubJet{id_}};
        if (two_sub_jet_range.InsideRange(jet)) Insert(triplets, TwoSubJets(jet, leptons, function, two_sub_jet_range));
        auto one_sub_jet_range = MomentumRange{SubJet{id_}};
        if (one_sub_jet_range.InsideRange(jet)) if (auto optional = HighlyBoosted(jet, leptons, function)) triplets.emplace_back(*optional);
    }
    INFO(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronic::ThreeJets(std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range)
{
    INFO(jets.size());
    return Triplets(w_hadronic_reader_.Multiplets(jets), ReduceResult(jets), leptons, function, range);
}

std::vector<Triplet> TopHadronic::TwoJets(std::vector<Jet> const& jets, Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range)
{
    INFO0;
    if (auto optional = w_hadronic_reader_.SubMultiplet(jet)) return Triplets(*optional, jets, leptons, function, range);
    return {};
}

std::vector<Triplet> TopHadronic::ThreeSubJets(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range)
{
    INFO0;
    auto pieces = bottom_reader_.SubMultiplet(jet, 3);
    return ordered_triplets(pieces, [&](Jet const & piece_1, Jet const & piece_2, Jet const & piece_3) -> boost::optional<Triplet> {
        if (auto optional = w_hadronic_reader_.Multiplet(piece_2, piece_3)) return Tripple(*optional, piece_1, leptons, function, range);
        return boost::none;
    });
}

std::vector<Triplet> TopHadronic::TwoSubJets(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range)
{
    INFO0;
    auto pieces = bottom_reader_.SubMultiplet(jet, 2);
    return ordered_doublets(pieces, [&](Jet const & piece_1, Jet const & piece_2) -> boost::optional<Triplet> {
        if (auto optional = w_hadronic_reader_.Multiplet(piece_2)) return Tripple(*optional, piece_1, leptons, function, range);
        return boost::none;
    });
}

boost::optional<Triplet> TopHadronic::HighlyBoosted(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function) const
{
    INFO0;
    auto triplet = Triplet{};
    triplet.Enforce(jet);
    triplet.Doublet().SetBdt(0);
    return function(triplet, leptons);
}

std::vector<Triplet> TopHadronic::Triplets(std::vector<boca::Doublet> const& doublets, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    INFO(doublets.size());
    auto triplets = std::vector<Triplet>{};
    for (auto const & doublet : doublets) Insert(triplets, Triplets(doublet, jets, leptons, function, range));
    INFO(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronic::Triplets(boca::Doublet const& doublet, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    INFO0;
    auto triplets = std::vector<Triplet>{};
    for (auto const & jet : jets) if (auto optional = Tripple(doublet, jet, leptons, function, range, true)) triplets.emplace_back(*optional);
    INFO(triplets.size());
    return triplets;
}

boost::optional<Triplet> TopHadronic::Tripple(boca::Doublet const& doublet, Jet const& jet, std::vector<Lepton> const& leptons , Function const& function, MomentumRange const& range, bool check_overlap) const
{
    INFO0;
    auto triplet = Triplet{doublet, jet};
    DEBUG(triplet.Pt(), range.Min(), range.Max());
    if (!range.InsideRange(triplet)) return boost::none;
    if (check_overlap && triplet.Overlap()) return boost::none;
    return function(triplet, leptons);
}

boost::optional<Triplet> TopHadronic::Tripple(Triplet& triplet, std::vector<Lepton> const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(triplet, pre_cuts, tag)) return boost::none;
    triplet.SetClosestLepton(leptons);
    triplet.SetTag(tag);
    return triplet;
}

bool TopHadronic::Problematic(Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    DEBUG0;
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal : if (id_ == Id::top && pre_cuts.OutSideMassWindow(triplet, top_mass_window_ , id_)) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopHadronic::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    DEBUG0;
    if (pre_cuts.ApplyCuts(id_, triplet)) return true;
    return false;
}

std::vector<Triplet> TopHadronic::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    auto triplets = Triplets(event, [&](Triplet & triplet, std::vector<Jet>const & leptons) {
        return Multiplet(triplet, leptons, pre_cuts, reader);
    });
//     ERROR(triplets.size());
//     triplets = SortedByBdt(triplets);
//     if (!triplets.empty()) if (triplets.front().Bdt() < 0) TruthLevel(event, pre_cuts, id_);

//     static int event_number = 0;
//     static int triplet_number = 0;
//
//     ++event_number;
//     triplet_number += triplets.size();
//     DEBUG(event_number, triplet_number);

    return triplets;
}

boost::optional<Triplet> TopHadronic::Multiplet(Triplet& triplet, std::vector<Lepton> const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    if (Problematic(triplet, pre_cuts)) return boost::none;
    triplet.SetClosestLepton(leptons);
    triplet.SetBdt(Bdt(triplet, reader));
    return triplet;
}

std::string TopHadronic::Name() const
{
    return "TopHadronic";
}

latex::String TopHadronic::LatexName() const
{
    return "t_{h}";
}

}

}

}

