
#pragma once
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "Jet.hh"

namespace boca
{

class ClusterSequence
{

public :

    ClusterSequence(std::vector<fastjet::PseudoJet> const& jets, fastjet::JetDefinition const& jet_definition) : cluster_sequence_(new fastjet::ClusterSequence(jets, jet_definition)) {}

    ClusterSequence(std::vector<Jet> const& jets, fastjet::JetDefinition const& jet_definition) : cluster_sequence_(new fastjet::ClusterSequence(PseudoJetVector(jets), jet_definition)) {}

    ~ClusterSequence() {
        if (!sucess) delete cluster_sequence_;
        cluster_sequence_->delete_self_when_unused();
    }

    std::vector<Jet> ExclusiveJets(int jet_number) const {
        std::vector<Jet> jets = JetVector(cluster_sequence_->exclusive_jets(jet_number));
        if (jets.empty()) sucess = false;
        return jets;
    }

    std::vector<Jet> ExclusiveJetsUpTo(int sub_jet_number) const {
        std::vector<Jet> jets = JetVector(cluster_sequence_->exclusive_jets_up_to(sub_jet_number));
        if (jets.empty()) sucess = false;
        return jets;
    }

    std::vector<Jet> InclusiveJets(Momentum const& min_pt) const {
        std::vector<Jet> jets = JetVector(cluster_sequence_->inclusive_jets(min_pt / GeV));
        if (jets.empty()) sucess = false;
        return jets;
    }

private :

    fastjet::ClusterSequence* cluster_sequence_;
    mutable bool sucess = true;

};

}
