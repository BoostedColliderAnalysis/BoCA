# ifndef HAnalysisHeavyHiggsDelphes_hh
# define HAnalysisHeavyHiggsDelphes_hh

# include "Analysis.hh"
// # include "HEventDelphes.hh"
# include <algorithm>

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class hheavyhiggs::HAnalysisHeavyHiggsDelphes : public analysis::Analysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsDelphes();

private:

    inline int EventNumberMax() const { return 10000;};

    inline std::string ProjectName() const {
        return "HeavyHiggs";
    };

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int Analysis(analysis::Event &event, const std::string &Name);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< analysis::File* > GetFiles(const std::string &Study);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *NewTreeWriter);

    void CloseFile();

    Strings GetStudyNameVector();

    void FillBranch(analysis::Event &event, fastjet::PseudoJet FrontJet, fastjet::PseudoJet BackJet);

    float Leptons(analysis::Event &event, fastjet::PseudoJet Jet);

//     bool JetIsBottom(const fastjet::PseudoJet &Jet);

    inline std::string ClassName() const {

        return "HeavyHiggs: HAnalysisDelphes";

    };

    bool Signal(analysis::Event &event);
    bool Test(analysis::Event &event);
    bool Background(analysis::Event &event);

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

};


#endif

