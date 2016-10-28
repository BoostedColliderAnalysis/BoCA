/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "fastjet/ClusterSequence.hh"

#include "boca/units/ElectronVolt.hh"

/**
* @brief <a href="http://fastjet.fr/">FastJet</a> A software package for jet finding in pp and e+e− collisions.
*
*/
namespace fastjet
{
class ClusterSequence;
class JetDefinition;
}

namespace boca
{

class Jet;

/**
 * @ingroup FastJet
 * @brief Wrapper around fastjet:ClusterSequence taking care of memory managment
 *
 */
class ClusterSequence
{

public :

    ClusterSequence(std::vector<fastjet::PseudoJet> const& jets, fastjet::JetDefinition const& jet_definition);

    ClusterSequence(std::vector<Jet> const& jets, fastjet::JetDefinition const& jet_definition);

    ClusterSequence(ClusterSequence const& cluster_sequence);

    ClusterSequence(ClusterSequence && cluster_sequence) noexcept;

    ~ClusterSequence();

    ClusterSequence& operator=(ClusterSequence const& cluster_sequence);

    ClusterSequence& operator=(ClusterSequence && cluster_sequence) noexcept;

    std::vector<Jet> ExclusiveJets(int jet_number) const;

    std::vector<Jet> ExclusiveJetsUpTo(int sub_jet_number) const;

    std::vector<Jet> InclusiveJets(Momentum const& min_pt = at_rest) const;

    fastjet::ClusterSequence& Get();

    fastjet::ClusterSequence const& Get() const;

    void AddConstituents(fastjet::PseudoJet const& jet, std::vector<fastjet::PseudoJet>& subjet_vector) const;

    void NoLongerNeeded();

private :

    fastjet::ClusterSequence* cluster_sequence_;

    mutable bool success_ = true;

};

}
