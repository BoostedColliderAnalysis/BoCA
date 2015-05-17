# ifndef HAnalysisTest_hh
# define HAnalysisTest_hh

# include "HAnalysis.hh"
# include "File.hh"
// # include "HEventDelphes.hh"
# include "HBranchTest.hh"

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class htest::HAnalysis : public analysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysis();

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
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *constituentBranch;

private:

    inline std::string ProjectName()const{return "Test";};

    /**
     * @brief Lepton calculations
     *
     * @param event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    Jets Leptons();

    /**
     * @brief Lepton event counter
     *
     */
    int LeptoneventCounter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int Analysis(analysis::Event &event,const std::string &StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< analysis::File* > GetFiles(const std::string &StudyName);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    Strings GetStudyNameVector();

    virtual inline std::string ClassName() const {

        return ("HAnalysisTest");

    };

};


#endif

