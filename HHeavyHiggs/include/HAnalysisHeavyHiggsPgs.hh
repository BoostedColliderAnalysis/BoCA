# ifndef HAnalysisHeavyHiggsPgs_hh
# define HAnalysisHeavyHiggsPgs_hh

# include "HAnalysis.hh"

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class hheavyhiggs::HAnalysisHeavyHiggsPgs : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsPgs();

private:


    inline int GetEventnumberMax()const{ return 10000;};

    inline std::string GetProjectName()const{ return "HeavyHiggsPgs";};

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
        EventCounter,
        JetCounter,
        Jet2Counter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent* Event,const std::string& StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< hanalysis::HFile* > GetFiles(const std::string& StudyName) const;

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

