#pragma once

#include "fastjet/JetDefinition.hh"

namespace analysis
{

class InfoRecombiner : public  fastjet::JetDefinition::DefaultRecombiner
{
public:
  InfoRecombiner(fastjet::RecombinationScheme recombination_scheme = fastjet::E_scheme);

  std::string description() const final;
  /// recombine jet_1 and jet_2 and put result into jet
  void recombine(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, fastjet::PseudoJet& jet) const final;
};

}
