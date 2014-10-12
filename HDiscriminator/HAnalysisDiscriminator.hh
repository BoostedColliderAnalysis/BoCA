# ifndef HAnalysisDiscriminator_hh
# define HAnalysisDiscriminator_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchDiscriminator.hh"

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class HAnalysisDiscriminator : public HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisDiscriminator();

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *CandidateBranch;

    /**
     * @brief Branch to write Lepton info into
     *
     */
    ExRootTreeBranch *LeptonBranch;

    /**
     * @brief Branch to write Constituent info into
     *
     */
    ExRootTreeBranch *ConstituentBranch;

private:

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    vector<PseudoJet> Leptons();

    /**
     * @brief Lepton event counter
     *
     */
    int LeptonEventCounter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis();

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    void SetFileVector();

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewFile();

    void CloseFile();

    vector<string> GetStudyNameVector();

    virtual string ClassName() const {

        return ("HAnalysisDiscriminator");

    };

};


#endif

