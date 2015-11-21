/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Discriminator.hh"

#include "fastjet/JetDefinition.hh"

#include "Sort.hh"
#include "Debug.hh"

namespace boca
{

std::vector<Jet>Discriminator::GetCandidateJets(std::vector<Jet> const& EFlowJets, float ScalarHt)
{
    INFO("Tagged Candidate Jets", EFlowJets.size());
    std::vector<Jet> jets;
    if (EFlowJets.empty()) {
        INFO("No EFlow Jets");
        return jets;
    }
    float DeltaR = 750. / ScalarHt;
    fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    std::vector<Jet> FatJets = GetFatJets(EFlowJets, FatJetDefinition);
    std::vector<Jet> MassDropJets = GetMassDropJets(FatJets);
//    std::vector<Jet> MassDropJets= GetSubjet_taggedJets(FatJets);
    MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());
    MassDropJets = SortedByMass(MassDropJets);
    MassDropJets = GetFatjet_tag(MassDropJets);
    return MassDropJets;
}


std::vector<Jet>Discriminator::GetCandidateJetsForced(std::vector<Jet> const& EFlowJets, float ScalarHt)
{
    INFO("Tagged Candidate Jets", EFlowJets.size());
    std::vector<Jet> jets;
    if (EFlowJets.empty()) {
        INFO("No EFlow Jets");
        return jets;
    }
//     float DeltaR = 1000. / ScalarHt;
    float DeltaR = 750. / ScalarHt;
    fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    std::vector<Jet>MassDropJets;
    while (MassDropJets.empty() && DeltaR < 7) {
        fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
        std::vector<Jet> FatJets = GetFatJets(EFlowJets, FatJetDefinition);
        MassDropJets = GetMassDropJets(FatJets);
        MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());
        DeltaR += .25;
    }
    MassDropJets = SortedByMass(MassDropJets);
    MassDropJets = GetFatjet_tag(MassDropJets);
    return MassDropJets;
}


bool Discriminator::JetIsBad(Jet const& Jet)
{
    if (std::abs(Jet.m()) <= 40.) {
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

}
