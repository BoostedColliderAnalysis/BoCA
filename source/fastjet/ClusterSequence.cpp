/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/ClusterSequence.hh"
#include "boca/fastjet/ClusterSequence.hh"

namespace boca
{

ClusterSequence::ClusterSequence(std::vector< fastjet::PseudoJet > const& jets, const fastjet::JetDefinition& jet_definition)
    : cluster_sequence_(new fastjet::ClusterSequence(jets, jet_definition))
{}

ClusterSequence::ClusterSequence(const std::vector< Jet >& jets, const fastjet::JetDefinition& jet_definition)
    : cluster_sequence_(new fastjet::ClusterSequence(PseudoJetVector(jets), jet_definition))
{}

ClusterSequence::~ClusterSequence()
{
    if (success_) cluster_sequence_->delete_self_when_unused();
    else delete cluster_sequence_;
}

std::vector< Jet > ClusterSequence::ExclusiveJets(int jet_number) const
{
    auto jets = JetVector(cluster_sequence_->exclusive_jets(jet_number));
    if (jets.empty()) success_ = false;
    return jets;
}

std::vector< Jet > ClusterSequence::ExclusiveJetsUpTo(int sub_jet_number) const
{
    auto jets = JetVector(cluster_sequence_->exclusive_jets_up_to(sub_jet_number));
    if (jets.empty()) success_ = false;
    return jets;
}

std::vector< Jet > ClusterSequence::InclusiveJets(const Momentum& min_pt) const
{
    auto jets = JetVector(cluster_sequence_->inclusive_jets(min_pt / GeV));
    if (jets.empty()) success_ = false;
    return jets;
}

fastjet::ClusterSequence& ClusterSequence::Get()
{
    return *cluster_sequence_;
}

void ClusterSequence::AddConstituents(fastjet::PseudoJet const& jet, std::vector< fastjet::PseudoJet >& subjet_vector) const
{
    cluster_sequence_->add_constituents(jet, subjet_vector);
}

void ClusterSequence::NoLongerNeeded()
{
    success_ = false;
}

}
