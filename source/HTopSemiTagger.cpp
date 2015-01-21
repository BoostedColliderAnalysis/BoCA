# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger(HBottomTagger *const NewBottomTagger, HWSemiTagger *const NewWSemiTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new HReader(WSemiTagger);
    SetTaggerName("TopSemi");
    Branch = new HTopSemiBranch();
    JetTag = new HJetTag();
    DefineVariables();
    TopWindow = 80;

}

hanalysis::HTopSemiTagger::~HTopSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WSemiReader;
}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch->BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch->WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HTopSemiTagger::FillBranch(HTopSemiBranch *const TopSemiBranch, const HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    TopSemiBranch->Mass = Triplet.Jet().m();
    TopSemiBranch->Rap = Triplet.Jet().rap();
    TopSemiBranch->Phi = Triplet.Jet().phi();
    TopSemiBranch->Pt = Triplet.Jet().pt();
    TopSemiBranch->Ht = Triplet.Ht();

    TopSemiBranch->BottomPt = Triplet.Singlet().pt();
    TopSemiBranch->WPt = Triplet.DoubletJet().pt();

    TopSemiBranch->DeltaR = Triplet.DeltaR();
    TopSemiBranch->DeltaRap = Triplet.DeltaRap();
    TopSemiBranch->DeltaPhi = Triplet.DeltaPhi();

    TopSemiBranch->Bdt = Triplet.Bdt();
    TopSemiBranch->Tag = Triplet.Tag();

}

void hanalysis::HTopSemiTagger::FillBranch(const HTriplet &Triple)
{
    Print(HInformation, "Fill Top Tagger", Triple.Bdt());
    FillBranch(Branch, Triple);
}

// struct SortByTopMass {
//     inline bool operator()(const hanalysis::HTriplet &Triplet1, const hanalysis::HTriplet &Triplet2) {
//         return (std::abs(Triplet1.GetJet().m() - Triplet1.TopMass) < std::abs(Triplet2.GetJet().m() - Triplet2.TopMass));
//     }
// };


std::vector<HTopSemiBranch *> hanalysis::HTopSemiTagger::GetBranches(HEvent *const Event, const HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
        std::vector<HTriplet> PreTriplets;
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.Tag() != Tag) continue;
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            if (Tag == HSignal && Triplet.DeltaR() > 1.5) continue; // FIXME assumption of boost larger 400
            PreTriplets.push_back(Triplet);
        }
        if (PreTriplets.size() > 2) Print(HError, "More than one semi lep W");
        if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByMass<HTriplet>(TopMass));
        if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
    }


// <<<<<<< .mine

//     for (const auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 2) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//                 if (Pieces.size() > 2) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         Piece.set_user_info(JetInfo);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//
//                     for (const auto & Piece : Pieces) {
//                         std::vector<HTriplet> PreTriplets;
//                         for (const auto & Doublet : Doublets) {
//                             HTriplet Triplet(Doublet, Piece);
//                             Triplet.SetTag(GetTag(Triplet));
//                             if (Triplet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//                             if (Triplet.GetDeltaR() > 1) continue;
//                             PreTriplets.push_back(Triplet);
//                         }
//                         if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByTopMass());
//                         if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
//                     }
//
//                 }
//             }
//     }
//
//
//
//     for (const auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 3) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
//                 if (Pieces.size() > 3) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         Piece.set_user_info(JetInfo);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//
//                     for (const auto & Piece : Pieces) {
//                         std::vector<HTriplet> PreTriplets;
//                         for (const auto & Doublet : Doublets) {
//                             HTriplet Triplet(Doublet, Piece);
//                             Triplet.SetTag(GetTag(Triplet));
//                             if (Triplet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//                             if (Triplet.GetDeltaR() > 1) continue;
//                             PreTriplets.push_back(Triplet);
//                         }
//                         if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByTopMass());
//                         if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
//                     }
//
//                 }
//             }
//     }


//     if (Tag == HBackground || (Tag == HSignal && Triplets.size() < 1)) {
//         for (const auto Jet : Jets) {
//             fastjet::PseudoJet EmptyJet(0, 0, 0, 0);
//             HDoublet Doublet(EmptyJet, EmptyJet);
//             Doublet.SetBdt(Jet.user_info<HJetInfo>().Bdt());
//             HTriplet Triplet(Doublet, Jet);
//             Triplet.SetTag(GetTag(Jet));
//             if (Triplet.Tag() != Tag) continue;
//             if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//             Triplets.push_back(Triplet);
//         }
//     }

// =======
// >>>>>>> .r716
    if (Tag == HSignal && Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end(), SortByMass<HTriplet>(TopMass));
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    Print(HInformation, "Number Triplets", Triplets.size());

    std::vector<HTopSemiBranch *> TopSemiBranches;
    for (const auto & Triplet : Triplets) {
        HTopSemiBranch *TopSemiBranch = new HTopSemiBranch();
        FillBranch(TopSemiBranch, Triplet);
        TopSemiBranches.push_back(TopSemiBranch);
    }
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

    if (std::abs(W1JetInfo.GetMaximalId()) != WId) return HBackground;
    if (std::abs(BJetInfo.GetMaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.GetMaximalId()) != sgn(W1JetInfo.GetMaximalId())) return HBackground;
    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HTopSemiTagger::GetTag(const fastjet::PseudoJet &Singlet) const
{
    Print(HInformation, "Get Triple Tag", GetParticleName(Singlet.user_index()));

    HJetInfo JetInfo = Singlet.user_info<HJetInfo>();
    JetInfo.ExtractFraction(TopId);
    JetInfo.PrintAllInfos(HInformation);

    if (std::abs(JetInfo.GetMaximalId()) != TopId) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const fastjet::PseudoJet &MissingEt, const HReader *const Reader)
{

    Print(HInformation, "Get Bdt",MissingEt.pt());

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
        std::vector<HTriplet> PreTriplets;
        for (const auto & Doublet : Doublets) {
          HTriplet Triplet(Doublet, Jet);
          if (std::abs(Triplet.Jet().m() - TopMass) > 2*TopWindow) continue; //FIXME remove this hack again
            FillBranch(Triplet);
            Triplet.SetBdt(Reader->Bdt());
            PreTriplets.push_back(Triplet);
        }
        if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByMass<HTriplet>(TopMass));
        if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());

    return Triplets;
}

