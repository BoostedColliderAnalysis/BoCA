# pragma once

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
     * @brief constructor
     *
     */
    TopHadronicHep();

    /**
     * @brief tagges the tops
     *
     */
    Jets Tops(std::vector< fastjet::PseudoJet > &e_flows);

private:

    /**
     * @brief Calculates Vector of granulated Jets
     *
     */
    Jets GranulatedJets(analysis::Jets &e_flows);

     std::string ClassName() const {
      return "TopHadronicHep";
    }

};

}
