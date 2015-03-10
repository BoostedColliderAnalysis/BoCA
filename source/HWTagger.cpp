# include "HWTagger.hh"

hanalysis::HWTagger::HWTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();

}

void hanalysis::HWTagger::SetTagger(const HBottomTagger &NewBottomTagger)
{
    Print(HNotification, "Set Tagger");
    BottomTagger = NewBottomTagger;
    WMassWindow = 20;
    DefineVariables();
}

void hanalysis::HWTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("WHadronic");
    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));

    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));
}

HWBranch hanalysis::HWTagger::GetBranch(const HDoublet &Doublet) const
{
    Print(HInformation, "FillPairTagger", Doublet.Bdt());
    HWBranch WBranch;
    WBranch.Mass = Doublet.Jet().m();
    WBranch.Rap = Doublet.Jet().rap();
    WBranch.Phi = Doublet.Jet().phi();
    WBranch.Pt = Doublet.Jet().pt();
    WBranch.Ht = Doublet.Ht();
    WBranch.DeltaPt = std::abs(Doublet.DeltaPt());
    WBranch.DeltaR = Doublet.DeltaR();
    WBranch.DeltaRap = std::abs(Doublet.DeltaRap());
    WBranch.DeltaPhi = std::abs(Doublet.DeltaPhi());
    WBranch.Bdt = Doublet.Bdt();
    WBranch.Tag = Doublet.Tag();
    return WBranch;

}

std::vector<HWBranch> hanalysis::HWTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get W Tags");
    std::vector<HDoublet> Doublets;

    HJets Jets = GetJets(Event);
    Print(HInformation, "Jets Number", Jets.size());

    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    Print(HInformation, "Bottom Tagger Number", Jets.size());

    HJets WKids = GetWDaughters(Event);
    int WHadId = WId;
    if (WKids.size() > 0) WHadId = GetWHadId(WKids);

//     // 2 Jets form 1 W
//     HJets JetPairs;
//     if (WKids.size() > 0) std::sort(Jets.begin(), Jets.end(), MinDeltaR(WKids.at(0)));
//     if (Tag == HSignal && Jets.size() > 1) JetPairs.push_back(Jets.front());
//     if (Tag == HBackground && Jets.size() > 1) JetPairs.insert(JetPairs.end(), Jets.begin() + 1 , Jets.end());
//
//     if (WKids.size() > 1) std::sort(Jets.begin(), Jets.end(), MinDeltaR(WKids.at(1)));
//     if (Tag == HSignal && Jets.size() > 1) JetPairs.push_back(Jets.front());
//     if (Tag == HSignal && JetPairs.size() != 2) Print(HError, "lost the W jets", JetPairs.size());
//
//     for (const auto & Jet1 : JetPairs) {
//         for (const auto & Jet2 : JetPairs) {
//             if (Jet1 == Jet2) continue;
//             HDoublet Doublet(Jet1, Jet2);
//             if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//             Doublets.push_back(Doublet);
//         }
//     }
//
//     fastjet::PseudoJet WParticle = WKids.at(0) + WKids.at(1);


    HJets WParticles = Event.GetParticles()->Generator();
    WParticles.erase(std::remove_if(WParticles.begin(), WParticles.end(), WrongId(WHadId)), WParticles.end());
    if (Tag == HSignal && WParticles.size() != 1) Print(HError, "Where is the W?", WParticles.size());
    std::sort(Jets.begin(), Jets.end(), MinDeltaR(WParticles.front()));

//  1 Jet (2 subjets) form(s) 1 W
//     HJets WJets;
//     if (Tag == HSignal && Jets.size() > 1) WJets.push_back(Jets.front());
//     if (Tag == HBackground && Jets.size() > 1) WJets.insert(WJets.end(), Jets.begin() + 1 , Jets.end());
//     for (const auto & Jet : WJets) {
//         HJets Pieces = GetSubJets(Jet, 2);
//         Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
//         for (const auto & Piece1 : Pieces) {
//             for (const auto & Piece2 : Pieces) {
//                 if (Piece1 == Piece2) continue;
//                 HDoublet Doublet(Piece1, Piece2);
//                 if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//                 Doublets.push_back(Doublet);
//             }
//         }
//     }
//
//     HJets TopParticles = Event.GetParticles()->Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(sgn(WHadId)*TopId)), TopParticles.end());
//     Print(HInformation, "Particle size", TopParticles.size());
//     if (TopParticles.size() != 1) Print(HError, "Where is the Top?", TopParticles.size());
//     std::sort(Jets.begin(), Jets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == HSignal && Jets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
//     if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());

    // W is in 2 of 3 subjets
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2)continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                Doublets.push_back(Doublet);
            }
    }

//     // W is in 1 of 2 subjet
//     for (const auto & Jet : Jets) {
//         HJets Pieces = GetSubJets(Jet, 2);
//         Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
//         for (const auto & Piece : Pieces) {
//             HDoublet Doublet(Piece, Piece);
//             if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//             Doublets.push_back(Doublet);
//         }
//     }



    const int WNumber = 1; // MUST BE 1 FOR THE ANALYSIS
    std::sort(Doublets.begin(), Doublets.end(), MinDeltaR(WParticles.front()));
//     std::sort(Doublets.begin(), Doublets.end(), SortByMass(WMass));
    if (Tag == HSignal && Doublets.size() > WNumber) Doublets.erase(Doublets.begin() + WNumber, Doublets.end());
    if (Tag == HBackground && Doublets.size() > WNumber) Doublets.erase(Doublets.begin());

    std::vector<HWBranch> Branches;
    for (const auto & Doublet : Doublets) Branches.push_back(GetBranch(Doublet));
    return Branches;
}

// hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const HDoublet &Doublet)
// {
//     Print(HInformation, "Get Doublet Tag");
//
//     if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
//
//     if (Doublet.Singlet1().user_info<HJetInfo>().MaximalId() != Doublet.Singlet2().user_info<HJetInfo>().MaximalId()) return HBackground;
//
//     return HSignal;
// }

// hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
// {
//     Print(HInformation, "Get Singlet Tag");
//
//     if (std::abs(Singlet.user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
//     return HSignal;
// }

HJets hanalysis::HWTagger::GetWDaughters(HEvent &Event)
{
    HJets WKids = Event.GetParticles()->Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(HError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfLetpons(WKids);
    if (WKids.size() != 2) Print(HError, "Where is the W 2?", WKids.size());
    else Print(HInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id));
    return WKids;
}

int hanalysis::HWTagger::GetWHadId(const HJets &Jets)
{
    if (Jets.size() < 1) return WId;
    else return Jets.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id;
}


std::vector<hanalysis::HDoublet>  hanalysis::HWTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &WReader)
{
    Print(HInformation, "Get Doublet Bdt");

    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            if (Doublet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
            if (Doublet.Jet().m() < 10) continue;
            if (Doublet.Jet().m() > (TopMass + WMass) / 2) continue;
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(WReader.Bdt());
            Doublets.push_back(Doublet);
        }

    for (auto & Jet : Jets) {
        HDoublet Doublet(Jet);
        if (Doublet.Jet().m() < 10) continue;
        if (Doublet.Jet().m() > (TopMass + WMass) / 2) continue;
        Branch = GetBranch(Doublet);
        Doublet.SetBdt(WReader.Bdt());
        Doublets.push_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}


hanalysis::HDoublet hanalysis::HWTagger::GetBdt(HDoublet &Doublet, const hanalysis::HReader &WReader)
{
    Print(HInformation, "Get Doublet Bdt");

    Branch = GetBranch(Doublet);
    Doublet.SetBdt(WReader.Bdt());
    return Doublet;
}

// std::vector<HParticleBranch> hanalysis::HWTagger::GetConstituentBranches()
// {
//
//     Print(HInformation, "Get Higgs Tags");
//
//     std::vector<HDoublet> JetPairs;
//
//     Print(HInformation, "Number of Jet Pairs", JetPairs.size());
//
//     std::vector<HParticleBranch> ConstituentBranches;
//     for (const auto & JetPair : JetPairs) for (const auto & Constituent : JetPair.Constituents()) ConstituentBranches.push_back(GetBranch(Constituent));
//     return ConstituentBranches;
// }
//
// HParticleBranch hanalysis::HWTagger::GetBranch(const HKinematics &Vector)
// {
//     Print(HInformation, "Fill Constituent Branch");
//
//     HParticleBranch ConstituentBranch;
//     ConstituentBranch.Pt = Vector.GetPt();
//     ConstituentBranch.Rap = Vector.GetRap();
//     ConstituentBranch.Phi = Vector.GetPhi();
//     return ConstituentBranch;
// }
