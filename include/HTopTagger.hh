# ifndef HTopTagger_hh
# define HTopTagger_hh

# include <vector>

// # include "TMath.h"
// # include "Rtypes.h"

# include "fastjet/PseudoJet.hh"
# include "fastjet/ClusterSequence.hh"

# include "HEPTopTagger.hh"
# include "HPull.hh"
# include "HObject.hh"

/**
 * @brief prepares the data for the top tagger
 *
 */
class HTopTagger : public HObject
{

public:

    /**
     * @brief vector of top lorentzvector
     *
     */
    vector<TLorentzVector> TopLorentzVectorVector;

    /**
     * @brief vector of top pseudo vector
     *
     */
    vector<PseudoJet> TopJetVector;

    /**
     * @brief vector of bottom pseudo vector
     *
     */
    vector<PseudoJet> BottomJetVector;

    /**
     * @brief vector of W Jet pseudo vector
     *
     */
    vector<PseudoJet> FirstWJetVector;

    /**
     * @brief vector of W Jet pseudo vectors
     *
     */
    vector<PseudoJet> SecondWJetVector;

    /**
     * @brief number of top candidates
     *
     */
    int NumberOfTop;

    /**
     * @brief tagges the tops
     *
     * @param HadronVector ...
     * @return void
     */
    void TaggingTop(vector< PseudoJet > HadronVector);

    /**
     * @brief removes the bottoms comming from the top decay from the vector of bottom lorentz vectors
     *
     * @param BottomClassVector .
     * @return void
     */
    void RemoveBottomComingFromTop(vector<HPull *> BottomClassVector);

    /**
     * @brief constructor
     *
     */
    HTopTagger();

    ~HTopTagger();

    void NewEvent();

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
    vector<PseudoJet> GranulateJets(vector<PseudoJet> &HadronVector, const float &CellEta, const float &CellPhi, const float &PtCutOff);

    string ClassName() const {

        return ("HTopTagger");

    };

};

#endif
