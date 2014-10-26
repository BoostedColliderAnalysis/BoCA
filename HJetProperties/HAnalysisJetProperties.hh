# ifndef HAnalysisJetProperties_hh
# define HAnalysisJetProperties_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"

#include "HJetPropertiesBranch.hh"

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class HAnalysisJetProperties : public Analysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisJetProperties();

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *JetPropertiesBranch;

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

    int GetEventnumberMax()const{ return 10000;};

    inline string GetProjectName() const {
        return "Discriminator";
    };

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
    bool Analysis(Analysis::HEvent* Event, string StudyName);

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

    virtual inline string ClassName() const {

        return ("HAnalysisJetProperties");

    };

};


#endif

