#pragma once

#include <vector>

namespace fastjet{
class PseudoJet;
}

namespace analysis {

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
    Jets Tops(Jets& e_flows);

private:

    /**
     * @brief Calculates Vector of granulated Jets
     *
     */
    Jets GranulatedJets(analysis::Jets& e_flows);

};

}
