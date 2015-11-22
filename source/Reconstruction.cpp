/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Reconstruction.hh"

#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/CASubJetTagger.hh"
#include "fastjet/ClusterSequence.hh"
#include "JetInfo.hh"
#include "Jet.hh"
#include "Debug.hh"

namespace boca {

void Reconstruction::NewEvent()
{
    INFO("New event");
//     FatJetVector.clear();
}

std::vector<Jet> Reconstruction::GetFatJets(std::vector<Jet> const& EFlowJets) const
{
    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    float DeltaR = 1.2;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    return GetFatJets(EFlowJets, FatJetDefinition);
}

std::vector<Jet> Reconstruction::GetFatJets(std::vector<Jet> const& EFlowJets, const fastjet::JetDefinition& FatJetDefinition) const
{
    INFO("Fat Jet Vector", FatJetDefinition.R());
    auto const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJets, FatJetDefinition);
    // FatJetPtMin = Jing: 40; fastjet: 0
    float FatJetPtMin = 0;
    const std::vector<Jet>FatJets= JetVector(FatJetClusterSequence->inclusive_jets(FatJetPtMin));
    if (FatJets.empty()) delete FatJetClusterSequence;
    else FatJetClusterSequence->delete_self_when_unused();
    return FatJets;
}


std::vector<Jet> Reconstruction::GetMassDropJets(std::vector<Jet> const& FatJets) const
{
    INFO("Mass Drop Jets", FatJets.size());
   std::vector<Jet>MassDropJets;
    for (auto& FatJet : FatJets) MassDropJets.emplace_back(GetMassDropJet(FatJet));
    return MassDropJets;
}

Jet Reconstruction::GetMassDropJet(Jet const& FatJet) const
{
//     Debug("Mass Drop Jet");
    //     MassDropMin = Jing: 0.667; fastjet: 0.67; Paper: 0.67
    float MassDropMin = 0.67;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    float AsymmetryCut = 0.09;
    return GetMassDropJet(FatJet, MassDropMin, AsymmetryCut);
}



Jet Reconstruction::GetMassDropJet(Jet const& FatJet, float MassDropMin, float AsymmetryCut) const
{
    Debug("Mass Drop Jet");
    const fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    const Jet MassDropJet = FatJetMassDroppTagger(FatJet);
    return MassDropJet;
}




std::vector<Jet> Reconstruction::GetSubjet_taggedJets(std::vector<Jet> const& FatJets) const
{
    INFO("Sub Jet Tagged Jets", FatJets.size());
   std::vector<Jet>Subjet_taggedJets;
    for (auto& FatJet : FatJets)
        Subjet_taggedJets.emplace_back(GetSubjet_taggedJet(FatJet));
    return Subjet_taggedJets;
}

Jet Reconstruction::GetSubjet_taggedJet(Jet const& FatJet) const
{
    Debug("Mass Drop Jet");
    const fastjet::CASubJetTagger Subjet_tagger;
    const Jet MassDropJet = Subjet_tagger.result(FatJet);
    return MassDropJet;
}


bool Reconstruction::JetIsBad(Jet const& Jet)
{
    if (std::abs(Jet.m()) <= 40) {
        INFO("Fat Jet Mass", Jet.m());
        return 1;
    }
    if (Jet.pieces().size() != 2) {
        Note("Pieces Sum", Jet.pieces().size());
        return 1;
    }
    if (!Jet.has_structure()) {
        Note("Jet has no structure");
        return 1;
    }
    return 0;
}



std::vector<Jet> Reconstruction::GetFatjet_tag(std::vector<Jet>& FatJets)
{
    INFO("Fat Jet Tag", FatJets.size());
    for (auto& FatJet : FatJets) {
        JetInfo jet_info;
        for (auto const& constituent : FatJet.constituents()) {
            if (constituent.has_user_info()) {
//                 jet_info.AddConstituents(constituent.Info().constituents());
//               std::map<int, float> JetFractions = constituent.Info().GetJetFractions();
//               for (std::map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {
//                     jet_info.Addconstituent((*Pair).first, (*Pair).second * constituent.pt());
//                 }
//                 constituent.Info().PrintAllInfos(Severity::detailed);
            } else {
                Error("No info in constituent jet");
//             jet_info.Addconstituent(constituent.user_index(), constituent.pt());
            }
        }
        FatJet.set_user_info(new JetInfo(jet_info));
//         FatJet.set_user_index(FatJet.Info().MaximalId());
//         FatJet.Info().PrintAllInfos(Severity::detailed);
//         Detail("Tag", FatJet.Info().MaximalId(), FatJet.Info().MaximalFraction(), FatJet.m());
    }
    return FatJets;
}

}
