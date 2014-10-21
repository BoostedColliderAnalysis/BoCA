# ifndef HAnalysisTest_hh
# define HAnalysisTest_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchTest.hh"

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class HAnalysisTest : public HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisTest();

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
    bool Analysis(HEvent* Event, string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector< HFile* > GetFiles();

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewFile(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    vector<string> GetStudyNameVector();

    virtual string ClassName() const {

        return ("HAnalysisTest");

    };

};


#endif

