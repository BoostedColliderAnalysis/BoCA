# ifndef HAnalysisCharged_hh
# define HAnalysisCharged_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"

# include "HChargedEventSemiTagger.hh"

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisCharged : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisCharged();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WHadronicTagger;

//     hanalysis::HTopLeptonicTagger TopLeptonicTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;

    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger JetPairTagger;

    hheavyhiggs::HChargedSignatureSemiTagger SignatureSemiTagger;
    hheavyhiggs::HChargedEventSemiTagger EventSemiTagger;

    std::vector< hanalysis::HFile > Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProjectName() const {
      // LHC
//         return "ChargedLHC400";
//         return "ChargedLHC500";
//         return "ChargedLHC1000";
//         return "ChargedLHC2000";
        return "ChargedLHC3000";
//         return "ChargedLHC4000";

        // 100 TeV
//         return "ChargedHiggs1";
//         return "ChargedHiggs2";
//         return "ChargedHiggs3";
//         return "ChargedHiggs4";
//         return "ChargedHiggs5";
//         return "ChargedHiggs6";
//         return "ChargedHiggs7";
//         return "ChargedHiggs8";
//         return "ChargedHiggs9";
//         return "ChargedHiggs10";
//         return "ChargedHiggs12";
//         return "ChargedHiggs15";
//         return "ChargedHiggs20";
//         return "ChargedHiggs25";
//         return "ChargedHiggsTest";
    }

    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    hanalysis::HJetTag JetTag;

    hanalysis::HReader BottomReader;
    hanalysis::HReader JetPairReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WHadronicReader;
    hanalysis::HReader TopLeptonicReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader ChargedHiggsSemiReader;
    hanalysis::HReader SignatureSemiReader;
    hanalysis::HReader EventSemiReader;

    inline int EventNumberMax() const {
        return 1000000;
//         return 100000;
//         return 10000;
//         return 1000;
//         return 100;
    };

    void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    /**
     * @brief Main Analysis function
     *
     */
    bool Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    bool GetBottomTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetBottomReader(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWSemiReader(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetJetPairTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetJetPairReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopLeptonicTag(hanalysis::HEvent &Event, hanalysis::HObject::HTag Tag);
    bool GetTopLeptonicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopHadronicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopSemiTag(hanalysis::HEvent &Event, hanalysis::HObject::HTag Tag);
    bool GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetChargedHiggsSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetChargdHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetSignatureSemiTag(hanalysis::HEvent &Event, const HTag Tag);
    bool GetSignatureSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag);

};

#endif
