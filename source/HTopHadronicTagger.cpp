# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger()
{
//         DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("TopHadronic");
    DefineVariables();
}

hanalysis::HTopHadronicTagger::~HTopHadronicTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HTopHadronicTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    BottomTagger = NewBottomTagger;
//     BottomTagger.SetTagger();
//     BottomReader.SetMva(BottomTagger);

    WTagger = NewWTagger;
//     WTagger.SetTagger(NewBottomTagger);
//     WReader.SetMva(WTagger);

    SetTaggerName("TopHadronic");
    DefineVariables();

    TopWindow = 50;
    JetRadiusParameter = 1;
}

void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

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
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

    Print(HNotification, "Variables defined");

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
    TopHadronicBranch.DeltaR = Triplet.DeltaR();
    TopHadronicBranch.DeltaRap = Triplet.DeltaRap();
    TopHadronicBranch.DeltaPhi = Triplet.DeltaPhi();

    TopHadronicBranch.Bdt = Triplet.Bdt();
    TopHadronicBranch.Tag = Triplet.Tag();
    return TopHadronicBranch;
}

std::vector< HTopHadronicBranch > hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag.HeavyParticles = {TopId};
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    HJets Jets = GetJets(Event, JetTag);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    std::vector<HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets;

    // 3 Jets are one top
    for (const auto & Jet : Jets) {
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            Triplets.push_back(Triplet);
        }
    }
//     Print(HError, "Number of Triplets 1", Triplets.size());


    HJets TopParticles = Event->GetParticles()->GetGeneratorJets();
    TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(-TopId)), TopParticles.end());
    if (TopParticles.size() != 1) Print(HError, "Where is the Top?", TopParticles.size());
    std::sort(Jets.begin(), Jets.end(), SortByDeltaR(TopParticles.front()));
    if (Tag == HSignal && Jets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
    if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());


    // 1 Jet is one top
    for (const auto Jet : Jets) {
        HJets Pieces = WTagger.GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PiecesDoublets = WTagger.GetBdt(Pieces, WReader);
        for (const auto & Doublet : PiecesDoublets)
            for (const auto & Piece : Pieces) {
                if (Piece == Doublet.Singlet1()) continue;
                if (Piece == Doublet.Singlet2()) continue;
                HTriplet Triplet(Doublet, Piece);
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                Triplets.push_back(Triplet);
            }
    }
//     Print(HError, "Number of Triplets 2", Triplets.size());

    // 1 Jet is one top
    for (const auto Jet : Jets) {
        HJets Pieces = WTagger.GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PiecesDoublets = WTagger.GetBdt(Pieces, WReader);
        for (const auto & Doublet : PiecesDoublets)
            for (const auto & Piece : Pieces) {
                if (Piece == Doublet.Singlet1()) continue;
                if (Piece == Doublet.Singlet2()) continue;
                HTriplet Triplet(Doublet, Piece);
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                Triplets.push_back(Triplet);
            }
    }
//     Print(HError, "Number of Triplets 3", Triplets.size());



    std::sort(Triplets.begin(), Triplets.end(), SortByDeltaR(TopParticles.front()));
    if (Tag == HSignal && Triplets.size() > 1) Triplets.erase(Triplets.begin() + 1, Triplets.end());
    if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());

//     Print(HError, "Number of Triplets 4", Triplets.size());

//     // combine jets with pairs
//     for (const auto & Jet : Jets)
//         for (const auto & Doublet : Doublets) {
//             if (Jet == Doublet.Singlet1()) continue;
//             if (Jet == Doublet.Singlet2()) continue;
//             HTriplet Triplet(Doublet, Jet);
//             Triplet.SetTag(GetTag(Triplet));
//             if (Triplet.Tag() != Tag) continue;
//             if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//             for (const auto Particle : TopParticles) if (Tag == HBackground && Triplet.Jet().delta_R(Particle) < std::min(Triplet.DeltaR(), float(0.4))) continue;
//             Triplets.push_back(Triplet);
//         }
//
//     // choose single jets
//     for (const auto & Jet : Jets) {
//         if (Tag == HSignal && std::abs(Jet.m() - TopMass) > TopWindow) continue;
//         HTriplet Triplet(Jet);
//         Triplet.SetTag(GetTag(Jet));
//         if (Triplet.Tag() != Tag) continue;
//         for (const auto Particle : TopParticles) if (Tag == HBackground && Triplet.Jet().delta_R(Particle) < std::min(Triplet.DeltaR(), float(0.4))) continue;
// //         if (Jet.m() != Triplet.Jet().m()) Print(HError, "Triplet Mass Error", Jet.m(), Triplet.Jet().m());
// //         if (Jet.pt() != Triplet.Jet().pt()) Print(HError, "Triplet Pt Error", Jet.pt(), Triplet.Jet().pt());
// //         if (Jet != Triplet.Jet()) Print(HError, "Triplet Jet Error 1", Jet);
// //         if (Jet != Triplet.Jet()) Print(HError, "Triplet Jet Error 3", Triplet.Jet());
//         Triplets.push_back(Triplet);
//     }

    if (Tag == HSignal && Triplets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
        Triplets.erase(Triplets.begin() + 1, Triplets.end()); // FIXME assuming maximal one hadronic top
    }

    if (Tag == HBackground && Triplets.size() > 1) {
      Print(HInformation, "Number of Jet Pairs", Triplets.size());
      std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
      Triplets.erase(Triplets.begin() ); // FIXME assuming maximal one hadronic top
    }
//     Print(HError, "Number of Triplets 5", Triplets.size());


    std::vector<HTopHadronicBranch> HadronicTopBranches;
    for (const auto & Triplet : Triplets) HadronicTopBranches.push_back(GetBranch(Triplet));

    return HadronicTopBranches;

}










hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    HJetInfo BJetInfo = Triplet.Singlet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    HJetInfo W1JetInfo = Triplet.Doublet().Singlet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(WId);
    HJetInfo W2JetInfo = Triplet.Doublet().Singlet2().user_info<HJetInfo>();
    W2JetInfo.ExtractFraction(WId);

    if (std::abs(W1JetInfo.MaximalId()) != WId) return HBackground;
    if (W1JetInfo.MaximalId() != W2JetInfo.MaximalId()) return HBackground;
    if (std::abs(BJetInfo.MaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.MaximalId()) != sgn(W1JetInfo.MaximalId())) return HBackground;
    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Get Jet Tag");

    HJetInfo JetInfo = Jet.user_info<HJetInfo>();
    JetInfo.ExtractFraction(TopId);

    if (JetInfo.MaximalId() != TopId) return HBackground;
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
            if (Triplet.DeltaR() < MinCellResolution) continue;
            if (Triplet.Jet().m() < 10) continue;
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader.Bdt());
            Triplets.push_back(Triplet);
        }

    for (const auto & Jet : Jets) {
        HTriplet Triplet(Jet);
        if (Triplet.Jet().m() < 10) continue;
        Branch = GetBranch(Triplet);
        Triplet.SetBdt(TopHadronicReader.Bdt());
        Triplets.push_back(Triplet);
    }


    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    return Triplets;
}
