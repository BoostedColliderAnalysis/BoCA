# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "HReader.hh"
# include "HFactory.hh"
// # include "HBottomTagger.hh"
// # include "HWTagger.hh"

// # include "HTopLeptonTagger.hh"
// # include "HTopLeptonicTagger.hh"
// # include "HTopHadronicTagger.hh"

// # include "HHeavyHiggsLeptonicTagger.hh"
// # include "HHeavyHiggsMixedTagger.hh"

# include "HEventLeptonicTagger.hh"
# include "HEventHadronicTagger.hh"
# include "HEventSemiTagger.hh"




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

//     enum HTagger {
//       HBottomTagger,
//       HWTagger,
//       HTopHadronicTagger,
//       HTopSemiTagger,
//       HTopLeptonicTagger,
//       HHeavyHiggsHadronicTagger,
//       HHeavyHiggsLeptonicTagger,
//       HHeavyHiggsSemiTagger,
//       HEventLeptonicTagger,
//       HEventHadronicTagger,
//       HEventSemiTagger,
//     };

    /**
     * @brief Branch to write Higgs info into
     *
     */
//     ExRootTreeBranch *ConstituentBranch;
    ExRootTreeBranch *BottomBranch;
    ExRootTreeBranch *WBranch;

    ExRootTreeBranch *TopLeptonicBranch;
    ExRootTreeBranch *TopHadronicBranch;
    ExRootTreeBranch *TopSemiBranch;

    ExRootTreeBranch *HeavyHiggsLeptonicBranch;
    ExRootTreeBranch *HeavyHiggsHadronicBranch;
    ExRootTreeBranch *HeavyHiggsSemiBranch;

    ExRootTreeBranch *EventLeptonicBranch;
    ExRootTreeBranch *EventHadronicBranch;
    ExRootTreeBranch *EventSemiBranch;

    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWTagger *WTagger;

    hanalysis::HTopLeptonicTagger *TopLeptonicTagger;
    hanalysis::HTopHadronicTagger *TopHadronicTagger;
    hanalysis::HTopSemiTagger *TopSemiTagger;

    hanalysis::HHeavyHiggsLeptonicTagger *HeavyHiggsLeptonicTagger;
    hanalysis::HHeavyHiggsHadronicTagger *HeavyHiggsHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger *HeavyHiggsSemiTagger;

    hheavyhiggs::HEventLeptonicTagger *EventLeptonicTagger;
    hheavyhiggs::HEventHadronicTagger *EventHadronicTagger;
    hheavyhiggs::HEventSemiTagger *EventSemiTagger;

    /**
     * @brief prepares the std::vector describing the input root files
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName){Print(HError,"we dont want to end up her");}

    std::vector<hanalysis::HFile *> GetFiles(const hanalysis::HAnalysis::HTagger Tagger, const HState State);

    inline std::string GetProjectName() const {
        return "HeavyHiggsMva";
    };
    std::string GetStudyNames(const hanalysis::HAnalysis::HTagger Tagger) const;

private:

    inline int GetEventNumberMax() const {
        return 10000;
    };

    hanalysis::HJetTag *JetTag;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
//     bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger);
    bool Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const HState State);

//     std::vector< HHeavyHiggsEvent > GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    bool GetBottomTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    bool GetWTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetTopLeptonicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    bool GetTopHadronicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    bool GetTopSemiTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetHeavyHiggsHadronicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    bool GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);
    bool GetHeavyHiggsSemiTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    bool GetEventLeptonicTag(hanalysis::HEvent *const Event, const HState State);
    bool GetEventHadronicTag(hanalysis::HEvent *const Event, const HState State);
    bool GetEventSemiTag(hanalysis::HEvent *const Event, const HState State);

    void NewBranches(ExRootTreeWriter *TreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    virtual inline std::string NameSpaceName() const {
        return "HHeavyHiggs";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


