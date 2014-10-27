# ifndef HAnalysisTest_hh
# define HAnalysisTest_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchTest.hh"

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class HAnalysisTest : public hanalysis::HAnalysis
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

    inline string GetProjectName()const{return "Test";};

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
    bool Analysis(hanalysis::HEvent* Event, string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector< hanalysis::HFile* > GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    vector<string> GetStudyNameVector();

    virtual inline string ClassName() const {

        return ("HAnalysisTest");

    };

};


#endif

