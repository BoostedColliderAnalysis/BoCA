# ifndef HAnalysisJetProperties_hh
# define HAnalysisJetProperties_hh

# include "Analysis.hh"
// # include "HEventDelphes.hh"
# include "File.hh"

# include "HJetPropertiesBranch.hh"
# include "HSubStructure.hh"

# include "fastjet/tools/Pruner.hh"
# include "fastjet/tools/CASubJetTagger.hh"

class hjetproperties::JetTag : public analysis::JetTag
{

public:

    int GetBranchId(const int particle_id, int BranchId);

    const std::set<int> HeavyParticles = {TopId, CpvHiggsId, HiggsId};

    inline std::string ClassName() const {

        return "HiggsCPV: jet_tag";

    };

};

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class hjetproperties::HAnalysis : public analysis::Analysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysis();

    inline int GeteventnumberMax()const {
        return 10000;
    };

    inline std::string ProjectName()const {
        return "JetProperties";
    }

    /**
     * @brief Branch to write Lepton info into
     *
     */
    ExRootTreeBranch *LeptonBranch;

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *eventBranch;

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *particle_branch;
    ExRootTreeBranch *ParticleconstituentBranch;

    /**
     * @brief Branch to write Lepton info into
     *
     */
    ExRootTreeBranch *TrimmedBranch;
    ExRootTreeBranch *TrimmedconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *AktFatJetBranch;
    ExRootTreeBranch *AktFatJetconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *AktMassDropBranch;
    ExRootTreeBranch *AktMassDropconstituentBranch;

    ExRootTreeBranch *AktPrunerBranch;
    ExRootTreeBranch *AktPrunerconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *CAFatJetBranch;
    ExRootTreeBranch *CAFatJetconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *CAMassDropBranch;
    ExRootTreeBranch *CAMassDropconstituentBranch;

    ExRootTreeBranch *CAPrunerBranch;
    ExRootTreeBranch *CAPrunerconstituentBranch;

    ExRootTreeBranch *CASJTBranch;
    ExRootTreeBranch *CASJTconstituentBranch;


    /**
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *constituentBranch;

private:


    analysis::JetTag jet_tag;

    analysis::HSubStructure SubStructure;


    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const fastjet::PseudoJet &Jet, const Jets &, const float DeltaR);

    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const fastjet::PseudoJet &Jet, const Jets &);

    float GetDeltaR(const fastjet::PseudoJet &Jet);

    /**
     * @brief Lepton calculations
     *
     * @param event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    Jets Leptons(analysis::Event &event);

    /**
     * @brief Lepton calculations
     *
     * @param event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    //     Jets Leptons();

    //     jet_tag *JetTag;

    /**
     * @brief Lepton event counter
     *
     */
    int LeptoneventCounter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int Analysis(analysis::Event &event, const std::string &StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< analysis::File* > GetFiles(const std::string &StudyName);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    inline Strings GetStudyNames() const;

    virtual inline std::string ClassName() const {

        return ("HAnalysisJetProperties");

    };

};


#endif

