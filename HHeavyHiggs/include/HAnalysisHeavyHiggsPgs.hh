# ifndef HAnalysisHeavyHiggsPgs_hh
# define HAnalysisHeavyHiggsPgs_hh

# include "HAnalysis.hh"

# include "HBranchHeavyHiggs.hh"

using std::iter_swap;

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class HeavyHiggs::HAnalysisHeavyHiggsPgs : public Analysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsPgs();

private:


    inline int GetEventnumberMax()const{ return 10000;};

    inline string GetProjectName()const{ return "HeavyHiggsPgs";};

    /**
     * @brief Branch to write Heavy Higgs info into
     *
     */
    ExRootTreeBranch *HeavyHiggsBranch;

    /**
     * @brief Cutflow counter
     *
     */
    int DeltaEtaCounter,
        BMassCounter,
        TMassCounter,
        EventCounter,
        JetCounter,
        Jet2Counter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(Analysis::HEvent* Event, string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector< Analysis::HFile* > GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter* TreeWriter);

    void CloseFile();

    virtual inline string ClassName() const {

        return ("HAnalysisHeavyHiggsPgs");

    };

};


#endif

