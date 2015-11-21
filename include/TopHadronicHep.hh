#pragma once

#include <vector>

namespace fastjet{
class PseudoJet;
}

namespace boca {

typedef std::vector<fastjet::PseudoJet> Jets;

/**
 * @brief prepares the data for the top tagger
 *
 */
class TopHadronicHep {

public:

    /**
     * @brief tagges the tops
     *
     */
   std::vector<fastjet::PseudoJet>Tops(Jets& e_flows);

private:

    /**
     * @brief Calculates Vector of granulated Jets
     *
     */
   std::vector<fastjet::PseudoJet> GranulatedJets(std::vector<fastjet::PseudoJet>& e_flows);

};

}
