/**
 * Copyright (C) 2015 Jan Hajer
 */

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
//     top_mass_window_ = (Mass(Id::top) - Mass(Id::higgs)) / 2;
    top_mass_window_ = 50. * GeV;
}

int TopHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    Info(jets.size());
    int comb = (sqr(jets.size()) + jets.size()) / 2;
    Info(comb);
    Jets leptons = event.Leptons().leptons();
    std::vector<boca::Triplet> triplets;

    Info("3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(jets);
    triplets = Triplets(doublets, jets, leptons, pre_cuts, tag);

    for (auto const & jet : jets) {

        Info("2 Jet form one top" , triplets.size());
        try {
            Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet);
            triplets = Join(triplets, Triplets(piece_doublet, jets, leptons, pre_cuts, tag));
        } catch (std::exception const&) {}

        Info("1 jet forms one top", triplets.size());
        boca::Triplet triplet(jet);
        if (Problematic(triplet, pre_cuts)) continue;    // Check if potential topjet otherwise next jet
        triplet.Doublet().SetBdt(0);
        try {
            triplets.emplace_back(Triplet(triplet, leptons, pre_cuts, tag));
        } catch (std::exception const&) {}

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
                } catch (std::exception const&) {}
            }
        }

        Info("3 sub jets forms one top" , triplets.size());
        sub_jet_number = 3;
        pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        triplets = Join(triplets, ordered_triplets(pieces, sub_jet_number, [&](fastjet::PseudoJet const & piece_1, fastjet::PseudoJet const & piece_2, fastjet::PseudoJet const & piece_3) {
            Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
            return Triplet(doublet, piece_1, leptons, pre_cuts, tag);
        }));

    }
    Jets top_particles = TopParticles(event);
    int size = top_particles.size();
    std::string particle = "";
    if(size > 0) particle = boca::Name(top_particles.front().user_info<ParticleInfo>().Family().particle().id());
    Error(size, particle);
    Info(triplets.size(), top_particles.size());
    return SaveEntries(triplets, top_particles, tag, Id::top);
}

Jets TopHadronicTagger::TopParticles(Event const& event) const {
  Jets particles = event.Partons().GenParticles();
  Jets quarks = CopyIfQuark(particles);
  quarks = CopyIfGrandMother(quarks, Id::top);
  if(quarks.empty()) return {};
  Check(quarks.size() == 2, quarks.size());
  int grand_mother = quarks.front().user_info<ParticleInfo>().Family().grand_mother().id();
  Info(grand_mother);
  return CopyIfExactParticle(particles, grand_mother);
//   int top_hadronic_id = TopHadronicId(event);
//   Jets particles = event.Partons().GenParticles();
//   Jets top_particles;
//   if (top_hadronic_id != to_int(Id::empty)) top_particles = CopyIfExactParticle(particles, top_hadronic_id);
//   else top_particles = CopyIfParticle(particles, Id::top);
//   return top_particles;
}

std::vector<Triplet> TopHadronicTagger::Triplets(std::vector<boca::Doublet> const& doublets, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(doublets.size());
    std::vector<boca::Triplet> triplets;
    for (auto const & doublet : doublets) triplets = Join(triplets, Triplets(doublet, jets, leptons, pre_cuts, tag));
    Info(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(boca::Doublet const& doublet, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(jets.size());
    std::vector<boca::Triplet> triplets;
    for (auto const & jet : jets) {
        try {
            triplets.emplace_back(Triplet(doublet, jet, leptons, pre_cuts, tag, true));
        } catch (std::exception const&) {}
    }
    Info(triplets.size());
    return triplets;
}

Triplet TopHadronicTagger::Triplet(boca::Doublet const& doublet, fastjet::PseudoJet const& jet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag, bool check_overlap) const
{
    boca::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) throw Overlap();
    try {
        return Triplet(triplet, leptons, pre_cuts, tag);
    } catch (std::exception const&) {
        throw;
    }
}

Triplet TopHadronicTagger::Triplet(boca::Triplet& triplet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, Tag tag) const
{
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
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
    case Tag::signal: {

        if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > top_mass_window_) return true;
        if ((triplet.Rho() < 0.5 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;


//         if (std::abs(triplet.Doublet().Mass() - Mass(Id::W)) > 40) return true;
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
    if (pre_cuts.PtLowerCut(Id::top) > at_rest && triplet.Pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > at_rest && triplet.Pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > massless && triplet.Mass() > pre_cuts.MassUpperCut(Id::top)) return true;
//     if (triplet.DeltaR() < DetectorGeometry::MinCellResolution() && triplet.DeltaR() > 0) return true;

    // FIXME the top tagger is very slow, due to many calls of Bdt(), therfore we have to reduce the number of candidates
    if (boost::units::abs(triplet.Mass() - MassOf(Id::top)) > 2. * top_mass_window_) return true;
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

    for (auto const & jet : jets) {

        Info("2 Jet form one top" , triplets.size());
        try {
            Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet);
            triplets = Join(triplets, Multiplets(piece_doublet, jets, leptons, pre_cuts, reader));
        } catch (std::exception const&) {}

        Info("1 jet forms one top", triplets.size());
        boca::Triplet triplet(jet);
        if (Problematic(triplet, pre_cuts)) continue; // Check if potential topjet otherwise next jet
        triplet.Doublet().SetBdt(0);
        try {
            bool failure = false;
            Multiplet(triplet, leptons, pre_cuts, reader, failure);
            if (!failure) triplets.emplace_back(triplet);
        } catch (std::exception const&) {}

        Info("2 sub jets forms one top" , triplets.size());
        size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() == sub_jet_number) {
            for (size_t i = 0; i < pieces.size(); ++i) {
                auto piece_1 = pieces.at(i);
                auto piece_2 = pieces.at((i + 1) % sub_jet_number);
                try {
                    Doublet doublet = w_hadronic_reader_.Multiplet(piece_2);
                    bool failure = false;
                    boca::Triplet triplet = Multiplet(doublet, piece_1, leptons, pre_cuts, reader, failure);
                    if (!failure) triplets.emplace_back(triplet);
                } catch (std::exception const&) {}
            }
        }

        Info("3 sub jets forms one top" , triplets.size());
        sub_jet_number = 3;
        pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        triplets = Join(triplets, ordered_triplets(pieces, sub_jet_number, [&](fastjet::PseudoJet const & piece_1, fastjet::PseudoJet const & piece_2, fastjet::PseudoJet const & piece_3) {
            Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
            bool failure = false;
            boca::Triplet triplet = Multiplet(doublet, piece_1, leptons, pre_cuts, reader, failure);
            if (failure) throw  boca::Problematic();
            return triplet;
        }));

    }
//     Error(triplets.size());
    return ReduceResult(triplets);
}

std::vector<Triplet> TopHadronicTagger::Multiplets(std::vector<boca::Doublet> const& doublets, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    std::vector<boca::Triplet> triplets;
    for (auto const & doublet : doublets) triplets = Join(triplets, Multiplets(doublet, jets, leptons, pre_cuts, reader));
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(boca::Doublet const& doublet, boca::Jets const& jets, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    std::vector<boca::Triplet> triplets;
    for (auto const & jet : jets) {
        try {
            bool failure = false;
            boca::Triplet triplet = Multiplet(doublet, jet, leptons, pre_cuts, reader, failure, true);
            if (!failure) triplets.emplace_back(triplet);
        } catch (std::exception const&) {
            continue;
        }
    }
    return triplets;
}

Triplet TopHadronicTagger::Multiplet(boca::Doublet const& doublet, fastjet::PseudoJet const& jet, boca::Jets const& leptons, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader, bool& failure, bool check_overlap) const
{
    Info();
    boca::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) {
        failure = true;
        return triplet;
        throw Overlap();
    }
    NSubJettiness(triplet);
    try {
        return Multiplet(triplet, leptons, pre_cuts, reader, failure);
    } catch (std::exception const&) {
        throw;
    }
}

Triplet TopHadronicTagger::Multiplet(boca::Triplet& triplet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader, bool& failure) const
{
    Info();
    triplet.set_pt(LeptonPt(triplet, leptons));
    // No throwing because this function fails too often
    if (Problematic(triplet, pre_cuts)) {
        failure = true;
        Info(failure);
        return triplet;
        throw boca::Problematic();
    }
    // FIXME how can this happen?
    if (triplet.Doublet().Bdt() < -10) {
        failure = true;
        return triplet;
        throw boca::Problematic();
    }
    triplet.SetBdt(Bdt(triplet, reader));
//     if (triplet.Bdt() == -999) Error(triplet.Doublet().Bdt(), triplet.Singlet().Bdt());
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
        } catch (std::exception const&) {}
    }
    return triplets;
}

}
