# ifndef HAnalysis_hh
# define HAnalysis_hh

# include "HAnalysisBase.hh"

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class HAnalysis : public HAnalysisBase
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysis();

private:

    /**
     * @brief Branch to write Heavy Higgs info into
     *
     */
    ExRootTreeBranch *HeavyHiggsBranch;

    /**
     * @brief Cutflow counter
     * 
     */
    int DeltaEtaCounter, BMassCounter, TMassCounter, EventCounter, JetCounter;
    
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
    void FillAnalysisVector();
    
    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewAnalysis();
    
    void CleanAnalysis();

    virtual TString ClassName() {
        return ("HAnalysis");
    };

};


#endif

