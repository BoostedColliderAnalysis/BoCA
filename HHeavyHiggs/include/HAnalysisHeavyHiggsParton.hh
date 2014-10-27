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
class hheavyhiggs::HAnalysisHeavyHiggsParton : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsParton();

private:

    int GetEventnumberMax()const{ return 10000;};

    inline string GetProjectName()const{
        return "HeavyHiggsParton";
    }

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
    bool Analysis(hanalysis::HEvent* Event, string);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    vector<hanalysis::HFile* > GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter* TreeWriter);

    void CloseFile();

    virtual inline string ClassName() const {

        return ("HAnalysisHeavyHiggsParton");

    };

};


#endif

