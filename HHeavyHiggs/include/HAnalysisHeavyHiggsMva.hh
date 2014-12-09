# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HBottomTagger.hh"
# include "HHadronicWTagger.hh"
# include "HLeptonicTopTagger.hh"
# include "HHeavyHiggsLeptonicTagger.hh"
# include "HEventTagger.hh"




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
//     ExRootTreeBranch *ConstituentBranch;
    ExRootTreeBranch *EventBranch;
    ExRootTreeBranch *HeavyHiggsBranch;
    ExRootTreeBranch *TopBranch;
    ExRootTreeBranch *HadronicWBranch;
    ExRootTreeBranch *BottomBranch;
    
    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HHadronicWTagger *HadronicWTagger;
    hanalysis::HLeptonicTopTagger *LeptonicTopTagger;
    hanalysis::HHeavyHiggsLeptonicTagger *HeavyHiggsTagger;
    hheavyhiggs::HEventTagger *HeavyHiggsEventTagger;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName);

    std::vector<hanalysis::HFile *> GetFiles(const HTagger Tagger, const HState State);


    inline std::string GetProjectName() const {
        return "HeavyHiggsMva";
    };
private:

    hanalysis::HMva *Mva;
    hanalysis::HReader *BottomReader;
    hanalysis::HReader *TopReader;
    hanalysis::HReader *HeavyHiggsReader;

    inline int GetEventNumberMax() const {
        return 100000;
    };

    hanalysis::HJetTag *JetTag;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger);

    bool Analysis(hanalysis::HEvent *const Event, const HTagger Tagger, const HState State);

    bool GetBottomTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    
    bool GetWTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetTopTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetHeavyHiggsTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetSignalTag(hanalysis::HEvent *const Event, const HState State);

    std::vector< HHeavyHiggsEvent > GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

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


