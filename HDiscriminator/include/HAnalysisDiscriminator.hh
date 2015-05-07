# ifndef __HAnalysisDiscriminator_hh__
# define __HAnalysisDiscriminator_hh__

# include "HAnalysis.hh"
# include "HFileDelphes.hh"
# include "HEventDelphes.hh"
# include "HBranchDiscriminator.hh"
# include "HSubStructure.hh"

/**
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

    inline int EventNumberMax() const {

        return 10000;

    };

    inline std::string ProjectName()const {

        return "Discriminator";

    };

    hanalysis::HJetTag  JetTag;

    hanalysis::HSubStructure * SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    HJets GetLeptonJets(hanalysis::HEvent &Event);

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
    int Analysis(hanalysis::HEvent &Event, const std::string &Study);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::RootFile * > GetFiles(const std::string &Name);

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


