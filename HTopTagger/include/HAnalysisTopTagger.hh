# ifndef HAnalysisTopTagger_hh
# define HAnalysisTopTagger_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchTopTagger.hh"
# include "HSubStructure.hh"

/**
 * \class HDiscriminatorJetTag
 *
 * \ingroup HDiscriminator
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
class HDiscriminatorJetTag : public Analysis::HJetTag
{

    int GetBranchId(const int ParticleId, int BranchId) const;

    const set<int> HeavyParticles = {TopId, CpvHiggsId};

    virtual inline string ClassName() const {

        return "HDiscriminatorJetTag";

    };

};

/**
 * \class HAnalysisTopTagger
 *
 * \ingroup HDiscriminator
 *
 * @brief HAnalysis ubclass defining the Disciminator Analysis
 *
 * \author Jan Hajer
 *
 */
class HAnalysisTopTagger : public Analysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisTopTagger();

    /**
     * @brief Constructor
     *
     */
    ~HAnalysisTopTagger();

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

    inline string GetProjectName()const {

        return "TopTagger";

    };

    HDiscriminatorJetTag *DiscriminatorJetTag;

    Analysis::HSubStructure *SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    vector<PseudoJet> GetLeptonJets(Analysis::HEvent *const Event);

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
    bool Analysis(Analysis::HEvent *const Event, const string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector< Analysis::HFile * > GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    inline vector<string> GetStudyNames() const;

    virtual inline string ClassName() const {

        return "HAnalysisTopTagger";

    };

};


#endif

