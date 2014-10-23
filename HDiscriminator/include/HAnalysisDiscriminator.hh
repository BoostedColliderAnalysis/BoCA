# ifndef HAnalysisDiscriminator_hh
# define HAnalysisDiscriminator_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchDiscriminator.hh"
# include "HSubStructure.hh"

/**
 * \class HDiscriminatorJetTag
 *
 * \ingroup HDiscriminator
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
class HDiscriminatorJetTag : public HJetTag
{

    int GetBranchId(const int ParticleId, int BranchId) const;

    const set<int> HeavyParticles = {TopId, CpvHiggsId};

    virtual string ClassName() const {

        return "HDiscriminatorJetTag";

    };

};

/**
 * \class HAnalysisDiscriminator
 *
 * \ingroup HDiscriminator
 *
 * @brief HAnalysis ubclass defining the Disciminator Analysis
 *
 * \author Jan Hajer
 *
 */
class HAnalysisDiscriminator : public HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisDiscriminator();

    /**
     * @brief Constructor
     *
     */
    ~HAnalysisDiscriminator();

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
    
    int GetEventNumberMax() const {
      
        return 10000;
        
    };

    string GetProjectName()const {
        
        return "Discriminator";
        
    };

    HDiscriminatorJetTag *DiscriminatorJetTag;

    HSubStructure *SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    vector<PseudoJet> GetLeptonJets(HEvent *const Event);

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
    bool Analysis(HEvent *const Event, const string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector< HFile * > GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    vector<string> GetStudyNames() const;

    virtual string ClassName() const {

        return ("HAnalysisDiscriminator");

    };

};


#endif

