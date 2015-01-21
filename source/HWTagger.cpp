# include "HWTagger.hh"

hanalysis::HWTagger::HWTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    SetTaggerName("WHadronic");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    Branch = new HWBranch();
    JetTag = new HJetTag();

    DefineVariables();
    WMassWindow = 20;
    JetRadiusParameter = 1;
}

hanalysis::HWTagger::~HWTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete BottomReader;
    delete JetTag;
}

void hanalysis::HWTagger::FillBranch(const HDoublet &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.Bdt());
    FillBranch(Branch, Pair);
}

void hanalysis::HWTagger::FillBranch(HWBranch *const WBranch, const HDoublet &Doublet)
{
    Print(HInformation, "FillPairTagger", Doublet.Bdt());

    WBranch->Mass = Doublet.Jet().m();
    WBranch->Rap = Doublet.Jet().rap();
    WBranch->Phi = Doublet.Jet().phi();
    WBranch->Pt = Doublet.Jet().pt();
    WBranch->Ht = Doublet.Ht();
    WBranch->DeltaPt = Doublet.DeltaPt();
    WBranch->DeltaR = Doublet.DeltaR();
    WBranch->DeltaRap = Doublet.DeltaRap();
    WBranch->DeltaPhi = Doublet.DeltaPhi();
    WBranch->Bdt = Doublet.Bdt();
    WBranch->Tag = Doublet.Tag();

}

void hanalysis::HWTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));
    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));

    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}


std::vector<HWBranch *> hanalysis::HWTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {WId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    std::vector<HDoublet> Doublets;

    // combine 2 jets to one W
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet((*Jet1), (*Jet2));
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.Tag() != Tag) continue;
            if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            Doublets.push_back(Doublet);
        }

    // combine subjets
    std::vector<HDoublet> Doublets2 = GetSubJets(Jets,2,Tag);
    Doublets.insert(Doublets.end(),Doublets2.begin(),Doublets2.end());

    std::vector<HDoublet> Doublets3 = GetSubJets(Jets,3,Tag);
    Doublets.insert(Doublets.end(),Doublets3.begin(),Doublets3.end());

    // choose single jets
    for (auto & Jet : Jets) {
        bool Repeat = false;
        for(const auto &Doublet : Doublets) {
            if(Doublet.Singlet1()==Jet) Repeat=true;
            if(Doublet.Singlet2()==Jet) Repeat=true;
            if(Doublet.Jet()==Jet) Repeat=true;
        }
        if(Repeat) continue;
        HTag Jettag = GetTag(Jet);
        if (Jettag != Tag) continue;
        if (Tag == HSignal && std::abs(Jet.m() - WMass) > WMassWindow) continue;
        HDoublet Doublet(Jet);
        Doublets.push_back(Doublet);
    }

//     // combine 2 subjets to one W
//     for (auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 1) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//                 Print(HInformation, "New Jet Number", Pieces.size());
//                 if (Pieces.size() > 1) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
//                         Piece.set_user_info(JetInfo);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                     for (auto Piece1 = Pieces.begin(); Piece1 != Pieces.end(); ++Piece1)
//                         for (auto Piece2 = Piece1 + 1; Piece2 != Pieces.end(); ++Piece2) {
//                             HDoublet Doublet((*Piece1), (*Piece2));
//                             Doublet.SetTag(GetTag(Doublet));
//                             if (Doublet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//                             Doublets.push_back(Doublet);
//                         }
//                 }
//             }
//     }
//
//     // combine 2 out of 3 subjets
//     for (auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 1) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
//                 Print(HInformation, "New Jet Number", Pieces.size());
//                 if (Pieces.size() > 1) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
//                         Piece.set_user_info(JetInfo);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                     for (auto Piece1 = Pieces.begin(); Piece1 != Pieces.end(); ++Piece1)
//                         for (auto Piece2 = Piece1 + 1; Piece2 != Pieces.end(); ++Piece2) {
//                             HDoublet Doublet((*Piece1), (*Piece2));
//                             Doublet.SetTag(GetTag(Doublet));
//                             if (Doublet.Tag() != Tag) continue;
//                             if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
//                             Doublets.push_back(Doublet);
//                         }
//                 }
//             }
//     }

    Print(HError, "Number of Jet Pairs", Doublets.size());
    if (Tag == HSignal && Doublets.size() > 1) { // FIXME assuming maximal one hadronic W
        Print(HInformation, "Number of Jet Pairs", Doublets.size());
        std::sort(Doublets.begin(), Doublets.end(), SortByMass<HDoublet>(WMass));
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    std::vector<HWBranch *> WBranches;
    for (const auto & Doublet : Doublets) {
        HWBranch *WBranch = new HWBranch();
        FillBranch(WBranch, Doublet);
        WBranches.push_back(WBranch);
    }

    return WBranches;

}

std::vector<hanalysis::HDoublet> hanalysis::HWTagger::GetSubJets(const HJets Jets,const int SubJetNumber,const HTag Tag) {

    std::vector<HDoublet> Doublets;

    for (auto & Jet : Jets) {
        if (!Jet.has_pieces()) continue;

        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
        fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
        std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(SubJetNumber);

        for (auto & Piece : Pieces) {
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
            JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
            JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
            JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
            Piece.set_user_info(JetInfo);
        }
        Pieces = BottomTagger->GetBdt(Pieces, BottomReader);

        for (auto Piece1 = Pieces.begin(); Piece1 != Pieces.end(); ++Piece1)
            for (auto Piece2 = Piece1 + 1; Piece2 != Pieces.end(); ++Piece2) {
                HDoublet Doublet((*Piece1), (*Piece2));
                Doublet.SetTag(GetTag(Doublet));
                if (Doublet.Tag() != Tag) continue;
                if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                Doublets.push_back(Doublet);
            }

        for (auto Piece = Pieces.begin(); Piece != Pieces.end(); ++Piece) {
            HTag PieceTag = GetTag(*Piece);
            if (PieceTag != Tag) continue;
            if (Tag == HSignal && std::abs((*Piece).m() - WMass) > WMassWindow) continue;
            HDoublet Doublet((*Piece));
            Doublets.push_back(Doublet);
        }
    }

    return Doublets;
}


hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Doublet Tag");

    HJetInfo JetInfo1 = Doublet.Singlet1().user_info<HJetInfo>();
    JetInfo1.ExtractFraction(WId);
    JetInfo1.PrintAllInfos(HDebug);
//     if (JetInfo1.GetMaximalFraction() < .8) return HBackground;
    if (std::abs(JetInfo1.GetMaximalId()) != WId) return HBackground;

    HJetInfo JetInfo2 = Doublet.Singlet2().user_info<HJetInfo>();
    JetInfo2.ExtractFraction(WId);
    JetInfo2.PrintAllInfos(HDebug);
//     if (JetInfo2.GetMaximalFraction() < .8) return HBackground;
    if (JetInfo1.GetMaximalId() != JetInfo2.GetMaximalId()) return HBackground;

    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
{
    Print(HInformation, "Get Singlet Tag");

    HJetInfo JetInfo1 = Singlet.user_info<HJetInfo>();
    JetInfo1.ExtractFraction(WId);

    if (std::abs(JetInfo1.GetMaximalId()) != WId) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HDoublet>  hanalysis::HWTagger::GetBdt(const HJets &Jets, const hanalysis::HReader *const WReader)
{
    Print(HInformation, "Get Doublet Bdt");

    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            FillBranch(Doublet);
            Doublet.SetBdt(WReader->Bdt());
            Doublets.push_back(Doublet);
        }

    // combine subjets
    std::vector<HDoublet> Doublets2 = GetSubBdt(Jets,2,WReader);
    Doublets.insert(Doublets.end(),Doublets2.begin(),Doublets2.end());

    std::vector<HDoublet> Doublets3 = GetSubBdt(Jets,3,WReader);
    Doublets.insert(Doublets.end(),Doublets3.begin(),Doublets3.end());

    for (auto &Jet : Jets) {
        HDoublet Doublet(Jet);
        FillBranch(Doublet);
        Doublet.SetBdt(WReader->Bdt());
        Doublets.push_back(Doublet);
    }


//     for (auto & Jet : Jets) {
// //<<<<<<< .mine
// //        if (Jet.has_pieces()) if(Jet.pieces().size()>1) {
// //          fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
// //          fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
// //          std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
// //            if (Pieces.size() > 1) {
// //                for (auto & Piece : Pieces) {
// //                    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
// //                    JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
// //                    JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
// //                    JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
// //                    JetInfo->ExtractFraction(WId);
// //                    Piece.set_user_info(JetInfo);
// //                    Piece.user_info<HJetInfo>().PrintAllFamilyInfos(HDebug);
// //                    Piece.user_info<HJetInfo>().PrintAllInfos(HDebug);
// //=======
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 1) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
//                 if (Pieces.size() > 1) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
//                         JetInfo->ExtractFraction(WId);
//                         Piece.set_user_info(JetInfo);
//                         Piece.user_info<HJetInfo>().PrintAllFamilyInfos(HDebug);
//                         Piece.user_info<HJetInfo>().PrintAllInfos(HDebug);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                     for (auto Piece1 = Pieces.begin(); Piece1 != Pieces.end(); ++Piece1)
//                         for (auto Piece2 = Piece1 + 1; Piece2 != Pieces.end(); ++Piece2) {
//                             HDoublet Doublet((*Piece1), (*Piece2));
//                             FillBranch(Doublet);
//                             Doublet.SetBdt(WReader->Bdt());
//                             Doublets.push_back(Doublet);
//                         }
// //>>>>>>> .r715
//                 }
//             }
//     }
//
//     for (auto & Jet : Jets) {
//         if (Jet.has_pieces()) if (Jet.pieces().size() > 1) {
//                 fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
//                 fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//                 std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
//                 if (Pieces.size() > 1) {
//                     for (auto & Piece : Pieces) {
//                         hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//                         JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
//                         JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
//                         JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
//                         JetInfo->ExtractFraction(WId);
//                         Piece.set_user_info(JetInfo);
//                         Piece.user_info<HJetInfo>().PrintAllFamilyInfos(HDebug);
//                         Piece.user_info<HJetInfo>().PrintAllInfos(HDebug);
//                     }
//                     Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
//                     for (auto Piece1 = Pieces.begin(); Piece1 != Pieces.end(); ++Piece1)
//                         for (auto Piece2 = Piece1 + 1; Piece2 != Pieces.end(); ++Piece2) {
//                             HDoublet Doublet((*Piece1), (*Piece2));
//                             FillBranch(Doublet);
//                             Doublet.SetBdt(WReader->Bdt());
//                             Doublets.push_back(Doublet);
//                         }
//                 }
//             }
//     }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}



std::vector<hanalysis::HDoublet> hanalysis::HWTagger::GetSubBdt(const HJets Jets,const int SubJetNumber, const hanalysis::HReader *const WReader) {

    std::vector<HDoublet> Doublets;

    for (auto & Jet : Jets) {
        if(!Jet.has_pieces()) continue;

        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
        fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
        std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(SubJetNumber);

        for (auto & Piece : Pieces) {
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
            JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
            JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
            JetInfo->SetJetFamily(Jet.user_info<HJetInfo>().GetJetFamily());
            Piece.set_user_info(JetInfo);
        }
        Pieces = BottomTagger->GetBdt(Pieces, BottomReader);

        for (auto Piece1 = Pieces.begin(); Piece1 != Pieces.end(); ++Piece1)
            for (auto Piece2 = Piece1 + 1; Piece2 != Pieces.end(); ++Piece2) {
                HDoublet Doublet((*Piece1), (*Piece2));
                FillBranch(Doublet);
                Doublet.SetBdt(WReader->Bdt());
                Doublets.push_back(Doublet);
            }

        for (auto &Piece : Pieces) {
            HDoublet Doublet(Piece);
            FillBranch(Doublet);
            Doublet.SetBdt(WReader->Bdt());
            Doublets.push_back(Doublet);
        }

    }

    return Doublets;
}



std::vector<HParticleBranch *> hanalysis::HWTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<HDoublet> JetPairs;

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HParticleBranch *> ConstituentBranches;
    for (const auto & JetPair : JetPairs) {
        for (const auto & Constituent : JetPair.Constituents()) {
            HParticleBranch *ConstituentBranch = new HParticleBranch();
            FillBranch(ConstituentBranch, Constituent);
            ConstituentBranches.push_back(ConstituentBranch);
        }
    }

    return ConstituentBranches;

}

void hanalysis::HWTagger::FillBranch(const HKinematics &Vector)
{
    Print(HInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void hanalysis::HWTagger::FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    ConstituentBranch->Pt = Vector.GetPt();
    ConstituentBranch->Rap = Vector.GetRap();
    ConstituentBranch->Phi = Vector.GetPhi();

}

