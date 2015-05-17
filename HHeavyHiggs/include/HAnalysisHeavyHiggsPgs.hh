# ifndef HAnalysisHeavyHiggsPgs_hh
# define HAnalysisHeavyHiggsPgs_hh

# include "Analysis.hh"

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class hheavyhiggs::HAnalysisHeavyHiggsPgs : public analysis::Analysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsPgs();

private:


    inline int GeteventnumberMax()const{ return 10000;};

    inline std::string ProjectName()const{ return "HeavyHiggsPgs";};

    /**
     * @brief Branch to write Heavy Higgs info into
     *
     */
    ExRootTreeBranch *HeavyHiggsBranch;

    /**
     * @brief Cutflow counter
     *
     */
    int DeltaRapCounter,
        BMassCounter,
        TMassCounter,
        eventCounter,
        JetCounter,
        Jet2Counter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int Analysis(analysis::Event &event,const std::string& StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< analysis::File* > GetFiles(const std::string& StudyName);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter* TreeWriter);

    void CloseFile();

    virtual inline std::string ClassName() const {

        return ("HAnalysisHeavyHiggsPgs");

    };

};


#endif

