# ifndef HDiscriminator_hh
# define HDiscriminator_hh

# include "HReconstruction.hh"
# include "HJetInfo.hh"

using std::sort;

/**
 * @brief Jet Discriminator
 *
 *
 */
class HDiscriminator : public HReconstruction
{

public:

    /**
     * @brief Constructor
     *
     */
    HDiscriminator();

    /**
     * @brief Destructor
     *
     */
    ~HDiscriminator();

    /**
     * @brief New File
     *
     * @return void
     */
    void NewFile();

    /**
     * @brief Clean after end of Analysis
     *
     * @return void
     */

    void CloseFile();

    /**
     * @brief New Event
     *
     * @return void
     */
    void NewEvent();

    /**
     * @brief Get Fat Higgs Jets
     *
     * @param  EFlow Jet Vector
     * @return Candidates
     */
    vector<PseudoJet> GetCandidateJets(const vector<PseudoJet> &, const float);

private:

    string ClassName() const {

        return ("HDiscriminator");

    };

};

# endif
