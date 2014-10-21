# ifndef HAnalysisHeavyHiggsParton_hh
# define HAnalysisHeavyHiggsParton_hh

# include "HAnalysis.hh"
# include "HEventParton.hh"
# include "HBranchHeavyHiggs.hh"

using std::iter_swap;

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class HAnalysisHeavyHiggsParton : public HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsParton();

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
    bool Analysis(HEvent* Event, string);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    vector<HFile* > GetFiles();

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewFile(ExRootTreeWriter* TreeWriter);

    void CloseFile();

    virtual string ClassName() const {

        return ("HAnalysisHeavyHiggsParton");

    };

};


#endif

