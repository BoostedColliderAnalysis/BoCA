# include "HBottomTagger.hh"

hanalysis::HBottomTagger::HBottomTagger(const std::string &ProjectName)
{
    Print(HInformation, "Constructor");
    SetAnalysisName(ProjectName);
    SetTagger();
}

hanalysis::HBottomTagger::HBottomTagger()
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
    SetTagger();
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

    ClearVectors();

    AddObservable(Branch.VertexMass, "VertexMass");
    AddObservable(Branch.Pt, "Pt"); // Tao doesnt like this
    AddSpectator(Branch.Rap, "Rap");
    AddSpectator(Branch.Phi, "Phi");
    AddObservable(Branch.MaxDisplacement, "MaxDisplacement");
    AddObservable(Branch.MeanDisplacement, "MeanDisplacement");
    AddObservable(Branch.SumDisplacement, "SumDisplacement");
    AddObservable(Branch.Multipliticity, "Multipliticity");
    AddObservable(Branch.DeltaR, "DeltaR");
    AddObservable(Branch.Spread, "Spread");
    AddObservable(Branch.VertexDeltaR, "VertexDeltaR");
    AddObservable(Branch.VertexSpread, "VertexSpread");
    AddObservable(Branch.EnergyFraction, "EnergyFraction");
    AddSpectator(Branch.BTag, "BTag");

    AddObservable(Branch.Mass, "Mass");
    AddSpectator(Branch.Tag, "Tag");
    AddSpectator(Branch.Bdt, "Bdt");
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
    if (MaxDisp > 0) BottomBranch.MaxDisplacement = std::log(MaxDisp);
    else BottomBranch.MaxDisplacement = -3;
    float MeanDisp = Jet.user_info<HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) BottomBranch.MeanDisplacement = std::log(MeanDisp);
    else BottomBranch.MeanDisplacement = -3;
    float SumDisp = Jet.user_info<HJetInfo>().SumDisplacement();
    if (SumDisp > 0) BottomBranch.SumDisplacement = std::log(SumDisp);
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

std::vector<HBottomBranch> hanalysis::HBottomTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get Bottom Tag", Tag);

    HJets Jets = GetJets(Event);
    Print(HInformation, "Number Jets", Jets.size());

    HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsPairId(BottomId, TopId)), Particles.end());
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
    Print(HInformation, "Particle size", Particles.size());

    std::vector<HBottomBranch> BottomBranches;
    if (Jets.size() < 1) return BottomBranches;
    HJets FinalJets = CleanJets(Jets, Particles, Tag);

    HJets Pieces = GetSubJets(Jets, Particles, Tag, 2);
    FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());

    HJets Pieces2 = GetSubJets(Jets, Particles, Tag, 3);
    FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());

    Print(HDebug, "Number B Jets", Jets.size());

    for (const auto & Jet : FinalJets) BottomBranches.push_back(GetBranch(Jet));

    return BottomBranches;
}

HJets hanalysis::HBottomTagger::GetSubJets(const HJets &Jets, const HJets &Particles, const Tag Tag, const int SubJetNumber)
{
    Print(HInformation, "Get Sub Jets");
    HJets Pieces;
    for (const auto & Jet : Jets) {
        if (!Jet.has_constituents()) {
            Print(HError, "Pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Sub Jets", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), DetectorGeometry.SubJetDefinition);
        HJets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();


        for (auto & Piece : NewPieces) {
            std::vector<HConstituent> Constituents;
            for (const auto & PieceConstituent : Piece.constituents()) {
                if (!PieceConstituent.has_user_info<HJetInfo>()) {
                    Print(HError, "Get Sub Jets", "No Piece Constituent Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = PieceConstituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            Piece.set_user_info(new HJetInfo(Constituents, Jet.user_info<HJetInfo>().BTag()));
            Pieces.push_back(Piece);
        }
    }
    return CleanJets(Pieces, Particles, Tag);
}


HJets hanalysis::HBottomTagger::CleanJets(HJets &Jets, const HJets &Particles, const Tag Tag)
{
    Print(HInformation, "Clean Jets");

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        if (Jets.front().delta_R(Particle) < DetectorGeometry.JetConeSize) static_cast<HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    HJets NewCleanJets;
    for (const auto & Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (std::abs(Jet.rap()) > DetectorGeometry.TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
//         static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         Jet.user_info<HJetInfo>().PrintAllInfos(HDebug);
//         if (Tag == kSignal && Jet.user_info<HJetInfo>().MaximalFraction() < .8) {
//             continue;
//         }
//         if (Tag == kSignal && Jet.user_info<HJetInfo>().MeanDisplacement() < .1) {
//             continue;
//         }
        if (Tag == kSignal && Jet.user_info<HJetInfo>().SumDisplacement() == 0) {
            continue;
        }
//         if (Tag == HBackground && Jet.user_info<HJetInfo>().Fraction(BottomId) > .2) {
//             continue;
//         }
// for (const auto &Particle : Particles) if (Tag == HBackground && Jet.delta_R(Particle) < std::min(GetDeltaR(Jet), float(0.4))) continue;
//         static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        Print(HDebug, "Jet Tag", Jet.user_info<HJetInfo>().Tag());
        if (Jet.user_info<HJetInfo>().Tag() != Tag) continue;
        NewCleanJets.push_back(Jet);
    }
    return NewCleanJets;
}

hanalysis::HObject::Tag hanalysis::HBottomTagger::GetTag(const fastjet::PseudoJet &) const
{

    return kSignal;
}

HJets hanalysis::HBottomTagger::GetMultiJetBdt(HJets &Jets, const HReader &BottomReader)
{

    HJets NewJets = GetJetBdt(Jets, BottomReader);

    HJets DiJets = GetSubBdt(Jets, BottomReader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());

    HJets TriJets = GetSubBdt(Jets, BottomReader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());

    return NewJets;
}

HJets hanalysis::HBottomTagger::GetSubBdt(const HJets &Jets, const HReader &BottomReader, const int SubJetNumber)
{
    Print(HInformation, "Get Sub Bdt");
    HJets Pieces;
    for (const auto & Jet : Jets) {
        if (!Jet.has_pieces()) {
            Print(HInformation, "pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Sub Bdt", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), DetectorGeometry.SubJetDefinition);
        HJets SubPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        std::vector<HConstituent> Constituents;
        for (auto & Piece : SubPieces) {
            for (const auto & Constituent : Piece.constituents()) {
                if (!Constituent.has_user_info<HJetInfo>()) {
                    Print(HInformation, "Get Constituent Bdt", "No Jet Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            Piece.set_user_info(new HJetInfo(Constituents/*, Jet.user_info<HJetInfo>().BTag()*/));
            Pieces.push_back(Piece);
        }
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
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetBdt(BottomReader.Bdt());
        NewJets.push_back(Jet);
    }
    return NewJets;
}

float hanalysis::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(HDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float hanalysis::HBottomTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * Constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}
