# include "HTopHadronTagger.hh"

#include "fastjet/AreaDefinition.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"
#include "fastjet/contrib/NjettinessDefinition.hh"
#include "fastjet/SharedPtr.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/MeasureFunction.hh"



HTopHadronTagger::HTopHadronTagger()
{
// DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void HTopHadronTagger::SetTagger(const hanalysis::BottomTagger &bottom_tagger, const hanalysis::HWHadronicTagger &w_tagger)
{
    Print(HNotification, "Constructor");
    bottom_tagger_ = bottom_tagger;
    WTagger = w_tagger;
    DefineVariables();
}

void HTopHadronTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    set_tagger_name("TopHadronic");
    TopWindow = (TopMass - WMass) / 2;
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

HTopHadronBranch HTopHadronTagger::GetBranch(const hanalysis::HTriplet &triplet) const
{
    Print(HInformation, "Fill Top Tagger", triplet.Bdt());

    HTopHadronBranch top_hadron_branch;

    top_hadron_branch.Mass = triplet.Jet().m();
    top_hadron_branch.Rap = triplet.Jet().rap();
    top_hadron_branch.Phi = triplet.Jet().phi();
    top_hadron_branch.Pt = triplet.Jet().pt();
    top_hadron_branch.Ht = triplet.Ht();

    top_hadron_branch.BottomPt = triplet.Singlet().pt();
    top_hadron_branch.WPt = triplet.DoubletJet().pt();

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

    if (triplet.Degenerate()) GetBottomInfo(top_hadron_branch, triplet.Singlet() * 2);
    else if (triplet.Doublet().Degenerate()) GetBottomInfo(top_hadron_branch, triplet.Doublet().Singlet1() * 2);
    else GetBottomInfo(top_hadron_branch, triplet.Singlet());

    top_hadron_branch.Bdt = triplet.Bdt();
    if (!triplet.Degenerate())top_hadron_branch.WBdt = triplet.Doublet().Bdt();
    top_hadron_branch.BBdt = triplet.Singlet().user_info<hanalysis::HJetInfo>().Bdt();
    top_hadron_branch.Tag = triplet.Tag();

    top_hadron_branch.LeptonPt = triplet.LeptonPt;

    //     if (!(top_hadron_branch.VertexMass >= 0)) Print(HError, "Vertex Mass", top_hadron_branch.VertexMass);
    if (top_hadron_branch.MaxDisplacement < -3) Print(HError, "Max Displ", top_hadron_branch.MaxDisplacement);
    if (top_hadron_branch.MeanDisplacement < -3) Print(HError, "Mean Displ", top_hadron_branch.MeanDisplacement);
    return top_hadron_branch;
}

void HTopHadronTagger::GetBottomInfo(HTopHadronBranch &top_hadron_branch, const fastjet::PseudoJet jet) const
{

    top_hadron_branch.VertexMass = jet.user_info<hanalysis::HJetInfo>().VertexMass();
    float MaxDisp = jet.user_info<hanalysis::HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) top_hadron_branch.MaxDisplacement = std::log(MaxDisp);
    else top_hadron_branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) top_hadron_branch.MeanDisplacement = std::log(MeanDisp);
    else top_hadron_branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) top_hadron_branch.SumDisplacement = std::log(SumDisp);
    else top_hadron_branch.SumDisplacement = -3;
    top_hadron_branch.Multipliticity = jet.user_info<hanalysis::HJetInfo>().VertexNumber();
//     TopHadronicBranch.DeltaR = GetDeltaR(jet);
    top_hadron_branch.Spread = GetSpread(jet);
    top_hadron_branch.VertexDeltaR = GetDeltaR(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    top_hadron_branch.VertexSpread = GetSpread(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    top_hadron_branch.EnergyFraction = jet.user_info<hanalysis::HJetInfo>().VertexEnergy() / jet.e();

}


std::vector< HTopHadronBranch > HTopHadronTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, float pre_cut)
{

    Print(HInformation, "Get Top Tags");

    const int TopNumber = 2;

//     int WHadId = WTagger.GetWHadId(Event);
    Jets TopParticles = Event.GetParticles()->Generator();
//     int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongAbsParticle(TopParticles, TopId);
    fastjet::PseudoJet TopQuark;
    if (Tag == kSignal) {
        if (TopParticles.size() == TopNumber) TopQuark = TopParticles.front();
        else Print(HError, "Where is the Top?", TopParticles.size());
    }

    Jets jets = GetJets(Event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    std::vector<hanalysis::HDoublet> Doublets = WTagger.GetBdt(jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets;

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();

// // 3 Jets form one top
//     for (const auto & Jet : jets)  {
//         for (const auto & Doublet : Doublets) {
//           hanalysis::HTriplet Triplet(Doublet, Jet);
//             if (Tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//             if (Tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
//             if (Tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//             if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
//             if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//             Triplets.emplace_back(Triplet);
//         }
//     }
// // Print(HError, "Number of Triplets 1", Triplets.size());
//
// // 2 Jet form one top
//     for (const auto Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// // 1 jet form one W
//         std::vector<hanalysis::HDoublet> PiecesDoublets = WTagger.GetBdt(Pieces, WReader);
//         for (const auto & Doublet : PiecesDoublets)
//             for (const auto & Jet2 : jets)  {
//                 if (Jet == Jet2) continue;
//                 hanalysis::HTriplet Triplet(Doublet, Jet2);
//                 if (Tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//                 if (Tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
//                 if (Tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//                 if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
//                 if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                 Triplets.emplace_back(Triplet);
//             }
//     }


// 1 Jet forms one top
    for (const auto Jet : jets)  {
        Jets Pieces = GetSubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
// 2 subjets form one W
                hanalysis::HDoublet Doublet(Piece1, Piece2);
                Doublet = WTagger.GetBdt(Doublet, WReader);
                if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                for (const auto & Piece3 : Pieces) {
                    if (Piece3 == Doublet.Singlet1()) continue;
                    if (Piece3 == Doublet.Singlet2()) continue;
                    hanalysis::HTriplet Triplet(Doublet, Piece3);
                    if (Tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                    if (Tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
//                     if (Tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//                     if (Tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                    if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                    Triplets.emplace_back(Triplet);
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
//             hanalysis::HDoublet Doublet(Piece1);
//             Doublet = WTagger.GetBdt(Doublet, WReader);
//             if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//             for (const auto & Piece3 : Pieces) {
//                 if (Piece3 == Doublet.Singlet1()) continue;
//                 if (Piece3 == Doublet.Singlet2()) continue;
//                 hanalysis::HTriplet Triplet(Doublet, Piece3);
//                 if (Tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//                 if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
// //                 if (Tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
// //                 if (Tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
//                 if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
//                 Triplets.emplace_back(Triplet);
//             }
//         }
//     }

// // 1 Jet forms one top
//     for (const auto Jet : jets)  {
//         hanalysis::HTriplet Triplet(Jet);
//         if (Tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
//         if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
// //         if (Tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
// //         if (Tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
//         for (const auto Lepton : Leptons) if (Triplet.Jet().delta_R(Lepton) && Lepton.pt() > Triplet.LeptonPt) Triplet.LeptonPt = Lepton.pt();
//         Triplets.emplace_back(Triplet);
//     }


    if (Triplets.size() > TopNumber) {
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        Triplets = SortByMassTo(Triplets, TopMass);
        switch (Tag) {
        case kSignal :
            Triplets.erase(Triplets.begin() + TopNumber, Triplets.end()); // FIXME assuming maximal one hadronic top
            break;
        case kBackground :
            std::sort(Triplets.begin(), Triplets.end(), MaxPt());
            Triplets.erase(Triplets.begin() + TopNumber, Triplets.end()); // FIXME assuming maximal one hadronic top
//             Triplets.erase(Triplets.begin()); // FIXME assuming maximal one hadronic top
            break;
        }
    }

    std::vector<HTopHadronBranch> HadronicTopBranches;
    for (auto & Triplet : Triplets) {
        Triplet.SetTag(Tag);
        NSubJettiness(Triplet);
        HadronicTopBranches.emplace_back(GetBranch(Triplet));
    }

    return HadronicTopBranches;

}


hanalysis::HObject::Tag HTopHadronTagger::GetTag(const hanalysis::HTriplet &)
{
    Print(HInformation, "Get Triple Tag");
}

hanalysis::HObject::Tag HTopHadronTagger::GetTag(const fastjet::PseudoJet &)
{
    Print(HInformation, "Get Jet Tag");

// HJetInfo JetInfo = Jet.user_info<HJetInfo>();
// JetInfo.ExtractFraction(TopId);
//
// if (JetInfo.MaximalId() != TopId) return HBackground;
    return kSignal;
}

std::vector<hanalysis::HTriplet> HTopHadronTagger::GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const Jets &jets, const hanalysis::Reader &TopHadronicReader)
{

    std::vector<hanalysis::HTriplet> Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : jets)  {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            hanalysis::HTriplet Triplet(Doublet, Jet);
//             if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            // if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
            NSubJettiness(Triplet);
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader.Bdt());
            Triplets.emplace_back(Triplet);
        }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());
    return Triplets;
}


hanalysis::HTriplet HTopHadronTagger::GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::Reader &TopHadronicReader)
{
    NSubJettiness(Triplet);
    Branch = GetBranch(Triplet);
    Triplet.SetBdt(TopHadronicReader.Bdt());
    return Triplet;
}


std::vector<hanalysis::HTriplet> HTopHadronTagger::GetBdt(const Jets &jets, const Jets &Leptons, const hanalysis::Reader &TopHadronicReader, hanalysis::HWHadronicTagger &WTagger, hanalysis::Reader &WReader, hanalysis::BottomTagger &BottomTagger, hanalysis::Reader &BottomReader)
{
    std::vector<hanalysis::HTriplet> Triplets;

// // 2 jets form a W
//     std::vector<hanalysis::HDoublet> Doublets = WTagger.GetPairBdt(jets, WReader);
// // 3 jets form a top
//     std::vector<hanalysis::HTriplet> Triplets = GetBdt(Doublets, jets, TopHadronicReader);
//
// // 2 jets form a top
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// // 2 subjets form a W
//         std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetPairBdt(Pieces, WReader);
// // 2 subjets and one jet form a top
//         std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, jets, TopHadronicReader);
//         Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
//     }

// 1 jet forms a top
    for (const auto & Jet : jets)  {
        Jets Pieces = GetSubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 2 subjets form a W
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetPairBdt(Pieces, WReader);
// 3 subjets form a top
        std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Pieces, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

// // 1 jet forms a top
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// // 1 subjets form a W
//         std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetSingletBdt(Pieces, WReader);
// // 2 subjets form a top
//         std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Pieces, TopHadronicReader);
//         Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
//     }
//
// // 1 jet forms a top
//     for (const auto & Jet : jets)  {
// // no supbjets
//         hanalysis::HTriplet Triplet(Jet);
//         for (const auto Lepton : Leptons) if (Triplet.Jet().delta_R(Lepton) && Lepton.pt() > Triplet.LeptonPt) Triplet.LeptonPt = Lepton.pt();
//
// //         NSubJettiness(Triplet);
// //         if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//         Branch = GetBranch(Triplet);
// //         Print(HError,"Disp",Branch.MeanDisplacement);
// //         Print(HError,"Mass",Branch.VertexMass);
//         Triplet.SetBdt(TopHadronicReader.Bdt());
// //         Print(HError,"Bdt",Triplet.Bdt());
//
//         Triplets.emplace_back(Triplet);
//     }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());

    return Triplets;

}



float HTopHadronTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(HDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float HTopHadronTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * Constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}


void HTopHadronTagger::NSubJettiness(hanalysis::HTriplet &triplet)
{
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Singlet() * 2));
    else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().Singlet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.Singlet(), triplet.Doublet().Singlet1()), triplet.Doublet().Singlet2())));
}


SubJettiness HTopHadronTagger::NSubJettiness(const fastjet::PseudoJet &jet)
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
