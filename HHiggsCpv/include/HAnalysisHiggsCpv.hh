# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "HSubStructure.hh"
# include "HSuperStructure.hh"
# include "HJetLeptonPair.hh"
// # include "HMvaPairs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HBottomTagger.hh"
# include "HLeptonicTopTagger.hh"
# include "HMvaHiggsTagger.hh"



class HHiggsCpv
{

public:

    hdelphes::HSuperStructure Higgs;
    hanalysis::HJetLeptonPair Top;
    hanalysis::HJetLeptonPair AntiTop;

    HHiggsCpv(const hdelphes::HSuperStructure &NewHiggs, const hanalysis::HJetLeptonPair &NewTop, const hanalysis::HJetLeptonPair &NewAntiTop) {
        Higgs = NewHiggs;
        Top = NewTop;
        AntiTop = NewAntiTop;
    };

    float GetBdt() const {
        return (Higgs.GetBdt() * Top.GetBdt() * AntiTop.GetBdt());
    }

    float GetTopDeltaRap() const {
        return (Top.GetJet().rap() - AntiTop.GetJet().rap());
    }

    float GetTopDeltaPhi() const {
        return (Top.GetJet().delta_phi_to(AntiTop.GetJet()));
    }

    float GetTopDeltaR() const {
        return (Top.GetJet().delta_R(AntiTop.GetJet()));
    }

};


/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class hhiggscpv::HAnalysis : public hanalysis::HAnalysis
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

    hdelphes::HBottomTagger *BottomTagger;
    hdelphes::HLeptonicTopTagger *LeptonicTopTagger;
    hdelphes::HMvaHiggsTagger *HiggsTagger;

private:

    /**
     * @brief Branch to write Higgs info into
     *
     */

    ExRootTreeBranch *BottomBranch;
    ExRootTreeBranch *HiggsBranch;
    ExRootTreeBranch *ConstituentBranch;
    ExRootTreeBranch *TopBranch;
    ExRootTreeBranch *EventBranch;

    hmva::HReader *BottomReader;
    hmva::HReader *TopReader;
    hmva::HReader *HiggsReader;

    inline int GetEventNumberMax() const {
        return 100000;
    }

    inline std::string GetProjectName() const {
        return "HiggsCpv";
    }

    hanalysis::HJetTag *JetTag;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const hhiggscpv::HAnalysis::HTagger Tagger);

    bool GetBottomTag(hanalysis::HEvent *const Event, const std::string &StudyName);

    bool GetTopTag(hanalysis::HEvent *const Event, const std::string &StudyName);

    bool GetHiggsTag(hanalysis::HEvent *const Event, const std::string &StudyName);

    bool GetSignalTag(hanalysis::HEvent *const Event, const std::string &StudyName);

    std::vector<HHiggsCpv> GetHiggsCpvs(const HJets &Jets, const HJets &Leptons);
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
    void NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger);

    inline HStrings GetStudyNames(const hhiggscpv::HAnalysis::HTagger NewTagger);

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


