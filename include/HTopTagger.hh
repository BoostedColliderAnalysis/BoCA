# ifndef HTopTagger_hh
# define HTopTagger_hh

# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

# include "Object.hh"

/**
 * @brief prepares the data for the top tagger
 *
 */
class analysis::HTopTagger : public analysis::Object
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
    HTopTagger();

    ~HTopTagger();

private:

    /**
     * @brief Calculates Vector of granulated Jets
     * 
     */
    Jets GetGranulatedJets(Jets& EFlowJets);

    inline std::string ClassName() const {
        return "HTopTagger";
    };

};

#endif
