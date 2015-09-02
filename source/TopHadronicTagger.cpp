/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TopHadronicTagger.hh"

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/NjettinessDefinition.hh"
#include "Event.hh"
#include "InfoRecombiner.hh"
// #define NOTIFICATION
#include "Debug.hh"

namespace boca
{

TopHadronicTagger::TopHadronicTagger()
{
    Info();
//     top_mass_window_ = (Mass(Id::top) - Mass(Id::higgs)) / 2;
    top_mass_window_ = 50;
    DefineVariables();
}

int TopHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    Info(jets.size());
    Jets leptons = event.Leptons().leptons();
    std::vector<boca::Triplet> triplets;

    Info("3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(jets);
    triplets = Triplets(doublets, jets, leptons, pre_cuts, tag);

    for (auto const& jet : jets) {

        Info("2 Jet form one top" , triplets.size());
        try {
            Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet);
            triplets = Join(triplets, Triplets(piece_doublet, jets, leptons, pre_cuts, tag));
        } catch (char const* message) {}

        Info("1 jet forms one top", triplets.size());
        boca::Triplet triplet(jet);
        if (Problematic(triplet, pre_cuts)) continue;    // Check if potential topjet otherwise next jet
        triplet.Doublet().SetBdt(0);
        try {
            triplets.emplace_back(Triplet(triplet, leptons, pre_cuts, tag));
        } catch (char const* message) {}

        Info("2 sub jets forms one top" , triplets.size());
        unsigned sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() == sub_jet_number) {
            for (size_t i = 0; i < pieces.size(); ++i) {
                auto piece_1 = pieces.at(i);
                auto piece_2 = pieces.at((i + 1) % sub_jet_number);
                try {
                    Doublet doublet = w_hadronic_reader_.Multiplet(piece_2);
                    triplets.emplace_back(Triplet(doublet, piece_1, leptons, pre_cuts, tag));
                } catch (char const* message) {}
            }
        }

        Info("3 sub jets forms one top" , triplets.size());
        sub_jet_number = 3;
        pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        triplets = Join(triplets, ordered_triplets(pieces, sub_jet_number, [&](fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3) {
            Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
            return Triplet(doublet, piece_1, leptons, pre_cuts, tag);
        }));

    }
    int top_hadronic_id = TopHadronicId(event);
    Jets particles = event.Partons().GenParticles();
    Jets top_particles;
    if (top_hadronic_id != to_int(Id::empty)) top_particles = CopyIfExactParticle(particles, top_hadronic_id);
    else top_particles = CopyIfParticle(particles, Id::top);
    Info(triplets.size(), top_particles.size());

    return SaveEntries(triplets, top_particles, tag, Id::top);
}

std::vector<Triplet> TopHadronicTagger::Triplets(std::vector<boca::Doublet> const& doublets, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(doublets.size());
    std::vector<boca::Triplet> triplets;
    for (auto const& doublet : doublets)
        triplets = Join(triplets, Triplets(doublet, jets, leptons, pre_cuts, tag));
    Info(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(boca::Doublet const& doublet, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(jets.size());
    std::vector<boca::Triplet> triplets;
    for (auto const& jet : jets) {
        try {
            triplets.emplace_back(Triplet(doublet, jet, leptons, pre_cuts, tag, true));
        } catch (char const* message) {}
    }
    Info(triplets.size());
    return triplets;
}

Triplet TopHadronicTagger::Triplet(boca::Doublet const& doublet, fastjet::PseudoJet const& jet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag, bool check_overlap) const
{
    boca::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) throw "top hadronic overlap";
    try {
        return Triplet(triplet, leptons, pre_cuts, tag);
    } catch (char const* message) {
        throw message;
    }
}

Triplet TopHadronicTagger::Triplet(boca::Triplet& triplet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts, tag)) throw "top hadronic triplet problem";
    NSubJettiness(triplet);
    triplet.SetTag(tag);
    return triplet;
}

float TopHadronicTagger::LeptonPt(boca::Triplet const& triplet, boca::Jets const& leptons) const
{
    float pt = 0;
    for (auto const& lepton : leptons) if (Close(lepton)(triplet) && lepton.pt() > pt) pt = lepton.pt();
    return pt;
}

bool TopHadronicTagger::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Debug();
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal: {

        if (std::abs(triplet.Jet().m() - Mass(Id::top)) > top_mass_window_) return true;
        if ((triplet.Rho() < 0.5 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;


//         if (std::abs(triplet.Doublet().Jet().m() - Mass(Id::W)) > 40) return true;
//         if (triplet.Doublet().Bdt() < 1) return true;
//         if (triplet.Singlet().Bdt() < 1) return true;
//         if (triplet.pt() > DetectorGeometry::LeptonMinPt()) return true;
        break;
    }
    case Tag::background :
        break;
    }
    return false;
}

bool TopHadronicTagger::Problematic(boca::Triplet const& triplet, PreCuts const& pre_cuts) const
{
    Debug();
    if (pre_cuts.PtLowerCut(Id::top) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && triplet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) return true;
//     if (triplet.DeltaR() < DetectorGeometry::MinCellResolution() && triplet.DeltaR() > 0) return true;

    // FIXME the top tagger is very slow, due to many calls of Bdt(), therfore we have to reduce the number of candidates
    if (std::abs(triplet.Jet().m() - Mass(Id::top)) > 2 * top_mass_window_) return true;
    if ((triplet.Rho() < 0.4 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
    return false;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<boca::Triplet> triplets;
    Jets leptons = event.Leptons().leptons();

    Info("3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(jets);
    triplets = Multiplets(doublets, jets, leptons, pre_cuts, reader);

    for (auto const& jet : jets) {

        Info("2 Jet form one top" , triplets.size());
        try {
            Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet);
            triplets = Join(triplets, Multiplets(piece_doublet, jets, leptons, pre_cuts, reader));
        } catch (char const* message) {}

        Info("1 jet forms one top", triplets.size());
        boca::Triplet triplet(jet);
        if (Problematic(triplet, pre_cuts)) continue;    // Check if potential topjet otherwise next jet
        triplet.Doublet().SetBdt(0);
        try {
            triplets.emplace_back(Multiplet(triplet, leptons, pre_cuts, reader));
        } catch (char const* message) {}

        Info("2 sub jets forms one top" , triplets.size());
        size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() == sub_jet_number) {
            for (size_t i = 0; i < pieces.size(); ++i) {
                auto piece_1 = pieces.at(i);
                auto piece_2 = pieces.at((i + 1) % sub_jet_number);
                try {
                    Doublet doublet = w_hadronic_reader_.Multiplet(piece_2);
                    triplets.emplace_back(Multiplet(doublet, piece_1, leptons, pre_cuts, reader));
                } catch (char const* message) {}
            }
        }

        Info("3 sub jets forms one top" , triplets.size());
        sub_jet_number = 3;
        pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        triplets = Join(triplets, ordered_triplets(pieces, sub_jet_number, [&](fastjet::PseudoJet const& piece_1, fastjet::PseudoJet const& piece_2, fastjet::PseudoJet const& piece_3) {
            Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
            return Multiplet(doublet, piece_1, leptons, pre_cuts, reader);
        }));

    }
//     Error(triplets.size());
    return ReduceResult(triplets);
}

std::vector<Triplet> TopHadronicTagger::Multiplets(std::vector<boca::Doublet> const& doublets, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    std::vector<boca::Triplet> triplets;
    for (auto const& doublet : doublets) triplets = Join(triplets, Multiplets(doublet, jets, leptons, pre_cuts, reader));
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(boca::Doublet const& doublet, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    std::vector<boca::Triplet> triplets;
    for (auto const& jet : jets) {
        try {
            triplets.emplace_back(Multiplet(doublet, jet, leptons, pre_cuts, reader, true));
        } catch (char const* message) {
            continue;
        }
    }
    return triplets;
}

Triplet TopHadronicTagger::Multiplet(boca::Doublet const& doublet, fastjet::PseudoJet const& jet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader, bool check_overlap) const
{
    boca::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) throw "overlap";
    NSubJettiness(triplet);
    try {
        return Multiplet(triplet, leptons, pre_cuts, reader);
    } catch (char const* message) {
        throw message;
    }
}

Triplet TopHadronicTagger::Multiplet(boca::Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts)) throw "problem";
    // FIXME how can this happen?
    if (triplet.Doublet().Bdt() < -10) throw "no doublet bdt";
    triplet.SetBdt(Bdt(triplet, reader));
    if (triplet.Bdt() == -999) Error(triplet.Doublet().Bdt(), triplet.Singlet().Bdt());
    return triplet;
}

void TopHadronicTagger::NSubJettiness(boca::Triplet& triplet) const
{
    return;
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Singlet().Jet() * 2));
    else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().Singlet1().Jet() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(triplet.Singlet().Jet(), triplet.Doublet().Singlet1().Jet(), triplet.Doublet().Singlet2().Jet(), InfoRecombiner())));
}

SubJettiness TopHadronicTagger::NSubJettiness(fastjet::PseudoJet const& jet) const
{
    Info();
    fastjet::contrib::OnePass_WTA_KT_Axes axis_mode_1;
    fastjet::contrib::OnePass_KT_Axes axis_mode_2;
    double beta_1 = 1.0;
    double beta_2 = 2.0;
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure_1(beta_1);
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure_2(beta_2);
//
    fastjet::contrib::Nsubjettiness n_subjettiness_1_1(1, axis_mode_1, unnormalized_measure_1);
    fastjet::contrib::Nsubjettiness n_subjettiness_2_1(2, axis_mode_1, unnormalized_measure_1);
    fastjet::contrib::Nsubjettiness n_subjettiness_3_1(3, axis_mode_1, unnormalized_measure_1);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_21_1(2, 1, axis_mode_1, unnormalized_measure_1);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_32_1(3, 2, axis_mode_1, unnormalized_measure_1);
    fastjet::contrib::Nsubjettiness n_subjettiness_1_2(1, axis_mode_2, unnormalized_measure_2);
    fastjet::contrib::Nsubjettiness n_subjettiness_2_2(2, axis_mode_2, unnormalized_measure_2);
    fastjet::contrib::Nsubjettiness n_subjettiness_3_2(3, axis_mode_2, unnormalized_measure_2);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_21_2(2, 1, axis_mode_2, unnormalized_measure_2);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_32_2(3, 2, axis_mode_2, unnormalized_measure_2);
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

int TopHadronicTagger::TopHadronicId(Event const& event) const
{
    return sgn(w_hadronic_reader_.Tagger().WHadronicId(event)) * to_int(Id::top);
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
        } catch (char const* message) {}
    }
    return triplets;
}

}
