# include "TopHadronicTagger.hh"

# include "fastjet/contrib/Nsubjettiness.hh"
# include "fastjet/contrib/NjettinessDefinition.hh"

namespace analysis
{

TopHadronicTagger::TopHadronicTagger()
{
//     debug_level_ = kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopHadronic");
//     top_mass_window_ = (Mass(TopId) - Mass(HiggsId)) / 2;
    top_mass_window_ = 50;
    bottom_reader_.SetTagger(bottom_tagger_);
    w_hadronic_reader_.SetTagger(w_hadronic_tagger_);
    boost_ = false; // be carefull with this one!!
    DefineVariables();
}

int TopHadronicTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Train");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kInformation, "Jet size", jets.size());

    Jets leptons = event.Leptons().leptons();

    //     int had_top_id = TopHadronicId(event);
    Jets particles = event.Partons().GenParticles();
    Jets top_particles = copy_if_abs_particle(particles, TopId);
    Jets top_jets;
//     switch (tag) {
//     case kSignal :
//         top_jets = CopyIfClose2(jets, top_particles);
//     case kBackground :
//         top_jets = RemoveIfClose2(jets, top_particles);
//     }
//     Print(kInformation, "particle size", top_jets.size());
    top_jets = jets;

    std::vector<analysis::Triplet> triplets;

    Print(kInformation, "3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets<WHadronicTagger>(jets);
    triplets = Triplets(doublets, jets, leptons, pre_cuts, tag);

    Print(kInformation, "2 Jet form one top" , triplets.size());
    for (const auto & jet : jets) {
        Print(kInformation, "1 jet form one W" , triplets.size());
        Doublet piece_doublet = w_hadronic_reader_.SubMultiplet<WHadronicTagger>(jet);
        triplets = Join(triplets, Triplets(piece_doublet, jets, leptons, pre_cuts, tag));
    }

    Print(kInformation, "3 sub jets forms one top" , triplets.size());
    for (const auto & jet : top_jets) {
        const int sub_jet_number = 3;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            auto piece_3 = pieces.at((i + 2) % sub_jet_number);
            Doublet doublet = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2, piece_3);
            triplets.emplace_back(Triplet(doublet, piece_1, leptons, pre_cuts, tag));
        }
    }

    Print(kInformation, "2 sub jets forms one top" , triplets.size());
    for (const auto & jet : top_jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            Doublet doublet = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2);
            triplets.emplace_back(Triplet(doublet, piece_1, leptons, pre_cuts, tag));
        }
    }

    Print(kInformation, "1 jet forms one top", triplets.size());
    for (const auto & jet : top_jets) {
        analysis::Triplet triplet(jet);
        triplet.set_pt(LeptonPt(triplet, leptons));
        if (Problematic(triplet, pre_cuts, tag)) continue;
        triplet.SetTag(tag);
        triplet.Doublet().SetBdt(1);
        NSubJettiness(triplet);
        triplets.emplace_back(triplet);
    }

    return SaveEntries(BestMatches(triplets, top_particles, tag));
}

std::vector<Triplet> TopHadronicTagger::Triplets(const std::vector<Doublet> &doublets, const Jets &jets, const  Jets &leptons, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "doublets size", doublets.size());
    std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets) triplets = Join(triplets, Triplets(doublet, jets, leptons, pre_cuts, tag));
    Print(kInformation, "triplets", triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Triplets(const Doublet &doublet, const Jets &jets, const  Jets &leptons, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "jets size", jets.size());
    std::vector<analysis::Triplet> triplets;
    for (const auto & jet : jets) {
//         if (doublet.SingletJet1().delta_R(jet) < detector_geometry().JetConeSize) continue;
//         if (doublet.SingletJet2().delta_R(jet) < detector_geometry().JetConeSize) continue;
        triplets.emplace_back(Triplet(doublet, jet, leptons, pre_cuts, tag));
    }
    Print(kInformation, "triplets", triplets.size());
    return triplets;
}

Triplet TopHadronicTagger::Triplet(const Doublet &doublet, const fastjet::PseudoJet &jet, const  Jets &leptons, PreCuts &pre_cuts, const Tag tag)
{
    analysis::Triplet empty_triplets;
    analysis::Triplet triplet(doublet, jet);
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts, tag)) return empty_triplets;
    NSubJettiness(triplet);
    triplet.SetTag(tag);
    return triplet;
}

float TopHadronicTagger::LeptonPt(const analysis::Triplet &triplet, const Jets &leptons)
{
    float pt = 0;
    for (const auto lepton : leptons) if (Close(lepton)(triplet) && triplet.Jet().pt() > pt) pt = lepton.pt();
//     for (const auto lepton : leptons) if (triplet.Jet().delta_R(lepton)<DetectorGeometry().JetConeSize && triplet.Jet().pt() > pt) pt = triplet.Jet().pt();
    return pt;
}

bool TopHadronicTagger::Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Check for Problems");
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case kSignal: {
        if (std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) return true;
//         if (std::abs(triplet.Doublet().Jet().m() - Mass(WId)) > 20) return true;
//         if (triplet.Rho() < 0.5 || triplet.Rho() > 2) return true;
//         if (triplet.Doublet().Bdt() < 1) return true;
        if (triplet.Singlet().Bdt() < 1) return true;
        if (triplet.pt() > DetectorGeometry().LeptonMinPt) return true;
        break;
    }
    case kBackground :
        break;
    }
    return false;
}

bool TopHadronicTagger::Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts)
{
    Print(kInformation, "Check for Problems");
    if (pre_cuts.PtLowerCut(TopId) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(TopId)) return true;
    if (pre_cuts.PtUpperCut(TopId) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(TopId)) return true;
    if (pre_cuts.MassUpperCut(TopId) > 0 && pre_cuts.MassUpperCut(TopId) < triplet.Jet().m()) return true;
    if (triplet.Doublet().IsEmpty()) return true;
//     if (!boost_ && triplet.DeltaR() < DetectorGeometry().MinCellResolution) return true;
    return false;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<analysis::Triplet> triplets;

    Jets leptons = event.Leptons().leptons();

    Print(kInformation, "3 Jets form one top" , triplets.size());
    std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets<WHadronicTagger>(jets);
    triplets = Multiplets(doublets, jets, leptons, pre_cuts, reader);

    Print(kInformation, "2 Jet form one top" , triplets.size());
    for (const auto & jet : jets) {
        // 2 subjets form a W
        Doublet piece_doublet = w_hadronic_reader_.SubMultiplet<WHadronicTagger>(jet);
        // 2 subjets and one jet form a top
        triplets = Join(triplets, Multiplets(piece_doublet, jets, leptons, pre_cuts, reader));
    }

    Print(kInformation, "3 sub jets forms one top" , triplets.size());
    for (const auto & jet : jets) {
        const int sub_jet_number = 3;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            auto piece_3 = pieces.at((i + 2) % sub_jet_number);
            Doublet doublet = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2, piece_3);
            triplets.emplace_back(Multiplet(doublet, piece_1, leptons, pre_cuts, reader));
        }
    }

    Print(kInformation, "2 sub jets forms one top" , triplets.size());
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (std::size_t i = 0; i < pieces.size(); ++i) {
            auto piece_1 = pieces.at(i);
            auto piece_2 = pieces.at((i + 1) % sub_jet_number);
            Doublet doublet = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2);
            triplets.emplace_back(Multiplet(doublet, piece_1, leptons, pre_cuts, reader));
        }
    }

    Print(kInformation, "1 jet forms one top", triplets.size());
    for (const auto & jet : jets) {
        analysis::Triplet triplet(jet);
        triplet.Doublet().SetBdt(1);
        triplet.set_pt(LeptonPt(triplet, leptons));
        if (Problematic(triplet, pre_cuts)) continue;
        triplets.emplace_back(Multiplet(triplet, leptons, pre_cuts, reader));
    }

    return ReduceResult(triplets);
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const std::vector<Doublet> &doublets, const Jets &jets, const  Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets) triplets = Join(triplets, Multiplets(doublet, jets, leptons, pre_cuts, reader));
    return ReduceResult(triplets);
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const Doublet &doublet, const Jets &jets, const  Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector<analysis::Triplet> triplets;
    for (const auto & jet : jets) {
//         if (doublet.SingletJet1().delta_R(jet) < detector_geometry().JetConeSize) continue;
//         if (doublet.SingletJet2().delta_R(jet) < detector_geometry().JetConeSize) continue;
        triplets.emplace_back(Multiplet(doublet, jet, leptons, pre_cuts, reader));
    }
    return ReduceResult(triplets);
}

Triplet TopHadronicTagger::Multiplet(const Doublet &doublet, const fastjet::PseudoJet &jet, const  Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    analysis::Triplet empty_triplets;
    analysis::Triplet triplet(doublet, jet);
    triplet.set_pt(LeptonPt(triplet, leptons));
    if (Problematic(triplet, pre_cuts)) return empty_triplets;
    return Multiplet(triplet, leptons, pre_cuts, reader);
}

Triplet TopHadronicTagger::Multiplet(analysis::Triplet &triplet, const  Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    NSubJettiness(triplet);
    triplet.SetBdt(Bdt(triplet, reader));
    return triplet;
}

void TopHadronicTagger::NSubJettiness(analysis::Triplet &triplet)
{
    return;
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.SingletJet() * 2));
    else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().SingletJet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.SingletJet(), triplet.Doublet().SingletJet1()), triplet.Doublet().SingletJet2())));
}

SubJettiness TopHadronicTagger::NSubJettiness(const fastjet::PseudoJet &jet)
{
    Print(kInformation, "NSubJettiness");
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

