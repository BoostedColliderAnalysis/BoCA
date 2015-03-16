# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger()
{
//         DebugLevel = hanalysis::HObject::HDebug;
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
    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch.WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaHt, "DeltaHt"));
    Observables.push_back(NewObservable(&Branch.DeltaM, "DeltaM"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.WBdt, "WBdt"));
    Observables.push_back(NewObservable(&Branch.BBdt, "BBdt"));
    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));
}

HTopHadronicBranch hanalysis::HTopHadronicTagger::GetBranch(const hanalysis::HTriplet &Triplet) const
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    HTopHadronicBranch TopHadronicBranch;

    TopHadronicBranch.Mass = Triplet.Jet().m();
    TopHadronicBranch.Rap = Triplet.Jet().rap();
    TopHadronicBranch.Phi = Triplet.Jet().phi();
    TopHadronicBranch.Pt = Triplet.Jet().pt();
    TopHadronicBranch.Ht = Triplet.Ht();

    TopHadronicBranch.BottomPt = Triplet.Singlet().pt();
    TopHadronicBranch.WPt = Triplet.DoubletJet().pt();

    TopHadronicBranch.DeltaPt = Triplet.DeltaPt();
    TopHadronicBranch.DeltaHt = Triplet.DeltaHt();
    TopHadronicBranch.DeltaM = Triplet.DeltaM();
    TopHadronicBranch.DeltaR = Triplet.DeltaR();
    TopHadronicBranch.DeltaRap = Triplet.DeltaRap();
    TopHadronicBranch.DeltaPhi = Triplet.DeltaPhi();

    TopHadronicBranch.Bdt = Triplet.Bdt();
    TopHadronicBranch.WBdt = Triplet.Doublet().Bdt();
    TopHadronicBranch.BBdt = Triplet.Singlet().user_info<HJetInfo>().Bdt();
    TopHadronicBranch.Tag = Triplet.Tag();
    return TopHadronicBranch;
}

std::vector< HTopHadronicBranch > hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
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

    // 3 Jets are one top
    for (const auto & Jet : Jets) {
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
            if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
            if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
            Triplets.push_back(Triplet);
        }
    }
//     Print(HError, "Number of Triplets 1", Triplets.size());

    // 2 Jet form one top
    for (const auto Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PiecesDoublets = WTagger.GetBdt(Pieces, WReader);
        for (const auto & Doublet : PiecesDoublets)
            for (const auto & Jet2 : Jets) {
                if (Jet == Jet2) continue;
                HTriplet Triplet(Doublet, Jet2);
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
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
                    if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
                    Triplets.push_back(Triplet);
                }
            }
        }
    }

    for (const auto Jet : Jets) {
        HTriplet Triplet(Jet);
        if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
        if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
        if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
        Triplets.push_back(Triplet);
    }


    if (Triplets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        Triplets = SortByMassTo(Triplets, TopMass);
        switch (Tag) {
        case HSignal :
            Triplets.erase(Triplets.begin() + 1, Triplets.end()); // FIXME assuming maximal one hadronic top
            break;
//         case HBackground :
//             Triplets.erase(Triplets.begin());  // FIXME assuming maximal one hadronic top
//             break;
        }
    }

    std::vector<HTopHadronicBranch> HadronicTopBranches;
    for (auto & Triplet : Triplets) {
        Triplet.SetTag(Tag);
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

//     HJetInfo JetInfo = Jet.user_info<HJetInfo>();
//     JetInfo.ExtractFraction(TopId);
//
//     if (JetInfo.MaximalId() != TopId) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader &TopHadronicReader)
{

    std::vector<HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//             if (Triplet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader.Bdt());
            Triplets.push_back(Triplet);
        }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    return Triplets;
}


hanalysis::HTriplet  hanalysis::HTopHadronicTagger::GetBdt(HTriplet &Triplet, const HReader &TopHadronicReader)
{
    Branch = GetBranch(Triplet);
    Triplet.SetBdt(TopHadronicReader.Bdt());
    return Triplet;
}


std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(HJets &Jets, const hanalysis::HReader &TopHadronicReader, hanalysis::HWTagger &WTagger, hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader)
{
    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
        TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
        TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    for (const auto & Jet : Jets) {
      HTriplet Triplet(Jet);
      if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
      Branch = GetBranch(Triplet);
      Triplet.SetBdt(TopHadronicReader.Bdt());
      TripletsHadronic.push_back(Triplet);
    }

    if (TripletsHadronic.size() > 1) {
        std::sort(TripletsHadronic.begin(), TripletsHadronic.end());
        TripletsHadronic.erase(TripletsHadronic.begin() + std::min(MaxCombi, int(TripletsHadronic.size())), TripletsHadronic.end());
    }

    return TripletsHadronic;

}


// std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(HJets &Jets, const HReader &TopHadronicReader)
// {
//   std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//   std::vector<hanalysis::HTriplet> TripletsHadronic = GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//
//   for (const auto & Jet : Jets) {
//     HJets Pieces = GetSubJets(Jet, 2);
//     Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
//     std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
//     std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
//     TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
//   }
//
//   for (const auto & Jet : Jets) {
//     HJets Pieces = GetSubJets(Jet, 3);
//     Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
//     std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
//     std::vector<hanalysis::HTriplet> PieceTriplets = GetBdt(PieceDoublets, Jets, TopHadronicReader);
//     TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
//   }
//
//   if(TripletsHadronic.size()>1){
//     std::sort(TripletsHadronic.begin(), TripletsHadronic.end());
//     TripletsHadronic.erase(TripletsHadronic.begin() + std::min(MaxCombi, int(TripletsHadronic.size())), TripletsHadronic.end());
//   }
//
//   return TripletsHadronic;
//
// }
