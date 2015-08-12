#include "InfoRecombiner.hh"
#include "JetInfo.hh"

namespace analysis {

InfoRecombiner::InfoRecombiner(fastjet::RecombinationScheme recombination_scheme): fastjet::JetDefinition::DefaultRecombiner(recombination_scheme) {}

std::string InfoRecombiner::description() const
{
    return fastjet::JetDefinition::DefaultRecombiner::description() + " (with user info)";
}

void InfoRecombiner::recombine(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2, fastjet::PseudoJet& jet) const
{
    fastjet::JetDefinition::DefaultRecombiner::recombine(jet_1, jet_2, jet);
    JetInfo jet_info;
    if(jet_1.has_user_info<JetInfo>()) jet_info = jet_1.user_info<JetInfo>();
    if(jet_2.has_user_info<JetInfo>()) jet_info += jet_2.user_info<JetInfo>();
    jet.set_user_info(new JetInfo(jet_info));
}

}
