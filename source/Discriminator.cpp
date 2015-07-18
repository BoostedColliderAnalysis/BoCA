#include "Discriminator.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

Jets Discriminator::GetCandidateJets(const Jets& EFlowJets, const float ScalarHt)
{
    Info("Tagged Candidate Jets", EFlowJets.size());
    const Jets jets;
    if (EFlowJets.empty()) {
        Info("No EFlow Jets");
        return jets;
    }
    const float DeltaR = 750. / ScalarHt;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    const Jets FatJets = GetFatJets(EFlowJets, FatJetDefinition);
    Jets MassDropJets = GetMassDropJets(FatJets);
//     Jets MassDropJets = GetSubjet_taggedJets(FatJets);
    MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());
    MassDropJets = SortedByMass(MassDropJets);
    MassDropJets = GetFatjet_tag(MassDropJets);
    return MassDropJets;
}


Jets Discriminator::GetCandidateJetsForced(const Jets& EFlowJets, const float ScalarHt)
{
    Info("Tagged Candidate Jets", EFlowJets.size());
    const Jets jets;
    if (EFlowJets.empty()) {
        Info("No EFlow Jets");
        return jets;
    }
//     float DeltaR = 1000. / ScalarHt;
    float DeltaR = 750. / ScalarHt;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    Jets MassDropJets;
    while (MassDropJets.empty() && DeltaR < 7) {
        const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
        const Jets FatJets = GetFatJets(EFlowJets, FatJetDefinition);
        MassDropJets = GetMassDropJets(FatJets);
        MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());
        DeltaR += .25;
    }
    MassDropJets = SortedByMass(MassDropJets);
    MassDropJets = GetFatjet_tag(MassDropJets);
    return MassDropJets;
}


bool Discriminator::JetIsBad(const fastjet::PseudoJet& Jet)
{
    if (std::abs(Jet.m()) <= 40.) {
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

}
