# include "HTauTagger.hh"

hanalysis::HTauTagger::HTauTagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    SetTagger();
}

hanalysis::HTauTagger::~HTauTagger()
{
    Print(kInformation, "Destructor");
}

void hanalysis::HTauTagger::SetTagger()
{
    Print(kNotification, "Set Tagger");
    set_tagger_name("Tau");
    DefineVariables();
}

void hanalysis::HTauTagger::DefineVariables()
{
    Print(kInformation , "Define Variables");

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
    Print(kInformation, "Fill Branch");

    HTauBranch TauBranch;

    if (!Jet.has_user_info<JetInfo>()) {
        Print(kError, "TauJet without user info");
        return TauBranch;
    }

    TauBranch.Mass = Jet.m();
    TauBranch.Pt = Jet.pt();
    TauBranch.Rap = Jet.rap();
    TauBranch.Phi = Jet.phi();
    TauBranch.EmRadius = Jet.user_info<JetInfo>().ElectroMagneticRadius(Jet);
    TauBranch.TrackRadius = Jet.user_info<JetInfo>().TrackRadius(Jet);
    TauBranch.MomentumFraction = Jet.user_info<JetInfo>().LeadingTrackMomentumFraction();
    TauBranch.CoreEnergyFraction = Jet.user_info<JetInfo>().CoreEnergyFraction(Jet);
    TauBranch.EmFraction = Jet.user_info<JetInfo>().ElectroMagneticFraction();
    TauBranch.ClusterMass = Jet.user_info<JetInfo>().ClusterMass();
    TauBranch.TrackMass = Jet.user_info<JetInfo>().TrackMass();
    float MeanDisp = Jet.user_info<JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) {
      TauBranch.FlightPath = std::log(MeanDisp);
    } else {
        TauBranch.FlightPath = -3;
    }
//     TauBranch.TrtHtFraction = GetSpread(Jet.user_info<JetInfo>().VertexJet());
    TauBranch.Tag = Jet.user_info<JetInfo>().Tag();
    TauBranch.Bdt = Jet.user_info<JetInfo>().Bdt();

    return TauBranch;

}

std::vector<HTauBranch> hanalysis::HTauTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(kInformation, "Get Tau Tag", Tag);

    JetTag.HeavyParticles = {TauId};
    Jets jets = GetJets(Event);
    Print(kInformation, "Number Jets", jets.size());

    Jets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(TauId)), Particles.end());
//     if(Particles.size()!=1)
    Print(kInformation, "Tau Partilces", Particles.size());

    Jets FinalJets = CleanJets(jets, Particles, Tag);
//     if(FinalJets.size()!=1)
      Print(kInformation, "Tau Jets", FinalJets.size());

//     Jets Pieces = GetSubJets(jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//     Jets Pieces2 = GetSubJets(jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());


    std::vector<HTauBranch> TauBranches;
    for (const auto & Jet : FinalJets) TauBranches.emplace_back(GetBranch(Jet));

    return TauBranches;
}

Jets hanalysis::HTauTagger::GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber)
{
    Print(kInformation, "Get Sub Jets");
    Jets Pieces;
    for (const auto & Jet : jets) {
        if (!Jet.has_constituents()) {
            Print(kError, "Pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Get Sub Jets", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, 0.4));
        Jets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();


        for (auto & Piece : NewPieces) {
            std::vector<Constituent> constituents;
            for (const auto & Piececonstituent : Piece.constituents()) {
                if (!Piececonstituent.has_user_info<JetInfo>()) {
                    Print(kError, "Get Sub Jets", "No Piece constituent Info");
                    continue;
                }
                std::vector<Constituent> Newconstituents = Piececonstituent.user_info<JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
            }
            Piece.set_user_info(new JetInfo(constituents/*, Jet.user_info<JetInfo>().BTag()*/));
            Pieces.emplace_back(Piece);
        }
    }
    return CleanJets(Pieces, Particles, Tag);
}


Jets hanalysis::HTauTagger::CleanJets(Jets &jets, const Jets &Particles, const Tag Tag)
{
    Print(kInformation, "Clean Jets");

    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if(jets.front().delta_R(Particle)<0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    Jets NewCleanJets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Clean Jets", "No Jet Info");
            continue;
        }
//         if (std::abs(Jet.rap()) > 2.5) continue;
// if (Jet.m() < 0){
//   Print(kError, "Clean Jets", "Massless Jet");
//           continue;
//         }
//         if (Tag == kSignal && Jet.user_info<JetInfo>().SumDisplacement() == 0) continue;
if (Jet.user_info<JetInfo>().Tag() != Tag){
//   Print(kError, "Clean Jets", "Not Tagged Jet");
          continue;

}
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

// hanalysis::HObject::HTag hanalysis::HTauTagger::GetTag(const fastjet::PseudoJet &Jet) const
// {
//
//     Print(kDebug, "Get Bottom Tag", Jet.rap(), Jet.user_info<JetInfo>().MaximalId());
//     if (std::abs(Jet.user_info<JetInfo>().MaximalId()) != BottomId) {
//         return HBackground;
//     }
//     return kSignal;
// }

Jets hanalysis::HTauTagger::GetBdt(Jets &jets, const Reader &BottomReader)
{

    Jets NewJets = GetJetBdt(jets, BottomReader);

    Jets DiJets = GetSubBdt(jets, BottomReader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());

    Jets TriJets = GetSubBdt(jets, BottomReader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());

    return NewJets;
}

Jets hanalysis::HTauTagger::GetSubBdt(const Jets &jets, const Reader &BottomReader, const int SubJetNumber)
{
    Print(kInformation, "Get Sub Bdt");
    Jets Pieces;
    for (const auto & Jet : jets) {
        if (!Jet.has_pieces()) {
            Print(kError, "pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Get Sub Bdt", "No Jet Info");
            continue;
        }
        fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), JetDefinition);
        Jets SubPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        std::vector<Constituent> constituents;
        for (auto & Piece : SubPieces) {
            for (const auto & constituent : Piece.constituents()) {
                if (!constituent.has_user_info<JetInfo>()) {
                    Print(kError, "Get constituent Bdt", "No Jet Info");
                    continue;
                }
                std::vector<Constituent> Newconstituents = constituent.user_info<JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
            }
            Piece.set_user_info(new JetInfo(constituents/*, Jet.user_info<JetInfo>().BTag()*/));
            Pieces.emplace_back(Piece);
        }
    }

    return GetJetBdt(Pieces, BottomReader);
}

Jets hanalysis::HTauTagger::GetJetBdt(const Jets &jets, const Reader &Reader)
{
    Jets NewJets;
    Print(kInformation, "Get Jet Bdt");
    for (const auto Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Get Jet Bdt", "No Jet Info");
            continue;
        }
//         if (Jet.m() <= 0) {
//             Print(kInformation, "Empty Piece");
//             continue;
//         }
        Branch = GetBranch(Jet);
        static_cast<JetInfo *>(Jet.user_info_shared_ptr().get())->SetBdt(Reader.Bdt());
        NewJets.emplace_back(Jet);
    }
    return NewJets;
}

float hanalysis::HTauTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(kDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float hanalysis::HTauTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}
