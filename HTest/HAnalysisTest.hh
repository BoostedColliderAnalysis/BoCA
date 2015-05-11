# ifndef HAnalysisTest_hh
# define HAnalysisTest_hh

# include "HAnalysis.hh"
# include "HFileDelphes.hh"
# include "HEventDelphes.hh"
# include "HBranchTest.hh"

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class htest::HAnalysis : public hanalysis::HAnalysis
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
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    Jets Leptons();

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
    int Analysis(hanalysis::HEvent &Event,const std::string &StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< hanalysis::RootFile* > GetFiles(const std::string &StudyName);

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

