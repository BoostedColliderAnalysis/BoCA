# ifndef __HAnalysisDiscriminator_hh__
# define __HAnalysisDiscriminator_hh__

# include "Analysis.hh"
# include "File.hh"
// # include "HEventDelphes.hh"
# include "HBranchDiscriminator.hh"
# include "HSubStructure.hh"

/**
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
class hcpvhiggs::HJetTag : public analysis::HJetTag
{

public:

    int GetBranchId(const int ParticleId, int BranchId);

    const std::set<int> HeavyParticles {TopId, CpvHiggsId, HiggsId};

    virtual inline std::string ClassName() const {

        return "HiggsCPV: HJetTag";

    };

};

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class hcpvhiggs::HAnalysis : public analysis::Analysis
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
     * @brief Branch to write constituent info into
     *
     */
    ExRootTreeBranch *constituentBranch;

private:

    inline int EventNumberMax() const {

        return 10000;

    };

    inline std::string ProjectName()const {

        return "Discriminator";

    };

    analysis::HJetTag  JetTag;

    analysis::HSubStructure * SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    Jets GetLeptonJets(analysis::Event &event);

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
    int RunAnalysis(analysis::Event &event, const std::string &Study);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<analysis::File * > GetFiles(const std::string &Name);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *NewTreeWriter);

    inline Strings GetStudyNames() const;

    virtual inline std::string ClassName() const {

        return "HiggsCPV: HAnalysis";

    };

};

#endif


