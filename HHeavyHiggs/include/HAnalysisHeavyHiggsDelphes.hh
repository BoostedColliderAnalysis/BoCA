# ifndef HAnalysisHeavyHiggsDelphes_hh
# define HAnalysisHeavyHiggsDelphes_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include <algorithm>

# include "HBranchHeavyHiggs.hh"

using std::iter_swap;
using std::remove_if;

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class HAnalysisHeavyHiggsDelphes : public Analysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsDelphes();

private:

    inline int GetEventNumberMax() const { return 10000;};

    inline string GetProjectName() const {
        return "HeavyHiggs";
    };

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(Analysis::HEvent* Event, const string StudyName);

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

    vector<string> GetStudyNameVector();

    void FillBranch(Analysis::HEvent* Event, PseudoJet FrontJet, PseudoJet BackJet);

    float Leptons(Analysis::HEvent* Event, PseudoJet Jet);

//     bool JetIsBottom(const PseudoJet &Jet);

    inline string ClassName() const {

        return ("HAnalysisHeavyHiggsDelphes");

    };

    bool Signal(Analysis::HEvent* Event);
    bool Test(Analysis::HEvent* Event);
    bool Background(Analysis::HEvent* Event);

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

};


#endif

