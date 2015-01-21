# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    SetTaggerName("TopHadronic");
    Branch = new HTopHadronicBranch();
    JetTag = new HJetTag();
    DefineVariables();
    TopWindow = 50;
    JetRadiusParameter = 1;
}

hanalysis::HTopHadronicTagger::~HTopHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WReader;
}

void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch->BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch->WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HTopHadronicTagger::FillBranch(HTopHadronicBranch *const TopHadronicBranch, const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    TopHadronicBranch->Mass = Triplet.Jet().m();
    TopHadronicBranch->Rap = Triplet.Jet().rap();
    TopHadronicBranch->Phi = Triplet.Jet().phi();
    TopHadronicBranch->Pt = Triplet.Jet().pt();
    TopHadronicBranch->Ht = Triplet.Ht();

    TopHadronicBranch->BottomPt = Triplet.Singlet().pt();
    TopHadronicBranch->WPt = Triplet.DoubletJet().pt();

    TopHadronicBranch->DeltaR = Triplet.DeltaPt();
    TopHadronicBranch->DeltaR = Triplet.DeltaR();
    TopHadronicBranch->DeltaRap = Triplet.DeltaRap();
    TopHadronicBranch->DeltaPhi = Triplet.DeltaPhi();

    TopHadronicBranch->Bdt = Triplet.Bdt();
    TopHadronicBranch->Tag = Triplet.Tag();
}

void hanalysis::HTopHadronicTagger::FillBranch(const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());
    FillBranch(Branch, Triplet);
}

// struct SortByTopMass {
//     inline bool operator()(const hanalysis::HTriplet &Triplet1, const hanalysis::HTriplet &Triplet2) {
//         return (std::abs(Triplet1.TopMass - Triplet1.GetJet().m()) < std::abs(Triplet2.TopMass - Triplet2.GetJet().m()));
//     }
// };


std::vector<HTopHadronicBranch *> hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

//     for(auto Jet :Jets) {
//         if(Jet.has_user_info<HJetInfo>()) Print(HError,"has info");
//         else Print(HError,"has no info");
//     }

//     Jets = WTagger->BottomTagger->GetBdt(Jets, WTagger->BottomReader);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    std::vector<HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet>  Triplets;

    // combine jets with pairs
    for (const auto & Jet : Jets)
        for (const auto & Doublet : Doublets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.Tag() != Tag) continue;
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            Triplets.push_back(Triplet);
        }

    // choose single jets
    for (const auto & Jet : Jets) {
        HTag Jettag = GetTag(Jet);
        if (Jettag != Tag) continue;
        if (Tag == HSignal && std::abs(Jet.m() - TopMass) > TopWindow) continue;
        HTriplet Triplet(Jet);
        Triplets.push_back(Triplet);
    }


    // combine subjets
    std::vector<HTriplet> Triplets2 = GetSubJets(Jets,2,Tag);
    Triplets.insert(Triplets.end(),Triplets2.begin(),Triplets2.end());

    std::vector<HTriplet> Triplets3 = GetSubJets(Jets,3,Tag);
    Triplets.insert(Triplets.end(),Triplets3.begin(),Triplets3.end());

// <<<<<<< .mine
//         for (auto & Jet : Jets) {
//           if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
//             fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//             std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//             //         if (Jet.has_pieces()) {
//             //             fastjet::JetDefinition JetDefinition(fastjet::cambridge_aachen_algorithm, JetSize);
//             //             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//             //             std::vector<fastjet::PseudoJet> Pieces = fastjet::sorted_by_pt(ClusterSequence.inclusive_jets());
//             Print(HInformation, "New Jet Number", Pieces.size());
//             if (Pieces.size() > 1) {
//               for (auto & Piece : Pieces) {
//                 hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                 JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                 JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                 Piece.set_user_info(JetInfo);
//               }
//               Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//               std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
//               for (auto Jet2 : Jets) {
//                 for (auto PiecesDoublet : PiecesDoublets) {
//                   if (Jet2 == Jet) continue;
//                   if (Jet2 == PiecesDoublet.Singlet1()) continue;
//                   if (Jet2 == PiecesDoublet.Singlet2()) continue;
//                   HTriplet Triplet(PiecesDoublet, Jet2);
//                   Triplet.SetTag(GetTag(Triplet));
//                   if (Triplet.Tag() != Tag) continue;
//                   if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//                   Triplets.push_back(Triplet);
// =======
//     for (auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 2) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//                 Print(HInformation, "New Jet Number", Pieces.size());
//                 if (Pieces.size() > 1) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         Piece.set_user_info(JetInfo);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                     std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
//                     for (auto Jet2 : Jets) {
//                         for (auto PiecesDoublet : PiecesDoublets) {
//                             if (Jet2 == Jet) continue;
//                             if (Jet2 == PiecesDoublet.Singlet1()) continue;
//                             if (Jet2 == PiecesDoublet.Singlet2()) continue;
//                             HTriplet Triplet(PiecesDoublet, Jet2);
//                             Triplet.SetTag(GetTag(Triplet));
//                             if (Triplet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//                             Triplets.push_back(Triplet);
//                         }
//                     }
// // >>>>>>> .r716
//                 }
//             }
//     }

// <<<<<<< .mine
//         for (auto & Jet : Jets) {
//           if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
//             fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//             std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
// //         if (Jet.has_pieces()) {
// //             fastjet::JetDefinition JetDefinition(fastjet::cambridge_aachen_algorithm, JetSize);
// //             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
// //             std::vector<fastjet::PseudoJet> Pieces = fastjet::sorted_by_pt(ClusterSequence.inclusive_jets());
//             Print(HInformation, "New Jet Number", Pieces.size());
//             if (Pieces.size() > 1) {
//                 for (auto & Piece : Pieces) {
//                     hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                     JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                     JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                     Piece.set_user_info(JetInfo);
//                 }
//                 Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                 std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
//                 for (auto Piece : Pieces) {
//                     for (auto PiecesDoublet : PiecesDoublets) {
//                         if (Piece == PiecesDoublet.Singlet1()) continue;
//                         if (Piece == PiecesDoublet.Singlet2()) continue;
//                         HTriplet Triplet(PiecesDoublet, Piece);
//                         Triplet.SetTag(GetTag(Triplet));
//                         if (Triplet.Tag() != Tag) continue;
//                         if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//                         Triplets.push_back(Triplet);
// =======
//     for (auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 2) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
//                 Print(HInformation, "New Jet Number", Pieces.size());
//                 if (Pieces.size() > 1) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         Piece.set_user_info(JetInfo);
// // >>>>>>> .r716
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                     std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
//                     for (auto Piece : Pieces) {
//                         for (auto PiecesDoublet : PiecesDoublets) {
//                             if (Piece == PiecesDoublet.Singlet1()) continue;
//                             if (Piece == PiecesDoublet.Singlet2()) continue;
//                             HTriplet Triplet(PiecesDoublet, Piece);
//                             Triplet.SetTag(GetTag(Triplet));
//                             if (Triplet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Triplet.GetJet().m() - TopMass) > TopWindow) continue;
//                             Triplets.push_back(Triplet);
//                         }
//                     }
//                     for (auto Jet : Jets) {
//                         for (auto PiecesDoublet : PiecesDoublets) {
//                             if (Jet == PiecesDoublet.GetJet1()) continue;
//                             if (Jet == PiecesDoublet.GetJet2()) continue;
//                             HTriplet Triplet(PiecesDoublet, Jet);
//                             Triplet.SetTag(GetTag(Triplet));
//                             if (Triplet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Triplet.GetTripletJet().m() - TopMass) > TopWindow) continue;
//                             Triplets.push_back(Triplet);
//                         }
//                     }
//                 }
//             }
//     }


    if (Tag == HSignal && Triplets.size() > 1) { // FIXME assuming maximal one hadronic W
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        std::sort(Triplets.begin(), Triplets.end(), SortByMass<HTriplet>(TopMass));
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }


    std::vector<HTopHadronicBranch *> HadronicTopBranches;
    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *HadronicTopBranch = new HTopHadronicBranch();
        FillBranch(HadronicTopBranch, Triplet);
        HadronicTopBranches.push_back(HadronicTopBranch);
    }


    return HadronicTopBranches;

}

std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::GetSubJets(const HJets &Jets,const int SubJetNumber, const HTag Tag) {

    std::vector<HTriplet> Triplets;

    for (auto & Jet : Jets) {
        if (!Jet.has_pieces()) {
            Print(HError,"Pieces without Info");
            continue;
        }

        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
        fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
        std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(SubJetNumber);

        for (auto & Piece : Pieces) {
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
            JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
            JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
            Piece.set_user_info(JetInfo);
        }
        Pieces = BottomTagger->GetBdt(Pieces, BottomReader);

        std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
        for (auto Jet2 : Jets) {
            for (auto PiecesDoublet : PiecesDoublets) {
                if (Jet2 == Jet) continue;
                if (Jet2 == PiecesDoublet.Singlet1()) continue;
                if (Jet2 == PiecesDoublet.Singlet2()) continue;
                HTriplet Triplet(PiecesDoublet, Jet2);
                Triplet.SetTag(GetTag(Triplet));
                if (Triplet.Tag() != Tag) continue;
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                Triplets.push_back(Triplet);
            }
        }
    }
// }

return Triplets;
}

// hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const HTriplet &Triplet)
// {
//     Print(HInformation, "Get Triple Tag");
//
//     HJetInfo BJetInfo = Triplet.GetSinglet().user_info<HJetInfo>();
//     BJetInfo.ExtractFraction(BottomId);
//     HJetInfo W1JetInfo = Triplet.GetDoublet().GetJet1().user_info<HJetInfo>();
//     W1JetInfo.ExtractFraction(WId);
//     HJetInfo W2JetInfo = Triplet.GetDoublet().GetJet2().user_info<HJetInfo>();
//     W2JetInfo.ExtractFraction(WId);
//
//     if (std::abs(W1JetInfo.GetMaximalId()) != WId) return HBackground;
//     if (W1JetInfo.GetMaximalId() != W2JetInfo.GetMaximalId()) return HBackground;
//     if (std::abs(BJetInfo.GetMaximalId()) != BottomId) return HBackground;
//     if (sgn(BJetInfo.GetMaximalId()) != sgn(W1JetInfo.GetMaximalId())) return HBackground;
//     return HSignal;
// }

hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

// <<<<<<< .mine
//     HJetInfo BJetInfo = Triplet.GetSinglet().user_info<HJetInfo>();
//     BJetInfo.ExtractFraction(BottomId);
//     HJetInfo W1JetInfo = Triplet.GetDoublet().Singlet1().user_info<HJetInfo>();
//     W1JetInfo.ExtractFraction(WId);
//     HJetInfo W2JetInfo = Triplet.GetDoublet().Singlet2().user_info<HJetInfo>();
//     W2JetInfo.ExtractFraction(WId);
// =======
    HJetInfo BJetInfo = Triplet.Singlet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(TopId);
    HJetInfo W1JetInfo = Triplet.Doublet().Singlet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(TopId);
    HJetInfo W2JetInfo = Triplet.Doublet().Singlet2().user_info<HJetInfo>();
    W2JetInfo.ExtractFraction(TopId);
// >>>>>>> .r716

    if (std::abs(W1JetInfo.GetMaximalId()) != TopId) return HBackground;
    if (W1JetInfo.GetMaximalId() != W2JetInfo.GetMaximalId()) return HBackground;
    if (std::abs(BJetInfo.GetMaximalId()) != TopId) return HBackground;
//   if (sgn(BJetInfo.GetMaximalId()) != sgn(W1JetInfo.GetMaximalId())) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader *const TopHadronicReader)
{

//   float DeltaRProtection = 0.02;
    std::vector<HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
//             if (Doublet.Jet().delta_R(Jet) < DeltaRProtection) continue;
            HTriplet Triplet(Doublet, Jet);
            FillBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader->Bdt());
            Triplets.push_back(Triplet);
        }

// <<<<<<< .mine
//         for (const auto & Jet : Jets) {
//           if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
//             fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//             std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//             if (Pieces.size() > 2) {
//               for (auto & Piece : Pieces) {
//                 hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                 JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                 JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                 Piece.set_user_info(JetInfo);
//               }
//               Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//               std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
//               for (auto Jet2 : Jets) {
//                 for (auto PiecesDoublet : PiecesDoublets) {
//                   if (Jet2 == Jet) continue;
//                   if (Jet2 == PiecesDoublet.Singlet1()) continue;
//                   if (Jet2 == PiecesDoublet.Singlet2()) continue;
// //                   if (PiecesDoublet.Jet().delta_R(Jet2) < DeltaRProtection) continue;
// =======
    for (const auto & Jet : Jets) {
        if (Jet.has_pieces()) if (Jet.pieces().size() > 2) {
                fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
                fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
                std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//                 if (Pieces.size() > 2) {
                for (auto & Piece : Pieces) {
                    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                    JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                    JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                    Piece.set_user_info(JetInfo);
                }
                Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
                std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
                for (auto Jet2 : Jets) {
                    for (auto PiecesDoublet : PiecesDoublets) {
                        if (Jet2 == Jet) continue;
                        if (Jet2 == PiecesDoublet.Singlet1()) continue;
                        if (Jet2 == PiecesDoublet.Singlet2()) continue;
//                   if (PiecesDoublet.GetDoubletJet().delta_R(Jet2) < DeltaRProtection) continue;
// >>>>>>> .r716
                        HTriplet Triplet(PiecesDoublet, Jet2);
                        FillBranch(Triplet);
                        Triplet.SetBdt(TopHadronicReader->Bdt());
                        Triplets.push_back(Triplet);
                    }
                }
//                 }
            }
    }

// <<<<<<< .mine
//         for (const auto & Jet : Jets) {
//           if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
//             fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//             std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
//             if (Pieces.size() > 2) {
//                 for (auto & Piece : Pieces) {
//                     hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                     JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                     JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                     Piece.set_user_info(JetInfo);
//                 }
//                 Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                 std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
//                 for (auto Piece : Pieces) {
//                     for (auto PiecesDoublet : PiecesDoublets) {
//                         if (Piece == PiecesDoublet.Singlet1()) continue;
//                         if (Piece == PiecesDoublet.Singlet2()) continue;
// //                         if (PiecesDoublet.Jet().delta_R(Piece) < DeltaRProtection) continue;
// =======
    for (const auto & Jet : Jets) {
        if (Jet.has_pieces()) if (Jet.pieces().size() > 2) {
                fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
                fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
                std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
                if (Pieces.size() > 2) {
                    for (auto & Piece : Pieces) {
                        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                        JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                        JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                        Piece.set_user_info(JetInfo);
                    }
                    Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
                    std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
                    for (auto Piece : Pieces) {
                        for (auto PiecesDoublet : PiecesDoublets) {
                            if (Piece == PiecesDoublet.Singlet1()) continue;
                            if (Piece == PiecesDoublet.Singlet2()) continue;
//                         if (PiecesDoublet.GetDoubletJet().delta_R(Piece) < DeltaRProtection) continue;
// >>>>>>> .r716
                            HTriplet Triplet(PiecesDoublet, Piece);
                            FillBranch(Triplet);
                            Triplet.SetBdt(TopHadronicReader->Bdt());
                            Triplets.push_back(Triplet);
                        }
                    }
                }
            }
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    return Triplets;
}
