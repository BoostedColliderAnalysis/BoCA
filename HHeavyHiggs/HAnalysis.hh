# ifndef HAnalysis_hh
# define HAnalysis_hh

# include "HAnalysisBase.hh"
# include "HEventDelphes.hh"

using std::iter_swap;

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
     * @brief Branch to write Heavy Higgs info into
     *
     */
//     ExRootTreeBranch *UnCutBranch;

    /**
     * @brief Cutflow counter
     * 
     */
    int DeltaEtaCounter, BMassCounter, TMassCounter, EventCounter, JetCounter, Jet2Counter;
    
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

    virtual TString ClassName() {
        return ("HAnalysisHeavyHiggs");
    };

};


#endif

