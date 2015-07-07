#include "TauTagger.hh"

#include "fastjet/ClusterSequence.hh"
#include "Singlet.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

TauTagger::TauTagger()
{
    Info();
    DefineVariables();
}

void TauTagger::DefineVariables()
{
    Info("Define Variables");
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

int TauTagger::Train(const Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info("Tau Tag", Name(tag));
    Jets jets = event.Hadrons().Jets();
    Info("Number Jets", jets.size());
    Jets Particles = event.Partons().GenParticles();
    Particles = RemoveIfWrongAbsParticle(Particles, Id::tau);
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(Id::tau)), Particles.end());
//     if(Particles.size()!=1)
    Info("Tau Partilces", Particles.size());
    Jets final_jets = CleanJets(jets, Particles,tag);
//     if(FinalJets.size()!=1)
    Info("Tau Jets", final_jets.size());
//     Jets Pieces = GetSubJets(jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//     Jets Pieces2 = GetSubJets(jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());
    std::vector<Singlet> singlets;
    for (const auto &final_jet : final_jets) singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}

// Jets TauTagger::GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber)
// {
//     Info("Sub Jets");
//     Jets Pieces;
//     for (const auto & Jet : jets) {
//         if (!Jet.has_constituents()) {
//             Error("Pieceless jet");
//             continue;
//         }
//         if (!Jet.has_user_info<JetInfo>()) {
//             Error("Sub Jets", "No Jet Info");
//             continue;
//         }
//         fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, 0.4));
//         Jets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
//         ClusterSequence->delete_self_when_unused();
//         for (auto & Piece : NewPieces) {
//             std::vector<Constituent> constituents;
//             for (const auto & Piececonstituent : Piece.constituents()) {
//                 if (!Piececonstituent.has_user_info<JetInfo>()) {
//                     Error("Sub Jets", "No Piece constituent Info");
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


Jets TauTagger::CleanJets(analysis::Jets &jets, const analysis::Jets &Particles, const analysis::Tag tag) const
{
    Info("Clean Jets");
    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(Tag::signal);
    }
    Jets NewCleanJets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) {
            Error("Clean Jets", "No Jet Info");
            continue;
        }
//         if (std::abs(Jet.rap()) > 2.5) continue;
// if (Jet.m() < 0){
//   Error("Clean Jets", "Massless Jet");
//           continue;
//         }
//         if (Tag == Tag::signal && Jet.user_info<JetInfo>().SumDisplacement() == 0) continue;
        if (Jet.user_info<JetInfo>().Tag() != tag) {
//   Error("Clean Jets", "Not Tagged Jet");
            continue;
        }
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

// Object::HTag HTauTagger::GetTag(const fastjet::PseudoJet &Jet) const
// {
//
//     Debug("Bottom Tag", Jet.rap(), Jet.user_info<JetInfo>().MaximalId());
//     if (std::abs(Jet.user_info<JetInfo>().MaximalId()) != Id::bottom) {
//         return HBackground;
//     }
//     return Tag::signal;
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
//     Info("Sub Bdt");
//     Jets Pieces;
//     for (const auto & Jet : jets) {
//         if (!Jet.has_pieces()) {
//             Error("pieceless jet");
//             continue;
//         }
//         if (!Jet.has_user_info<JetInfo>()) {
//             Error("Sub Bdt", "No Jet Info");
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
//                     Error("constituent Bdt", "No Jet Info");
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

Jets TauTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Jets final_jets;
    Info("Jet Bdt");
    Jets jets = event.Hadrons().Jets();
    for (const auto &jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Error("Jet Bdt", "No Jet Info");
            continue;
        }
//         if (Jet.m() <= 0) {
//             Info("Empty Piece");
//             continue;
//         }
        static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet,reader));
        final_jets.emplace_back(jet);
    }
    return final_jets;
}

}
