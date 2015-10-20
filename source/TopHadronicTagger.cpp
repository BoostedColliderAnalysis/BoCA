/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <boost/range/algorithm/adjacent_find.hpp>

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/NjettinessDefinition.hh"

#include "TopHadronicTagger.hh"
#include "Event.hh"
#include "InfoRecombiner.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

TopHadronicTagger::TopHadronicTagger()
{
    Info();
//     top_mass_window_ = (MassOf(Id::top) - MassOf(Id::higgs)) / 2;
    top_mass_window_ = 50. * GeV;
}

int TopHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    return SaveEntries(Triplets(event, pre_cuts, [&](boca::Triplet & triplet, Jets const & leptons, bool & failure) {
        return Triplet(triplet, leptons, pre_cuts, tag, failure);
    }), TopParticles(event), tag, Id::top);
}

Jets TopHadronicTagger::TopParticles(Event const& event) const
{
    Info();
    Jets particles = event.Partons().GenParticles();
    Jets quarks = CopyIfGrandMother(CopyIfQuark(particles), Id::top);
    if (quarks.empty()) return {};
    std::vector<int> ids;
    for (auto const & quark : quarks) ids.emplace_back(quark.user_info<ParticleInfo>().Family().grand_mother().id());

    if (boost::range::adjacent_find(ids, std::not_equal_to<int>()) == ids.end()) return CopyIfExactParticle(particles, ids.front());
    else return CopyIfParticle(particles, Id::top);
}

std::vector<Triplet> TopHadronicTagger::Triplets(Event const& event, PreCuts const& pre_cuts, std::function<boca::Triplet(boca::Triplet&, Jets const&, bool&)> const& function) const
{
    Info();
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    Jets leptons = event.Leptons().leptons();
    std::vector<boca::Triplet> triplets;

    Info("3 Jets form one top" , triplets.size());
    Jets softer_than_W = RemoveIfHard(jets, PtMax(Id::W));
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(softer_than_W);
    Jets softer_than_top = RemoveIfHard(jets, PtMax(Id::top));
    triplets = Triplets(doublets, softer_than_top, leptons, function);

    Jets harder_than_W = RemoveIfSoft(jets, PtMin(Id::W));
    for (auto const & jet : harder_than_W) {

        Info("2 Jet form one top" , triplets.size());
        try {
            Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet);
            triplets = Join(triplets, Triplets(piece_doublet, softer_than_top, leptons, function));
        } catch (std::exception const&) {}

        Info("1 jet forms one top", triplets.size());
        if (jet.pt() * GeV < PtMin(Id::top)) continue;
        boca::Triplet jet_triplet(jet);
        if (Problematic(jet_triplet, pre_cuts)) continue; // Check if potential topjet otherwise next jet

        Info("3 sub jets forms one top" , triplets.size());

        if (jet.pt() * GeV < PtMax(Id::W, DetectorGeometry::MinCellResolution())) {

        unsigned sub_jet_number = 3;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        triplets = Join(triplets, ordered_triplets(pieces, sub_jet_number, [&](fastjet::PseudoJet const & piece_1, fastjet::PseudoJet const & piece_2, fastjet::PseudoJet const & piece_3) {
            Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
            bool failure = false;
            boca::Triplet triplet = Triplet(doublet, piece_1, leptons, function, failure);
            if (failure) throw  boca::Problematic();
            return triplet;
        }));

        }

        Info("2 sub jets forms one top" , triplets.size());
        if (jet.pt() * GeV < PtMin(Id::W, DetectorGeometry::MinCellResolution())) continue;
        
        unsigned sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() == sub_jet_number) {
            for (size_t i = 0; i < pieces.size(); ++i) {
                auto piece_1 = pieces.at(i);
                auto piece_2 = pieces.at((i + 1) % sub_jet_number);
                try {
                    Doublet doublet = w_hadronic_reader_.Multiplet(piece_2);
                    bool failure = false;
                    boca::Triplet triplet = Triplet(doublet, piece_1, leptons, function, failure);
                    if (!failure) triplets.emplace_back(triplet);
                } catch (std::exception const&) {}
            }
        }

        Info("1 sub jet forms one top", triplets.size());
        if (jet.pt() * GeV < PtMin(Id::top, DetectorGeometry::MinCellResolution())) continue;
        jet_triplet.Doublet().SetBdt(0);
        try {
            bool failure = false;
            jet_triplet = function(jet_triplet, leptons, failure);
            if (!failure) triplets.emplace_back(jet_triplet);
        } catch (std::exception const&) {}

    }
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(std::vector<boca::Doublet> const& doublets, boca::Jets const& jets, boca::Jets const& leptons, std::function<boca::Triplet(boca::Triplet&, Jets const&, bool&)> const& function) const
{
    Info(doublets.size());
    std::vector<boca::Triplet> triplets;
    for (auto const & doublet : doublets) triplets = Join(triplets, Triplets(doublet, jets, leptons, function));
    Info(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(boca::Doublet const& doublet, boca::Jets const& jets, boca::Jets const& leptons, std::function<boca::Triplet(boca::Triplet&, Jets const&, bool&)> const& function) const
{
    Info();
    std::vector<boca::Triplet> triplets;
    for (auto const & jet : jets) {
        try {
            bool failure = false;
            boca::Triplet triplet = Triplet(doublet, jet, leptons, function, failure , true);
            if (!failure) triplets.emplace_back(triplet);
        } catch (std::exception const&) {}
    }
    Info(triplets.size());
    return triplets;
}

Triplet TopHadronicTagger::Triplet(boca::Doublet const& doublet, fastjet::PseudoJet const& jet, boca::Jets const& leptons , std::function<boca::Triplet(boca::Triplet&, Jets const&, bool&)> const& function, bool& failure, bool check_overlap) const
{
    boca::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) {
        failure = true;
        return triplet;
        throw Overlap();
    }
    try {
        return function(triplet, leptons, failure);
    } catch (std::exception const&) {
        throw;
    }
}

Triplet TopHadronicTagger::Triplet(boca::Triplet& triplet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag, bool& failure) const
{
    // No throwing because this function fails too often
    if (Problematic(triplet, pre_cuts, tag)) {
        failure = true;
        return triplet;
        throw boca::Problematic();
    }
    triplet.set_pt(LeptonPt(triplet, leptons));
    NSubJettiness(triplet);
    triplet.SetTag(tag);
    return triplet;
}

float TopHadronicTagger::LeptonPt(boca::Triplet const& triplet, boca::Jets const& leptons) const
{
    float pt = 0;
    for (auto const & lepton : leptons) if (lepton.pt() > pt && Close(lepton)(triplet)) pt = lepton.pt();
    return pt;
}

bool TopHadronicTagger::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Debug();
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal:
        if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > top_mass_window_) return true;
        if ((triplet.Rho() < 0.5 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
//         if (std::abs(triplet.Doublet().Mass() - Mass(Id::W)) > 40) return true;
//         if (triplet.Doublet().Bdt() < 1) return true;
//         if (triplet.Singlet().Bdt() < 1) return true;
//         if (triplet.pt() > DetectorGeometry::LeptonMinPt()) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopHadronicTagger::Problematic(boca::Triplet const& triplet, PreCuts const& pre_cuts) const
{
    Debug();
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
//     if (pre_cuts.PtLowerCut(Id::top) > at_rest && triplet.Pt() < pre_cuts.PtLowerCut(Id::top)) return true;
//     if (pre_cuts.PtUpperCut(Id::top) > at_rest && triplet.Pt() > pre_cuts.PtUpperCut(Id::top)) return true;
//     if (pre_cuts.MassUpperCut(Id::top) > massless && triplet.Mass() > pre_cuts.MassUpperCut(Id::top)) return true;
//     if (triplet.DeltaR() < DetectorGeometry::MinCellResolution() && triplet.DeltaR() > 0) return true;

    // FIXME the top tagger is very slow, due to many calls of Bdt(), therfore we have to reduce the number of candidates
    if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > 2. * top_mass_window_) return true;
    if ((triplet.Rho() < 0.4 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
    return false;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    return ReduceResult(Triplets(event, pre_cuts, [&](boca::Triplet & triplet, Jets const & leptons, bool &  failure) {
        return Multiplet(triplet, leptons, pre_cuts, reader, failure);
    }));
}

Triplet TopHadronicTagger::Multiplet(boca::Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader, bool& failure) const
{
    Info();
    // No throwing because this function fails too often
    if (Problematic(triplet, pre_cuts)) {
        failure = true;
        return triplet;
        throw boca::Problematic();
    }
    triplet.set_pt(LeptonPt(triplet, leptons));
    NSubJettiness(triplet);
    triplet.SetBdt(Bdt(triplet, reader));
    return triplet;
}

void TopHadronicTagger::NSubJettiness(boca::Triplet&) const
{
    Info();
    return;
//     if (!triplet.()) triplet.set_sub_jettiness(NSubJettiness(triplet.Singlet().Jet() * 2));
//     else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().Singlet1().Jet() * 2));
//     else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(triplet.Singlet().Jet(), triplet.Doublet().Singlet1().Jet(), triplet.Doublet().Singlet2().Jet(), InfoRecombiner())));
}

SubJettiness TopHadronicTagger::NSubJettiness(fastjet::PseudoJet const& jet) const
{
    Info();
    fastjet::contrib::OnePass_WTA_KT_Axes wta_kt_axes;
    fastjet::contrib::OnePass_KT_Axes kt_axes;
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure_1(1);
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure_2(2);
//
    fastjet::contrib::Nsubjettiness n_subjettiness_1_1(1, wta_kt_axes, unnormalized_measure_1);
    fastjet::contrib::Nsubjettiness n_subjettiness_2_1(2, wta_kt_axes, unnormalized_measure_1);
    fastjet::contrib::Nsubjettiness n_subjettiness_3_1(3, wta_kt_axes, unnormalized_measure_1);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_21_1(2, 1, wta_kt_axes, unnormalized_measure_1);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_32_1(3, 2, wta_kt_axes, unnormalized_measure_1);
    fastjet::contrib::Nsubjettiness n_subjettiness_1_2(1, kt_axes, unnormalized_measure_2);
    fastjet::contrib::Nsubjettiness n_subjettiness_2_2(2, kt_axes, unnormalized_measure_2);
    fastjet::contrib::Nsubjettiness n_subjettiness_3_2(3, kt_axes, unnormalized_measure_2);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_21_2(2, 1, kt_axes, unnormalized_measure_2);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_32_2(3, 2, kt_axes, unnormalized_measure_2);
//
    SubJettiness sub_jettiness;
//
    // calculate Nsubjettiness values (beta = 1.0)
    sub_jettiness.tau1_beta1(n_subjettiness_1_1(jet));
    sub_jettiness.tau2_beta1(n_subjettiness_2_1(jet));
    sub_jettiness.tau3_beta1(n_subjettiness_3_1(jet));
    sub_jettiness.tau21_beta1(n_subjettiness_21_1(jet));
    sub_jettiness.tau32_beta1(n_subjettiness_32_1(jet));
    // calculate Nsubjettiness values (beta = 2.0)
    sub_jettiness.tau1_beta2(n_subjettiness_1_2(jet));
    sub_jettiness.tau2_beta2(n_subjettiness_2_2(jet));
    sub_jettiness.tau3_beta2(n_subjettiness_3_2(jet));
    sub_jettiness.tau21_beta2(n_subjettiness_21_2(jet));
    sub_jettiness.tau32_beta2(n_subjettiness_32_2(jet));
    return sub_jettiness;
}

std::vector< Triplet > TopHadronicTagger::ordered_triplets(Jets const& jets, unsigned int sub_jet_number, std::function< boca::Triplet(fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3)> const& function) const
{
    std::vector<boca::Triplet> triplets;
    if (jets.size() < sub_jet_number) return {};
    for (size_t i = 0; i < jets.size(); ++i) {
        auto piece_1 = jets.at(i);
        auto piece_2 = jets.at((i + 1) % sub_jet_number);
        auto piece_3 = jets.at((i + 2) % sub_jet_number);
        try {
            triplets.emplace_back(function(piece_1, piece_2, piece_3));
        } catch (std::exception const&) {}
    }
    return triplets;
}

}

