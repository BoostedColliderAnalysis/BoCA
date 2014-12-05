# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
// # include "HSubStructure.hh"
# include "HSuperStructure.hh"
// # include "HMvaBTagger.hh"
// # include "HMvaPairs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HBottomTagger.hh"
# include "HLeptonicTopTagger.hh"
# include "HHeavyHiggsTagger.hh"
# include "HPairPair.hh"



class HHeavyHiggsEvent
{

public:

    fastjet::PseudoJet Bottom;
    fastjet::PseudoJet AntiBottom;
    hanalysis::HPairPair HeavyHiggs;

    HHeavyHiggsEvent(const hanalysis::HPairPair &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
        HeavyHiggs = NewHeavyHiggs;
        Bottom = NewBottom;
        AntiBottom = NewAntiBottom;
    }

    float GetBdt() const {
        return (HeavyHiggs.GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt());
    }

    float GetDeltaRap() const {
        return (Bottom.rap() - AntiBottom.rap());
    }

    float GetDeltaPhi() const {
        return Bottom.delta_phi_to(AntiBottom);
    }

    float GetDeltaR() const {
        return Bottom.delta_R(AntiBottom);
    }

};


/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisMva : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisMva();

    /**
     * @brief Constructor
     *
     */
    ~HAnalysisMva();

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *EventBranch;

    ExRootTreeBranch *HeavyHiggsBranch;

//     ExRootTreeBranch *ConstituentBranch;

    ExRootTreeBranch *BottomBranch;

    ExRootTreeBranch *TopBranch;

    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HLeptonicTopTagger *LeptonicTopTagger;
    hanalysis::HHeavyHiggsTagger *HeavyHiggsTagger;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName);
    
    std::vector<hanalysis::HFile *> GetFiles(const HTagger Tagger,const HState State);


    inline std::string GetProjectName() const {
        return "HeavyHiggsMva";
    };
private:


//     std::string TaggerName;



    hanalysis::HMva *Mva;

    hanalysis::HReader  *BottomReader;

    hanalysis::HReader  *TopReader;

    hanalysis::HReader  *HeavyHiggsReader;

    inline int GetEventNumberMax() const {
        return 1000;
    };

    hanalysis::HJetTag *JetTag;


    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger);
    
    bool Analysis(hanalysis::HEvent *const Event, const HTagger Tagger, const HState State);
    
    bool GetBottomTag(hanalysis::HEvent*const Event, const hanalysis::HObject::HState State);

    bool GetTopTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetHeavyHiggsTag(hanalysis::HEvent*const Event, const hanalysis::HObject::HState State);

//     bool GetSignalTag(hanalysis::HEvent *const Event, const std::string &StudyName);
    bool GetSignalTag(hanalysis::HEvent *const Event, const HState State);

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);
    

    void NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger);

    inline HStrings GetStudyNames(const HTagger NewTagger);

    virtual inline std::string NameSpaceName() const {
        return "HHeavyHiggs";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


