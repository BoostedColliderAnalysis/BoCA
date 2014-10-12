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
class HAnalysisHeavyHiggsDelphes : public HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsDelphes();

private:

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

    vector<string> GetStudyNameVector();

    void FillBranch(PseudoJet, PseudoJet);

    float Leptons(PseudoJet);

//     bool JetIsBottom(const PseudoJet &Jet);

    string ClassName() const {

        return ("HAnalysisHeavyHiggsDelphes");

    };

    bool Signal();
    bool Test();
    bool Background();

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

