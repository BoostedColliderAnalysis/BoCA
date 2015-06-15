# include "TopHadronicTagger.hh"

# include "fastjet/contrib/Nsubjettiness.hh"
# include "fastjet/contrib/NjettinessDefinition.hh"

namespace analysis {

TopHadronicTagger::TopHadronicTagger()
{
    debug_level_ = Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopHadronic");
    top_mass_window_ = (Mass(TopId) - Mass(WId)) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_hadronic_reader_.set_tagger(w_hadronic_tagger_);
    boost_ = false; // be carefull with this one!!
    DefineVariables();
}

void TopHadronicTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Ht, "Ht");
    AddVariable(branch().BottomPt, "BottomPt");
    AddVariable(branch().WPt, "WPt");
    if (!boost_) {
        AddVariable(branch().DeltaPt, "DeltaPt");
        AddVariable(branch().DeltaHt, "DeltaHt");
        AddVariable(branch().DeltaM, "DeltaM");
        AddVariable(branch().DeltaPhi, "DeltaPhi");
        AddVariable(branch().DeltaRap, "DeltaRap");
        AddVariable(branch().DeltaR, "DeltaR");
    }
    AddVariable(branch().Tau1_1, "Tau1_1");
    AddVariable(branch().Tau2_1, "Tau2_1");
    AddVariable(branch().Tau3_1, "Tau3_1");
    AddVariable(branch().Tau21_1, "Tau21_1");
    AddVariable(branch().Tau32_1, "Tau32_1");
    AddVariable(branch().Tau1_2, "Tau1_2");
    AddVariable(branch().Tau2_2, "Tau2_2");
    AddVariable(branch().Tau3_2, "Tau3_2");
    AddVariable(branch().Tau21_2, "Tau21_2");
    AddVariable(branch().Tau32_2, "Tau32_2");
    if (!boost_) {
        AddVariable(branch().WBdt, "WBdt");
    }
    AddVariable(branch().BBdt, "BBdt");
    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

int TopHadronicTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Train");
    int had_top_id = TopHadronicId(event);
    Jets particles = event.Partons().GenParticles();
    Jets top_particles = copy_if_particle(particles, had_top_id);

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kInformation, "Jet size", jets.size());

    Jets top_jets;
    switch (tag) {
    case kSignal :
        top_jets = copy_if_particle(jets, had_top_id);
    case kBackground :
        top_jets = remove_if_particle(jets, had_top_id);
    }

    std::vector<Triplet> triplets;

    if (!boost_) {

        Print(kInformation, "3 Jets form one top" , triplets.size());
        std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets<WHadronicTagger>(event);
        triplets = Multiplets(doublets, jets, top_particles, pre_cuts, tag);

        Print(kInformation, "2 Jet form one top" , triplets.size());
        for (const auto & jet : jets) {
            Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, 2);

            Print(kInformation, "1 jet form one W" , triplets.size());
            std::vector<Doublet> piece_doublets = w_hadronic_reader_.Multiplet<WHadronicTagger>(jet);
            if (!piece_doublets.empty()) triplets = Join(triplets, Multiplets(piece_doublets.front(), jets, top_particles, pre_cuts, tag));
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
                std::vector<Doublet> piece_doublets = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2, piece_3);
                if (!piece_doublets.empty()) triplets = Join(triplets, Multiplets(piece_doublets.front(), piece_1, top_particles, pre_cuts, tag));
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
                std::vector<Doublet> sub_doublets = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2);
                for (const auto & doublet : sub_doublets) triplets = Join(triplets, Multiplets(doublet, piece_1, top_particles, pre_cuts, tag));
            }
        }
    }

    Print(kInformation, "1 jet forms one top", triplets.size());
    for (const auto & jet : top_jets) {
        Triplet triplet(jet);
        if (Problematic(triplet, top_particles, pre_cuts, tag)) continue;
        triplets.emplace_back(triplet);
    }

    for (auto & triplet : triplets) {
        Print(kError, "delta pt", triplet.DeltaPt() , triplets.size());
        triplet.SetTag(tag);
        NSubJettiness(triplet);
    }

    Print(kInformation, "Clean Entries");
    if (tag == kSignal && triplets.size() > top_particles.size()) {
        Print(kInformation, "Number of Jet Pairs", triplets.size());
        triplets = SortedByMassTo(triplets, Mass(TopId));
        triplets.erase(triplets.begin() + top_particles.size(), triplets.end());
    }
    return SaveEntries(triplets);

}

std::vector<Triplet> TopHadronicTagger::Multiplets(const std::vector<Doublet> &doublets, const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "triplets", doublets.size(), jets.size());
    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) triplets = Join(triplets, Multiplets(doublet, jets, particles, pre_cuts, tag));
    Print(kInformation, "triplets", triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const Doublet &doublet, const Jets &jets, const Jets &quarks, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "triplets", jets.size());
    std::vector<Triplet> triplets;
    for (const auto & jet : jets) {
        if (doublet.SingletJet1().delta_R(jet) < detector_geometry().JetConeSize) continue;
        if (doublet.SingletJet2().delta_R(jet) < detector_geometry().JetConeSize) continue;
        triplets = Join(triplets, Multiplets(doublet, jet, quarks, pre_cuts, tag));
    }
    Print(kInformation, "triplets", triplets.size());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const Doublet &doublet, const fastjet::PseudoJet &jet, const Jets &quarks, PreCuts &pre_cuts, const Tag tag)
{
    std::vector<Triplet> triplets;
    Triplet triplet(doublet, jet);
    if (Problematic(triplet, quarks, pre_cuts, tag)) return triplets;
    if (triplet.DeltaR() < detector_geometry().MinCellResolution)  return triplets;
    triplets.emplace_back(triplet);
    return triplets;
}

bool TopHadronicTagger::Problematic(const Triplet &triplet, const Jets &quarks, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Check for Problems");
    if (pre_cuts.PtLowerCut(TopId) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(TopId)) return true;
    if (pre_cuts.PtUpperCut(TopId) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(TopId)) return true;
    switch (tag) {
    case kSignal: {
        if (std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) return true;
        bool problematic = true;
        for (const auto & quark : quarks) if (triplet.Jet().delta_R(quark) < detector_geometry().JetConeSize) problematic = false;
        if (problematic) return true;
        break;
    }
    case kBackground :
        for (const auto & quark : quarks) if (triplet.Jet().delta_R(quark) < detector_geometry().JetConeSize) return true;
        break;
    }
    return false;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const std::vector<Doublet> &doublets, const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader)
{

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) triplets = Join(triplets, Multiplets(doublet, jets, pre_cuts, reader));

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const Doublet &doublet, const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader)
{

    std::vector<Triplet> triplets;
    for (const auto & jet : jets)  {
        if (jet == doublet.SingletJet1()) continue;
        if (jet == doublet.SingletJet2()) continue;
        Triplet triplet(doublet, jet);
        // if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
        triplets.emplace_back(Multiplet(triplet, pre_cuts, reader));
    }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
    return triplets;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(const Doublet &doublet, const fastjet::PseudoJet &jet, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector<Triplet> triplets;
    Triplet triplet(doublet, jet);
    triplets.emplace_back(Multiplet(triplet, pre_cuts, reader));
    return triplets;
}

Triplet TopHadronicTagger::Multiplet(Triplet &triplet, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    NSubJettiness(triplet);
    triplet.SetBdt(Bdt(triplet, reader));
    return triplet;
}

std::vector<Triplet> TopHadronicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Triplet> triplets;
    if (!boost_) {
        // 2 jets form a W
      std::vector<Doublet> doublets = w_hadronic_reader_.Multiplets<WHadronicTagger>(jets);
        // 3 jets form a top
        triplets = Multiplets(doublets, jets, pre_cuts, reader);

        // 2 jets form a top
        for (const auto & jet : jets) {
            // 2 subjets form a W
          std::vector<Doublet> piece_doublets = w_hadronic_reader_.Multiplet<WHadronicTagger>(jet);
            // 2 subjets and one jet form a top
            if (!piece_doublets.empty()) {
                std::vector<Triplet> piece_triplets = Multiplets(piece_doublets.front(), jets, pre_cuts, reader);
                triplets = Join(triplets, piece_triplets);
            }
        }

        // 1 jet forms a top
        for (const auto & jet : jets) {
            const int sub_jet_number = 3;
            Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
            if (pieces.size() < sub_jet_number) continue;
            // 2 subjets form a W
            for (std::size_t i = 0; i < pieces.size(); ++i) {
                auto piece_1 = pieces.at(i);
                auto piece_2 = pieces.at((i + 1) % sub_jet_number);
                auto piece_3 = pieces.at((i + 2) % sub_jet_number);
                std::vector<Doublet> piece_doublets = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2, piece_3);
                // 3 subjets form a top
                if (!piece_doublets.empty()) {
                    std::vector<Triplet> piece_triplets = Multiplets(piece_doublets.front(), piece_1, pre_cuts, reader);
                    triplets = Join(triplets, piece_triplets);
                }
            }
        }

        // 1 jet forms a top
        for (const auto & jet : jets) {
            const int sub_jet_number = 2;
            Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
            if (pieces.size() < sub_jet_number) continue;
            // 1 subjets form a W
            for (std::size_t i = 0; i < pieces.size(); ++i) {
                auto piece_1 = pieces.at(i);
                auto piece_2 = pieces.at((i + 1) % sub_jet_number);
                std::vector<Doublet> piece_doublets = w_hadronic_reader_.Multiplet<WHadronicTagger>(piece_2);
                // 2 subjets form a top
                if (!piece_doublets.empty()) {
                    std::vector<Triplet> piece_triplets = Multiplets(piece_doublets.front(), piece_1, pre_cuts, reader);
                    triplets = Join(triplets, piece_triplets);
                }
            }
        }

    }

    // 1 jet forms a top
    for (const auto & jet : jets) {
        // no subjets
        Triplet triplet(jet);
        triplets.emplace_back(Multiplet(triplet, pre_cuts, reader));
    }

    return ReduceResult(triplets);
}

void TopHadronicTagger::NSubJettiness(Triplet &triplet)
{
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.SingletJet() * 2));
    else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().SingletJet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.SingletJet(), triplet.Doublet().SingletJet1()), triplet.Doublet().SingletJet2())));
}

SubJettiness TopHadronicTagger::NSubJettiness(const fastjet::PseudoJet &jet)
{
    fastjet::contrib::OnePass_WTA_KT_Axes axis_mode_1;
    fastjet::contrib::OnePass_KT_Axes axis_mode_2;

    const double beta_1 = 1.0;
    const double beta_2 = 2.0;
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure_1(beta_1);
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure_2(beta_2);

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

    SubJettiness sub_jettiness;

    // calculate Nsubjettiness values (beta = 1.0)
    sub_jettiness.tau1_beta1 = n_subjettiness_1_1(jet);
    sub_jettiness.tau2_beta1 = n_subjettiness_2_1(jet);
    sub_jettiness.tau3_beta1 = n_subjettiness_3_1(jet);
    sub_jettiness.tau21_beta1 = n_subjettiness_21_1(jet);
    sub_jettiness.tau32_beta1 = n_subjettiness_32_1(jet);

    // calculate Nsubjettiness values (beta = 2.0)
    sub_jettiness.tau1_beta2 = n_subjettiness_1_2(jet);
    sub_jettiness.tau2_beta2 = n_subjettiness_2_2(jet);
    sub_jettiness.tau3_beta2 = n_subjettiness_3_2(jet);
    sub_jettiness.tau21_beta2 = n_subjettiness_21_2(jet);
    sub_jettiness.tau32_beta2 = n_subjettiness_32_2(jet);

    return sub_jettiness;

}

}
