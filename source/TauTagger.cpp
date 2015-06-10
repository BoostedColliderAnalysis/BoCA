# include "TauTagger.hh"

# include "fastjet/ClusterSequence.hh"
# include "Singlet.hh"

analysis::TauTagger::TauTagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    set_tagger_name("Tau");
    DefineVariables();
}

void analysis::TauTagger::DefineVariables()
{
    Print(kInformation , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.EmRadius, "EmRadius");
    AddVariable(branch_.TrackRadius, "TrackRadius");
//     AddObservable(Branch.MomentumFraction, "MomentumFraction");
    AddVariable(branch_.CoreEnergyFraction, "CoreEnergyFraction");
    AddSpectator(branch_.EmFraction, "EmFraction");
    AddVariable(branch_.ClusterMass, "ClusterMass");
    AddVariable(branch_.TrackMass, "TrackMass");
    AddVariable(branch_.FlightPath, "FlightPath");
    AddSpectator(branch_.TrtHtFraction, "TrtHtFraction");
    AddSpectator(branch_.Tag, "Tag");
    AddSpectator(branch_.Bdt, "Bdt");
}

int analysis::TauTagger::Train(analysis::Event &event, const analysis::Object::Tag tag)
{
    Print(kInformation, "Tau Tag", tag);
    Jets jets = event.Hadrons().Jets();
    Print(kInformation, "Number Jets", jets.size());
    Jets Particles = event.Partons().GenParticles();
    Particles = RemoveIfWrongAbsParticle(Particles, TauId);
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(TauId)), Particles.end());
//     if(Particles.size()!=1)
    Print(kInformation, "Tau Partilces", Particles.size());
    Jets final_jets = CleanJets(jets, Particles, tag);
//     if(FinalJets.size()!=1)
    Print(kInformation, "Tau Jets", final_jets.size());
//     Jets Pieces = GetSubJets(jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//     Jets Pieces2 = GetSubJets(jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());
    std::vector<Singlet> singlets;
    for (const auto final_jet : final_jets) singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}

// analysis::Jets analysis::TauTagger::GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber)
// {
//     Print(kInformation, "Sub Jets");
//     Jets Pieces;
//     for (const auto & Jet : jets) {
//         if (!Jet.has_constituents()) {
//             Print(kError, "Pieceless jet");
//             continue;
//         }
//         if (!Jet.has_user_info<JetInfo>()) {
//             Print(kError, "Sub Jets", "No Jet Info");
//             continue;
//         }
//         fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, 0.4));
//         Jets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
//         ClusterSequence->delete_self_when_unused();
//         for (auto & Piece : NewPieces) {
//             std::vector<Constituent> constituents;
//             for (const auto & Piececonstituent : Piece.constituents()) {
//                 if (!Piececonstituent.has_user_info<JetInfo>()) {
//                     Print(kError, "Sub Jets", "No Piece constituent Info");
//                     continue;
//                 }
//                 std::vector<Constituent> Newconstituents = Piececonstituent.user_info<JetInfo>().constituents();
//                 constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
//             }
//             Piece.set_user_info(new JetInfo(constituents/*, Jet.user_info<JetInfo>().BTag()*/));
//             Pieces.emplace_back(Piece);
//         }
//     }
//     return CleanJets(Pieces, Particles, Tag);
// }


analysis::Jets analysis::TauTagger::CleanJets(Jets &jets, const Jets &Particles, const Tag Tag)
{
    Print(kInformation, "Clean Jets");
    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
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
        if (Jet.user_info<JetInfo>().Tag() != Tag) {
//   Print(kError, "Clean Jets", "Not Tagged Jet");
            continue;
        }
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

// analysis::Object::HTag analysis::HTauTagger::GetTag(const fastjet::PseudoJet &Jet) const
// {
//
//     Print(kDebug, "Bottom Tag", Jet.rap(), Jet.user_info<JetInfo>().MaximalId());
//     if (std::abs(Jet.user_info<JetInfo>().MaximalId()) != BottomId) {
//         return HBackground;
//     }
//     return kSignal;
// }

// analysis::Jets analysis::TauTagger::GetBdt(Jets &jets, const Reader &BottomReader)
// {
//     Jets NewJets = GetJetBdt(jets, BottomReader);
//     Jets DiJets = GetSubBdt(jets, BottomReader, 2);
//     NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());
//     Jets TriJets = GetSubBdt(jets, BottomReader, 3);
//     NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());
//     return NewJets;
// }

// analysis::Jets analysis::TauTagger::GetSubBdt(const Jets &jets, const Reader &BottomReader, const int SubJetNumber)
// {
//     Print(kInformation, "Sub Bdt");
//     Jets Pieces;
//     for (const auto & Jet : jets) {
//         if (!Jet.has_pieces()) {
//             Print(kError, "pieceless jet");
//             continue;
//         }
//         if (!Jet.has_user_info<JetInfo>()) {
//             Print(kError, "Sub Bdt", "No Jet Info");
//             continue;
//         }
//         fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, 1);
//         fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), JetDefinition);
//         Jets SubPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
//         ClusterSequence->delete_self_when_unused();
//         std::vector<Constituent> constituents;
//         for (auto & Piece : SubPieces) {
//             for (const auto & constituent : Piece.constituents()) {
//                 if (!constituent.has_user_info<JetInfo>()) {
//                     Print(kError, "constituent Bdt", "No Jet Info");
//                     continue;
//                 }
//                 std::vector<Constituent> Newconstituents = constituent.user_info<JetInfo>().constituents();
//                 constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
//             }
//             Piece.set_user_info(new JetInfo(constituents/*, Jet.user_info<JetInfo>().BTag()*/));
//             Pieces.emplace_back(Piece);
//         }
//     }
//     return GetJetBdt(Pieces, BottomReader);
// }

analysis::Jets analysis::TauTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Jets final_jets;
    Print(kInformation, "Jet Bdt");
    Jets jets = event.Hadrons().Jets();
    for (const auto jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Print(kError, "Jet Bdt", "No Jet Info");
            continue;
        }
//         if (Jet.m() <= 0) {
//             Print(kInformation, "Empty Piece");
//             continue;
//         }
        branch_ = branch(Singlet(jet));
        static_cast<JetInfo *>(jet.user_info_shared_ptr().get())->SetBdt(Bdt(reader));
        final_jets.emplace_back(jet);
    }
    return final_jets;
}
