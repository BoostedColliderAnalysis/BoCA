#include "TopHadronicTagger.hh"

#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/NjettinessDefinition.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

TopHadronicTagger::TopHadronicTagger()
{
    Note();
//     top_mass_window_ = (Mass(Id::top) - Mass(Id::higgs)) / 2;
    top_mass_window_ = 50;
    DefineVariables();
}

int TopHadronicTagger::Train(const Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info();

    Jets jets = bottom_reader_.Multiplets(event);
    Info(jets.size());

    Jets leptons = event.Leptons().leptons();

    std::vector<analysis::Triplet> triplets;

    Info("3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(jets);
    triplets = Triplets(doublets, jets, leptons, pre_cuts, tag);

    Info("2 Jet form one top" , triplets.size());
    ordered_pairs(jets, triplets, [&](const auto & jet_1, const auto & jet_2) {
        Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet_1);
        return Triplet(piece_doublet, jet_2, leptons, pre_cuts, tag);
    });

    for (const auto & jet : jets) {

        Info("1 jet forms one top", triplets.size());
        analysis::Triplet triplet(jet);
        if (Problematic(triplet, pre_cuts)) continue; // Check if potential topjet otherwise next jet
        triplet.Doublet().SetBdt(1);
        try {
            triplets.emplace_back(Triplet(triplet, leptons, pre_cuts, tag));
        } catch (const char *message) {
            continue;
        }

        Info("2 sub jets forms one top" , triplets.size());
        std::size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            try {
                Doublet doublet = w_hadronic_reader_.Multiplet(piece_2);
                try {
                    triplets.emplace_back(Triplet(doublet, piece_1, leptons, pre_cuts, tag));
                } catch (const char *message) {
                    continue;
                }
            } catch (const char *message) {
                continue;
            }
        }

        Info("3 sub jets forms one top" , triplets.size());
        sub_jet_number = 3;
        pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            auto piece_3 = pieces.at((i + 2) % sub_jet_number);
            try {
                Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
                try {
                    triplets.emplace_back(Triplet(doublet, piece_1, leptons, pre_cuts, tag));
                } catch (const char *message) {
                    continue;
                }
            } catch (const char *message) {
                continue;
            }
        }
    }

    int top_hadronic_id = TopHadronicId(event);
    Jets particles = event.Partons().GenParticles();
    Jets top_particles;
    if (top_hadronic_id != 0) top_particles = CopyIfParticle(particles, top_hadronic_id);
    else top_particles = CopyIfAbsParticle(particles, Id::top);
    return SaveEntries(BestMatches(triplets, top_particles, tag));
}

std::vector<Triplet> TopHadronicTagger::Triplets(const std::vector< analysis::Doublet > &doublets, const analysis::Jets &jets, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info(doublets.size());
    std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets) triplets = Join(triplets, Triplets(doublet, jets, leptons, pre_cuts, tag));
    Info(triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(const analysis::Doublet &doublet, const analysis::Jets &jets, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info(jets.size());
    std::vector<analysis::Triplet> triplets;
    for (const auto & jet : jets) {
        try {
            triplets.emplace_back(Triplet(doublet, jet, leptons, pre_cuts, tag, true));
        } catch (const char *message) {
            continue;
        }
    }
    Info(triplets.size());
    return triplets;
}

Triplet TopHadronicTagger::Triplet(const analysis::Doublet &doublet, const fastjet::PseudoJet &jet, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const analysis::Tag tag, const bool check_overlap) const
{
    analysis::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) throw "top hadronic triplet problem";
    try {
        return Triplet(triplet, leptons, pre_cuts, tag);
    } catch (const char *message) {
        throw message;
    }
}

Triplet TopHadronicTagger::Triplet(analysis::Triplet &triplet, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts, tag)) throw "top hadronic triplet problem";
    NSubJettiness(triplet);
    triplet.SetTag(tag);
    return triplet;
}

float TopHadronicTagger::LeptonPt(const analysis::Triplet &triplet, const analysis::Jets &leptons) const
{
    float pt = 0;
    for (const auto & lepton : leptons) if (Close2(lepton)(triplet) && lepton.pt() > pt) pt = lepton.pt();
    return pt;
}

bool TopHadronicTagger::Problematic(const analysis::Triplet &triplet, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info();
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal: {
        if (std::abs(triplet.Jet().m() - Mass(Id::top)) > top_mass_window_) return true;
//         if (std::abs(triplet.Doublet().Jet().m() - Mass(Id::W)) > 40) return true;
        if ((triplet.Rho() < 0.5 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
//         if (triplet.Doublet().Bdt() < 1) return true;
//         if (triplet.Singlet().Bdt() < 1) return true;
//         if (triplet.pt() > DetectorGeometry().LeptonMinPt()) return true;
        break;
    }
    case Tag::background :
        break;
    }
    return false;
}

bool TopHadronicTagger::Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts) const
{
    Info();
    if (pre_cuts.PtLowerCut(Id::top) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && pre_cuts.MassUpperCut(Id::top) < triplet.Jet().m()) return true;
//     if (triplet.Doublet().IsEmpty()) return true;
//     if (triplet.DeltaR() < DetectorGeometry().MinCellResolution() && triplet.DeltaR() > 0) return true;

    // FIXME the top tagger is very slow, due to many calls of Bdt(), therfore we have to reduce the number of candidates
    if (std::abs(triplet.Jet().m() - Mass(Id::top)) > 2 * top_mass_window_) return true;
    if ((triplet.Rho() < 0.4 || triplet.Rho() > 1.5) && triplet.Rho() > 0) return true;


    return false;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<analysis::Triplet> triplets;

    Jets leptons = event.Leptons().leptons();

    Info("3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets(jets);
    triplets = Multiplets(doublets, jets, leptons, pre_cuts, reader);

    for (const auto & jet : jets) {

        Info("2 Jet form one top" , triplets.size());
        Doublet piece_doublet = w_hadronic_reader_.SubMultiplet(jet);
        triplets = Join(triplets, Multiplets(piece_doublet, jets, leptons, pre_cuts, reader));

        Info("1 jet forms one top", triplets.size());
        analysis::Triplet triplet(jet);
        if (Problematic(triplet, pre_cuts)) continue; // Check if potential topjet otherwise next jet
        triplet.Doublet().SetBdt(1);
        triplets.emplace_back(Multiplet(triplet, leptons, pre_cuts, reader));

        Info("2 sub jets forms one top" , triplets.size());
        std::size_t sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            try {
                Doublet doublet = w_hadronic_reader_.Multiplet(piece_2);
                triplets.emplace_back(Multiplet(doublet, piece_1, leptons, pre_cuts, reader));
            } catch (const char *message) {}
        }

        Info("3 sub jets forms one top" , triplets.size());
        sub_jet_number = 3;
        pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            auto piece_3 = pieces.at((i + 2) % sub_jet_number);
            try {
                Doublet doublet = w_hadronic_reader_.Multiplet(piece_2, piece_3);
                triplets.emplace_back(Multiplet(doublet, piece_1, leptons, pre_cuts, reader));
            } catch (const char *message) {}
        }
    }

    return ReduceResult(triplets);
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const std::vector< analysis::Doublet > &doublets, const analysis::Jets &jets, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets) triplets = Join(triplets, Multiplets(doublet, jets, leptons, pre_cuts, reader));
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const analysis::Doublet &doublet, const analysis::Jets &jets, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    std::vector<analysis::Triplet> triplets;
    for (const auto & jet : jets) {
        try {
            triplets.emplace_back(Multiplet(doublet, jet, leptons, pre_cuts, reader, true));
        } catch (const char *message) {
            continue;
        }
    }
    return triplets;
}

Triplet TopHadronicTagger::Multiplet(const analysis::Doublet &doublet, const fastjet::PseudoJet &jet, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader, const bool check_overlap) const
{
    analysis::Triplet triplet(doublet, jet);
    if (check_overlap && triplet.Overlap()) throw "top hadronic triplet problem";
    NSubJettiness(triplet);
    try {
        return Multiplet(triplet, leptons, pre_cuts, reader);
    } catch (const char *message) {
        throw message;
    }
}

Triplet TopHadronicTagger::Multiplet(analysis::Triplet &triplet, const  Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts)) throw "top hadronic triplet problem";
    triplet.SetBdt(Bdt(triplet, reader));
    return triplet;
}

void TopHadronicTagger::NSubJettiness(analysis::Triplet &triplet) const
{
    return;
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Singlet().Jet() * 2));
    else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().SingletJet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.Singlet().Jet(), triplet.Doublet().SingletJet1()), triplet.Doublet().SingletJet2())));
}

SubJettiness TopHadronicTagger::NSubJettiness(const fastjet::PseudoJet &jet) const
{
    Info();
    fastjet::contrib::OnePass_WTA_KT_Axes axis_mode_1;
    fastjet::contrib::OnePass_KT_Axes axis_mode_2;

    const double beta_1 = 1.0;
    const double beta_2 = 2.0;
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

}

