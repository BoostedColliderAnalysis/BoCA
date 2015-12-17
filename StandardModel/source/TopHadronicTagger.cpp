/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <boost/range/algorithm/adjacent_find.hpp>

#include "plotting/Font.hh"
#include "TopHadronicTagger.hh"
#include "Event.hh"
#include "Exception.hh"
#include "ParticleInfo.hh"
#include "MomentumRange.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

namespace
{

void TruthLevel(Event const& event, PreCuts const& pre_cuts)
{
    Info0;
    std::vector<Particle> particle = event.Partons().GenParticles();
    std::vector<Particle> tops = CopyIfParticle(particle, Id::top);
    for (auto const & top : tops) {
        if (top.Pt() < pre_cuts.PtLowerCut().Get(Id::top) || top.Pt() > pre_cuts.PtUpperCut().Get(Id::top)) continue;
        std::vector<Particle> bottoms = CopyIfMother(CopyIfParticle(particle, Id::bottom), top);
        if (bottoms.empty()) continue;
        std::vector<Particle> Ws = CopyIfMother(CopyIfParticle(particle, Id::W), top);
        if (Ws.empty()) continue;
        std::vector<Particle> quarks = CopyIfGrandMother(CopyIfQuark(particle), top);
        if (quarks.size() < 2) continue;
        quarks = SortedByPt(quarks);
        Debug(top.Pt(), bottoms.front().Pt(), Ws.front().Pt(), quarks.at(0).Pt(), quarks.at(1).Pt());
        Angle delta_r_top = Ws.front().DeltaRTo(bottoms.front());
        Angle delat_r_w = quarks.at(0).DeltaRTo(quarks.at(1));
        Debug(delta_r_top, delat_r_w);
    }
}

}

TopHadronicTagger::TopHadronicTagger()
{
    Info0;
//     top_mass_window_ = 80_GeV;
    top_mass_window_ = 2. * MassOf(Id::top);
}

int TopHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    int number = SaveEntries(Triplets(event, [&](Triplet & triplet, std::vector<Jet>const & leptons) {
        return Tripple(triplet, leptons, pre_cuts, tag);
    }), Particles(event, pre_cuts), tag, Id::top);
    INFO(number);
//     if (number == 0) TruthLevel(event, pre_cuts);
    return number;
}

std::vector<Particle> TopHadronicTagger::Particles(Event const& event, boca::PreCuts const& pre_cuts) const
{
    Info0;
    std::vector<Particle> particles = event.Partons().GenParticles();
    Debug(particles.size());
    std::vector<Particle> quarks = CopyIfQuark(particles);
    Debug(quarks.size());
    quarks = CopyIfGrandMother(quarks, Id::top);
    Debug(quarks.size());
    std::vector<Particle> tops = CopyIfGrandDaughter(particles, quarks);
    Debug(tops.size());
    tops = pre_cuts.ApplyCuts(Id::top, tops);
    Debug(tops.size());
    return tops;
}

std::vector<Triplet> TopHadronicTagger::Triplets(Event const& event, Function const& function) const
{
    Info0;
    std::vector<Jet> jets = SortedByPt(bottom_reader_.Jets(event));
    std::vector<Lepton> leptons = event.Leptons().leptons();

    MomentumRange three_jet_range(Id::W);
    std::vector<Triplet> triplets = ThreeJets(three_jet_range.SofterThanMax(jets), leptons, function, three_jet_range);

    MomentumRange two_jet_range(Id::W, Id::top);
    for (auto const & jet : two_jet_range.InsidePtWindow(jets)) triplets = Join(triplets, TwoJets(two_jet_range.SofterThanMax(jets), jet, leptons, function, two_jet_range));

    MomentumRange three_sub_jet_range(Id::top, SubJet(Id::W));
    for (auto const & jet : three_sub_jet_range.HarderThanMin(jets)) {
        if (three_sub_jet_range.InsideBounds(jet)) triplets = Join(triplets, ThreeSubJets(jet, leptons, function, three_sub_jet_range));
        MomentumRange two_sub_jet_range((SubJet(Id::W)), (SubJet(Id::top)));
        if (two_sub_jet_range.InsideBounds(jet)) triplets = Join(triplets, TwoSubJets(jet, leptons, function, two_sub_jet_range));
        MomentumRange one_sub_jet_range((SubJet(Id::top)));
        if (one_sub_jet_range.InsideBounds(jet)) if (boost::optional<Triplet> optional = HighlyBoosted(jet, leptons, function)) triplets.emplace_back(*optional);
    }
    INFO(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::ThreeJets(std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    INFO(jets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(jets);
//     doublets = range.SofterThanMax(doublets);
    return Triplets(doublets, jets, leptons, function, range);
}

std::vector<Triplet> TopHadronicTagger::TwoJets(std::vector<Jet> const& jets, Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    if (boost::optional<Doublet> optional = w_hadronic_reader_.SubMultiplet(jet)) {
        Doublet doublet = *optional;
        Debug(doublet.Pt(), doublet.Bdt());
//         if (!range.InsideBounds(doublet)) return {};
        return Triplets(doublet, jets, leptons, function, range);
    }
    return {};
}

std::vector<Triplet> TopHadronicTagger::ThreeSubJets(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    unsigned sub_jet_number = 3;
    std::vector<Jet> pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
    return ordered_triplets(pieces, sub_jet_number, [&](Jet const & piece_1, Jet const & piece_2, Jet const & piece_3) -> boost::optional<Triplet> {
        if (boost::optional<Doublet> optional = w_hadronic_reader_.Multiplet(piece_2, piece_3)) {
            Doublet doublet = *optional;
//             if (!range.InsideBounds(doublet)) return boost::none;
            return Tripple(doublet, piece_1, leptons, function, range) ;
        }
        return boost::none;
    });
}

std::vector<Triplet> TopHadronicTagger::TwoSubJets(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    std::vector<Triplet> triplets;
    unsigned sub_jet_number = 2;
    std::vector<Jet> pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
    if (pieces.size() == sub_jet_number) {
        for (size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            if (boost::optional<Doublet> optional_doublet = w_hadronic_reader_.Multiplet(piece_2)) if (boost::optional<Triplet> optional_triplet = Tripple(*optional_doublet, piece_1, leptons, function, range)) triplets.emplace_back(*optional_triplet);
        }
    }
    return triplets;
}

boost::optional<Triplet> TopHadronicTagger::HighlyBoosted(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function) const
{
    Info0;
    Triplet triplet(jet);
    triplet.Doublet().SetBdt(0);
    return function(triplet, leptons);
}

std::vector<Triplet> TopHadronicTagger::Triplets(std::vector<boca::Doublet> const& doublets, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    INFO(doublets.size());
    std::vector<Triplet> triplets;
    for (auto const & doublet : doublets) triplets = Join(triplets, Triplets(doublet, jets, leptons, function, range));
    INFO(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(boca::Doublet const& doublet, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    std::vector<Triplet> triplets;
    for (auto const & jet : jets) if (boost::optional<Triplet> optional = Tripple(doublet, jet, leptons, function, range, true)) triplets.emplace_back(*optional);
    INFO(triplets.size());
    return triplets;
}

boost::optional<Triplet> TopHadronicTagger::Tripple(boca::Doublet const& doublet, Jet const& jet, std::vector<Lepton> const& leptons , Function const& function, MomentumRange const& range, bool check_overlap) const
{
    Info0;
    Triplet triplet(doublet, jet);
    Debug(triplet.Pt(), range.Min(), range.Max());
    if (!range.InsideBounds(triplet)) return boost::none;
    if (check_overlap && triplet.Overlap()) return boost::none;
    return function(triplet, leptons);
}

boost::optional<Triplet> TopHadronicTagger::Tripple(Triplet& triplet, std::vector<Lepton> const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    if (Problematic(triplet, pre_cuts, tag)) return boost::none;
    triplet.set_pt(LeptonPt(triplet, leptons));
    NSubJettiness(triplet);
    triplet.SetTag(tag);
    return triplet;
}

Momentum TopHadronicTagger::LeptonPt(Triplet const& triplet, std::vector<Lepton> const& leptons) const
{
    Momentum pt = at_rest;
    for (auto const & lepton : leptons) if (lepton.Pt() > pt && Close(lepton)(triplet)) pt = lepton.Pt();
    return pt;
}

bool TopHadronicTagger::Problematic(Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Debug0;
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal:
        if (pre_cuts.OutSideMassWindow(triplet, top_mass_window_ , Id::top)) return true;
//         if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > top_mass_window_) return true;
//         if (pre_cuts.NotParticleRho(triplet)) return true;
//         if (std::abs(triplet.Doublet().Mass() - Mass(Id::W)) > 40) return true;
//         if (triplet.Doublet().Bdt() < 1) return true;
//         if (triplet.Singlet().Bdt() < 1) return true;
//         if (triplet.Pt() > DetectorGeometry::LeptonMinPt()) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopHadronicTagger::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    Debug0;
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
    // FIXME the top tagger is very slow, due to many calls of Bdt(), therfore we have to reduce the number of candidates
//     if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > 2. * top_mass_window_) return true;
//     if ((triplet.Rho() < 0.4 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
    return false;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Triplet> triplets = ReduceResult(Triplets(event, [&](Triplet & triplet, std::vector<Jet>const & leptons) {
        return Multiplet(triplet, leptons, pre_cuts, reader);
    }));
//     Error(triplets.size());
    triplets = SortedByBdt(triplets);
    if (!triplets.empty()) if (triplets.front().Bdt() < 0) TruthLevel(event, pre_cuts);

    static int event_number = 0;
    static int triplet_number = 0;

    ++event_number;
    triplet_number += triplets.size();
    Debug(event_number, triplet_number);

    return triplets;
}

boost::optional<Triplet> TopHadronicTagger::Multiplet(Triplet& triplet, std::vector<Lepton> const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    if (Problematic(triplet, pre_cuts)) return boost::none;
    triplet.set_pt(LeptonPt(triplet, leptons));
    NSubJettiness(triplet);
    triplet.SetBdt(Bdt(triplet, reader));
    return triplet;
}

void TopHadronicTagger::NSubJettiness(Triplet& triplet) const
{
    Info0;
    return;
    triplet.set_sub_jettiness();
}

std::vector< Triplet > TopHadronicTagger::ordered_triplets(std::vector<Jet> const& jets, unsigned int sub_jet_number, std::function< boost::optional<Triplet>(Jet const& piece_1, Jet const& piece_2, Jet const& piece_3)> const& function) const
{
    Info0;
    std::vector<Triplet> triplets;
    if (jets.size() < sub_jet_number) return {};
    for (size_t i = 0; i < jets.size(); ++i) {
        auto piece_1 = jets.at(i);
        auto piece_2 = jets.at((i + 1) % sub_jet_number);
        auto piece_3 = jets.at((i + 2) % sub_jet_number);
        if (boost::optional<Triplet> optional = function(piece_1, piece_2, piece_3)) triplets.emplace_back(*optional);
    }
    return triplets;
}

std::string TopHadronicTagger::Name() const
{
    return "TopHadronic";
}

std::string TopHadronicTagger::LatexName() const
{
    return Formula("t_{h}");
}

}

}


