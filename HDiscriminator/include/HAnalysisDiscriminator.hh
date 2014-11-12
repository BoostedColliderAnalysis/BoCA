# ifndef HAnalysisDiscriminator_hh
# define HAnalysisDiscriminator_hh

# include "HAnalysis.hh"
# include "HFileDelphes.hh"
# include "HEventDelphes.hh"
# include "HBranchDiscriminator.hh"
# include "HSubStructure.hh"

/**
 * \class HDiscriminatorJetTag
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
class hcpvhiggs::HJetTag : public hanalysis::HJetTag
{

public:

    int GetBranchId(const int ParticleId, int BranchId);

    const std::set<int> HeavyParticles {TopId, CpvHiggsId, HiggsId};

    virtual inline std::string ClassName() const {

        return "HiggsCPV: HJetTag";

    };

};

/**
 * \class HAnalysisDiscriminator
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class hcpvhiggs::HAnalysis : public hanalysis::HAnalysis
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

        return "Discriminator";

    };

    hcpvhiggs::HJetTag * JetTag;

    hdelphes::HSubStructure * SubStructure;

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
    bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    inline std::vector<std::string> GetStudyNames() const;

    virtual inline std::string ClassName() const {

        return "HiggsCPV: HAnalysis";

    };

};

#endif


