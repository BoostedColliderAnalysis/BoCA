# include "TauTagger.hh"

# include "fastjet/ClusterSequence.hh"
# include "Singlet.hh"

namespace analysis {

TauTagger::TauTagger()
{
//     DebugLevel = Severity::Debug;
    Print(Severity::Information, "Constructor");
    set_tagger_name("Tau");
    DefineVariables();
}

void TauTagger::DefineVariables()
{
    Print(Severity::Information , "Define Variables");
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().EmRadius, "EmRadius");
    AddVariable(branch().TrackRadius, "TrackRadius");
//     AddObservable(Branch.MomentumFraction, "MomentumFraction");
    AddVariable(branch().CoreEnergyFraction, "CoreEnergyFraction");
    AddSpectator(branch().EmFraction, "EmFraction");
    AddVariable(branch().ClusterMass, "ClusterMass");
    AddVariable(branch().TrackMass, "TrackMass");
    AddVariable(branch().FlightPath, "FlightPath");
    AddSpectator(branch().TrtHtFraction, "TrtHtFraction");
    AddSpectator(branch().Tag, "Tag");
    AddSpectator(branch().Bdt, "Bdt");
}

int TauTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag)
{
    Print(Severity::Information, "Tau Tag", Name(tag));
    Jets jets = event.Hadrons().Jets();
    Print(Severity::Information, "Number Jets", jets.size());
    Jets Particles = event.Partons().GenParticles();
    Particles = RemoveIfWrongAbsParticle(Particles, Id::Tau);
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(Id::Tau)), Particles.end());
//     if(Particles.size()!=1)
    Print(Severity::Information, "Tau Partilces", Particles.size());
    Jets final_jets = CleanJets(jets, Particles,tag);
//     if(FinalJets.size()!=1)
    Print(Severity::Information, "Tau Jets", final_jets.size());
//     Jets Pieces = GetSubJets(jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//     Jets Pieces2 = GetSubJets(jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());
    std::vector<Singlet> singlets;
    for (const auto final_jet : final_jets) singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}

// Jets TauTagger::GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber)
// {
//     Print(Severity::Information, "Sub Jets");
//     Jets Pieces;
//     for (const auto & Jet : jets) {
//         if (!Jet.has_constituents()) {
//             Print(Severity::Error, "Pieceless jet");
//             continue;
//         }
//         if (!Jet.has_user_info<JetInfo>()) {
//             Print(Severity::Error, "Sub Jets", "No Jet Info");
//             continue;
//         }
//         fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, 0.4));
//         Jets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
//         ClusterSequence->delete_self_when_unused();
//         for (auto & Piece : NewPieces) {
//             std::vector<Constituent> constituents;
//             for (const auto & Piececonstituent : Piece.constituents()) {
//                 if (!Piececonstituent.has_user_info<JetInfo>()) {
//                     Print(Severity::Error, "Sub Jets", "No Piece constituent Info");
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


Jets TauTagger::CleanJets(Jets &jets, const Jets &Particles, const Tag tag)
{
    Print(Severity::Information, "Clean Jets");
    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(Tag::Signal);
    }
    Jets NewCleanJets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) {
            Print(Severity::Error, "Clean Jets", "No Jet Info");
            continue;
        }
//         if (std::abs(Jet.rap()) > 2.5) continue;
// if (Jet.m() < 0){
//   Print(Severity::Error, "Clean Jets", "Massless Jet");
//           continue;
//         }
//         if (Tag == Tag::Signal && Jet.user_info<JetInfo>().SumDisplacement() == 0) continue;
        if (Jet.user_info<JetInfo>().Tag() != tag) {
//   Print(Severity::Error, "Clean Jets", "Not Tagged Jet");
            continue;
        }
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

// Object::HTag HTauTagger::GetTag(const fastjet::PseudoJet &Jet) const
// {
//
//     Print(Severity::Debug, "Bottom Tag", Jet.rap(), Jet.user_info<JetInfo>().MaximalId());
//     if (std::abs(Jet.user_info<JetInfo>().MaximalId()) != Id::Bottom) {
//         return HBackground;
//     }
//     return Tag::Signal;
// }

// Jets TauTagger::GetBdt(Jets &jets, const Reader &BottomReader)
// {
//     Jets NewJets = GetJetBdt(jets, BottomReader);
//     Jets DiJets = GetSubBdt(jets, BottomReader, 2);
//     NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());
//     Jets TriJets = GetSubBdt(jets, BottomReader, 3);
//     NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());
//     return NewJets;
// }

// Jets TauTagger::GetSubBdt(const Jets &jets, const Reader &BottomReader, const int SubJetNumber)
// {
//     Print(Severity::Information, "Sub Bdt");
//     Jets Pieces;
//     for (const auto & Jet : jets) {
//         if (!Jet.has_pieces()) {
//             Print(Severity::Error, "pieceless jet");
//             continue;
//         }
//         if (!Jet.has_user_info<JetInfo>()) {
//             Print(Severity::Error, "Sub Bdt", "No Jet Info");
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
//                     Print(Severity::Error, "constituent Bdt", "No Jet Info");
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

Jets TauTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets final_jets;
    Print(Severity::Information, "Jet Bdt");
    Jets jets = event.Hadrons().Jets();
    for (const auto jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Print(Severity::Error, "Jet Bdt", "No Jet Info");
            continue;
        }
//         if (Jet.m() <= 0) {
//             Print(Severity::Information, "Empty Piece");
//             continue;
//         }
        static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet,reader));
        final_jets.emplace_back(jet);
    }
    return final_jets;
}

}
