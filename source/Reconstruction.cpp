/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Reconstruction.hh"

#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/CASubJetTagger.hh"
#include "fastjet/ClusterSequence.hh"
#include "JetInfo.hh"
#include "Debug.hh"

namespace boca {

void Reconstruction::NewEvent()
{
    Info("New event");
//     FatJetVector.clear();
}

Jets Reconstruction::GetFatJets(Jets const& EFlowJets) const
{
    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    float DeltaR = 1.2;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    return GetFatJets(EFlowJets, FatJetDefinition);
}

Jets Reconstruction::GetFatJets(Jets const& EFlowJets, const fastjet::JetDefinition& FatJetDefinition) const
{
    Info("Fat Jet Vector", FatJetDefinition.R());
    auto const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJets, FatJetDefinition);
    // FatJetPtMin = Jing: 40; fastjet: 0
    float FatJetPtMin = 0;
    const Jets FatJets = FatJetClusterSequence->inclusive_jets(FatJetPtMin);
    if (FatJets.empty()) delete FatJetClusterSequence;
    else FatJetClusterSequence->delete_self_when_unused();
    return FatJets;
}


Jets Reconstruction::GetMassDropJets(Jets const& FatJets) const
{
    Info("Mass Drop Jets", FatJets.size());
    Jets MassDropJets;
    for (auto& FatJet : FatJets)
        MassDropJets.emplace_back(GetMassDropJet(FatJet));
    return MassDropJets;
}

fastjet::PseudoJet Reconstruction::GetMassDropJet(fastjet::PseudoJet const& FatJet) const
{
//     Debug("Mass Drop Jet");
    //     MassDropMin = Jing: 0.667; fastjet: 0.67; Paper: 0.67
    float MassDropMin = 0.67;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    float AsymmetryCut = 0.09;
    return GetMassDropJet(FatJet, MassDropMin, AsymmetryCut);
}



fastjet::PseudoJet Reconstruction::GetMassDropJet(fastjet::PseudoJet const& FatJet, float MassDropMin, float AsymmetryCut) const
{
    Debug("Mass Drop Jet");
    const fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    const fastjet::PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);
    return MassDropJet;
}




Jets Reconstruction::GetSubjet_taggedJets(Jets const& FatJets) const
{
    Info("Sub Jet Tagged Jets", FatJets.size());
    Jets Subjet_taggedJets;
    for (auto& FatJet : FatJets)
        Subjet_taggedJets.emplace_back(GetSubjet_taggedJet(FatJet));
    return Subjet_taggedJets;
}

fastjet::PseudoJet Reconstruction::GetSubjet_taggedJet(fastjet::PseudoJet const& FatJet) const
{
    Debug("Mass Drop Jet");
    const fastjet::CASubJetTagger Subjet_tagger;
    const fastjet::PseudoJet MassDropJet = Subjet_tagger.result(FatJet);
    return MassDropJet;
}


bool Reconstruction::JetIsBad(fastjet::PseudoJet const& Jet)
{
    if (std::abs(Jet.m()) <= 40) {
        Info("Fat Jet Mass", Jet.m());
        return 1;
    }
    if (Jet.pieces().size() != 2) {
        Note("Pieces Sum", Jet.pieces().size());
        return 1;
    }
    if (!Jet.has_structure()) {
        Note("fastjet::PseudoJet has no structure");
        return 1;
    }
    return 0;
}



Jets Reconstruction::GetFatjet_tag(Jets& FatJets)
{
    Info("Fat Jet Tag", FatJets.size());
    for (auto& FatJet : FatJets) {
        JetInfo jet_info;
        for (auto const& constituent : FatJet.constituents()) {
            if (constituent.has_user_info()) {
//                 jet_info.AddConstituents(constituent.user_info<JetInfo>().constituents());
//               std::map<int, float> JetFractions = constituent.user_info<JetInfo>().GetJetFractions();
//               for (std::map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {
//                     jet_info.Addconstituent((*Pair).first, (*Pair).second * constituent.pt());
//                 }
//                 constituent.user_info<JetInfo>().PrintAllInfos(Severity::detailed);
            } else {
                Error("No info in constituent jet");
//             jet_info.Addconstituent(constituent.user_index(), constituent.pt());
            }
        }
        FatJet.set_user_info(new JetInfo(jet_info));
//         FatJet.set_user_index(FatJet.user_info<JetInfo>().MaximalId());
//         FatJet.user_info<JetInfo>().PrintAllInfos(Severity::detailed);
//         Detail("Tag", FatJet.user_info<JetInfo>().MaximalId(), FatJet.user_info<JetInfo>().MaximalFraction(), FatJet.m());
    }
    return FatJets;
}

}
