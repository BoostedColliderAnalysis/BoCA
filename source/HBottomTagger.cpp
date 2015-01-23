# include "HBottomTagger.hh"

hanalysis::HBottomTagger::HBottomTagger()
{
//     DebugLevel = HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("Bottom");
    Branch = new HBottomBranch();
    JetTag = new HJetTag();
    DefineVariables();
}

hanalysis::HBottomTagger::~HBottomTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
}


void hanalysis::HBottomTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
//     Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
//     Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->MaxDisplacement, "MaxDisplacement"));
    Observables.push_back(NewObservable(&Branch->MeanDisplacement, "MeanDisplacement"));
    Observables.push_back(NewObservable(&Branch->SumDisplacement, "SumDisplacement"));
    Observables.push_back(NewObservable(&Branch->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Spread, "Spread"));
    Observables.push_back(NewObservable(&Branch->VertexDeltaR, "VertexDeltaR"));
    Observables.push_back(NewObservable(&Branch->VertexSpread, "VertexSpread"));
    Observables.push_back(NewObservable(&Branch->EnergyFraction, "EnergyFraction"));
    Observables.push_back(NewObservable(&Branch->BTag, "BTag"));

//     Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));
    Spectators.push_back(NewObservable(&Branch->Bdt, "Bdt"));
}

void hanalysis::HBottomTagger::FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Fill Branch");

    if (Jet.has_user_info<HJetInfo>()) {
        HJetInfo JetInfo = Jet.user_info<HJetInfo>();
        JetInfo.ExtractAbsFraction(BottomId);
        BottomBranch->VertexMass = JetInfo.VertexMass();
        BottomBranch->Mass = Jet.m();
        BottomBranch->Pt = Jet.pt();
        BottomBranch->Rap = Jet.rap();
        BottomBranch->Phi = Jet.phi();
        float MaxDisp = JetInfo.MaxDisplacement();
        if (MaxDisp > 0)BottomBranch->MaxDisplacement = std::log(MaxDisp);
        else BottomBranch->MaxDisplacement = -3;
        float MeanDisp = JetInfo.MeanDisplacement();
        if (MeanDisp > 0)BottomBranch->MeanDisplacement = std::log(MeanDisp);
        else BottomBranch->MeanDisplacement = -3;
        float SumDisp = JetInfo.SumDisplacement();
        if (SumDisp > 0)BottomBranch->SumDisplacement = std::log(SumDisp);
        else BottomBranch->SumDisplacement = -3;
        BottomBranch->Multipliticity = JetInfo.VertexNumber();
        BottomBranch->DeltaR = GetDeltaR(Jet);
        BottomBranch->Spread = GetSpread(Jet);
        BottomBranch->VertexDeltaR = GetDeltaR(JetInfo.VertexJet());
        BottomBranch->VertexSpread = GetSpread(JetInfo.VertexJet());
        BottomBranch->EnergyFraction = JetInfo.VertexEnergy() / Jet.e();
        BottomBranch->BTag = JetInfo.BTag();
        BottomBranch->Tag = JetInfo.Tag();
        BottomBranch->Bdt = JetInfo.Bdt();
    } else Print(HError, "BJet without user info");

//     if (BottomBranch->Bdt <= -10) {
//         Print(HError, "VertexMass", BottomBranch->VertexMass);
//         Print(HError, "Mass", BottomBranch->Mass);
//         Print(HError, "Pt", BottomBranch->Pt);
//         Print(HError, "Rap", BottomBranch->Rap);
//         Print(HError, "Phi", BottomBranch->Phi);
//         Print(HError, "Max", BottomBranch->MaxDisplacement);
//         Print(HError, "Mmmean", BottomBranch->MeanDisplacement);
//         Print(HError, "SumDisp", BottomBranch->SumDisplacement);
//         Print(HError, "Multi", BottomBranch->Multipliticity);
//         Print(HError, "DeltaR", BottomBranch->DeltaR);
//         Print(HError, "Spread", BottomBranch->Spread);
//         Print(HError, "DeltaR", BottomBranch->VertexDeltaR);
//         Print(HError, "Spread", BottomBranch->VertexSpread);
//         Print(HError, "Energy", BottomBranch->EnergyFraction);
//     }
}

void hanalysis::HBottomTagger::FillBranch(const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Fill Branch");
    FillBranch(Branch, Jet);
}

std::vector<HBottomBranch *> hanalysis::HBottomTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Bottom Tag", Tag);

    JetTag->HeavyParticles = {BottomId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());


    HJets FinalJets = CleanJets(Jets, Tag);

    HJets Pieces = GetSubJets(Jets, 2, Tag);
    FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());

    HJets Pieces2 = GetSubJets(Jets, 3, Tag);
    FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());

    Print(HDebug, "Number B Jets", Jets.size());

    std::vector<HBottomBranch *> BottomBranches;
    for (auto & Jet : FinalJets) {
        HBottomBranch *BottomBranch = new HBottomBranch;
        FillBranch(BottomBranch, Jet);
        BottomBranches.push_back(BottomBranch);
    }

    return BottomBranches;
}

HJets hanalysis::HBottomTagger::GetSubJets(const HJets &Jets, const int SubJetNumber, const HTag Tag)
{
    Print(HInformation, "Get Sub Jets");
    HJets Pieces;
    for (const auto & Jet : Jets) {
        if (!Jet.has_pieces()) {
            Print(HError, "Pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Sub Jets", "No Jet Info");
            continue;
        }
        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), JetDefinition);
        Pieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        for (auto & Piece : Pieces) {
//             Print(HError, "Jet", Piece);
            std::vector<HConstituent> Constituents;
            for (const auto & PieceConstituent : Piece.constituents()) {
                std::vector<HConstituent> NewConstituents = PieceConstituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
//                 for(HConstituent &NC :NewConstituents){Print(HError,"NC",NC.Momentum().Pt());}
            }
//             Print(HError, "Const size", Constituents.size());
//             for (HConstituent Constituent : Constituents) Print(HError,"Const",Constituent.Position().Pt());
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo(Constituents);
//             Print(HError, "Inf", JetInfo->Constituents().size(),JetInfo->MaxDisplacement());
            //         Print(HError,"Jet Info",JetInfo->MaximalId());
//             for(HConstituent &NC2 :Constituents){Print(HError,"NC2",NC2.Momentum().Pt());}
            Piece.set_user_info(JetInfo);
        }
    }
    HJets NewPieces = CleanJets(Pieces, Tag);
    return NewPieces;
}


HJets hanalysis::HBottomTagger::CleanJets(const HJets &Jets, const HTag Tag)
{
    Print(HInformation, "Clean Jets");
    HJets NewCleanJets;
    for (const auto & Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (std::abs(Jet.rap()) > 2.5) continue;
        if (Jet.m() < 0) continue;
        HJetInfo JetInfo = Jet.user_info<HJetInfo>();
        JetInfo.ExtractAbsFraction(BottomId);
        JetInfo.PrintAllInfos(HDebug);
        if (Tag == HSignal && JetInfo.MaximalFraction() < .8) continue;
        if (Tag == HSignal && JetInfo.MeanDisplacement() < .1) continue;
        if (Tag == HBackground && JetInfo.Fraction(BottomId) > .2)continue;
//         if (Jet.m() <= 0)continue;
//         if (Jet == fastjet::PseudoJet(0,0,0,0))continue;
//         if (!Jet.has_user_info<HJetInfo>())continue;
        if (Tag == HBackground && std::log(JetInfo.SumDisplacement()) <= -3)continue;
        JetInfo.SetTag(GetTag(Jet));
        if (JetInfo.Tag() != Tag) continue;
        NewCleanJets.push_back(Jet);
    }
    return NewCleanJets;
}

hanalysis::HObject::HTag hanalysis::HBottomTagger::GetTag(const fastjet::PseudoJet &Jet) const
{
    Print(HDebug, "Get Bottom Tag", Jet.user_info<HJetInfo>().MaximalFraction());

    HJetInfo JetInfo = Jet.user_info<HJetInfo>();
    JetInfo.ExtractAbsFraction(BottomId);
    JetInfo.PrintAllInfos(HDebug);

    Print(HDebug, "B Tag Info", Jet.rap(), JetInfo.MaximalId(), JetInfo.MaximalId());
    if (std::abs(JetInfo.MaximalId()) != BottomId) return HBackground;
    return HSignal;
}

HJets hanalysis::HBottomTagger::GetBdt(HJets &Jets, const HReader *const BottomReader)
{
    HJets NewJets = GetJetBdt(Jets, BottomReader);
    HJets DiJets = GetSubBdt(Jets, BottomReader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());
    HJets TriJets = GetSubBdt(Jets, BottomReader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());
    return NewJets;
}

HJets hanalysis::HBottomTagger::GetSubBdt(HJets &Jets, const HReader *const BottomReader, const int SubJetNumber)
{
    Print(HInformation, "Get Sub Bdt");
    HJets Pieces;
    for (const auto & Jet : Jets) {
        if (!Jet.has_pieces()) {
            Print(HError, "pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Sub Bdt", "No Jet Info");
            continue;
        }
        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), JetDefinition);
        Pieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        std::vector<HConstituent> Constituents;
        for (auto & Piece : Pieces) {
            for (auto & Constituent : Piece.constituents()) {
              if (!Constituent.has_user_info<HJetInfo>()) {
                    Print(HError, "Get Constituent Bdt", "No Jet Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo(Constituents);
            Piece.set_user_info(JetInfo);
        }
    }
    return GetJetBdt(Pieces, BottomReader);
}

HJets hanalysis::HBottomTagger::GetJetBdt(HJets &Jets, const HReader *const BottomReader)
{
    Print(HInformation, "Get Jet Bdt");
    for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        Print(HInformation, "We are here");
//         if (!(*Jet).has_user_info<HJetInfo>()) {
//             Print(HError, "Get Jet Bdt", "No Jet Info");
//             continue;
//         }
        HJetInfo *JetInfo = new HJetInfo();
        if ((*Jet).has_user_info<HJetInfo>()) *JetInfo = (*Jet).user_info<HJetInfo>();
        FillBranch(*Jet);
        JetInfo->SetBdt(BottomReader->Bdt());
        Print(HInformation, "Bdt", JetInfo->Bdt());
        (*Jet).set_user_info(JetInfo);
    }
    return Jets;
}


HJets hanalysis::HBottomTagger::GetBdt2(HJets &Jets, const HReader *const BottomReader)
{
    Print(HInformation, "Get Bdt2");
    for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        HJetInfo *JetInfo = new HJetInfo();
        if ((*Jet).has_user_info<HJetInfo>()) *JetInfo = (*Jet).user_info<HJetInfo>();
        FillBranch(*Jet);
        JetInfo->SetBdt(BottomReader->Bdt());
        JetInfo->SetTag(GetTag(*Jet));
        Print(HInformation, "Bdt", JetInfo->Bdt(), JetInfo->Tag());
        (*Jet).set_user_info(JetInfo);
    }
    return Jets;
}



float hanalysis::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    if (!Jet.has_constituents()) return 0;

    float DeltaR = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) continue;
        Print(HDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;
}

float hanalysis::HBottomTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");
    if (!Jet.has_constituents()) return 0;

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) return 0;
    float Spread = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) continue;
        Spread += TempDeltaR * Constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}
