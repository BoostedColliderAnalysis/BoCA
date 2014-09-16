# ifndef HAnalysis_hh
# define HAnalysis_hh

# include "HAnalysisBase.hh"

/**
 * @brief Class defining the Disciminator Analysis
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

