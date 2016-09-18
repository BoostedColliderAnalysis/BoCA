/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/ClusterSequence.hh"
#include "boca/fastjet/ClusterSequence.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

ClusterSequence::ClusterSequence(std::vector< fastjet::PseudoJet > const &jets, fastjet::JetDefinition const &jet_definition)
    : cluster_sequence_(new fastjet::ClusterSequence(jets, jet_definition))
{
    DEBUG(jets.size());
}

ClusterSequence::ClusterSequence(std::vector< Jet > const &jets, fastjet::JetDefinition const &jet_definition)
    : cluster_sequence_(new fastjet::ClusterSequence(PseudoJetVector(jets), jet_definition))
{
    DEBUG(jets.size());
}

ClusterSequence::ClusterSequence(ClusterSequence const &cluster_sequence) :
    cluster_sequence_(new fastjet::ClusterSequence(*cluster_sequence.cluster_sequence_))
{
    DEBUG0;
}

ClusterSequence::ClusterSequence(ClusterSequence  &&cluster_sequence) noexcept :
cluster_sequence_(cluster_sequence.cluster_sequence_)
{
    DEBUG0;
    cluster_sequence.cluster_sequence_ = nullptr;
}

ClusterSequence::~ClusterSequence()
{
    DEBUG0;
    if (success_) cluster_sequence_->delete_self_when_unused();
    else delete cluster_sequence_;
}

ClusterSequence &ClusterSequence::operator=(ClusterSequence const &cluster_sequence)
{
    DEBUG0;
    auto tmp = ClusterSequence {cluster_sequence};
    *this = std::move(tmp);
    return *this;
}

ClusterSequence &ClusterSequence::operator=(ClusterSequence && cluster_sequence) noexcept {
    DEBUG0;
    if (success_) cluster_sequence_->delete_self_when_unused();
    else delete cluster_sequence_;
    cluster_sequence_ = cluster_sequence.cluster_sequence_;
    cluster_sequence.cluster_sequence_ = nullptr;
    return *this;
}

std::vector< Jet > ClusterSequence::ExclusiveJets(int jet_number) const
{
    DEBUG(jet_number);
    auto jets = JetVector(cluster_sequence_->exclusive_jets(jet_number));
    if (jets.empty()) success_ = false;
    return jets;
}

std::vector< Jet > ClusterSequence::ExclusiveJetsUpTo(int sub_jet_number) const
{
    DEBUG(sub_jet_number);
    auto jets = JetVector(cluster_sequence_->exclusive_jets_up_to(sub_jet_number));
    if (jets.empty()) success_ = false;
    return jets;
}

std::vector< Jet > ClusterSequence::InclusiveJets(Momentum const &min_pt) const
{
    DEBUG(min_pt);
    auto jets = JetVector(cluster_sequence_->inclusive_jets(min_pt / GeV));
    if (jets.empty()) success_ = false;
    return jets;
}

fastjet::ClusterSequence &ClusterSequence::Get()
{
    DEBUG0;
    return *cluster_sequence_;
}

void ClusterSequence::AddConstituents(fastjet::PseudoJet const &jet, std::vector< fastjet::PseudoJet > &subjet_vector) const
{
    DEBUG0;
    cluster_sequence_->add_constituents(jet, subjet_vector);
}

void ClusterSequence::NoLongerNeeded()
{
    DEBUG0;
    success_ = false;
}

}
