# include "HBottomTagger.hh"

hanalysis::HBottomTagger::HBottomTagger(const std::string &ProjectName)
{
    Print(kInformation, "Constructor");
    set_analysis_name(ProjectName);
    SetTagger();
}

hanalysis::HBottomTagger::HBottomTagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    SetTagger();
}

void hanalysis::HBottomTagger::SetTagger()
{
    Print(kNotification, "Set Tagger");
    SetTaggerName("Bottom");
    DefineVariables();
}

void hanalysis::HBottomTagger::DefineVariables()
{
    Print(kInformation , "Define Variables");

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

BottomBranch hanalysis::HBottomTagger::GetBranch(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Fill Branch");

    BottomBranch bottom_branch;

    if (!Jet.has_user_info<JetInfo>()) {
        Print(kError, "BJet without user info");
        return bottom_branch;
    }

    bottom_branch.VertexMass = Jet.user_info<JetInfo>().VertexMass();
    bottom_branch.Mass = Jet.m();
    bottom_branch.Pt = Jet.pt();
    bottom_branch.Rap = Jet.rap();
    bottom_branch.Phi = Jet.phi();
    float MaxDisp = Jet.user_info<JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) bottom_branch.MaxDisplacement = std::log(MaxDisp);
    else bottom_branch.MaxDisplacement = -3;
    float MeanDisp = Jet.user_info<JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) bottom_branch.MeanDisplacement = std::log(MeanDisp);
    else bottom_branch.MeanDisplacement = -3;
    float SumDisp = Jet.user_info<JetInfo>().SumDisplacement();
    if (SumDisp > 0) bottom_branch.SumDisplacement = std::log(SumDisp);
    else bottom_branch.SumDisplacement = -3;
    bottom_branch.Multipliticity = Jet.user_info<JetInfo>().VertexNumber();
    bottom_branch.DeltaR = GetDeltaR(Jet);
    bottom_branch.Spread = GetSpread(Jet);
    bottom_branch.VertexDeltaR = GetDeltaR(Jet.user_info<JetInfo>().VertexJet());
    bottom_branch.VertexSpread = GetSpread(Jet.user_info<JetInfo>().VertexJet());
    bottom_branch.EnergyFraction = Jet.user_info<JetInfo>().VertexEnergy() / Jet.e();
    bottom_branch.BTag = Jet.user_info<JetInfo>().BTag();
    bottom_branch.Tag = Jet.user_info<JetInfo>().Tag();
    bottom_branch.Bdt = Jet.user_info<JetInfo>().Bdt();

    return bottom_branch;

}

std::vector<BottomBranch> hanalysis::HBottomTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(kInformation, "Get Bottom Tag", Tag);

    Jets jets = GetJets(Event);
    Print(kInformation, "Number Jets", jets.size());

    Jets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsPairId(BottomId, TopId)), Particles.end());
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
    Print(kInformation, "Particle size", Particles.size());

    std::vector<BottomBranch> bottom_branches;
    if (jets.empty()) return bottom_branches;
    Jets FinalJets = CleanJets(jets, Particles, Tag);

    Jets Pieces = GetSubJets(jets, Particles, Tag, 2);
    FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());

    Jets Pieces2 = GetSubJets(jets, Particles, Tag, 3);
    FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());

    Print(kDebug, "Number B Jets", jets.size());

    for (const auto & Jet : FinalJets) bottom_branches.emplace_back(GetBranch(Jet));

    return bottom_branches;
}

Jets hanalysis::HBottomTagger::GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber)
{
    Print(kInformation, "Get Sub Jets");
    Jets Pieces;
    for (const auto & Jet : jets)  {
        if (!Jet.has_constituents()) {
            Print(kError, "Pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Get Sub Jets", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), detector_geometry().SubJetDefinition);
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
            Piece.set_user_info(new JetInfo(constituents, Jet.user_info<JetInfo>().BTag()));
            Pieces.emplace_back(Piece);
        }
    }
    return CleanJets(Pieces, Particles, Tag);
}


Jets hanalysis::HBottomTagger::CleanJets(Jets &jets, const Jets &Particles, const Tag Tag)
{
    Print(kInformation, "Clean Jets");

    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    Jets NewCleanJets;
    for (const auto & Jet : jets)  {
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
//         static_cast<JetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         Jet.user_info<JetInfo>().PrintAllInfos(kDebug);
//         if (Tag == kSignal && Jet.user_info<JetInfo>().MaximalFraction() < .8) {
//             continue;
//         }
//         if (Tag == kSignal && Jet.user_info<JetInfo>().MeanDisplacement() < .1) {
//             continue;
//         }
        if (Tag == kSignal && Jet.user_info<JetInfo>().SumDisplacement() == 0) {
            continue;
        }
//         if (Tag == HBackground && Jet.user_info<JetInfo>().Fraction(BottomId) > .2) {
//             continue;
//         }
// for (const auto &Particle : Particles) if (Tag == HBackground && Jet.delta_R(Particle) < std::min(GetDeltaR(Jet), float(0.4))) continue;
//         static_cast<JetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        Print(kDebug, "Jet Tag", Jet.user_info<JetInfo>().Tag());
        if (Jet.user_info<JetInfo>().Tag() != Tag) continue;
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

hanalysis::HObject::Tag hanalysis::HBottomTagger::GetTag(const fastjet::PseudoJet &) const
{

    return kSignal;
}

Jets hanalysis::HBottomTagger::GetMultiJetBdt(Jets &jets, const Reader &BottomReader)
{

    Jets NewJets = GetJetBdt(jets, BottomReader);

    Jets DiJets = GetSubBdt(jets, BottomReader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());

    Jets TriJets = GetSubBdt(jets, BottomReader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());

    return NewJets;
}

Jets hanalysis::HBottomTagger::GetSubBdt(const Jets &jets, const Reader &BottomReader, const int SubJetNumber)
{
    Print(kInformation, "Get Sub Bdt");
    Jets Pieces;
    for (const auto & Jet : jets)  {
        if (!Jet.has_pieces()) {
            Print(kInformation, "pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Get Sub Bdt", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), detector_geometry().SubJetDefinition);
        Jets SubPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
        ClusterSequence->delete_self_when_unused();

        std::vector<Constituent> constituents;
        for (auto & Piece : SubPieces) {
            for (const auto & constituent : Piece.constituents()) {
                if (!constituent.has_user_info<JetInfo>()) {
                    Print(kInformation, "Get constituent Bdt", "No Jet Info");
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

Jets hanalysis::HBottomTagger::GetJetBdt(const Jets &jets, const Reader &BottomReader)
{
    Jets NewJets;
    Print(kInformation, "Get Jet Bdt");
    for (const auto Jet : jets)  {
        if (!Jet.has_user_info<JetInfo>()) {
            Print(kError, "Get Jet Bdt", "No Jet Info");
            continue;
        }
        if (Jet.m() <= 0) {
            Print(kInformation, "Empty Piece");
            continue;
        }
        Branch = GetBranch(Jet);
        static_cast<JetInfo *>(Jet.user_info_shared_ptr().get())->SetBdt(BottomReader.Bdt());
        NewJets.emplace_back(Jet);
    }
    return NewJets;
}

float hanalysis::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
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

float hanalysis::HBottomTagger::GetSpread(const fastjet::PseudoJet &Jet) const
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
