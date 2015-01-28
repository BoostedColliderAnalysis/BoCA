# include "HBottomTagger.hh"

hanalysis::HBottomTagger::HBottomTagger()
{
//     DebugLevel = HDebug;
    Print(HNotification, "Constructor");
    SetTagger();
}

hanalysis::HBottomTagger::~HBottomTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HBottomTagger::SetTagger()
{
    Print(HNotification, "Set Tagger");
    SetTaggerName("Bottom");
    DefineVariables();
}

void hanalysis::HBottomTagger::DefineVariables()
{
    Print(HInformation , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Spectators.push_back(NewObservable(&Branch.Rap, "Rap"));
    Spectators.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.MaxDisplacement, "MaxDisplacement"));
    Observables.push_back(NewObservable(&Branch.MeanDisplacement, "MeanDisplacement"));
    Observables.push_back(NewObservable(&Branch.SumDisplacement, "SumDisplacement"));
    Observables.push_back(NewObservable(&Branch.Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch.Spread, "Spread"));
    Observables.push_back(NewObservable(&Branch.VertexDeltaR, "VertexDeltaR"));
    Observables.push_back(NewObservable(&Branch.VertexSpread, "VertexSpread"));
    Observables.push_back(NewObservable(&Branch.EnergyFraction, "EnergyFraction"));
    Observables.push_back(NewObservable(&Branch.BTag, "BTag"));

    Spectators.push_back(NewObservable(&Branch.Mass, "Mass"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));
    Spectators.push_back(NewObservable(&Branch.Bdt, "Bdt"));
}

HBottomBranch hanalysis::HBottomTagger::GetBranch(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Fill Branch");

    HBottomBranch BottomBranch;

    if (!Jet.has_user_info<HJetInfo>()) {
        Print(HError, "BJet without user info");
        return BottomBranch;
    }

    BottomBranch.VertexMass = Jet.user_info<HJetInfo>().VertexMass();
    BottomBranch.Mass = Jet.m();
    BottomBranch.Pt = Jet.pt();
    BottomBranch.Rap = Jet.rap();
    BottomBranch.Phi = Jet.phi();
    float MaxDisp = Jet.user_info<HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0)BottomBranch.MaxDisplacement = std::log(MaxDisp);
    else BottomBranch.MaxDisplacement = -3;
    float MeanDisp = Jet.user_info<HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0)BottomBranch.MeanDisplacement = std::log(MeanDisp);
    else BottomBranch.MeanDisplacement = -3;
    float SumDisp = Jet.user_info<HJetInfo>().SumDisplacement();
    if (SumDisp > 0)BottomBranch.SumDisplacement = std::log(SumDisp);
    else BottomBranch.SumDisplacement = -3;
    BottomBranch.Multipliticity = Jet.user_info<HJetInfo>().VertexNumber();
    BottomBranch.DeltaR = GetDeltaR(Jet);
    BottomBranch.Spread = GetSpread(Jet);
    BottomBranch.VertexDeltaR = GetDeltaR(Jet.user_info<HJetInfo>().VertexJet());
    BottomBranch.VertexSpread = GetSpread(Jet.user_info<HJetInfo>().VertexJet());
    BottomBranch.EnergyFraction = Jet.user_info<HJetInfo>().VertexEnergy() / Jet.e();
    BottomBranch.BTag = Jet.user_info<HJetInfo>().BTag();
    BottomBranch.Tag = Jet.user_info<HJetInfo>().Tag();
    BottomBranch.Bdt = Jet.user_info<HJetInfo>().Bdt();

    return BottomBranch;

}

std::vector<HBottomBranch> hanalysis::HBottomTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Bottom Tag", Tag);

    JetTag.HeavyParticles = {BottomId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());


    HJets FinalJets = CleanJets(Jets, Tag);

    HJets Pieces = GetSubJets(Jets, Tag, 2);
    FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());

    HJets Pieces2 = GetSubJets(Jets, Tag, 3);
    FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());

    Print(HDebug, "Number B Jets", Jets.size());

    std::vector<HBottomBranch> BottomBranches;
    for (const auto & Jet : FinalJets) BottomBranches.push_back(GetBranch(Jet));

    return BottomBranches;
}

HJets hanalysis::HBottomTagger::GetSubJets(const HJets &Jets, const HTag Tag, const int SubJetNumber)
{
    Print(HInformation, "Get Sub Jets");
    HJets Pieces;
    for (const auto & Jet : Jets) {
        if (!Jet.has_pieces()) {
            Print(HError, "Pieceless jet");
            continue;
        }
        if (!Jet.has_user_info()) {
            Print(HError, "Get Sub Jets", "No Jet Info");
            continue;
        }
        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), JetDefinition);
        HJets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        for (auto & Piece : NewPieces) {
            std::vector<HConstituent> Constituents;
            for (const auto & PieceConstituent : Piece.constituents()) {
                if (!PieceConstituent.has_user_info()) {
                    Print(HError, "Get Sub Jets", "No PieceConstituent Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = PieceConstituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            Piece.set_user_info(new HJetInfo(Constituents, Jet.user_info<HJetInfo>().BTag()));
        }
        Pieces.insert(Pieces.end(), NewPieces.begin(), NewPieces.end());
    }
    return CleanJets(Pieces, Tag);
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
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
        Jet.user_info<HJetInfo>().PrintAllInfos(HDebug);
        if (Tag == HSignal && Jet.user_info<HJetInfo>().MaximalFraction() < .8) continue;
        if (Tag == HSignal && Jet.user_info<HJetInfo>().MeanDisplacement() < .1) continue;
        if (Tag == HSignal && Jet.user_info<HJetInfo>().SumDisplacement() == 0)continue;
        if (Tag == HBackground && Jet.user_info<HJetInfo>().Fraction(BottomId) > .2)continue;
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        if (Jet.user_info<HJetInfo>().Tag() != Tag) continue;
        NewCleanJets.push_back(Jet);
    }
    return NewCleanJets;
}

hanalysis::HObject::HTag hanalysis::HBottomTagger::GetTag(const fastjet::PseudoJet &Jet) const
{

    Print(HDebug, "Get Bottom Tag", Jet.rap(), Jet.user_info<HJetInfo>().MaximalId());
    if (std::abs(Jet.user_info<HJetInfo>().MaximalId()) != BottomId) return HBackground;
    return HSignal;
}

HJets hanalysis::HBottomTagger::GetBdt(HJets &Jets, const HReader &BottomReader)
{
    HJets NewJets = GetJetBdt(Jets, BottomReader);

    HJets DiJets = GetSubBdt(Jets, BottomReader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());

    HJets TriJets = GetSubBdt(Jets, BottomReader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());

    return NewJets;
}

HJets hanalysis::HBottomTagger::GetSubBdt(HJets &Jets, const HReader &BottomReader, const int SubJetNumber)
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
        HJets SubPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        std::vector<HConstituent> Constituents;
        for (auto & Piece : SubPieces) {
            for (const auto & Constituent : Piece.constituents()) {
                if (!Constituent.has_user_info<HJetInfo>()) {
                    Print(HError, "Get Constituent Bdt", "No Jet Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            Piece.set_user_info(new HJetInfo(Constituents, Jet.user_info<HJetInfo>().BTag()));
            Pieces.push_back(Piece);
        }
//         Pieces.insert(Pieces.end(), SubPieces.begin(), SubPieces.end());
    }

    return GetJetBdt(Pieces, BottomReader);
}

HJets hanalysis::HBottomTagger::GetJetBdt(const HJets &Jets, const HReader &BottomReader)
{
    HJets NewJets;
    Print(HInformation, "Get Jet Bdt");
    for (const auto Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Jet Bdt", "No Jet Info");
            continue;
        }
        if (Jet.m() <= 0) {
            Print(HInformation, "Empty Piece");
            continue;
        }
        Branch = GetBranch(Jet);
        //         Print(HError, "Jet", Jet.pt(), Branch.Pt);
        //         Print(HError, "Bdt", BottomReader.Mva->GetTaggerName());
        //         Print(HError, "Bdt", BottomReader.Mva->GetObservables().size());
//                 for (auto Obs : BottomReader.Mva->GetObservables()) Print(HError, "Obs", Obs.GetValue());
        //         Print(HError, "Bdt", BottomReader.Mva->GetSpectators().size());
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetBdt(BottomReader.Bdt());
//         Print(HError, "Bdt", Jet.user_info<HJetInfo>().Bdt());
//         Print(HError, "Jet", Jet);
        NewJets.push_back(Jet);
    }
    return NewJets;
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
