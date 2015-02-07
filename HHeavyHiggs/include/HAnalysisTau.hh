# ifndef HAnalysisTau_hh
# define HAnalysisTau_hh

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

// # include "HChargedSemiTagger.hh"
# include "HChargedJetPairTagger.hh"
# include "HTauTagger.hh"
# include "HHeavyHiggsTauTagger.hh"




/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisTau : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisTau();

    /**
     * @brief Constructor
     *
     */
    ~HAnalysisTau();

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *Branch;

    hanalysis::HTauTagger TauTagger;
    hanalysis::HHeavyHiggsTauTagger HiggsTauTagger;
//     hanalysis::HWTagger WHadronicTagger;
//
//     hanalysis::HTopLeptonicTagger TopLeptonicTagger;
//     hanalysis::HTopHadronicTagger TopHadronicTagger;
//     hanalysis::HTopSemiTagger TopSemiTagger;
//
//     hanalysis::HHiggsTauSemiTagger HiggsTauSemiTagger;
//     hanalysis::HChargedJetPairTagger JetPairTagger;
//
//     hheavyhiggs::HChargedSemiTagger EventSemiTagger;

    std::vector< hanalysis::HFile > Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProjectName() const {
//         return "HiggsTau1";
//         return "HiggsTau2";
//         return "HiggsTau3";
//         return "HiggsTau4";
//         return "HiggsTau5";
//         return "HiggsTau6";
//         return "HiggsTau7";
//         return "HiggsTau8";
//         return "HiggsTau9";
//         return "HiggsTau10";
//         return "HiggsTau12";
//         return "HiggsTau15";
        return "HiggsTauTest";
    }

    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void ResetBranch();

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

    hanalysis::HReader TauReader;
//     hanalysis::HReader JetPairReader;
    hanalysis::HReader HeavyHiggsTauReader;
//     hanalysis::HReader WHadronicReader;
//     hanalysis::HReader TopLeptonicReader;
//     hanalysis::HReader TopHadronicReader;
//     hanalysis::HReader TopSemiReader;
//     hanalysis::HReader HiggsTauSemiReader;
//     hanalysis::HReader EventSemiReader;

    inline int EventNumberMax() const {
//         return 100000;
//         return 10000;
        return 1000;
//         return 100;
//         return 500;
    };

    void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    /**
     * @brief Main Analysis function
     *
     */
    bool Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    bool GetTauTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetTauReader(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsTauTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsTauReader(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
//     bool GetWTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
//     bool GetWReader(hanalysis::HEvent *const Event, const HTag Tag);
//     bool GetJetPairTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
//     bool GetJetPairReader(hanalysis::HEvent *const Event, const HTag Tag);
//     bool GetTopLeptonicTag(hanalysis::HEvent *const Event, hanalysis::HObject::HTag Tag);
//     bool GetTopLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag);
//     bool GetTopHadronicTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
//     bool GetTopSemiTag(hanalysis::HEvent *const Event, hanalysis::HObject::HTag Tag);
//     bool GetTopHadronicReader(hanalysis::HEvent *const Event, const HTag Tag);
//     bool GetTopSemiReader(hanalysis::HEvent *const Event, const HTag Tag);
//     bool GetHiggsTauSemiTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);
//     bool GetChargdHiggsSemiReader(hanalysis::HEvent *const Event, const HTag Tag);
//     bool GetEventSemiTag(hanalysis::HEvent *const Event, const HTag Tag);
//
//     bool GetEventSemiReader(hanalysis::HEvent *const Event, const HTag Tag);

};

#endif
