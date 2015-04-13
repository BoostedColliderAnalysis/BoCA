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
    DefineVariables();
}

void hanalysis::HTopHadronicTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger)
{
    Print(HNotification, "Constructor");
    BottomTagger = NewBottomTagger;
    WTagger = NewWTagger;
    DefineVariables();
}

void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    SetTaggerName("TopHadronic");
    TopWindow = (TopMass - WMass) / 2;
    WMassWindow = 20;
    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.BottomPt, "BottomPt");
    AddObservable(Branch.WPt, "WPt");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.Tau1_1, "Tau1_1");
    AddObservable(Branch.Tau2_1, "Tau2_1");
    AddObservable(Branch.Tau3_1, "Tau3_1");
    AddObservable(Branch.Tau21_1, "Tau21_1");
    AddObservable(Branch.Tau32_1, "Tau32_1");
    AddObservable(Branch.Tau1_2, "Tau1_2");
    AddObservable(Branch.Tau2_2, "Tau2_2");
    AddObservable(Branch.Tau3_2, "Tau3_2");
    AddObservable(Branch.Tau21_2, "Tau21_2");
    AddObservable(Branch.Tau32_2, "Tau32_2");




    AddObservable(Branch.VertexMass, "VertexMass");
    AddObservable(Branch.MaxDisplacement, "MaxDisplacement");
    AddObservable(Branch.MeanDisplacement, "MeanDisplacement");
    AddObservable(Branch.SumDisplacement, "SumDisplacement");
    AddObservable(Branch.Multipliticity, "Multipliticity");
    AddObservable(Branch.Spread, "Spread");
    AddObservable(Branch.VertexDeltaR, "VertexDeltaR");
    AddObservable(Branch.VertexSpread, "VertexSpread");
    AddObservable(Branch.EnergyFraction, "EnergyFraction");












    AddObservable(Branch.WBdt, "WBdt");
    AddObservable(Branch.BBdt, "BBdt");
    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");
}

HTopHadronicBranch hanalysis::HTopHadronicTagger::GetBranch(const hanalysis::HTriplet &triplet) const
{
    Print(HInformation, "Fill Top Tagger", triplet.Bdt());

    HTopHadronicBranch TopHadronicBranch;

    TopHadronicBranch.Mass = triplet.Jet().m();
    TopHadronicBranch.Rap = triplet.Jet().rap();
    TopHadronicBranch.Phi = triplet.Jet().phi();
    TopHadronicBranch.Pt = triplet.Jet().pt();
    TopHadronicBranch.Ht = triplet.Ht();

    TopHadronicBranch.BottomPt = triplet.Singlet().pt();
    TopHadronicBranch.WPt = triplet.DoubletJet().pt();

    TopHadronicBranch.DeltaPt = triplet.DeltaPt();
    TopHadronicBranch.DeltaHt = triplet.DeltaHt();
    TopHadronicBranch.DeltaM = triplet.DeltaM();
    TopHadronicBranch.DeltaR = triplet.DeltaR();
    TopHadronicBranch.DeltaRap = triplet.DeltaRap();
    TopHadronicBranch.DeltaPhi = triplet.DeltaPhi();

    TopHadronicBranch.Tau1_1 = triplet.sub_jettiness().tau1_beta1;
    TopHadronicBranch.Tau2_1 = triplet.sub_jettiness().tau2_beta1;
    TopHadronicBranch.Tau3_1 = triplet.sub_jettiness().tau3_beta1;
    if (triplet.sub_jettiness().tau1_beta1 > 0) TopHadronicBranch.Tau21_1 = triplet.sub_jettiness().tau21_beta1;
    if (triplet.sub_jettiness().tau2_beta1 > 0) TopHadronicBranch.Tau32_1 = triplet.sub_jettiness().tau32_beta1;
    TopHadronicBranch.Tau1_2 = triplet.sub_jettiness().tau1_beta2;
    TopHadronicBranch.Tau2_2 = triplet.sub_jettiness().tau2_beta2;
    TopHadronicBranch.Tau3_2 = triplet.sub_jettiness().tau3_beta2;
    if (triplet.sub_jettiness().tau1_beta2 > 0) TopHadronicBranch.Tau21_2 = triplet.sub_jettiness().tau21_beta2;
    if (triplet.sub_jettiness().tau2_beta2 > 0) TopHadronicBranch.Tau32_2 = triplet.sub_jettiness().tau32_beta2;

    if (triplet.Degenerate()) GetBottomInfo(TopHadronicBranch, triplet.Singlet() * 2);
    else if (triplet.Doublet().Degenerate()) GetBottomInfo(TopHadronicBranch, triplet.Doublet().Singlet1() * 2);
    else GetBottomInfo(TopHadronicBranch, triplet.Singlet());

    TopHadronicBranch.Bdt = triplet.Bdt();
    if (!triplet.Degenerate())TopHadronicBranch.WBdt = triplet.Doublet().Bdt();
    TopHadronicBranch.BBdt = triplet.Singlet().user_info<HJetInfo>().Bdt();
    TopHadronicBranch.Tag = triplet.Tag();
    return TopHadronicBranch;
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


std::vector< HTopHadronicBranch > hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag, float pre_cut)
{

    Print(HInformation, "Get Top Tags");

    int WHadId = WTagger.GetWHadId(Event);
    HJets TopParticles = Event.GetParticles()->Generator();
    int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    std::vector<HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets;

// 3 Jets form one top
    for (const auto & Jet : Jets) {
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
            if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
            if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
            if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
            Triplets.push_back(Triplet);
        }
    }
// Print(HError, "Number of Triplets 1", Triplets.size());

// 2 Jet form one top
    for (const auto Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
// 1 jet form one W
        std::vector<hanalysis::HDoublet> PiecesDoublets = WTagger.GetBdt(Pieces, WReader);
        for (const auto & Doublet : PiecesDoublets)
            for (const auto & Jet2 : Jets) {
                if (Jet == Jet2) continue;
                HTriplet Triplet(Doublet, Jet2);
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
                if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
                if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
                Triplets.push_back(Triplet);
            }
    }


// 1 Jet forms one top
    for (const auto Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
// 2 subjets form one W
                hanalysis::HDoublet Doublet(Piece1, Piece2);
                Doublet = WTagger.GetBdt(Doublet, WReader);
                if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                for (const auto & Piece3 : Pieces) {
                    if (Piece3 == Doublet.Singlet1()) continue;
                    if (Piece3 == Doublet.Singlet2()) continue;
                    HTriplet Triplet(Doublet, Piece3);
                    if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
                    if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
                    if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                    if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                    if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
                    Triplets.push_back(Triplet);
                }
            }
        }
    }

// 1 Jet forms one top
    for (const auto Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
// 1 subjets forms one W
            hanalysis::HDoublet Doublet(Piece1);
            Doublet = WTagger.GetBdt(Doublet, WReader);
            if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            for (const auto & Piece3 : Pieces) {
                if (Piece3 == Doublet.Singlet1()) continue;
                if (Piece3 == Doublet.Singlet2()) continue;
                HTriplet Triplet(Doublet, Piece3);
                if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
                if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
                Triplets.push_back(Triplet);
            }
        }
    }

// 1 Jet forms one top
    for (const auto Jet : Jets) {
        HTriplet Triplet(Jet);
        if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
        if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
        if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
        if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
        Triplets.push_back(Triplet);
    }


    if (Triplets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        Triplets = SortByMassTo(Triplets, TopMass);
        switch (Tag) {
        case HSignal :
            Triplets.erase(Triplets.begin() + 1, Triplets.end()); // FIXME assuming maximal one hadronic top
            break;
// case HBackground :
// Triplets.erase(Triplets.begin()); // FIXME assuming maximal one hadronic top
// break;
        }
    }

    std::vector<HTopHadronicBranch> HadronicTopBranches;
    for (auto & Triplet : Triplets) {
        Triplet.SetTag(Tag);
        NSubJettiness(Triplet);
        HadronicTopBranches.push_back(GetBranch(Triplet));
    }

    return HadronicTopBranches;

}


hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const HTriplet &)
{
    Print(HInformation, "Get Triple Tag");
}

hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const fastjet::PseudoJet &)
{
    Print(HInformation, "Get Jet Tag");

// HJetInfo JetInfo = Jet.user_info<HJetInfo>();
// JetInfo.ExtractFraction(TopId);
//
// if (JetInfo.MaximalId() != TopId) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader &TopHadronicReader)
{

    std::vector<HTriplet> Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            // if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
            NSubJettiness(Triplet);
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader.Bdt());
            Triplets.push_back(Triplet);
        }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());
    return Triplets;
}


hanalysis::HTriplet hanalysis::HTopHadronicTagger::GetBdt(HTriplet &Triplet, const HReader &TopHadronicReader)
{
    NSubJettiness(Triplet);
    Branch = GetBranch(Triplet);
    Triplet.SetBdt(TopHadronicReader.Bdt());
    return Triplet;
}


std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &TopHadronicReader, hanalysis::HWTagger &WTagger, hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader)
{

// 2 jets form a W
    std::vector<hanalysis::HDoublet> Doublets = WTagger.GetPairBdt(Jets, WReader);
// 3 jets form a top
    std::vector<hanalysis::HTriplet> Triplets = GetBdt(Doublets, Jets, TopHadronicReader);

// 2 jets form a top
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
// 2 subjets form a W
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetPairBdt(Pieces, WReader);
// 2 subjets and one jet form a top
        std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

// 1 jet forms a top
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
// 2 subjets form a W
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetPairBdt(Pieces, WReader);
// 3 subjets form a top
        std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Pieces, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

// 1 jet forms a top
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
// 1 subjets form a W
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetSingletBdt(Pieces, WReader);
// 2 subjets form a top
        std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Pieces, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

// 1 jet forms a top
    for (const auto & Jet : Jets) {
// no supbjets
        HTriplet Triplet(Jet);
        NSubJettiness(Triplet);
        if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
        Branch = GetBranch(Triplet);
        Triplet.SetBdt(TopHadronicReader.Bdt());
        Triplets.push_back(Triplet);
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());

    return Triplets;

}


// std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetBdt(HJets &Jets, const HReader &TopHadronicReader)
// {
// std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
// std::vector<hanalysis::HTriplet> TripletsHadronic = GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//
// for (const auto & Jet : Jets) {
// HJets Pieces = GetSubJets(Jet, 2);
// Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
// std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
// std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
// TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
// }
//
// for (const auto & Jet : Jets) {
// HJets Pieces = GetSubJets(Jet, 3);
// Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
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



























// void hanalysis::HTopHadronicTagger::BasicNSubJettiness(const std::vector<fastjet::PseudoJet> &input_particles)
// {
//
//     ////////
//     //
//     // Start of analysis. First find anti-kT jets, then find N-subjettiness values of those jets
//     //
//     ///////
//
//     // Initial clustering with anti-kt algorithm
//     fastjet::JetAlgorithm algorithm = fastjet::antikt_algorithm;
//     double jet_rad = 1.00; // jet radius for anti-kt algorithm
//     fastjet::JetDefinition jetDef = fastjet::JetDefinition(algorithm, jet_rad, fastjet::E_scheme, fastjet::Best);
//     fastjet::ClusterSequence clust_seq(input_particles, jetDef);
//     std::vector<fastjet::PseudoJet> antikt_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets());
//
//     for (int j = 0; j < 2; j++) { // Two hardest jets per event
//         if (antikt_jets[j].perp() < 200) continue;
//
//         std::vector<fastjet::PseudoJet> jet_constituents = clust_seq.constituents(antikt_jets[j]);
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "Analyzing Jet " << j + 1 << ":" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
//         ////////
//         //
//         // Basic checks of tau values first
//         //
//         // If you don't want to know the directions of the subjets,
//         // then you can use the simple function Nsubjettiness.
//         //
//         // Recommended usage for Nsubjettiness:
//         // AxesMode: kt_axes, wta_kt_axes, onepass_kt_axes, or onepass_wta_kt_axes
//         // MeasureMode: unnormalized_measure
//         // beta with kt_axes: 2.0
//         // beta with wta_kt_axes: anything greater than 0.0 (particularly good for 1.0)
//         // beta with onepass_kt_axes or onepass_wta_kt_axes: between 1.0 and 3.0
//         //
//         ///////
//
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "N-subjettiness with Unnormalized Measure (in GeV)" << std::endl;
//         std::cout << "beta = 1.0: One-pass Winner-Take-All kT Axes" << std::endl;
//         std::cout << "beta = 2.0: One-pass E-Scheme kT Axes" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
//         // Now loop through all options
//         std::cout << std::setprecision(6) << std::right << std::fixed;
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << std::setw(15) << "beta"
//                   << std::setw(14) << "tau1"
//                   << std::setw(14) << "tau2"
//                   << std::setw(14) << "tau3"
//                   << std::setw(14) << "tau2/tau1"
//                   << std::setw(14) << "tau3/tau2"
//                   << std::endl;
//
//
//         // Axes modes to try
//         fastjet::contrib::OnePass_WTA_KT_Axes axisMode1;
//         fastjet::contrib::OnePass_KT_Axes axisMode2;
//
//
//         // Measure modes to try
//         double beta1 = 1.0;
//         double beta2 = 2.0;
//         fastjet::contrib::UnnormalizedMeasure measureSpec1(beta1);
//         fastjet::contrib::UnnormalizedMeasure measureSpec2(beta2);
//
//         // define Nsubjettiness functions (beta = 1.0)
//         fastjet::contrib::Nsubjettiness nSub1_beta1(1, axisMode1, measureSpec1);
//         // an alternative (but more prone to error) constructor is nSub1_beta1(1, axisMode1,Njettiness::unnormalized_measure,beta1);
//         fastjet::contrib::Nsubjettiness nSub2_beta1(2, axisMode1, measureSpec1);
//         fastjet::contrib::Nsubjettiness nSub3_beta1(3, axisMode1, measureSpec1);
//         fastjet::contrib::NsubjettinessRatio nSub21_beta1(2, 1, axisMode1, measureSpec1);
//         fastjet::contrib::NsubjettinessRatio nSub32_beta1(3, 2, axisMode1, measureSpec1);
//
//         // define Nsubjettiness functions (beta = 2.0)
//         fastjet::contrib::Nsubjettiness nSub1_beta2(1, axisMode2, measureSpec2);
//         fastjet::contrib::Nsubjettiness nSub2_beta2(2, axisMode2, measureSpec2);
//         fastjet::contrib::Nsubjettiness nSub3_beta2(3, axisMode2, measureSpec2);
//         fastjet::contrib::NsubjettinessRatio nSub21_beta2(2, 1, axisMode2, measureSpec2);
//         fastjet::contrib::NsubjettinessRatio nSub32_beta2(3, 2, axisMode2, measureSpec2);
//
//         // calculate Nsubjettiness values (beta = 1.0)
//         double tau1_beta1 = nSub1_beta1(antikt_jets[j]);
//         double tau2_beta1 = nSub2_beta1(antikt_jets[j]);
//         double tau3_beta1 = nSub3_beta1(antikt_jets[j]);
//         double tau21_beta1 = nSub21_beta1(antikt_jets[j]);
//         double tau32_beta1 = nSub32_beta1(antikt_jets[j]);
//
//         // calculate Nsubjettiness values (beta = 2.0)
//         double tau1_beta2 = nSub1_beta2(antikt_jets[j]);
//         double tau2_beta2 = nSub2_beta2(antikt_jets[j]);
//         double tau3_beta2 = nSub3_beta2(antikt_jets[j]);
//         double tau21_beta2 = nSub21_beta2(antikt_jets[j]);
//         double tau32_beta2 = nSub32_beta2(antikt_jets[j]);
//
//         // Output results (beta = 1.0)
//         std::cout << std::setw(15) << beta1
//                   << std::setw(14) << tau1_beta1
//                   << std::setw(14) << tau2_beta1
//                   << std::setw(14) << tau3_beta1
//                   << std::setw(14) << tau21_beta1
//                   << std::setw(14) << tau32_beta1
//                   << std::endl;
//
//         // Output results (beta = 2.0)
//         std::cout << std::setw(15) << beta2
//                   << std::setw(14) << tau1_beta2
//                   << std::setw(14) << tau2_beta2
//                   << std::setw(14) << tau3_beta2
//                   << std::setw(14) << tau21_beta2
//                   << std::setw(14) << tau32_beta2
//                   << std::endl;
//
//
//         std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
//         std::cout << "Subjets found using beta = 1.0 tau values" << std::endl;
//         PrintJets(nSub1_beta1.currentSubjets(), nSub1_beta1.currentTauComponents()); // these subjets have valid constituents
//         std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//         PrintJets(nSub2_beta1.currentSubjets(), nSub2_beta1.currentTauComponents()); // these subjets have valid constituents
//         std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//         PrintJets(nSub3_beta1.currentSubjets(), nSub3_beta1.currentTauComponents()); // these subjets have valid constituents
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//         std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
//         std::cout << "Axes used for above beta = 1.0 tau values" << std::endl;
//
//         PrintJets(nSub1_beta1.currentAxes(), nSub1_beta1.currentTauComponents(), false);
//         //PrintJets(nSub1_beta1.seedAxes()); // For one-pass minimization, this would show starting seeds
//         std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//         PrintJets(nSub2_beta1.currentAxes(), nSub2_beta1.currentTauComponents(), false);
//         //PrintJets(nSub2_beta1.seedAxes()); // For one-pass minimization, this would show starting seeds
//         std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//         PrintJets(nSub3_beta1.currentAxes(), nSub3_beta1.currentTauComponents(), false);
//         //PrintJets(nSub3_beta1.seedAxes()); // For one-pass minimization, this would show starting seeds
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//     }
//
// }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// // Simple class to store Axes along with a name for display
// class AxesStruct
// {
//
// private:
// // Shared Ptr so it handles memory management
//     fastjet::SharedPtr<fastjet::contrib::AxesDefinition> _axes_def;
//
// public:
//     AxesStruct(const fastjet::contrib::AxesDefinition &axes_def)
//         : _axes_def(axes_def.create()) {}
//
// // Need special copy constructor to make it possible to put in a std::vector
//     AxesStruct(const AxesStruct &myStruct)
//         : _axes_def(myStruct._axes_def->create()) {}
//
//     const fastjet::contrib::AxesDefinition &def() const {
//         return *_axes_def;
//     }
//     std::string description() const {
//         return _axes_def->description();
//     }
//     std::string short_description() const {
//         return _axes_def->short_description();
//     }
//
// };
//
//
// // Simple class to store Measures to make it easier to put in std::vector
// class MeasureStruct
// {
//
// private:
// // Shared Ptr so it handles memory management
//     fastjet::SharedPtr<fastjet::contrib::MeasureDefinition> _measure_def;
//
// public:
//     MeasureStruct(const fastjet::contrib::MeasureDefinition &measure_def)
//         : _measure_def(measure_def.create()) {}
//
// // Need special copy constructor to make it possible to put in a std::vector
//     MeasureStruct(const MeasureStruct &myStruct)
//         : _measure_def(myStruct._measure_def->create()) {}
//
//     const fastjet::contrib::MeasureDefinition &def() const {
//         return *_measure_def;
//     }
//     std::string description() const {
//         return _measure_def->description();
//     }
//
// };
//
//
// void hanalysis::HTopHadronicTagger::AdvancedNSubJettiness(const std::vector<fastjet::PseudoJet> &input_particles)
// {
//
// ////////
// //
// // This code will check multiple axes/measure modes
// // First thing we do is establish the various modes we will check
// //
// ///////
//
// // A list of all of the available axes modes
//     std::vector<AxesStruct> _testAxes;
//     _testAxes.push_back(fastjet::contrib::KT_Axes());
//     _testAxes.push_back(fastjet::contrib::CA_Axes());
//     _testAxes.push_back(fastjet::contrib::AntiKT_Axes(0.2));
//     _testAxes.push_back(fastjet::contrib::WTA_KT_Axes());
//     _testAxes.push_back(fastjet::contrib::WTA_CA_Axes());
//     _testAxes.push_back(fastjet::contrib::OnePass_KT_Axes());
//     _testAxes.push_back(fastjet::contrib::OnePass_CA_Axes());
//     _testAxes.push_back(fastjet::contrib::OnePass_AntiKT_Axes(0.2));
//     _testAxes.push_back(fastjet::contrib::OnePass_WTA_KT_Axes());
//     _testAxes.push_back(fastjet::contrib::OnePass_WTA_CA_Axes());
//     _testAxes.push_back(fastjet::contrib::MultiPass_Axes(100));
//
// //
// // Note: Njettiness::min_axes is not guarenteed to give a global
// // minimum, only a local minimum, and different choices of the random
// // number seed can give different results. For that reason,
// // the one-pass minimization are recommended over min_axes.
// //
//
// // Getting a smaller list of recommended axes modes
// // These are the ones that are more likely to give sensible results (and are all IRC safe)
//     std::vector<AxesStruct> _testRecommendedAxes;
//     _testRecommendedAxes.push_back(fastjet::contrib::KT_Axes());
//     _testRecommendedAxes.push_back(fastjet::contrib::WTA_KT_Axes());
//     _testRecommendedAxes.push_back(fastjet::contrib::OnePass_KT_Axes());
//     _testRecommendedAxes.push_back(fastjet::contrib::OnePass_WTA_KT_Axes());
//
// // Getting some of the measure modes to test
// // (When applied to a single jet we won't test the cutoff measures,
// // since cutoffs aren't typically helpful when applied to single jets)
// // Note that we are calling measures by their MeasureDefinition
//     std::vector<MeasureStruct> _testMeasures;
//     _testMeasures.push_back(fastjet::contrib::NormalizedMeasure(1.0, 1.0));
//     _testMeasures.push_back(fastjet::contrib::UnnormalizedMeasure(1.0));
//     _testMeasures.push_back(fastjet::contrib::NormalizedMeasure(2.0, 1.0));
//     _testMeasures.push_back(fastjet::contrib::UnnormalizedMeasure(2.0));
//     _testMeasures.push_back(fastjet::contrib::GeometricMeasure(2.0));
//
// // When doing Njettiness as a jet algorithm, want to test the cutoff measures.
// // (Since they are not senisible without a cutoff)
//     std::vector<MeasureStruct> _testCutoffMeasures;
//     _testCutoffMeasures.push_back(fastjet::contrib::UnnormalizedCutoffMeasure(1.0, 0.8));
//     _testCutoffMeasures.push_back(fastjet::contrib::UnnormalizedCutoffMeasure(2.0, 0.8));
//     _testCutoffMeasures.push_back(fastjet::contrib::GeometricCutoffMeasure(2.0, 0.8));
//
//
// /////// N-subjettiness /////////////////////////////
//
// ////////
// //
// // Start of analysis. First find anti-kT jets, then find N-subjettiness values of those jets
// //
// ///////
//
// // Initial clustering with anti-kt algorithm
//     fastjet::JetAlgorithm algorithm = fastjet::antikt_algorithm;
//     double jet_rad = 1.00; // jet radius for anti-kt algorithm
//     fastjet::JetDefinition jetDef = fastjet::JetDefinition(algorithm, jet_rad, fastjet::E_scheme, fastjet::Best);
//     fastjet::ClusterSequence clust_seq(input_particles, jetDef);
//     std::vector<fastjet::PseudoJet> antikt_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets());
//
// // small number to show equivalence of doubles
//     double epsilon = 0.0001;
//
//     for (int j = 0; j < 2; j++) { // Two hardest jets per event
//         if (antikt_jets[j].perp() < 200) continue;
//
//         std::vector<fastjet::PseudoJet> jet_constituents = clust_seq.constituents(antikt_jets[j]);
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "Analyzing Jet " << j + 1 << ":" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
// ////////
// //
// // Basic checks of tau values first
// //
// // If you don't want to know the directions of the subjets,
// // then you can use the simple function Nsubjettiness.
// //
// // Recommended usage for Nsubjettiness:
// // AxesMode: kt_axes, wta_kt_axes, onepass_kt_axes, or onepass_wta_kt_axes
// // MeasureMode: unnormalized_measure
// // beta with kt_axes: 2.0
// // beta with wta_kt_axes: anything greater than 0.0 (particularly good for 1.0)
// // beta with onepass_kt_axes or onepass_wta_kt_axes: between 1.0 and 3.0
// //
// ///////
//
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "Outputting N-subjettiness Values" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
// // Now loop through all options
//         std::cout << std::setprecision(6) << std::right << std::fixed;
//         for (unsigned iM = 0; iM < _testMeasures.size(); iM++) {
//
//             std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//             std::cout << _testMeasures[iM].description() << ":" << std::endl;
//             std::cout << " AxisMode"
//                       << std::setw(14) << "tau1"
//                       << std::setw(14) << "tau2"
//                       << std::setw(14) << "tau3"
//                       << std::setw(14) << "tau2/tau1"
//                       << std::setw(14) << "tau3/tau2"
//                       << std::endl;
//
//             for (unsigned iA = 0; iA < _testAxes.size(); iA++) {
//
// // This case doesn't work, so skip it.
//                 if (_testAxes[iA].def().givesRandomizedResults() && !_testMeasures[iM].def().supportsMultiPassMinimization()) continue;
//
// // define Nsubjettiness functions
//                 fastjet::contrib::Nsubjettiness nSub1(1, _testAxes[iA].def(), _testMeasures[iM].def());
//                 fastjet::contrib::Nsubjettiness nSub2(2, _testAxes[iA].def(), _testMeasures[iM].def());
//                 fastjet::contrib::Nsubjettiness nSub3(3, _testAxes[iA].def(), _testMeasures[iM].def());
//                 fastjet::contrib::NsubjettinessRatio nSub21(2, 1, _testAxes[iA].def(), _testMeasures[iM].def());
//                 fastjet::contrib::NsubjettinessRatio nSub32(3, 2, _testAxes[iA].def(), _testMeasures[iM].def());
// // calculate Nsubjettiness values
//                 double tau1 = nSub1(antikt_jets[j]);
//                 double tau2 = nSub2(antikt_jets[j]);
//                 double tau3 = nSub3(antikt_jets[j]);
//                 double tau21 = nSub21(antikt_jets[j]);
//                 double tau32 = nSub32(antikt_jets[j]);
//
// // Make sure calculations are consistent
//                 if (!_testAxes[iA].def().givesRandomizedResults()) {
//                     assert(abs(tau21 - tau2 / tau1) < epsilon);
//                     assert(abs(tau32 - tau3 / tau2) < epsilon);
//                 }
//
//                 std::string axesName = _testAxes[iA].short_description();
// // comment out with # because MultiPass uses random number seed
//                 if (_testAxes[iA].def().givesRandomizedResults()) axesName = "# " + axesName;
//
// // Output results:
//                 std::cout << std::right
//                           << std::setw(14)
//                           << axesName
//                           << ":"
//                           << std::setw(14) << tau1
//                           << std::setw(14) << tau2
//                           << std::setw(14) << tau3
//                           << std::setw(14) << tau21
//                           << std::setw(14) << tau32
//                           << std::endl;
//             }
//         }
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "Done Outputting N-subjettiness Values" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
// ////////
// //
// // Finding axes/jets found by N-subjettiness partitioning
// //
// // This uses the NjettinessPlugin as a jet finder (in this case, acting on an individual jet)
// // Recommended usage is same as above
// //
// ///////
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "Outputting N-subjettiness Subjets" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
// // Loop through all options, this time setting up jet finding
//         std::cout << std::setprecision(6) << std::left << std::fixed;
//         for (unsigned iM = 0; iM < _testMeasures.size(); iM++) {
//
//             for (unsigned iA = 0; iA < _testRecommendedAxes.size(); iA++) {
//
// // This case doesn't work, so skip it.
//                 if (_testAxes[iA].def().givesRandomizedResults() && !_testMeasures[iM].def().supportsMultiPassMinimization()) continue;
//
// // define the plugins
//                 fastjet::contrib::NjettinessPlugin nsub_plugin1(1, _testRecommendedAxes[iA].def(), _testMeasures[iM].def());
//                 fastjet::contrib::NjettinessPlugin nsub_plugin2(2, _testRecommendedAxes[iA].def(), _testMeasures[iM].def());
//                 fastjet::contrib::NjettinessPlugin nsub_plugin3(3, _testRecommendedAxes[iA].def(), _testMeasures[iM].def());
//
// // define the corresponding jet definitions
//                 fastjet::JetDefinition nsub_jetDef1(&nsub_plugin1);
//                 fastjet::JetDefinition nsub_jetDef2(&nsub_plugin2);
//                 fastjet::JetDefinition nsub_jetDef3(&nsub_plugin3);
//
// // and the corresponding cluster sequences
//                 fastjet::ClusterSequence nsub_seq1(antikt_jets[j].constituents(), nsub_jetDef1);
//                 fastjet::ClusterSequence nsub_seq2(antikt_jets[j].constituents(), nsub_jetDef2);
//                 fastjet::ClusterSequence nsub_seq3(antikt_jets[j].constituents(), nsub_jetDef3);
//
//                 std::vector<fastjet::PseudoJet> jets1 = nsub_seq1.inclusive_jets();
//                 std::vector<fastjet::PseudoJet> jets2 = nsub_seq2.inclusive_jets();
//                 std::vector<fastjet::PseudoJet> jets3 = nsub_seq3.inclusive_jets();
//
//                 std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//                 std::cout << _testMeasures[iM].description() << ":" << std::endl;
//                 std::cout << _testRecommendedAxes[iA].description() << ":" << std::endl;
//
//                 bool commentOut = false;
//                 if (_testAxes[iA].def().givesRandomizedResults()) commentOut = true; // have to comment out min_axes, because it has random values
//
// // This helper function tries to find out if the jets have tau information for printing
//                 PrintJets(jets1, commentOut);
//                 std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//                 PrintJets(jets2, commentOut);
//                 std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//                 PrintJets(jets3, commentOut);
//
// // Also try to find axes location (if njettiness_extras works)
//                 std::vector<fastjet::PseudoJet> axes1;
//                 std::vector<fastjet::PseudoJet> axes2;
//                 std::vector<fastjet::PseudoJet> axes3;
//                 const fastjet::contrib::NjettinessExtras *extras1 = fastjet::contrib::njettiness_extras(nsub_seq1);
//                 const fastjet::contrib::NjettinessExtras *extras2 = fastjet::contrib::njettiness_extras(nsub_seq2);
//                 const fastjet::contrib::NjettinessExtras *extras3 = fastjet::contrib::njettiness_extras(nsub_seq3);
//
//                 axes1 = extras1->axes();
//                 axes2 = extras2->axes();
//                 axes3 = extras3->axes();
//
//                 std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
//                 std::cout << "Axes Used for Above Subjets" << std::endl;
//
//                 PrintJets(axes1, commentOut);
//                 std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//                 PrintJets(axes2, commentOut);
//                 std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//                 PrintJets(axes3, commentOut);
//
//             }
//         }
//
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//         std::cout << "Done Outputting N-subjettiness Subjets" << std::endl;
//         std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//     }
//
//
// ////////// N-jettiness as a jet algorithm ///////////////////////////
//
// ////////
// //
// // You can also find jets event-wide with Njettiness.
// // In this case, Winner-Take-All axes are a must, since the other axes get trapped in local minima
// //
// // Recommended usage of NjettinessPlugin (event-wide)
// // AxesMode: wta_kt_axes or onepass_wta_kt_axes
// // MeasureMode: unnormalized_measure
// // beta with wta_kt_axes: anything greater than 0.0 (particularly good for 1.0)
// // beta with onepass_wta_kt_axes: between 1.0 and 3.0
// //
// ///////
//
//     std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//     std::cout << "Using N-jettiness as a Jet Algorithm" << std::endl;
//     std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
//
//     for (unsigned iM = 0; iM < _testCutoffMeasures.size(); iM++) {
//
//         for (unsigned iA = 0; iA < _testRecommendedAxes.size(); iA++) {
//
// // define the plugins
//             fastjet::contrib::NjettinessPlugin njet_plugin2(2, _testRecommendedAxes[iA].def(), _testCutoffMeasures[iM].def());
//             fastjet::contrib::NjettinessPlugin njet_plugin3(3, _testRecommendedAxes[iA].def(), _testCutoffMeasures[iM].def());
//             fastjet::contrib::NjettinessPlugin njet_plugin4(4, _testRecommendedAxes[iA].def(), _testCutoffMeasures[iM].def());
//
// // and the jet definitions
//             fastjet::JetDefinition njet_jetDef2(&njet_plugin2);
//             fastjet::JetDefinition njet_jetDef3(&njet_plugin3);
//             fastjet::JetDefinition njet_jetDef4(&njet_plugin4);
//
// // and the cluster sequences
//             fastjet::ClusterSequence njet_seq2(input_particles, njet_jetDef2);
//             fastjet::ClusterSequence njet_seq3(input_particles, njet_jetDef3);
//             fastjet::ClusterSequence njet_seq4(input_particles, njet_jetDef4);
//
// // and associated extras for more information
//             const fastjet::contrib::NjettinessExtras *extras2 = fastjet::contrib::njettiness_extras(njet_seq2);
//             const fastjet::contrib::NjettinessExtras *extras3 = fastjet::contrib::njettiness_extras(njet_seq3);
//             const fastjet::contrib::NjettinessExtras *extras4 = fastjet::contrib::njettiness_extras(njet_seq4);
//
// // and find the jets
//             std::vector<fastjet::PseudoJet> njet_jets2 = njet_seq2.inclusive_jets();
//             std::vector<fastjet::PseudoJet> njet_jets3 = njet_seq3.inclusive_jets();
//             std::vector<fastjet::PseudoJet> njet_jets4 = njet_seq4.inclusive_jets();
//
// // (alternative way to find the jets)
// //std::vector<fastjet::PseudoJet> njet_jets2 = extras2->jets();
// //std::vector<fastjet::PseudoJet> njet_jets3 = extras3->jets();
// //std::vector<fastjet::PseudoJet> njet_jets4 = extras4->jets();
//
//             std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//             std::cout << _testCutoffMeasures[iM].description() << ":" << std::endl;
//             std::cout << _testRecommendedAxes[iA].description() << ":" << std::endl;
//
//             PrintJets(njet_jets2);
//             std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//             PrintJets(njet_jets3);
//             std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//             PrintJets(njet_jets4);
//
// // The axes might point in a different direction than the jets
// // Using the NjettinessExtras pointer (ClusterSequence::Extras) to access that information
//             std::vector<fastjet::PseudoJet> njet_axes2 = extras2->axes();
//             std::vector<fastjet::PseudoJet> njet_axes3 = extras3->axes();
//             std::vector<fastjet::PseudoJet> njet_axes4 = extras4->axes();
//
//             std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
//             std::cout << "Axes Used for Above Jets" << std::endl;
//
//             PrintJets(njet_axes2);
//             std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//             PrintJets(njet_axes3);
//             std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//             PrintJets(njet_axes4);
//
//             bool calculateArea = false;
//             if (calculateArea) {
//                 std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
//                 std::cout << "Adding Area Information (quite slow)" << std::endl;
//
//                 double ghost_maxrap = 5.0; // e.g. if particles go up to y=5
//                 fastjet::AreaDefinition area_def(fastjet::active_area_explicit_ghosts, fastjet::GhostedAreaSpec(ghost_maxrap));
//
// // Defining cluster sequences with area
//                 fastjet::ClusterSequenceArea njet_seq_area2(input_particles, njet_jetDef2, area_def);
//                 fastjet::ClusterSequenceArea njet_seq_area3(input_particles, njet_jetDef3, area_def);
//                 fastjet::ClusterSequenceArea njet_seq_area4(input_particles, njet_jetDef4, area_def);
//
//                 std::vector<fastjet::PseudoJet> njet_jets_area2 = njet_seq_area2.inclusive_jets();
//                 std::vector<fastjet::PseudoJet> njet_jets_area3 = njet_seq_area3.inclusive_jets();
//                 std::vector<fastjet::PseudoJet> njet_jets_area4 = njet_seq_area4.inclusive_jets();
//
//                 PrintJets(njet_jets_area2);
//                 std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//                 PrintJets(njet_jets_area3);
//                 std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
//                 PrintJets(njet_jets_area4);
//             }
//
//         }
//     }
//
//     std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//     std::cout << "Done Using N-jettiness as a Jet Algorithm" << std::endl;
//     std::cout << "-------------------------------------------------------------------------------------" << std::endl;
//
// }
//
//
//
//
//
//
//
//

