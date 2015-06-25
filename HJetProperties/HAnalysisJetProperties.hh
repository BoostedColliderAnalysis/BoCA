# ifndef HAnalysisJetProperties_hh
# define HAnalysisJetProperties_hh

# include "Analysis.hh"
// # include "HEventDelphes.hh"
# include "File.hh"

# include "HJetPropertiesBranch.hh"
# include "SubStructure.hh"

# include "fastjet/tools/Pruner.hh"
# include "fastjet/tools/CASubJetTagger.hh"

class hjetproperties::JetTag : public analysis::JetTag
{

public:

    int GetBranchId(const int id, int BranchId);

    const std::set<analysis::Id> HeavyParticles = {analysis::Id::Top, analysis::Id::CpvHiggs, analysis::Id::Higgs};

     std::string ClassName() const {

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

     int GeteventnumberMax()const {
        return 10000;
    };

     std::string ProjectName()const {
        return "JetProperties";
    }

    /**
     * @brief Branch to write Lepton info into
     *
     */
    exroot::TreeBranch *LeptonBranch;

    /**
     * @brief Branch to write Higgs info into
     *
     */
    exroot::TreeBranch *eventBranch;

    /**
     * @brief Branch to write Higgs info into
     *
     */
    exroot::TreeBranch *particle_branch;
    exroot::TreeBranch *ParticleconstituentBranch;

    /**
     * @brief Branch to write Lepton info into
     *
     */
    exroot::TreeBranch *TrimmedBranch;
    exroot::TreeBranch *TrimmedconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    exroot::TreeBranch *AktFatJetBranch;
    exroot::TreeBranch *AktFatJetconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    exroot::TreeBranch *AktMassDropBranch;
    exroot::TreeBranch *AktMassDropconstituentBranch;

    exroot::TreeBranch *AktPrunerBranch;
    exroot::TreeBranch *AktPrunerconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    exroot::TreeBranch *CAFatJetBranch;
    exroot::TreeBranch *CAFatJetconstituentBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    exroot::TreeBranch *CAMassDropBranch;
    exroot::TreeBranch *CAMassDropconstituentBranch;

    exroot::TreeBranch *CAPrunerBranch;
    exroot::TreeBranch *CAPrunerconstituentBranch;

    exroot::TreeBranch *CASJTBranch;
    exroot::TreeBranch *CASJTconstituentBranch;


    /**
     * @brief Branch to write constituent info into
     *
     */
    exroot::TreeBranch *constituentBranch;

private:


    analysis::JetTag jet_tag;

    analysis::SubStructure sub_structure;


    bool FillTree(exroot::TreeBranch *const, exroot::TreeBranch *const, const fastjet::PseudoJet &Jet, const analysis::Jets &, const float DeltaR);

    bool FillTree(exroot::TreeBranch *const, exroot::TreeBranch *const, const fastjet::PseudoJet &Jet, const analysis::Jets &);

    float GetDeltaR(const fastjet::PseudoJet &Jet);

    /**
     * @brief Lepton calculations
     *
     * @param event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    analysis::Jets Leptons(analysis::Event &event);

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
    void NewBranches(exroot::TreeWriter *TreeWriter);

    void CloseFile();

     analysis::Strings GetStudyNames() const;

    virtual  std::string ClassName() const {

        return ("HAnalysisJetProperties");

    };

};


#endif

