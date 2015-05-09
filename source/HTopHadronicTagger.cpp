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
// DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    set_tagger_name("TopHadronic");
    top_mass_window_ = (TopMass - WMass) / 2;
    w_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_hadronic_reader_.set_tagger(w_hadronic_tagger_);
    DefineVariables();
}


void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
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

HTopHadronicBranch hanalysis::HTopHadronicTagger::GetBranch(const hanalysis::HTriplet &triplet) const
{
    Print(HInformation, "Fill Top Tagger", triplet.Bdt());

    HTopHadronicBranch branch;

    branch.Mass = triplet.Jet().m();
    branch.Rap = triplet.Jet().rap();
    branch.Phi = triplet.Jet().phi();
    branch.Pt = triplet.Jet().pt();
    branch.Ht = triplet.Ht();

    branch.BottomPt = triplet.Singlet().pt();
    branch.WPt = triplet.DoubletJet().pt();

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
    else if (triplet.Doublet().Degenerate()) GetBottomInfo(branch, triplet.Doublet().Singlet1() * 2);
    else GetBottomInfo(branch, triplet.Singlet());

    branch.Bdt = triplet.Bdt();
    if (!triplet.Degenerate())branch.WBdt = triplet.Doublet().Bdt();
    branch.BBdt = triplet.Singlet().user_info<HJetInfo>().Bdt();
    branch.Tag = triplet.Tag();
    return branch;
}

void hanalysis::HTopHadronicTagger::GetBottomInfo(HTopHadronicBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const
{

    TopHadronicBranch.VertexMass = jet.user_info<hanalysis::HJetInfo>().VertexMass();
    float MaxDisp = jet.user_info<hanalysis::HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) TopHadronicBranch.MaxDisplacement = std::log(MaxDisp);
    else TopHadronicBranch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) TopHadronicBranch.MeanDisplacement = std::log(MeanDisp);
    else TopHadronicBranch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) TopHadronicBranch.SumDisplacement = std::log(SumDisp);
    else TopHadronicBranch.SumDisplacement = -3;
    TopHadronicBranch.Multipliticity = jet.user_info<hanalysis::HJetInfo>().VertexNumber();
//     TopHadronicBranch.DeltaR = GetDeltaR(jet);
    TopHadronicBranch.Spread = GetSpread(jet);
    TopHadronicBranch.VertexDeltaR = GetDeltaR(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    TopHadronicBranch.VertexSpread = GetSpread(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    TopHadronicBranch.EnergyFraction = jet.user_info<hanalysis::HJetInfo>().VertexEnergy() / jet.e();
}


int hanalysis::HTopHadronicTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{

    Print(HInformation, "Get Top Tags");

    float pre_cut = 0;

    int WHadId = w_hadronic_tagger_.GetWHadId(event);
    HJets TopParticles = event.GetParticles()->Generator();
    int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());

    HJets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<hanalysis::HDoublet> doublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublets(event, w_hadronic_reader_.reader());

//     HJets Jets = GetJets(event);
//     //     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader); // TODO reenable this
//     std::vector<HDoublet> Doublets = w_hadronic_tagger_.GetBdt(Jets, w_hadronic_reader_);
    std::vector<hanalysis::HTriplet> triplets;

    if (!boost_) {

// 3 Jets form one top
        for (const auto & Jet : jets) {
            for (const auto & Doublet : doublets) {
                HTriplet Triplet(Doublet, Jet);
                if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                triplets.emplace_back(Triplet);
            }
        }
// Print(HError, "Number of Triplets 1", Triplets.size());

// 2 Jet form one top
        for (const auto Jet : jets) {
            HJets Pieces = GetSubJets(Jet, 2);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 1 jet form one W
            std::vector<hanalysis::HDoublet> PiecesDoublets = w_hadronic_tagger_.GetBdt(Pieces, w_hadronic_reader_);
            for (const auto & Doublet : PiecesDoublets)
                for (const auto & Jet2 : jets) {
                    if (Jet == Jet2) continue;
                    HTriplet Triplet(Doublet, Jet2);
                    if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                    if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                    if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                    if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                    if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                    triplets.emplace_back(Triplet);
                }
        }


// 1 Jet forms one top
        for (const auto Jet : jets) {
            HJets Pieces = GetSubJets(Jet, 3);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
            for (const auto & Piece1 : Pieces) {
                for (const auto & Piece2 : Pieces) {
// 2 subjets form one W
                    hanalysis::HDoublet Doublet(Piece1, Piece2);
                    Doublet = w_hadronic_tagger_.GetBdt(Doublet, w_hadronic_reader_);
                    if (std::abs(Doublet.Jet().m() - WMass) > w_mass_window_) continue;
                    for (const auto & Piece3 : Pieces) {
                        if (Piece3 == Doublet.Singlet1()) continue;
                        if (Piece3 == Doublet.Singlet2()) continue;
                        HTriplet Triplet(Doublet, Piece3);
                        if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                        if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                        if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                        if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                        if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                        triplets.emplace_back(Triplet);
                    }
                }
            }
        }

// 1 Jet forms one top
        for (const auto Jet : jets) {
            HJets Pieces = GetSubJets(Jet, 2);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
            for (const auto & Piece1 : Pieces) {
// 1 subjets forms one W
                hanalysis::HDoublet Doublet(Piece1);
                Doublet = w_hadronic_tagger_.GetBdt(Doublet, w_hadronic_reader_);
                if (std::abs(Doublet.Jet().m() - WMass) > w_mass_window_) continue;
                for (const auto & Piece3 : Pieces) {
                    if (Piece3 == Doublet.Singlet1()) continue;
                    if (Piece3 == Doublet.Singlet2()) continue;
                    HTriplet Triplet(Doublet, Piece3);
                    if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                    if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                    if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                    if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                    if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
                    triplets.emplace_back(Triplet);
                }
            }
        }

    }

// 1 Jet forms one top
    for (const auto Jet : jets) {
        HTriplet Triplet(Jet);
        if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
        if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
        if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
        if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
        triplets.emplace_back(Triplet);
    }

    if (triplets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", triplets.size());
        triplets = SortByMassTo(triplets, TopMass);
        switch (tag) {
        case kSignal :
            triplets.erase(triplets.begin() + 1, triplets.end()); // FIXME assuming maximal one hadronic top
            break;
// case HBackground :
// Triplets.erase(Triplets.begin()); // FIXME assuming maximal one hadronic top
// break;
        }
    }

    std::vector<HTopHadronicBranch> HadronicTopBranches;
    for (auto & Triplet : triplets) {
        Triplet.SetTag(tag);
        NSubJettiness(Triplet);
    }

    return SaveEntries(triplets);

}

std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const TMVA::Reader &reader)
{

    std::vector<HTriplet> Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            if (std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
            // if (Triplet.DeltaR() < detector_geometry().MinCellResolution) continue;
            NSubJettiness(Triplet);
            branch_ = GetBranch(Triplet);
            Triplet.SetBdt(Bdt(reader));
            Triplets.emplace_back(Triplet);
        }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());
    return Triplets;
}


hanalysis::HTriplet hanalysis::HTopHadronicTagger::GetBdt(HTriplet &Triplet, const Reader &TopHadronicReader)
{
    NSubJettiness(Triplet);
    branch_ = GetBranch(Triplet);
    Triplet.SetBdt(TopHadronicReader.Bdt());
    return Triplet;
}


std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetTriplets(HEvent &event, const TMVA::Reader &reader)
{
    HJets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<hanalysis::HTriplet> triplets;
    if (!boost_) {


// 2 jets form a W
        std::vector<hanalysis::HDoublet> Doublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublets(event, w_hadronic_reader_.reader());
//         std::vector<hanalysis::HDoublet> Doublets = WTagger.GetPairBdt(jets, WReader);
// 3 jets form a top
        triplets = GetBdt(Doublets, jets, reader);

// 2 jets form a top
        for (const auto & Jet : jets) {
           HJets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubBdt(jets, bottom_reader_.reader(),2);
//             HJets Pieces = GetSubJets(Jet, 2);
            //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// 2 subjets form a W
           std::vector<hanalysis::HDoublet> PieceDoublets = static_cast<HWHadronicTagger &>(w_hadronic_reader_.tagger()).GetDoublets(event, w_hadronic_reader_.reader());
//             std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetPairBdt(pieces, WReader);
// 2 subjets and one jet form a top
            std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, jets, reader);
            triplets.insert(triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
        }

        // TODO reenable the following
// // 1 jet forms a top
//         for (const auto & Jet : jets) {
//             HJets Pieces = GetSubJets(Jet, 3);
//             //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// // 2 subjets form a W
//             std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetPairBdt(Pieces, WReader);
// // 3 subjets form a top
//             std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Pieces, reader);
//             triplets.insert(triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
//         }
//
// // 1 jet forms a top
//         for (const auto & Jet : jets) {
//             HJets Pieces = GetSubJets(Jet, 2);
//             //             Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
// // 1 subjets form a W
//             std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetSingletBdt(Pieces, WReader);
// // 2 subjets form a top
//             std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Pieces, reader);
//             triplets.insert(triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
//         }

    }

// 1 jet forms a top
    for (const auto & Jet : jets) {
// no supbjets
        HTriplet Triplet(Jet);
        NSubJettiness(Triplet);
//         if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // seems to be a really bad idea; no more higgses left
        branch_ = GetBranch(Triplet);
        Triplet.SetBdt(Bdt(reader));
        triplets.emplace_back(Triplet);
    }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());

    return triplets;

}


// std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetBdt(HJets &Jets, const Reader &TopHadronicReader)
// {
// std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
// std::vector<hanalysis::HTriplet> TripletsHadronic = GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//
// for (const auto & Jet : Jets) {
// HJets Pieces = GetSubJets(Jet, 2);
// Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
// std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
// TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
// }
//
// for (const auto & Jet : Jets) {
// HJets Pieces = GetSubJets(Jet, 3);
// Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
// std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
// TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
// }
//
// if(TripletsHadronic.size()>1){
// std::sort(TripletsHadronic.begin(), TripletsHadronic.end());
// TripletsHadronic.erase(TripletsHadronic.begin() + std::min(MaxCombi, int(TripletsHadronic.size())), TripletsHadronic.end());
// }
//
// return TripletsHadronic;
//
// }








float hanalysis::HTopHadronicTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
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

float hanalysis::HTopHadronicTagger::GetSpread(const fastjet::PseudoJet &Jet) const
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










void hanalysis::HTopHadronicTagger::NSubJettiness(HTriplet &triplet)
{
    if (triplet.Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Singlet() * 2));
    else if (triplet.Doublet().Degenerate()) triplet.set_sub_jettiness(NSubJettiness(triplet.Doublet().Singlet1() * 2));
    else triplet.set_sub_jettiness(NSubJettiness(fastjet::join(fastjet::join(triplet.Singlet(), triplet.Doublet().Singlet1()), triplet.Doublet().Singlet2())));
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

