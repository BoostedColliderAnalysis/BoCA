# ifndef HAnalysisHeavyHiggsDelphes_hh
# define HAnalysisHeavyHiggsDelphes_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include <algorithm>

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Class defining the Heavy Higgs Analysis
 *
 */
class hheavyhiggs::HAnalysisHeavyHiggsDelphes : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisHeavyHiggsDelphes();

private:

    inline int GetEventNumberMax() const { return 10000;};

    inline std::string GetProjectName() const {
        return "HeavyHiggs";
    };

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent* Event, const std::string &StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< hanalysis::HFile* > GetFiles(const std::string &StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter* TreeWriter);

    void CloseFile();

    HStrings GetStudyNameVector();

    void FillBranch(hanalysis::HEvent* Event, fastjet::PseudoJet FrontJet, fastjet::PseudoJet BackJet);

    float Leptons(hanalysis::HEvent* Event, fastjet::PseudoJet Jet);

//     bool JetIsBottom(const fastjet::PseudoJet &Jet);

    inline std::string ClassName() const {

        return "HeavyHiggs: HAnalysisDelphes";

    };

    bool Signal(hanalysis::HEvent* Event);
    bool Test(hanalysis::HEvent* Event);
    bool Background(hanalysis::HEvent* Event);

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

