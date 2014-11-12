# ifndef HAnalysisTopTagger_hh
# define HAnalysisTopTagger_hh

# include "HAnalysis.hh"
# include "HFileDelphes.hh"
# include "HEventDelphes.hh"
# include "HBranchTopTagger.hh"
# include "HSubStructure.hh"

/**
 * \class HDiscriminatorJetTag
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
class htoptagger::HJetTag : public hanalysis::HJetTag
{

    int GetBranchId(const int ParticleId, int BranchId);

    const std::set<int> HeavyParticles = {TopId, CpvHiggsId};

    virtual inline std::string ClassName() const {

        return "HDiscriminatorJetTag";

    };

};

/**
 * \class HAnalysisTopTagger
 *
 * @brief HAnalysis ubclass defining the Disciminator Analysis
 *
 * \author Jan Hajer
 *
 */
class htoptagger::HAnalysis : public hanalysis::HAnalysis
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

    inline int GetEventNumberMax() const {

        return 10000;

    };

    inline std::string GetProjectName()const {

        return "TopTagger";

    };

    HJetTag *JetTag;

    hdelphes::HSubStructure *SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    HJets GetLeptonJets(hanalysis::HEvent *const Event);

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
    bool Analysis(hanalysis::HEvent *const Event, const std::string& StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector< hanalysis::HFile * > GetFiles(const std::string& StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    inline std::vector<std::string> GetStudyNames() const;

    virtual inline std::string ClassName() const {

        return "htoptagger: HAnalysis";

    };

};


#endif

