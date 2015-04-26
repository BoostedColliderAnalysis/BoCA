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

//     Boost = true; // be carefull with this one!!


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.BottomPt, "BottomPt");
    AddObservable(Branch.WPt, "WPt");

    if (!Boost) {
        AddObservable(Branch.DeltaPt, "DeltaPt");
        AddObservable(Branch.DeltaHt, "DeltaHt");
        AddObservable(Branch.DeltaM, "DeltaM");
        AddObservable(Branch.DeltaPhi, "DeltaPhi");
        AddObservable(Branch.DeltaRap, "DeltaRap");
        AddObservable(Branch.DeltaR, "DeltaR");
    }

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


    if (!Boost) {
    AddObservable(Branch.WBdt, "WBdt");
    }
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

    if (!Boost) {

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
    std::vector<hanalysis::HTriplet> Triplets;
    if (!Boost) {

// 2 jets form a W
        std::vector<hanalysis::HDoublet> Doublets = WTagger.GetPairBdt(Jets, WReader);
// 3 jets form a top
        Triplets = GetBdt(Doublets, Jets, TopHadronicReader);

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

    }

// 1 jet forms a top
    for (const auto & Jet : Jets) {
// no supbjets
        HTriplet Triplet(Jet);
        NSubJettiness(Triplet);
//         if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // seems to be a really bad idea; no more higgses left
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

