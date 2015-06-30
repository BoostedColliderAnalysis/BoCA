#pragma once

#include "Global.hh"

namespace analysis {

/**
 * @brief prepares the data for the top tagger
 *
 */
class TopHadronicHep
{

public:

    /**
     * @brief constructor
     *
     */
    TopHadronicHep();

    /**
     * @brief tagges the tops
     *
     */
    Jets Tops(Jets &e_flows);

private:

    /**
     * @brief Calculates Vector of granulated Jets
     *
     */
    Jets GranulatedJets(analysis::Jets &e_flows);

};

}
