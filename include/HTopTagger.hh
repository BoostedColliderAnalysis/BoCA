# ifndef HTopTagger_hh
# define HTopTagger_hh

# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

# include "HObject.hh"
# include "HEPTopTagger.hh"

/**
 * @brief prepares the data for the top tagger
 *
 */
class hdelphes::HTopTagger : public hanalysis::HObject
{

public:

    /**
     * @brief tagges the tops
     *
     * @param HadronVector ...
     * @return void
     */
    std::vector< PseudoJet > GetTops(std::vector< PseudoJet > &EFlowJets);

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
     * @param HadronVector Vector of Jet Candidates derived from EFlow data
     * @param CellEta Delta Eta of Cells
     * @param CellPhi Delta Phi of Cells
     * @param PtCutOff Pt Cutoff for cells
     * @return std::vector< fastjet::PseudoJet, std::allocator >
     */
    HJets GetGranulatedJets(HJets &HadronVector, const float &CellEta, const float &CellPhi, const float &PtCutOff);

    inline std::string NameSpaceName() const {
      return "HDelphes";
    };

    inline std::string ClassName() const {
        return "HTopTagger";
    };

};

#endif
