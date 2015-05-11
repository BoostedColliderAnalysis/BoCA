# include "HTauTagger.hh"

hanalysis::HTauTagger::HTauTagger()
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
    SetTagger();
}

hanalysis::HTauTagger::~HTauTagger()
{
    Print(HInformation, "Destructor");
}

void hanalysis::HTauTagger::SetTagger()
{
    Print(HNotification, "Set Tagger");
    set_tagger_name("Tau");
    DefineVariables();
}

void hanalysis::HTauTagger::DefineVariables()
{
    Print(HInformation , "Define Variables");

    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");

    AddVariable(Branch.EmRadius, "EmRadius");
    AddVariable(Branch.TrackRadius, "TrackRadius");
//     AddObservable(Branch.MomentumFraction, "MomentumFraction");
    AddVariable(Branch.CoreEnergyFraction, "CoreEnergyFraction");
    AddSpectator(Branch.EmFraction, "EmFraction");
    AddVariable(Branch.ClusterMass, "ClusterMass");
    AddVariable(Branch.TrackMass, "TrackMass");
    AddVariable(Branch.FlightPath, "FlightPath");
    AddSpectator(Branch.TrtHtFraction, "TrtHtFraction");

    AddSpectator(Branch.Tag, "Tag");
    AddSpectator(Branch.Bdt, "Bdt");
}

HTauBranch hanalysis::HTauTagger::GetBranch(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Fill Branch");

    HTauBranch TauBranch;

    if (!Jet.has_user_info<HJetInfo>()) {
        Print(HError, "TauJet without user info");
        return TauBranch;
    }

    TauBranch.Mass = Jet.m();
    TauBranch.Pt = Jet.pt();
    TauBranch.Rap = Jet.rap();
    TauBranch.Phi = Jet.phi();
    TauBranch.EmRadius = Jet.user_info<HJetInfo>().ElectroMagneticRadius(Jet);
    TauBranch.TrackRadius = Jet.user_info<HJetInfo>().TrackRadius(Jet);
    TauBranch.MomentumFraction = Jet.user_info<HJetInfo>().LeadingTrackMomentumFraction();
    TauBranch.CoreEnergyFraction = Jet.user_info<HJetInfo>().CoreEnergyFraction(Jet);
    TauBranch.EmFraction = Jet.user_info<HJetInfo>().ElectroMagneticFraction();
    TauBranch.ClusterMass = Jet.user_info<HJetInfo>().ClusterMass();
    TauBranch.TrackMass = Jet.user_info<HJetInfo>().TrackMass();
    float MeanDisp = Jet.user_info<HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) {
      TauBranch.FlightPath = std::log(MeanDisp);
    } else {
        TauBranch.FlightPath = -3;
    }
//     TauBranch.TrtHtFraction = GetSpread(Jet.user_info<HJetInfo>().VertexJet());
    TauBranch.Tag = Jet.user_info<HJetInfo>().Tag();
    TauBranch.Bdt = Jet.user_info<HJetInfo>().Bdt();

    return TauBranch;

}

std::vector<HTauBranch> hanalysis::HTauTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get Tau Tag", Tag);

    JetTag.HeavyParticles = {TauId};
    HJets Jets = GetJets(Event);
    Print(HInformation, "Number Jets", Jets.size());

    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(TauId)), Particles.end());
//     if(Particles.size()!=1)
    Print(HInformation, "Tau Partilces", Particles.size());

    HJets FinalJets = CleanJets(Jets, Particles, Tag);
//     if(FinalJets.size()!=1)
      Print(HInformation, "Tau Jets", FinalJets.size());

//     HJets Pieces = GetSubJets(Jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//     HJets Pieces2 = GetSubJets(Jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());


    std::vector<HTauBranch> TauBranches;
    for (const auto & Jet : FinalJets) TauBranches.emplace_back(GetBranch(Jet));

    return TauBranches;
}

HJets hanalysis::HTauTagger::GetSubJets(const HJets &Jets, const HJets &Particles, const Tag Tag, const int SubJetNumber)
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
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, 0.4));
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
            Piece.set_user_info(new HJetInfo(Constituents/*, Jet.user_info<HJetInfo>().BTag()*/));
            Pieces.emplace_back(Piece);
        }
    }
    return CleanJets(Pieces, Particles, Tag);
}


HJets hanalysis::HTauTagger::CleanJets(HJets &Jets, const HJets &Particles, const Tag Tag)
{
    Print(HInformation, "Clean Jets");

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaRTo(Particle));
        if(Jets.front().delta_R(Particle)<0.4) static_cast<HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    HJets NewCleanJets;
    for (const auto & Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Clean Jets", "No Jet Info");
            continue;
        }
//         if (std::abs(Jet.rap()) > 2.5) continue;
// if (Jet.m() < 0){
//   Print(HError, "Clean Jets", "Massless Jet");
//           continue;
//         }
//         if (Tag == kSignal && Jet.user_info<HJetInfo>().SumDisplacement() == 0) continue;
if (Jet.user_info<HJetInfo>().Tag() != Tag){
//   Print(HError, "Clean Jets", "Not Tagged Jet");
          continue;

}
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

// hanalysis::HObject::HTag hanalysis::HTauTagger::GetTag(const fastjet::PseudoJet &Jet) const
// {
//
//     Print(HDebug, "Get Bottom Tag", Jet.rap(), Jet.user_info<HJetInfo>().MaximalId());
//     if (std::abs(Jet.user_info<HJetInfo>().MaximalId()) != BottomId) {
//         return HBackground;
//     }
//     return kSignal;
// }

HJets hanalysis::HTauTagger::GetBdt(HJets &Jets, const Reader &BottomReader)
{

    HJets NewJets = GetJetBdt(Jets, BottomReader);

    HJets DiJets = GetSubBdt(Jets, BottomReader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());

    HJets TriJets = GetSubBdt(Jets, BottomReader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());

    return NewJets;
}

HJets hanalysis::HTauTagger::GetSubBdt(const HJets &Jets, const Reader &BottomReader, const int SubJetNumber)
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
            Piece.set_user_info(new HJetInfo(Constituents/*, Jet.user_info<HJetInfo>().BTag()*/));
            Pieces.emplace_back(Piece);
        }
    }

    return GetJetBdt(Pieces, BottomReader);
}

HJets hanalysis::HTauTagger::GetJetBdt(const HJets &Jets, const Reader &Reader)
{
    HJets NewJets;
    Print(HInformation, "Get Jet Bdt");
    for (const auto Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Jet Bdt", "No Jet Info");
            continue;
        }
//         if (Jet.m() <= 0) {
//             Print(HInformation, "Empty Piece");
//             continue;
//         }
        Branch = GetBranch(Jet);
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetBdt(Reader.Bdt());
        NewJets.emplace_back(Jet);
    }
    return NewJets;
}

float hanalysis::HTauTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
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

float hanalysis::HTauTagger::GetSpread(const fastjet::PseudoJet &Jet) const
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
