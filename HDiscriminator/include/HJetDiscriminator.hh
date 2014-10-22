# ifndef HJetDiscriminator_hh
# define HJetDiscriminator_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"

# include "HBranchDiscriminator.hh"
# include "HSubStructure.hh"

# include "fastjet/tools/Pruner.hh"
# include "fastjet/tools/CASubJetTagger.hh"

class HDiscriminatorJetTag : public HJetTag
{

    int GetBranchId(const int, int) const;

    const set<int> HeavyParticles = {TopId, CpvHiggsId};

    const set<int> RadiationParticles = {GluonId, UpId, DownId, StrangeId, CharmId, BottomId, UpDown0Id, UpDown1Id, UpUp1Id, DownDown1Id};

    const set<int> ChargeParticle = {UpId, DownId, StrangeId, CharmId, BottomId, TopId, PionId, RhoMesonId, ElectronId, MuonId, TauLeptonId, BMesonId, KMesonId, BMesonId, BMesonSId, ProtonId, DeltaBaryonId, KMesonSId, WId, DeltaBaryon2Id, DMesonId, DMesonS2Id, DMesonSId};

    const set<int> NeutralParticle = {DMeson0Id, KMeson0Id, KMeson0SId, NeutronId, BMeson0Id, BMeson0SId, DMesonS0Id, BMesonS0Id, BMesonSS0Id};

    string ClassName() const {

        return ("HDiscriminatorJetTag");

    };


};

/**
 * @brief Class defining the Disciminator Analysis
 *
 * \class HDiscriminator
 *
 */
class HJetDiscriminator : public HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetDiscriminator();

    /**
     * @brief Constructor
     *
     */
    ~HJetDiscriminator();
    
    int GetEventnumberMax()const{ return 10000;};

    string GetProjectName()const {
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


    HDiscriminatorJetTag *DiscriminatorJetTag;

    HSubStructure *SubStructure;


    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const PseudoJet &Jet, const vector<PseudoJet> &, const float DeltaR);

    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const PseudoJet &Jet, const vector<PseudoJet> &);

    float GetDeltaR(const PseudoJet &Jet);

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    vector<PseudoJet> Leptons(HEvent *Event);

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
//     vector<PseudoJet> Leptons();

    HDiscriminatorJetTag *HDiscriminatorTag;

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
    bool Analysis(HEvent *Event, string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector< HFile*> GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    vector<string> GetStudyNames() const;

    virtual string ClassName() const {

        return ("HJetDiscriminator");

    };

};


#endif

