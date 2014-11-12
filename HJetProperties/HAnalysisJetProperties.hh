# ifndef HAnalysisJetProperties_hh
# define HAnalysisJetProperties_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HFileDelphes.hh"

# include "HJetPropertiesBranch.hh"
# include "HSubStructure.hh"

# include "fastjet/tools/Pruner.hh"
# include "fastjet/tools/CASubJetTagger.hh"

class hjetproperties::HJetTag : public hanalysis::HJetTag
{

public:

    int GetBranchId(const int ParticleId, int BranchId);

    const std::set<int> HeavyParticles = {TopId, CpvHiggsId, HiggsId};

    inline std::string ClassName() const {

        return "HiggsCPV: JetTag";

    };

};

/**
 * @brief Class defining the Disciminator Analysis
 *
 */
class hjetproperties::HAnalysis : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysis();

    /**
     * @brief Constructor
     *
     */
    ~HAnalysis();

    inline int GetEventnumberMax()const {
        return 10000;
    };

    inline std::string GetProjectName()const {
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
    ExRootTreeBranch *EventBranch;

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *ParticleBranch;
    ExRootTreeBranch *ParticleConstituentBranch;

    /**
     * @brief Branch to write Lepton info into
     *
     */
    ExRootTreeBranch *TrimmedBranch;
    ExRootTreeBranch *TrimmedConstituentBranch;

    /**
     * @brief Branch to write Constituent info into
     *
     */
    ExRootTreeBranch *AktFatJetBranch;
    ExRootTreeBranch *AktFatJetConstituentBranch;

    /**
     * @brief Branch to write Constituent info into
     *
     */
    ExRootTreeBranch *AktMassDropBranch;
    ExRootTreeBranch *AktMassDropConstituentBranch;

    ExRootTreeBranch *AktPrunerBranch;
    ExRootTreeBranch *AktPrunerConstituentBranch;

    /**
     * @brief Branch to write Constituent info into
     *
     */
    ExRootTreeBranch *CAFatJetBranch;
    ExRootTreeBranch *CAFatJetConstituentBranch;

    /**
     * @brief Branch to write Constituent info into
     *
     */
    ExRootTreeBranch *CAMassDropBranch;
    ExRootTreeBranch *CAMassDropConstituentBranch;

    ExRootTreeBranch *CAPrunerBranch;
    ExRootTreeBranch *CAPrunerConstituentBranch;

    ExRootTreeBranch *CASJTBranch;
    ExRootTreeBranch *CASJTConstituentBranch;


    /**
     * @brief Branch to write Constituent info into
     *
     */
    ExRootTreeBranch *ConstituentBranch;

private:


    hanalysis::HJetTag *JetTag;

    hdelphes::HSubStructure *SubStructure;


    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const PseudoJet &Jet, const HJets &, const float DeltaR);

    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const PseudoJet &Jet, const HJets &);

    float GetDeltaR(const PseudoJet &Jet);

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    HJets Leptons(hanalysis::HEvent* Event);

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    //     HJets Leptons();

    //     JetTag *HJetTag;

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
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    inline std::vector<std::string> GetStudyNames() const;

    virtual inline std::string ClassName() const {

        return ("HAnalysisJetProperties");

    };

};


#endif

