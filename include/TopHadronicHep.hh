# pragma once

# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

# include "Object.hh"

namespace analysis {

/**
 * @brief prepares the data for the top tagger
 *
 */
class TopHadronicHep : public Object
{

public:

    /**
     * @brief tagges the tops
     *
     */
    std::vector< fastjet::PseudoJet > GetTops(std::vector< fastjet::PseudoJet > &EFlowJets);

    /**
     * @brief constructor
     *
     */
    TopHadronicHep();

private:

    /**
     * @brief Calculates Vector of granulated Jets
     *
     */
    Jets GetGranulatedJets(Jets& EFlowJets);

    inline std::string ClassName() const {
      return "TopHadronicHep";
    }

};

}
