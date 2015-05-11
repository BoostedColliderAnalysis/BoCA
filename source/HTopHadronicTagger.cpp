# include "HTopHadronicTagger.hh"

#include "fastjet/AreaDefinition.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"
#include "fastjet/contrib/NjettinessDefinition.hh"
#include "fastjet/SharedPtr.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/MeasureFunction.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger()
{
// DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopHadronic");
    top_mass_window_ = (TopMass - WMass) / 2;
    w_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_hadronic_reader_.set_tagger(w_hadronic_tagger_);
    DefineVariables();
}

void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");
    ClearVectors();
//     Boost = true; // be carefull with this one!!

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.WPt, "WPt");

    if (!boost_) {
        AddVariable(branch_.DeltaPt, "DeltaPt");
        AddVariable(branch_.DeltaHt, "DeltaHt");
        AddVariable(branch_.DeltaM, "DeltaM");
        AddVariable(branch_.DeltaPhi, "DeltaPhi");
        AddVariable(branch_.DeltaRap, "DeltaRap");
        AddVariable(branch_.DeltaR, "DeltaR");
    }

    AddVariable(branch_.Tau1_1, "Tau1_1");
    AddVariable(branch_.Tau2_1, "Tau2_1");
    AddVariable(branch_.Tau3_1, "Tau3_1");
    AddVariable(branch_.Tau21_1, "Tau21_1");
    AddVariable(branch_.Tau32_1, "Tau32_1");
    AddVariable(branch_.Tau1_2, "Tau1_2");
    AddVariable(branch_.Tau2_2, "Tau2_2");
    AddVariable(branch_.Tau3_2, "Tau3_2");
    AddVariable(branch_.Tau21_2, "Tau21_2");
    AddVariable(branch_.Tau32_2, "Tau32_2");


    AddVariable(branch_.VertexMass, "VertexMass");
    AddVariable(branch_.MaxDisplacement, "MaxDisplacement");
    AddVariable(branch_.MeanDisplacement, "MeanDisplacement");
    AddVariable(branch_.SumDisplacement, "SumDisplacement");
    AddVariable(branch_.Multipliticity, "Multipliticity");
    AddVariable(branch_.Spread, "Spread");
    AddVariable(branch_.VertexDeltaR, "VertexDeltaR");
    AddVariable(branch_.VertexSpread, "VertexSpread");
    AddVariable(branch_.EnergyFraction, "EnergyFraction");


    if (!boost_) {
        AddVariable(branch_.WBdt, "WBdt");
    }
    AddVariable(branch_.BBdt, "BBdt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

TopHadronicBranch hanalysis::HTopHadronicTagger::GetBranch(const hanalysis::Triplet &triplet) const
{
    Print(kInformation, "Fill Top Tagger", triplet.Bdt());

    TopHadronicBranch branch;

    branch.Mass = triplet.Jet().m();
    branch.Rap = triplet.Jet().rap();
    branch.Phi = triplet.Jet().phi();
    branch.Pt = triplet.Jet().pt();
    branch.Ht = triplet.Ht();

    branch.BottomPt = triplet.Singlet().pt();
    branch.WPt = triplet.doublet_jet().pt();

    branch.DeltaPt = triplet.DeltaPt();
    branch.DeltaHt = triplet.DeltaHt();
    branch.DeltaM = triplet.DeltaM();
    branch.DeltaR = triplet.DeltaR();
    branch.DeltaRap = triplet.DeltaRap();
    branch.DeltaPhi = triplet.DeltaPhi();

    branch.Tau1_1 = triplet.sub_jettiness().tau1_beta1;
    branch.Tau2_1 = triplet.sub_jettiness().tau2_beta1;
    branch.Tau3_1 = triplet.sub_jettiness().tau3_beta1;
    if (triplet.sub_jettiness().tau1_beta1 > 0) branch.Tau21_1 = triplet.sub_jettiness().tau21_beta1;
    if (triplet.sub_jettiness().tau2_beta1 > 0) branch.Tau32_1 = triplet.sub_jettiness().tau32_beta1;
    branch.Tau1_2 = triplet.sub_jettiness().tau1_beta2;
    branch.Tau2_2 = triplet.sub_jettiness().tau2_beta2;
    branch.Tau3_2 = triplet.sub_jettiness().tau3_beta2;
    if (triplet.sub_jettiness().tau1_beta2 > 0) branch.Tau21_2 = triplet.sub_jettiness().tau21_beta2;
    if (triplet.sub_jettiness().tau2_beta2 > 0) branch.Tau32_2 = triplet.sub_jettiness().tau32_beta2;

    if (triplet.Degenerate()) GetBottomInfo(branch, triplet.Singlet() * 2);
    else if (triplet.doublet().Degenerate()) GetBottomInfo(branch, triplet.doublet().Singlet1() * 2);
    else GetBottomInfo(branch, triplet.Singlet());

    branch.Bdt = triplet.Bdt();
    if (!triplet.Degenerate())branch.WBdt = triplet.doublet().Bdt();
    branch.BBdt = triplet.Singlet().user_info<JetInfo>().Bdt();
    branch.Tag = triplet.Tag();
    return branch;
}

void hanalysis::HTopHadronicTagger::GetBottomInfo(TopHadronicBranch &branch, const fastjet::PseudoJet jet) const
{

    branch.VertexMass = jet.user_info<hanalysis::JetInfo>().VertexMass();
    float MaxDisp = jet.user_info<hanalysis::JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) branch.MaxDisplacement = std::log10(MaxDisp);
    else branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<hanalysis::JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) branch.MeanDisplacement = std::log10(MeanDisp);
    else branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<hanalysis::JetInfo>().SumDisplacement();
    if (SumDisp > 0) branch.SumDisplacement = std::log10(SumDisp);
    else branch.SumDisplacement = -3;
    branch.Multipliticity = jet.user_info<hanalysis::JetInfo>().VertexNumber();
    //     top_hadronic_branch.DeltaR = bottom_tagger_.GetDeltaR(jet);
    branch.Spread = bottom_tagger_.GetSpread(jet);
    branch.VertexDeltaR = bottom_tagger_.GetDeltaR(jet.user_info<hanalysis::JetInfo>().VertexJet());
    branch.VertexSpread = bottom_tagger_.GetSpread(jet.user_info<hanalysis::JetInfo>().VertexJet());
    branch.EnergyFraction = jet.user_info<hanalysis::JetInfo>().VertexEnergy() / jet.e();
}


int hanalysis::HTopHadronicTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{

    Print(kInformation, "Get Top Tags");

    int w_had_id = w_hadronic_tagger_.GetWHadId(event);
    Jets top_particles = event.GetParticles()->Generator();
    int had_top_id = sgn(w_had_id) * std::abs(TopId);
    top_particles = RemoveIfWrongParticle(top_particles, had_top_id);
    fastjet::PseudoJet top_quark;
    if (top_particles.size() == 1) top_quark = top_particles.front();
    else Print(kError, "Where is the Top?", top_particles.size());

    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());

    std::vector<hanalysis::Triplet> triplets;

    if (!boost_) {

// 3 Jets form one top
//         for (const auto & jet : jets) {
//             for (const auto & doublet : doublets) {
//                 Triplet triplet(doublet, jet);
//                 if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
//                 if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//                 if (tag == kSignal && triplet.Jet().delta_R(top_quark) > detector_geometry().JetConeSize) continue;
//                 if (tag == kBackground && triplet.Jet().delta_R(top_quark) < detector_geometry().JetConeSize) continue;
//                 if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                 triplets.emplace_back(triplet);
//             }
//         }

        std::vector<hanalysis::Doublet> doublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublets(event, w_hadronic_reader_.reader());
        std::vector<hanalysis::Triplet> triplets = GetTriplets(doublets, jets, top_quark, tag);


// 2 Jet form one top
        for (const auto jet : jets) {
            Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 2);


//             Jets Pieces = GetSubJets(Jet, 2);
//             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 1 jet form one W
//             std::vector<hanalysis::Doublet> Piecesdoublets = w_hadronic_tagger_.GetBdt(pieces, w_hadronic_reader_);
            std::vector<hanalysis::Doublet> Piecesdoublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublet(jet, bottom_reader_.reader());
            triplets = JoinVectors(triplets, GetTriplets(Piecesdoublets, jets, top_quark, tag));
//             for (const auto & doublet : Piecesdoublets)
//                 for (const auto & Jet2 : jets) {
//                     if (Jet == Jet2) continue;
//                     Triplet triplet(doublet, Jet2);
//                     if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
//                     if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//                     if (tag == kSignal && triplet.Jet().delta_R(top_quark) > detector_geometry().JetConeSize) continue;
//                     if (tag == kBackground && triplet.Jet().delta_R(top_quark) < detector_geometry().JetConeSize) continue;
//                     if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                     triplets.emplace_back(triplet);
//                 }
        }


// 1 Jet forms one top
        for (const auto jet : jets) {
            Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 3);
//             Jets Pieces = GetSubJets(Jet, 3);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
            for (const auto & piece_1 : pieces) {
                for (const auto & piece_2 : pieces) {
// 2 subjets form one W
//                   hanalysis::Doublet doublet(piece1, piece2);
                    std::vector<hanalysis::Doublet> doublet = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublet(piece_1, piece_2, bottom_reader_.reader());
//                     doublet = w_hadronic_tagger_.GetBdt(doublet, w_hadronic_reader_);
                    for (const auto doublet : doublets) {
                        if (std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
                        for (const auto & piece_3 : pieces) {
                            if (piece_3 == doublet.Singlet1()) continue;
                            if (piece_3 == doublet.Singlet2()) continue;
                            Triplet triplet(doublet, piece_3);
//                         if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
//                         if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//                         if (tag == kSignal && triplet.Jet().delta_R(top_quark) > detector_geometry().JetConeSize) continue;
//                         if (tag == kBackground && triplet.Jet().delta_R(top_quark) < detector_geometry().JetConeSize) continue;
//                         if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                         triplets.emplace_back(triplet);
                            triplets = JoinVectors(triplets, GetTriplets(doublet, piece_3, top_quark, tag));
                        }
                    }
                }
            }
        }

// 1 Jet forms one top
        for (const auto jet : jets) {
//             Jets pieces = GetSubJets(jet, 2);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
            Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 2);
            for (const auto & piece_1 : pieces) {
// 1 subjets forms one W
//                 hanalysis::Doublet doublet(piece_1);
//                 doublet = w_hadronic_tagger_.GetBdt(doublet, w_hadronic_reader_);
                std::vector<hanalysis::Doublet> doublet = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublet(piece_1, bottom_reader_.reader());
                for (const auto doublet : doublets) {
                    if (std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
                    for (const auto & piece_3 : pieces) {
                        if (piece_3 == doublet.Singlet1()) continue;
                        if (piece_3 == doublet.Singlet2()) continue;
//                     Triplet triplet(doublet, piece_3);
//                     if (tag == kSignal && triplet.Jet().delta_R(top_quark) > detector_geometry().JetConeSize) continue;
//                     if (tag == kBackground && triplet.Jet().delta_R(top_quark) < detector_geometry().JetConeSize) continue;
//                     if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
//                     if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//                     if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                        //                     triplets.emplace_back(triplet);
                        triplets = JoinVectors(triplets, GetTriplets(doublet, piece_3, top_quark, tag));
                    }
                }
            }
        }
    }

// 1 Jet forms one top
    for (const auto Jet : jets) {
        Triplet triplet(Jet);
        if (Problematic(triplet, top_quark, tag)) continue;
        triplets.emplace_back(triplet);
    }

    if (triplets.size() > 1) {
        Print(kInformation, "Number of Jet Pairs", triplets.size());
        triplets = SortByMassTo(triplets, TopMass);
        switch (tag) {
        case kSignal :
            triplets.erase(triplets.begin() + 1, triplets.end()); // FIXME assuming maximal one hadronic top
            break;
// case HBackground :
// triplets.erase(triplets.begin()); // FIXME assuming maximal one hadronic top
// break;
        }
    }

    std::vector<TopHadronicBranch> HadronicTopBranches;
    for (auto & triplet : triplets) {
        triplet.SetTag(tag);
        NSubJettiness(triplet);
    }

    return SaveEntries(triplets);

}

std::vector<hanalysis::Triplet> hanalysis::HTopHadronicTagger::GetTriplets(const std::vector<Doublet> &doublets, const std::vector<fastjet::PseudoJet> &jets, const fastjet::PseudoJet &quark, const Tag tag)
{
    std::vector<hanalysis::Triplet> triplets;
    for (const auto & jet : jets) {
        for (const auto & doublet : doublets) {
            if (doublet.Singlet1().delta_R(jet) < detector_geometry().JetConeSize) continue;
            if (doublet.Singlet2().delta_R(jet) < detector_geometry().JetConeSize) continue;
            triplets = JoinVectors(triplets, GetTriplets(doublet, jet, quark, tag));
        }
    }
    return triplets;
}

std::vector<hanalysis::Triplet> hanalysis::HTopHadronicTagger::GetTriplets(const Doublet &doublet, const fastjet::PseudoJet &jet, const fastjet::PseudoJet &quark, const Tag tag)
{
    std::vector<hanalysis::Triplet> triplets;
    Triplet triplet(doublet, jet);
    if (Problematic(triplet, quark, tag)) return triplets;
    if (triplet.DeltaR() < detector_geometry().MinCellResolution)  return triplets;
    triplets.emplace_back(triplet);
    return triplets;
}

bool hanalysis::HTopHadronicTagger::Problematic(const Triplet &triplet, const fastjet::PseudoJet &quark, const Tag tag)
{
    float pre_cut = 0;
    if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) return true;
    if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2)  return true;
    if (tag == kSignal && triplet.Jet().delta_R(quark) > detector_geometry().JetConeSize)  return true;
    if (tag == kBackground && triplet.Jet().delta_R(quark) < detector_geometry().JetConeSize)  return true;
    return false;
}

std::vector<hanalysis::Triplet> hanalysis::HTopHadronicTagger::GetBdt(const std::vector<Doublet> &doublets, const Jets &jets, const TMVA::Reader &reader)
{

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets)
        for (const auto & Jet : jets)  {
            if (Jet == doublet.Singlet1()) continue;
            if (Jet == doublet.Singlet2()) continue;
            Triplet triplet(doublet, Jet);
            if (std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
            // if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
            NSubJettiness(triplet);
            branch_ = GetBranch(triplet);
            triplet.SetBdt(Bdt(reader));
            triplets.emplace_back(triplet);
        }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
    return triplets;
}


hanalysis::Triplet hanalysis::HTopHadronicTagger::GetBdt(Triplet &triplet, const Reader &TopHadronicReader)
{
    NSubJettiness(triplet);
    branch_ = GetBranch(triplet);
    triplet.SetBdt(TopHadronicReader.Bdt());
    return triplet;
}


std::vector<hanalysis::Triplet> hanalysis::HTopHadronicTagger::GetTriplets(HEvent &event, const TMVA::Reader &reader)
{
    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<hanalysis::Triplet> triplets;
    if (!boost_) {


// 2 jets form a W
      std::vector<hanalysis::Doublet> doublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetJetDoublets(jets, w_hadronic_reader_.reader());
// 3 jets form a top
        triplets = GetBdt(doublets, jets, reader);

// 2 jets form a top
        for (const auto & Jet : jets) {
            Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubBdt(jets, bottom_reader_.reader(), 2);
//             Jets Pieces = GetSubJets(Jet, 2);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 2 subjets form a W
            std::vector<hanalysis::Doublet> Piecedoublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetJetDoublets(pieces, w_hadronic_reader_.reader());
//             std::vector<hanalysis::Doublet> Piecedoublets = WTagger.GetPairBdt(pieces, WReader);
// 2 subjets and one jet form a top
            std::vector<hanalysis::Triplet> Piecetriplets = GetBdt(Piecedoublets, jets, reader);
            triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
        }

// 1 jet forms a top
        for (const auto & jet : jets) {
//           Jets Pieces = GetSubJets(Jet, 3);
          Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 3);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 2 subjets form a W
//             std::vector<hanalysis::Doublet> Piecedoublets = WTagger.GetPairBdt(Pieces, WReader);
            std::vector<hanalysis::Doublet> Piecedoublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetJetDoublets(pieces, w_hadronic_reader_.reader());
// 3 subjets form a top
            std::vector<hanalysis::Triplet> Piecetriplets = GetBdt(Piecedoublets, pieces, reader);
            triplets = JoinVectors(triplets,Piecetriplets);
        }

// 1 jet forms a top
        for (const auto & jet : jets) {
//           Jets Pieces = GetSubJets(Jet, 2);
          Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 2);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 1 subjets form a W
//           std::vector<hanalysis::Doublet> Piecedoublets = WTagger.GetSingletBdt(pieces, WReader);
          std::vector<hanalysis::Doublet> Piecedoublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetJetDoublets(pieces, w_hadronic_reader_.reader());
// 2 subjets form a top
            std::vector<hanalysis::Triplet> Piecetriplets = GetBdt(Piecedoublets, pieces, reader);
//             triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
            triplets = JoinVectors(triplets,Piecetriplets);
        }

    }

// 1 jet forms a top
    for (const auto & Jet : jets) {
// no supbjets
        Triplet triplet(Jet);
        NSubJettiness(triplet);
//         if (std::abs(triplet.Jet().m() - TopMass) > TopWindow) continue; // seems to be a really bad idea; no more higgses left
        branch_ = GetBranch(triplet);
        triplet.SetBdt(Bdt(reader));
        triplets.emplace_back(triplet);
    }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());

    return triplets;

}


void hanalysis::HTopHadronicTagger::NSubJettiness(Triplet &triplet)
{
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Singlet() * 2));
    else if (triplet.doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.doublet().Singlet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.Singlet(), triplet.doublet().Singlet1()), triplet.doublet().Singlet2())));
}


SubJettiness hanalysis::HTopHadronicTagger::NSubJettiness(const fastjet::PseudoJet &jet)
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


