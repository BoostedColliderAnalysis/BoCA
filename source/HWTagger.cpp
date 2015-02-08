# include "HWTagger.hh"

hanalysis::HWTagger::HWTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    SetTaggerName("WHadronic");
    DefineVariables();

}

hanalysis::HWTagger::~HWTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HWTagger::SetTagger(const HBottomTagger &NewBottomTagger)
{

    Print(HNotification, "Set Tagger");
    BottomTagger = NewBottomTagger;
//     BottomTagger.SetTagger();
//     BottomReader.SetMva(BottomTagger);

    WMassWindow = 20;
    JetRadiusParameter = 1;
    SetTaggerName("WHadronic");
    DefineVariables();
}

void hanalysis::HWTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

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

    Print(HNotification, "Variables defined");

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

std::vector<HWBranch> hanalysis::HWTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag.HeavyParticles = {WId};
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    HJets Jets = GetJets(Event, JetTag);
    Print(HInformation, "Jets Number", Jets.size());

    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    Print(HInformation, "Bottom Tagger Number", Jets.size());


    HJets WParticles = Event->GetParticles()->GetGeneratorJets();
    WParticles.erase(std::remove_if(WParticles.begin(), WParticles.end(), WrongFamily(-WId, -TopId)), WParticles.end());
    if (WParticles.size() != 1) Print(HError, "Where is the W?", WParticles.size());
    std::sort(Jets.begin(), Jets.end(), MinDeltaR(WParticles.front()));

    // 2 Jets in 1 W
    HJets W2Jets = Jets;
    if (Tag == HSignal && W2Jets.size() > 1) W2Jets.erase(W2Jets.begin() + 2, W2Jets.end());
    if (Tag == HBackground && W2Jets.size() > 1) W2Jets.erase(W2Jets.begin(), W2Jets.begin() + 1);

    std::vector<HDoublet> Doublets;
    for (const auto & Jet1 : Jets) {
        for (const auto & Jet2 : Jets) {
            if (Jet1 == Jet2) continue;
            HDoublet Doublet(Jet1, Jet2);
            if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            Doublets.push_back(Doublet);
        }
    }

    //  1 Jet (2 subjets) is 1 W
    HJets WJets = Jets;
    if (Tag == HSignal && WJets.size() > 1) WJets.erase(WJets.begin() + 1, WJets.end());
    if (Tag == HBackground && WJets.size() > 1) WJets.erase(WJets.begin());

    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                Doublets.push_back(Doublet);
            }
        }
    }


    HJets TopParticles = Event->GetParticles()->GetGeneratorJets();
    TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(-TopId)), TopParticles.end());
    Print(HInformation, "Particle size", TopParticles.size());
    if (TopParticles.size() != 1) Print(HError, "Where is the Top?", TopParticles.size());
    std::sort(Jets.begin(), Jets.end(), MinDeltaR(TopParticles.front()));
    if (Tag == HSignal && Jets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
    if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());

    // W is in 2 of 3 subjets
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<HDoublet> PiecePairs;
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2)continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                PiecePairs.push_back(Doublet);
            }
        std::sort(PiecePairs.begin(), PiecePairs.end(), MinDeltaR(WParticles.front()));
        if (Tag == HSignal && PiecePairs.size() > 1) PiecePairs.erase(PiecePairs.begin() + 1, PiecePairs.end());
        for (const auto & Pair : PiecePairs)Doublets.push_back(Pair);
    }

    // W is in 1 of 2 subjet
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<HDoublet> PieceDoublets;
        for (const auto & Piece1 : Pieces) {
            HDoublet Doublet(Piece1, Piece1);
            if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            PieceDoublets.push_back(Doublet);
        }
        std::sort(PieceDoublets.begin(), PieceDoublets.end(), MinDeltaR(WParticles.front()));
        if (Tag == HSignal && PieceDoublets.size() > 1) PieceDoublets.erase(PieceDoublets.begin() + 1, PieceDoublets.end());
        for (const auto & Doublet : PieceDoublets)Doublets.push_back(Doublet);
    }





//     for (const auto & Jet : Jets) static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractFraction(WId);


//     // combine 2 jets to one W
//     for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
//         for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
//             HDoublet Doublet((*Jet1), (*Jet2));
//             Doublet.SetTag(GetTag(Doublet));
//             if (Doublet.Tag() != Tag) continue;
//             if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//             for (const auto Particle : WParticles) if (Tag == HBackground && Doublet.Jet().delta_R(Particle) < std::min(Doublet.DeltaR(), float(0.4))) continue;
//             Doublets.push_back(Doublet);
    //         }


//     // choose single jets
//     for (const auto & Jet : Jets) {
//         if (!Jet.has_user_info<HJetInfo>()) {
//             Print(HError, "Jet without Jet Info");
//             continue;
//         }
//         static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
//         if (Jet.user_info<HJetInfo>().Tag() != Tag) continue;
//         if (Tag == HSignal && std::abs(Jet.m() - WMass) > WMassWindow) continue;
//         HDoublet Doublet(Jet);
//         for (const auto Particle : WParticles) if (Tag == HBackground && Doublet.Jet().delta_R(Particle) < std::min(Doublet.DeltaR(), float(0.4))) continue;
//         Doublets.push_back(Doublet);
//     }

    if (Tag == HSignal && Doublets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", Doublets.size());
        std::sort(Doublets.begin(), Doublets.end(), SortByMass(WMass));
        Doublets.erase(Doublets.begin() + 1, Doublets.end()); // FIXME assuming maximal one hadronic W
    }

    if (Tag == HBackground && Doublets.size() > 0) {
        Print(HInformation, "Number of Jet Pairs", Doublets.size());
        std::sort(Doublets.begin(), Doublets.end(), SortByMass(WMass));
        Doublets.erase(Doublets.begin()); // FIXME assuming maximal one hadronic W
    }

    std::vector<HWBranch> Branches;
    for (const auto & Doublet : Doublets) Branches.push_back(GetBranch(Doublet));
    return Branches;

}



hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Doublet Tag");

    if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != WId) return HBackground;

    if (Doublet.Singlet1().user_info<HJetInfo>().MaximalId() != Doublet.Singlet2().user_info<HJetInfo>().MaximalId()) return HBackground;

    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
{
    Print(HInformation, "Get Singlet Tag");

    if (std::abs(Singlet.user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HDoublet>  hanalysis::HWTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &WReader)
{
    Print(HInformation, "Get Doublet Bdt");

    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            if (Doublet.DeltaR() < MinCellResolution) continue;
            if (Doublet.Jet().m() < 10) continue;
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(WReader.Bdt());
            Doublets.push_back(Doublet);
        }

    for (auto & Jet : Jets) {
        HDoublet Doublet(Jet);
        if (Doublet.Jet().m() < 10) continue;
        Branch = GetBranch(Doublet);
        Doublet.SetBdt(WReader.Bdt());
        Doublets.push_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}

std::vector<HParticleBranch> hanalysis::HWTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<HDoublet> JetPairs;

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HParticleBranch> ConstituentBranches;
    for (const auto & JetPair : JetPairs) for (const auto & Constituent : JetPair.Constituents()) ConstituentBranches.push_back(GetBranch(Constituent));
    return ConstituentBranches;
}

HParticleBranch hanalysis::HWTagger::GetBranch(const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    HParticleBranch ConstituentBranch;
    ConstituentBranch.Pt = Vector.GetPt();
    ConstituentBranch.Rap = Vector.GetRap();
    ConstituentBranch.Phi = Vector.GetPhi();
    return ConstituentBranch;
}

