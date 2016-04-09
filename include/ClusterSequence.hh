/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "fastjet/ClusterSequence.hh"
#include "multiplets/Jet.hh"

namespace boca
{

  /**
   * @brief Wrapper around fastjet:ClusterSequence taking care of memory managment
   *
   */
  class ClusterSequence
{

public :

    ClusterSequence(std::vector<fastjet::PseudoJet> const& jets, fastjet::JetDefinition const& jet_definition);

    ClusterSequence(std::vector<Jet> const& jets, fastjet::JetDefinition const& jet_definition);

    ~ClusterSequence();

    std::vector<Jet> ExclusiveJets(int jet_number) const;

    std::vector<Jet> ExclusiveJetsUpTo(int sub_jet_number) const;

    std::vector<Jet> InclusiveJets(Momentum const& min_pt = at_rest) const;

    fastjet::ClusterSequence& Get();

    void AddConstituents(fastjet::PseudoJet const& jet, std::vector<fastjet::PseudoJet>& subjet_vector) const;

private :

    fastjet::ClusterSequence* cluster_sequence_;
    mutable bool sucess_ = true;

};

}
