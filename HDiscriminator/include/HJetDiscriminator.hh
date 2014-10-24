# ifndef HJetDiscriminator_hh
# define HJetDiscriminator_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"

# include "HBranchDiscriminator.hh"
# include "HSubStructure.hh"

# include "fastjet/tools/Pruner.hh"
# include "fastjet/tools/CASubJetTagger.hh"

using fastjet::antikt_algorithm;

class HDiscriminatorJetTag : public Analysis::HJetTag
{

    int GetBranchId(const int, int) const;

    const set<int> HeavyParticles = {TopId, CpvHiggsId};

    inline string ClassName() const {

        return ("HDiscriminatorJetTag");

    };


};

/**
 * @brief Class defining the Disciminator Analysis
 *
 * \class HDiscriminator
 *
 */
class HJetDiscriminator : public Analysis::HAnalysis
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

    inline int GetEventnumberMax()const {
        return 10000;
    };

    inline string GetProjectName()const {
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

    Analysis::HSubStructure *SubStructure;


    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const PseudoJet &Jet, const vector<PseudoJet> &, const float DeltaR);

    bool FillTree(ExRootTreeBranch *const, ExRootTreeBranch *const, const PseudoJet &Jet, const vector<PseudoJet> &);

    float GetDeltaR(const PseudoJet &Jet);

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    vector<PseudoJet> Leptons(Analysis::HEvent* Event);

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
    void NewBranches(ExRootTreeWriter *TreeWriter);

    void CloseFile();

    inline vector<string> GetStudyNames() const;

    virtual inline string ClassName() const {

        return ("HJetDiscriminator");

    };

};


#endif

