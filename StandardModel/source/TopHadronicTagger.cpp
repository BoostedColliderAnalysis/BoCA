/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <boost/range/algorithm/adjacent_find.hpp>

#include "TopHadronicTagger.hh"
#include "Event.hh"
#include "InfoRecombiner.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

TopHadronicTagger::TopHadronicTagger()
{
    Info0;
    top_mass_window_ = 50. * GeV;
}

int TopHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    return SaveEntries(Triplets(event, [&](Triplet & triplet, Jets const & leptons) {
        return Tripple(triplet, leptons, pre_cuts, tag);
    }), TopParticles(event), tag, Id::top);
}

Jets TopHadronicTagger::TopParticles(Event const& event) const
{
    Info0;
    Jets particles = event.Partons().GenParticles();
    Jets quarks = CopyIfGrandMother(CopyIfQuark(particles), Id::top);
    if (quarks.empty()) return {};
    std::vector<int> ids;
    for (auto const & quark : quarks) ids.emplace_back(quark.user_info<ParticleInfo>().Family().GrandMother().Id());
    if (boost::range::adjacent_find(ids, std::not_equal_to<int>()) == ids.end()) return CopyIfExactParticle(particles, ids.front());
    else return CopyIfParticle(particles, Id::top);
}

std::vector<Triplet> TopHadronicTagger::Triplets(Event const& event, Function const& function) const
{
    Info0;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Jets(event));
    Jets leptons = event.Leptons().leptons();

    Info(jets.size(), leptons.size());

    MomentumRange three_jet_range(Id::W);
    MomentumRange two_jet_range(Id::W, Id::top);
    Jets softer_than_top = two_jet_range.SofterThanMax(jets);
    std::vector<Triplet> triplets = ThreeJets(softer_than_top, leptons, function, three_jet_range);

    for (auto const & jet : two_jet_range.HarderThanMin(jets)) {
        if (two_jet_range.InsideBounds(jet)) triplets = Join(triplets, TwoJets(jets, jet, leptons, function, two_jet_range));
        MomentumRange three_sub_jet_range(Id::top, SubJet(Id::W));
        if (three_sub_jet_range.InsideBounds(jet)) triplets = Join(triplets, ThreeSubJets(jet, leptons, function, three_sub_jet_range));
        MomentumRange two_sub_jet_range((SubJet(Id::W)), (SubJet(Id::top)));
        if (two_sub_jet_range.InsideBounds(jet)) triplets = Join(triplets, TwoSubJets(jet, leptons, function, two_sub_jet_range));
        MomentumRange one_sub_jet_range((SubJet(Id::top)));
        if (one_sub_jet_range.InsideBounds(jet)) if (boost::optional<Triplet> optional = HighlyBoosted(jet, leptons, function)) triplets.emplace_back(*optional);
    }
    Info(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::ThreeJets(Jets const& jets, Jets const& leptons, Function const& function, MomentumRange const& range) const
{
    Info(jets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(range.SofterThanMax(jets));
    doublets = range.SofterThanMax(doublets);
    return Triplets(doublets, jets, leptons, function, range);
}

std::vector<Triplet> TopHadronicTagger::TwoJets(Jets const& jets, fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    if (boost::optional<Doublet> optional = w_hadronic_reader_.SubMultiplet(jet)) {
        Doublet doublet = *optional;
        Debug(doublet.Pt(), doublet.Bdt());
        if (!range.InsideBounds(doublet)) return {};
        return Triplets(doublet, jets, leptons, function, range);
    }
    return {};
}

std::vector<Triplet> TopHadronicTagger::ThreeSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    unsigned sub_jet_number = 3;
    Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
    return ordered_triplets(pieces, sub_jet_number, [&](fastjet::PseudoJet const & piece_1, fastjet::PseudoJet const & piece_2, fastjet::PseudoJet const & piece_3) -> boost::optional<Triplet> {
        if (boost::optional<Doublet> optional = w_hadronic_reader_.Multiplet(piece_2, piece_3)) {
            Doublet doublet = *optional;
            if (!range.InsideBounds(doublet)) return boost::none;
            return Tripple(doublet, piece_1, leptons, function, range) ;
        }
        return boost::none;
    });
}

std::vector<Triplet> TopHadronicTagger::TwoSubJets(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    std::vector<Triplet> triplets;
    unsigned sub_jet_number = 2;
    Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
    if (pieces.size() == sub_jet_number) {
        for (size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            if (boost::optional<Doublet> optional_doublet = w_hadronic_reader_.Multiplet(piece_2)) if (boost::optional<Triplet> optional_triplet = Tripple(*optional_doublet, piece_1, leptons, function, range)) triplets.emplace_back(*optional_triplet);
        }
    }
    return triplets;
}

boost::optional<Triplet> TopHadronicTagger::HighlyBoosted(fastjet::PseudoJet const& jet, Jets const& leptons, Function const& function) const
{
    Info0;
    Triplet triplet(jet);
    triplet.Doublet().SetBdt(0);
    return function(triplet, leptons);
}

std::vector<Triplet> TopHadronicTagger::Triplets(std::vector<boca::Doublet> const& doublets, boca::Jets const& jets, boca::Jets const& leptons, Function const& function, MomentumRange const& range) const
{
    Info(doublets.size());
    std::vector<Triplet> triplets;
    for (auto const & doublet : doublets) triplets = Join(triplets, Triplets(doublet, jets, leptons, function, range));
    Info(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(boca::Doublet const& doublet, boca::Jets const& jets, boca::Jets const& leptons, Function const& function, MomentumRange const& range) const
{
    Info0;
    std::vector<Triplet> triplets;
    for (auto const & jet : jets) {
        if (boost::optional<Triplet> optional = Tripple(doublet, jet, leptons, function, range, true)) triplets.emplace_back(*optional);
    }
    Info(triplets.size());
    return triplets;
}

boost::optional<Triplet> TopHadronicTagger::Tripple(boca::Doublet const& doublet, fastjet::PseudoJet const& jet, boca::Jets const& leptons , Function const& function, MomentumRange const& range, bool check_overlap) const
{
    Info0;
    Triplet triplet(doublet, jet);
    Debug(triplet.Pt(), range.Min(), range.Max());
    if (!range.InsideBounds(triplet)) return boost::none;
    if (check_overlap && triplet.Overlap()) return boost::none;
    return function(triplet, leptons);
}

boost::optional<Triplet> TopHadronicTagger::Tripple(Triplet& triplet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    if (Problematic(triplet, pre_cuts, tag)) return boost::none;
    triplet.set_pt(LeptonPt(triplet, leptons));
    NSubJettiness(triplet);
    triplet.SetTag(tag);
    return triplet;
}

float TopHadronicTagger::LeptonPt(Triplet const& triplet, boca::Jets const& leptons) const
{
    float pt = 0;
    for (auto const & lepton : leptons) if (lepton.pt() > pt && Close(lepton)(triplet)) pt = lepton.pt();
    return pt;
}

bool TopHadronicTagger::Problematic(Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Debug0;
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal:
        if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > top_mass_window_) return true;
//         if (pre_cuts.NotParticleRho(triplet)) return true;
//         if (std::abs(triplet.Doublet().Mass() - Mass(Id::W)) > 40) return true;
//         if (triplet.Doublet().Bdt() < 1) return true;
//         if (triplet.Singlet().Bdt() < 1) return true;
//         if (triplet.pt() > DetectorGeometry::LeptonMinPt()) return true;
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
    return ReduceResult(Triplets(event, [&](Triplet & triplet, Jets const & leptons) {
        return Multiplet(triplet, leptons, pre_cuts, reader);
    }));
}

boost::optional<Triplet> TopHadronicTagger::Multiplet(Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
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

std::vector< Triplet > TopHadronicTagger::ordered_triplets(Jets const& jets, unsigned int sub_jet_number, std::function< boost::optional<Triplet>(fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3)> const& function) const
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
    Info0;
    return "TopHadronic";
}

std::string TopHadronicTagger::NiceName() const
{
    Info0;
    return "t_{h}";
}

}

}


