# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"

# include "HEventLeptonicTagger.hh"
# include "HEventHadronicTagger.hh"
# include "HEventSemiTagger.hh"
# include "HJetPairTagger.hh"

// # include "HChargedSemiTagger.hh"




/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
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
    ExRootTreeBranch *BottomReaderBranch;
    ExRootTreeBranch *WBranch;
    ExRootTreeBranch *WReaderBranch;
    ExRootTreeBranch *WSemiBranch;
    ExRootTreeBranch *WSemiReaderBranch;

    ExRootTreeBranch *JetPairBranch;
    ExRootTreeBranch *JetPairReaderBranch;

    ExRootTreeBranch *TopLeptonicBranch;
    ExRootTreeBranch *TopLeptonicReaderBranch;
    ExRootTreeBranch *TopHadronicBranch;
    ExRootTreeBranch *TopSemiBranch;
    ExRootTreeBranch *TopSemiReaderBranch;
    ExRootTreeBranch *TopHadronicReaderBranch;

    ExRootTreeBranch *HeavyHiggsLeptonicBranch;
    ExRootTreeBranch *HeavyHiggsLeptonicReaderBranch;
    ExRootTreeBranch *HeavyHiggsHadronicBranch;
    ExRootTreeBranch *HeavyHiggsSemiBranch;
    ExRootTreeBranch *HeavyHiggsSemiReaderBranch;

    ExRootTreeBranch *EventLeptonicBranch;
    ExRootTreeBranch *EventHadronicBranch;
    ExRootTreeBranch *EventSemiBranch;
    ExRootTreeBranch *EventSemiReaderBranch;
    ExRootTreeBranch *EventLeptonicReaderBranch;

    ExRootTreeBranch *ChargedHiggsSemiBranch;

    hanalysis::HBottomTagger *BottomTagger;
    hanalysis::HWSemiTagger *WSemiTagger;
    hanalysis::HWTagger *WTagger;
    hanalysis::HJetPairTagger *JetPairTagger;

    hanalysis::HTopLeptonicTagger *TopLeptonicTagger;
    hanalysis::HTopHadronicTagger *TopHadronicTagger;
    hanalysis::HTopSemiTagger *TopSemiTagger;

    hanalysis::HHeavyHiggsLeptonicTagger *HeavyHiggsLeptonicTagger;
    hanalysis::HHeavyHiggsHadronicTagger *HeavyHiggsHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger *HeavyHiggsSemiTagger;

    hheavyhiggs::HEventLeptonicTagger *EventLeptonicTagger;
    hheavyhiggs::HEventHadronicTagger *EventHadronicTagger;
    hheavyhiggs::HEventSemiTagger *EventSemiTagger;

//     hanalysis::HReader *LeptonicReader;

    /**
     * @brief prepares the std::vector describing the input root files
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName) {
        Print(HError, "we dont want to end up her", StudyName);
        std::vector<hanalysis::HFile * > Files;
        return Files;
    }

    std::vector<hanalysis::HFile *> GetFiles(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string GetProjectName() const {
//         return "HeavyHiggsMva1000";
//         return "HeavyHiggsMva2000";
//         return "HeavyHiggsMva3000";
//         return "HeavyHiggsMva4000";
//         return "HeavyHiggsMva5000";
//         return "HeavyHiggsMva6000";
//         return "HeavyHiggsMva7000";
//         return "HeavyHiggsMva8000";
//         return "HeavyHiggsMva9000";
        return "HeavyHiggsMvaTest";
    }

    std::string GetStudyNames(const hanalysis::HAnalysis::HTagger Tagger) const;

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:
    hanalysis::HJetTag *JetTag;

    hanalysis::HReader *BottomReader;
    hanalysis::HReader *JetPairReader;
    hanalysis::HReader *WSemiReader;
    hanalysis::HReader *WReader;
    hanalysis::HReader *TopLeptonicReader;
    hanalysis::HReader *TopHadronicReader;
    hanalysis::HReader *TopSemiReader;
    hanalysis::HReader *HeavyHiggsSemiReader;
    hanalysis::HReader *HeavyHiggsLeptonicReader;
    hanalysis::HReader *EventSemiReader;
    hanalysis::HReader *EventLeptonicReader;
    hanalysis::HReader *ChargedHiggsSemiReader;

    HStrings JoinHStrings(const HStrings &Strings1, const HStrings &Strings2);

    std::vector<hanalysis::HFile *>  JoinFiles(const std::vector<hanalysis::HFile *> &Files1, const std::vector<hanalysis::HFile *> &Files2);

    inline int GetEventNumberMax() const {
//         return 100000;
        return 10000;
    };

    void NewBranches(ExRootTreeWriter *TreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
//     bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger);
    bool Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

//     std::vector< HHeavyHiggsEvent > GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    bool GetBottomTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetBottomReader(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetWSemiTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetWSemiReader(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetWTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetWReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetJetPairTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetJetPairReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetTopLeptonicTag(hanalysis::HEvent *const Event, hanalysis::HObject::HTag Tag);
    bool GetTopLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetTopHadronicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetTopSemiTag(hanalysis::HEvent *const Event, hanalysis::HObject::HTag Tag);
    bool GetTopHadronicReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetTopSemiReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetHeavyHiggsHadronicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetHeavyHiggsSemiTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsSemiReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetEventLeptonicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetEventHadronicTag(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetEventSemiTag(hanalysis::HEvent *const Event, const HTag Tag);

    bool GetEventSemiReader(hanalysis::HEvent *const Event, const HTag Tag);
    bool GetEventLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag);

};

#endif
