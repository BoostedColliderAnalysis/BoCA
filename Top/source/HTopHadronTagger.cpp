# include "HTopHadronTagger.hh"
# include "Predicate.hh"

#include "fastjet/AreaDefinition.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"
#include "fastjet/contrib/NjettinessDefinition.hh"
#include "fastjet/SharedPtr.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/MeasureFunction.hh"



top::HTopHadronTagger::HTopHadronTagger()
{
// DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    DefineVariables();
}

void top::HTopHadronTagger::SetTagger(const analysis::BottomTagger &bottom_tagger, const analysis::WHadronicTagger &w_tagger)
{
    Print(kNotification, "Constructor");
    bottom_tagger_ = bottom_tagger;
//     WTagger = w_tagger;
    DefineVariables();
}

void top::HTopHadronTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");
    set_tagger_name("TopHadronic");
    TopWindow = (Mass(TopId) - Mass(WId)) / 2;
    WMassWindow = 20;
    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.BottomPt, "BottomPt");
    AddVariable(Branch.WPt, "WPt");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.Tau1_1, "Tau1_1");
    AddVariable(Branch.Tau2_1, "Tau2_1");
    AddVariable(Branch.Tau3_1, "Tau3_1");
    AddVariable(Branch.Tau21_1, "Tau21_1");
    AddVariable(Branch.Tau32_1, "Tau32_1");
    AddVariable(Branch.Tau1_2, "Tau1_2");
    AddVariable(Branch.Tau2_2, "Tau2_2");
    AddVariable(Branch.Tau3_2, "Tau3_2");
    AddVariable(Branch.Tau21_2, "Tau21_2");
    AddVariable(Branch.Tau32_2, "Tau32_2");

    AddVariable(Branch.MaxDisplacement, "MaxDisplacement");
    AddVariable(Branch.MeanDisplacement, "MeanDisplacement");
    AddVariable(Branch.SumDisplacement, "SumDisplacement");
    AddVariable(Branch.VertexMass, "VertexMass");
    AddVariable(Branch.Multipliticity, "Multipliticity");
    AddVariable(Branch.VertexDeltaR, "VertexDeltaR");
    AddVariable(Branch.VertexSpread, "VertexSpread");
    AddVariable(Branch.Spread, "Spread");
    AddVariable(Branch.EnergyFraction, "EnergyFraction");

    AddVariable(Branch.LeptonPt, "LeptonPt");
    AddVariable(Branch.WBdt, "WBdt");
    AddVariable(Branch.BBdt, "BBdt");
    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");
}

top::HTopHadronBranch top::HTopHadronTagger::GetBranch(const analysis::Triplet &triplet) const
{
    Print(kInformation, "Fill Top Tagger", triplet.Bdt());

    HTopHadronBranch top_hadron_branch;

    top_hadron_branch.Mass = triplet.Jet().m();
    top_hadron_branch.Rap = triplet.Jet().rap();
    top_hadron_branch.Phi = triplet.Jet().phi();
    top_hadron_branch.Pt = triplet.Jet().pt();
    top_hadron_branch.Ht = triplet.Ht();

    top_hadron_branch.BottomPt = triplet.singlet().pt();
    top_hadron_branch.WPt = triplet.doublet_jet().pt();

    top_hadron_branch.DeltaPt = triplet.DeltaPt();
    top_hadron_branch.DeltaHt = triplet.DeltaHt();
    top_hadron_branch.DeltaM = triplet.DeltaM();
    top_hadron_branch.DeltaR = triplet.DeltaR();
    top_hadron_branch.DeltaRap = triplet.DeltaRap();
    top_hadron_branch.DeltaPhi = triplet.DeltaPhi();

    top_hadron_branch.Tau1_1 = triplet.sub_jettiness().tau1_beta1;
    top_hadron_branch.Tau2_1 = triplet.sub_jettiness().tau2_beta1;
    top_hadron_branch.Tau3_1 = triplet.sub_jettiness().tau3_beta1;
    if (triplet.sub_jettiness().tau1_beta1 > 0) top_hadron_branch.Tau21_1 = triplet.sub_jettiness().tau21_beta1;
    if (triplet.sub_jettiness().tau2_beta1 > 0) top_hadron_branch.Tau32_1 = triplet.sub_jettiness().tau32_beta1;
    top_hadron_branch.Tau1_2 = triplet.sub_jettiness().tau1_beta2;
    top_hadron_branch.Tau2_2 = triplet.sub_jettiness().tau2_beta2;
    top_hadron_branch.Tau3_2 = triplet.sub_jettiness().tau3_beta2;
    if (triplet.sub_jettiness().tau1_beta2 > 0) top_hadron_branch.Tau21_2 = triplet.sub_jettiness().tau21_beta2;
    if (triplet.sub_jettiness().tau2_beta2 > 0) top_hadron_branch.Tau32_2 = triplet.sub_jettiness().tau32_beta2;

    if (triplet.Degenerate()) GetBottomInfo(top_hadron_branch, triplet.singlet() * 2);
    else if (triplet.doublet().Degenerate()) GetBottomInfo(top_hadron_branch, triplet.doublet().Singlet1() * 2);
    else GetBottomInfo(top_hadron_branch, triplet.singlet());

    top_hadron_branch.Bdt = triplet.Bdt();
    if (!triplet.Degenerate())top_hadron_branch.WBdt = triplet.doublet().Bdt();
    top_hadron_branch.BBdt = triplet.singlet().user_info<analysis::JetInfo>().Bdt();
    top_hadron_branch.Tag = triplet.Tag();

    top_hadron_branch.LeptonPt = triplet.LeptonPt;

    //     if (!(top_hadron_branch.VertexMass >= 0)) Print(kError, "Vertex Mass", top_hadron_branch.VertexMass);
    if (top_hadron_branch.MaxDisplacement < -3) Print(kError, "Max Displ", top_hadron_branch.MaxDisplacement);
    if (top_hadron_branch.MeanDisplacement < -3) Print(kError, "Mean Displ", top_hadron_branch.MeanDisplacement);
    return top_hadron_branch;
}

void top::HTopHadronTagger::GetBottomInfo(HTopHadronBranch &top_hadron_branch, const fastjet::PseudoJet jet) const
{

    top_hadron_branch.VertexMass = jet.user_info<analysis::JetInfo>().VertexMass();
    float MaxDisp = jet.user_info<analysis::JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) top_hadron_branch.MaxDisplacement = std::log(MaxDisp);
    else top_hadron_branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<analysis::JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) top_hadron_branch.MeanDisplacement = std::log(MeanDisp);
    else top_hadron_branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<analysis::JetInfo>().SumDisplacement();
    if (SumDisp > 0) top_hadron_branch.SumDisplacement = std::log(SumDisp);
    else top_hadron_branch.SumDisplacement = -3;
    top_hadron_branch.Multipliticity = jet.user_info<analysis::JetInfo>().VertexNumber();
//     top_hadronic_branch.DeltaR = GetDeltaR(jet);
    top_hadron_branch.Spread = GetSpread(jet);
    top_hadron_branch.VertexDeltaR = GetDeltaR(jet.user_info<analysis::JetInfo>().VertexJet());
    top_hadron_branch.VertexSpread = GetSpread(jet.user_info<analysis::JetInfo>().VertexJet());
    top_hadron_branch.EnergyFraction = jet.user_info<analysis::JetInfo>().VertexEnergy() / jet.e();

}


std::vector< top::HTopHadronBranch > top::HTopHadronTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag, float pre_cut)
{

    Print(kInformation, "Top Tags");

    const int TopNumber = 2;

//     int WHadId = WTagger.GetWHadId(event);
    analysis::Jets TopParticles = event.Partons().GenParticles();
//     int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongAbsParticle(TopParticles, TopId);
    fastjet::PseudoJet TopQuark;
    if (Tag == kSignal) {
        if (TopParticles.size() == TopNumber) TopQuark = TopParticles.front();
        else Print(kError, "Where is the Top?", TopParticles.size());
    }

    analysis::Jets jets = event.Hadrons().Jets();
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    std::vector<analysis::Doublet> doublets ;//= WTagger.GetBdt(jets, WReader);
    std::vector<analysis::Triplet> triplets;

    analysis::Jets Leptons = event.Leptons().leptons();

// // 3 Jets form one top
//     for (const auto & Jet : jets)  {
//         for (const auto & doublet : doublets) {
//           analysis::Triplet triplet(doublet, Jet);
//             if (Tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
//             if (Tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//             if (Tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//             if (Tag == HBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
//             if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//             triplets.emplace_back(triplet);
//         }
//     }
// // Print(kError, "Number of triplets 1", triplets.size());
//
// // 2 Jet form one top
//     for (const auto Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// // 1 jet form one W
//         std::vector<analysis::Doublet> Piecesdoublets = WTagger.GetBdt(Pieces, WReader);
//         for (const auto & doublet : Piecesdoublets)
//             for (const auto & Jet2 : jets)  {
//                 if (Jet == Jet2) continue;
//                 analysis::Triplet triplet(doublet, Jet2);
//                 if (Tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
//                 if (Tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//                 if (Tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//                 if (Tag == HBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
//                 if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                 triplets.emplace_back(triplet);
//             }
//     }


// 1 Jet forms one top
    for (const auto Jet : jets)  {
      analysis::Jets Pieces = SubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
// 2 subjets form one W
                analysis::Doublet doublet(Piece1, Piece2);
//                 doublet = WTagger.GetBdt(doublet, WReader);
                if (std::abs(doublet.Jet().m() - Mass(WId)) > WMassWindow) continue;
                for (const auto & Piece3 : Pieces) {
                    if (Piece3 == doublet.Singlet1()) continue;
                    if (Piece3 == doublet.Singlet2()) continue;
                    analysis::Triplet triplet(doublet, Piece3);
                    if (Tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                    if (Tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
//                     if (Tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
//                     if (Tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
                    if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                    triplets.emplace_back(triplet);
                }
            }
        }
    }

// // 1 Jet forms one top
//     for (const auto Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         for (const auto & Piece1 : Pieces) {
// // 1 subjets forms one W
//             analysis::Doublet doublet(Piece1);
//             doublet = WTagger.GetBdt(doublet, WReader);
//             if (std::abs(doublet.Jet().m() - Mass(WId)) > WMassWindow) continue;
//             for (const auto & Piece3 : Pieces) {
//                 if (Piece3 == doublet.Singlet1()) continue;
//                 if (Piece3 == doublet.Singlet2()) continue;
//                 analysis::Triplet triplet(doublet, Piece3);
//                 if (Tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//                 if (Tag == HBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
// //                 if (Tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
// //                 if (Tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//                 if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                 triplets.emplace_back(triplet);
//             }
//         }
//     }

// // 1 Jet forms one top
//     for (const auto Jet : jets)  {
//         analysis::Triplet triplet(Jet);
//         if (Tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//         if (Tag == HBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
// //         if (Tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
// //         if (Tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
//         for (const auto Lepton : Leptons) if (triplet.Jet().delta_R(Lepton) && Lepton.pt() > triplet.LeptonPt) triplet.LeptonPt = Lepton.pt();
//         triplets.emplace_back(triplet);
//     }


    if (triplets.size() > TopNumber) {
        Print(kInformation, "Number of Jet Pairs", triplets.size());
        triplets = SortedByMassTo(triplets, Mass(TopId));
        switch (Tag) {
        case kSignal :
            triplets.erase(triplets.begin() + TopNumber, triplets.end()); // FIXME assuming maximal one hadronic top
            break;
        case kBackground :
          triplets = SortedByPt(triplets);
//             std::sort(triplets.begin(), triplets.end(), analysis::MaxPt());
            triplets.erase(triplets.begin() + TopNumber, triplets.end()); // FIXME assuming maximal one hadronic top
//             triplets.erase(triplets.begin()); // FIXME assuming maximal one hadronic top
            break;
        }
    }

    std::vector<HTopHadronBranch> HadronicTopBranches;
    for (auto & triplet : triplets) {
        triplet.SetTag(Tag);
        NSubJettiness(triplet);
        HadronicTopBranches.emplace_back(GetBranch(triplet));
    }

    return HadronicTopBranches;

}


analysis::Object::Tag top::HTopHadronTagger::GetTag(const analysis::Triplet &)
{
    Print(kInformation, "Triple Tag");
}

analysis::Object::Tag top::HTopHadronTagger::GetTag(const fastjet::PseudoJet &)
{
    Print(kInformation, "Jet Tag");

// JetInfo jet_info = Jet.user_info<JetInfo>();
// jet_info.ExtractFraction(TopId);
//
// if (jet_info.MaximalId() != TopId) return HBackground;
    return kSignal;
}

std::vector<analysis::Triplet> top::HTopHadronTagger::GetBdt(const std::vector< analysis::Doublet > &doublets, const analysis::Jets &jets, const analysis::Reader &TopHadronicReader)
{

    std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets)
        for (const auto & Jet : jets)  {
            if (Jet == doublet.Singlet1()) continue;
            if (Jet == doublet.Singlet2()) continue;
            analysis::Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
            // if (triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
            NSubJettiness(triplet);
            Branch = GetBranch(triplet);
            triplet.SetBdt(TopHadronicReader.Bdt());
            triplets.emplace_back(triplet);
        }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
    return triplets;
}


analysis::Triplet top::HTopHadronTagger::GetBdt(analysis::Triplet &triplet, const analysis::Reader &TopHadronicReader)
{
    NSubJettiness(triplet);
    Branch = GetBranch(triplet);
    triplet.SetBdt(TopHadronicReader.Bdt());
    return triplet;
}


std::vector<analysis::Triplet> top::HTopHadronTagger::GetBdt(const analysis::Jets &jets, const analysis::Jets &Leptons, const analysis::Reader &TopHadronicReader, analysis::WHadronicTagger &WTagger, analysis::Reader &WReader, analysis::BottomTagger &BottomTagger, analysis::Reader &BottomReader)
{
    std::vector<analysis::Triplet> triplets;

// // 2 jets form a W
//     std::vector<analysis::Doublet> doublets = WTagger.GetPairBdt(jets, WReader);
// // 3 jets form a top
//     std::vector<analysis::Triplet> triplets = GetBdt(doublets, jets, TopHadronicReader);
//
// // 2 jets form a top
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// // 2 subjets form a W
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetPairBdt(Pieces, WReader);
// // 2 subjets and one jet form a top
//         std::vector<analysis::Triplet> Piecetriplets = GetBdt(Piecedoublets, jets, TopHadronicReader);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }

// 1 jet forms a top
    for (const auto & Jet : jets)  {
      analysis::Jets Pieces = SubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 2 subjets form a W
        std::vector<analysis::Doublet> Piecedoublets ;//= WTagger.Multiplets(Pieces, WReader);
// 3 subjets form a top
        std::vector<analysis::Triplet> Piecetriplets = GetBdt(Piecedoublets, Pieces, TopHadronicReader);
        triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
    }

// // 1 jet forms a top
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// // 1 subjets form a W
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetSingletBdt(Pieces, WReader);
// // 2 subjets form a top
//         std::vector<analysis::Triplet> Piecetriplets = GetBdt(Piecedoublets, Pieces, TopHadronicReader);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
// // 1 jet forms a top
//     for (const auto & Jet : jets)  {
// // no supbjets
//         analysis::Triplet triplet(Jet);
//         for (const auto Lepton : Leptons) if (triplet.Jet().delta_R(Lepton) && Lepton.pt() > triplet.LeptonPt) triplet.LeptonPt = Lepton.pt();
//
// //         NSubJettiness(triplet);
// //         if (std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue;
//         Branch = GetBranch(triplet);
// //         Print(kError,"Disp",Branch.MeanDisplacement);
// //         Print(kError,"Mass",Branch.VertexMass);
//         triplet.SetBdt(TopHadronicReader.Bdt());
// //         Print(kError,"Bdt",triplet.Bdt());
//
//         triplets.emplace_back(triplet);
//     }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());

    return triplets;

}



float top::HTopHadronTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(kDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float top::HTopHadronTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}


void top::HTopHadronTagger::NSubJettiness(analysis::Triplet &triplet)
{
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.singlet() * 2));
    else if (triplet.doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.doublet().Singlet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.singlet(), triplet.doublet().Singlet1()), triplet.doublet().Singlet2())));
}


analysis::SubJettiness top::HTopHadronTagger::NSubJettiness(const fastjet::PseudoJet &jet)
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


    analysis::SubJettiness sub_jettiness;

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
