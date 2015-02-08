# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("TopSemi");
    DefineVariables();
}

hanalysis::HTopSemiTagger::~HTopSemiTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HTopSemiTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger)
{
    Print(HNotification, "SetTagger");

    SetTaggerName("TopSemi");
    DefineVariables();

    BottomTagger = NewBottomTagger;
//     BottomTagger.SetTagger();
//     BottomReader.SetMva(BottomTagger);

    WSemiTagger = NewWSemiTagger;
//     WSemiTagger.SetTagger();
//     WSemiReader.SetMva(WSemiTagger);

    TopWindow = 50;

}

void hanalysis::HTopSemiTagger::DefineVariables()
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

HTopSemiBranch hanalysis::HTopSemiTagger::GetBranch(const hanalysis::HTriplet &Triplet) const
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    HTopSemiBranch TopSemiBranch;
    TopSemiBranch.Mass = Triplet.Jet().m();
    TopSemiBranch.Rap = Triplet.Jet().rap();
    TopSemiBranch.Phi = Triplet.Jet().phi();
    TopSemiBranch.Pt = Triplet.Jet().pt();
    TopSemiBranch.Ht = Triplet.Ht();

    TopSemiBranch.BottomPt = Triplet.Singlet().pt();
    TopSemiBranch.WPt = Triplet.DoubletJet().pt();

    TopSemiBranch.DeltaPt = Triplet.DeltaPt();
    TopSemiBranch.DeltaR = Triplet.DeltaR();
    TopSemiBranch.DeltaRap = Triplet.DeltaRap();
    TopSemiBranch.DeltaPhi = Triplet.DeltaPhi();

    TopSemiBranch.Bdt = Triplet.Bdt();
    TopSemiBranch.Tag = Triplet.Tag();

    return TopSemiBranch;
}

std::vector< HTopSemiBranch > hanalysis::HTopSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Top Tags");

    HJets Jets = GetJets(Event);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());
    Leptons = fastjet::sorted_by_pt(Leptons);
    if (Leptons.size() > 1) Leptons.erase(Leptons.begin() + 1, Leptons.end());

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    Print(HInformation, "Number Doublets", Doublets.size());

    HJets WParticles = Event->GetParticles()->GetGeneratorJets();
    WParticles.erase(std::remove_if(WParticles.begin(), WParticles.end(), WrongFamily(WId, TopId)), WParticles.end());
    if (WParticles.size() != 1) {
        Print(HError, "Where is the W?", WParticles.size());
    } else {
        std::sort(Doublets.begin(), Doublets.end(), MinDeltaR(WParticles.front()));
        if (Tag == HSignal && Doublets.size() > 1) Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    HJets BParticles = Event->GetParticles()->GetGeneratorJets();
    BParticles.erase(std::remove_if(BParticles.begin(), BParticles.end(), WrongFamily(BottomId, TopId)), BParticles.end());
    if (BParticles.size() != 1) {
        Print(HError, "Where is the Bottom?");
    } else {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(BParticles.front()));
//         if (Tag == HSignal && Jets.size() > 2) {
//             Jets.erase(Jets.begin() + 2, Jets.end());
//         } else
          if (Tag == HSignal && Jets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
//         if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());
    }



//     if (BParticles.size() > 0 && WParticles.size() > 0 && Jets.size() > 0 && Doublets.size() > 0)Print(HError, "Delta R", BParticles.front().delta_R(WParticles.front()), Jets.front().delta_R(Doublets.front().Jet()));

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
//         std::vector<HTriplet> PreTriplets;
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(Tag);
//             Triplet.SetTag(GetTag(Triplet));
//             if (Triplet.Tag() != Tag) continue;
//             if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//             if (Tag == HBackground && std::abs(Triplet.Jet().m() - TopMass) < TopWindow / 2) continue;
//             for (const auto Particle : Particles) if (Tag == HBackground && Triplet.Jet().delta_R(Particle) < std::min(Triplet.DeltaR(),float(0.4))) continue;
            if (Tag == HSignal && Triplet.DeltaR() > 1) continue; // FIXME assumption of boost larger 400
//             if (Tag == HBackground && Triplet.DeltaR() < 0.5) continue; // FIXME assumption of boost larger 400
//             PreTriplets.push_back(Triplet);
            Triplets.push_back(Triplet);
        }
//         if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByMass(TopMass));
//         if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
    }




    HJets TopParticles = Event->GetParticles()->GetGeneratorJets();
//     if (Tag == HSignal) {
        TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(TopId)), TopParticles.end());
        if (TopParticles.size() != 1) {
            Print(HError, "Where is the Top?");
        } else {
            std::sort(Triplets.begin(), Triplets.end(), MinDeltaR(TopParticles.front()));
//             if (Tag == HSignal && Triplets.size() > 1) Triplets.erase(Triplets.begin() + 1, Triplets.end());
            if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());
        }
//     } else {
//         TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongFamily(TopId, GluonId)), TopParticles.end());
//         if (TopParticles.size() != 1) {
//             Print(HError, "Where is the Top?");
//         } else {
//             std::sort(Triplets.begin(), Triplets.end(), SortByDeltaR(TopParticles.front()));
// //             if (Tag == HSignal && Triplets.size() > 1) Triplets.erase(Triplets.begin() + 1, Triplets.end());
//             if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());
//         }
//     }



    if (Tag == HSignal && Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

//     if (Tag == HBackground && Triplets.size() > 1) {
//       std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
//       Triplets.erase(Triplets.begin());
//     }

    Print(HInformation, "Number Triplets", Triplets.size());

    std::vector<HTopSemiBranch> TopSemiBranches;
    for (const auto & Triplet : Triplets) TopSemiBranches.push_back(GetBranch(Triplet));

    return TopSemiBranches;
}

hanalysis::HObject::HTag hanalysis::HTopSemiTagger::GetTag(const hanalysis::HTriplet &Triplet) const
{
    Print(HInformation, "Get Triple Tag");

    HJetInfo BJetInfo = Triplet.Singlet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    BJetInfo.PrintAllInfos(HInformation);
    HJetInfo W1JetInfo = Triplet.Doublet().Singlet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(WId);
    W1JetInfo.PrintAllInfos(HInformation);

    if (std::abs(W1JetInfo.MaximalId()) != WId) return HBackground;
    if (std::abs(BJetInfo.MaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.MaximalId()) != sgn(W1JetInfo.MaximalId())) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader &Reader)
{

    Print(HInformation, "Get Bdt");

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
//         std::vector<HTriplet> PreTriplets;
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
//             if (std::abs(Triplet.DeltaRap()) > 100) continue;
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(Reader.Bdt());
//             PreTriplets.push_back(Triplet);
            Triplets.push_back(Triplet);
        }
//         if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByMass(TopMass));
//         if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());

    return Triplets;
}

