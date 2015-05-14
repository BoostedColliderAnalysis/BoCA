# ifndef HAnalysisTau_hh
# define HAnalysisTau_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "Reader.hh"
# include "Factory.hh"
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

  using hanalysis::HAnalysis::HAnalysis;
    /**
     * @brief Constructor
     *
     */
//     HAnalysisTau();

    /**
     * @brief Constructor
     *
     */
//     ~HAnalysisTau();

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *Branch;

    hanalysis::HTauTagger TauTagger;
    hanalysis::HHeavyHiggsTauTagger HiggsTauTagger;
//     hanalysis::HWTagger w_hadronic_tagger;
//
//     hanalysis::HTopLeptonicTagger TopLeptonicTagger;
//     hanalysis::TopHadronicTagger top_hadronic_tagger;
//     hanalysis::HTopSemiTagger TopSemiTagger;
//
//     hanalysis::HHiggsTauSemiTagger HiggsTauSemiTagger;
//     hanalysis::HChargedJetPairTagger JetPairTagger;
//
//     hheavyhiggs::HChargedSemiTagger eventSemiTagger;

    std::vector< hanalysis::RootFile > Files(const hanalysis::HObject::Tag tag);

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

//     std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

//     void ResetBranch();

    void SetTrees();

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:
    hanalysis::HJetTag JetTag;

    hanalysis::Reader TauReader;
//     hanalysis::Reader JetPairReader;
    hanalysis::Reader HeavyHiggsTauReader;
//     hanalysis::Reader WHadronicReader;
//     hanalysis::Reader TopLeptonicReader;
//     hanalysis::Reader TopHadronicReader;
//     hanalysis::Reader TopSemiReader;
//     hanalysis::Reader HiggsTauSemiReader;
//     hanalysis::Reader eventSemiReader;

    inline int EventNumberMax() const {
//         return 100000;
//         return 10000;
        return 1000;
//         return 100;
//         return 500;
    };

//     void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

//     void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::Tag Tag);

    /**
     * @brief Main Analysis function
     *
     */
    int Analysis(hanalysis::Event &event, const hanalysis::Tagger::Stage stage, const Tag tag);

//     bool GetTauTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetTauReader(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetHeavyHiggsTauTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetHeavyHiggsTauReader(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetWTag(hanalysis::Event &event, const hanalysis::HObject::HTag Tag);
//     bool GetWReader(hanalysis::Event &event, const HTag Tag);
//     bool GetJetPairTag(hanalysis::Event &event, const hanalysis::HObject::HTag Tag);
//     bool GetJetPairReader(hanalysis::Event &event, const HTag Tag);
//     bool GetTopLeptonicTag(hanalysis::Event &event, hanalysis::HObject::HTag Tag);
//     bool GetTopLeptonicReader(hanalysis::Event &event, const HTag Tag);
//     bool GetTopHadronicTag(hanalysis::Event &event, const hanalysis::HObject::HTag Tag);
//     bool GetTopSemiTag(hanalysis::Event &event, hanalysis::HObject::HTag Tag);
//     bool GetTopHadronicReader(hanalysis::Event &event, const HTag Tag);
//     bool GetTopSemiReader(hanalysis::Event &event, const HTag Tag);
//     bool GetHiggsTauSemiTag(hanalysis::Event &event, const hanalysis::HObject::HTag Tag);
//     bool GetChargdHiggsSemiReader(hanalysis::Event &event, const HTag Tag);
//     bool GeteventSemiTag(hanalysis::Event &event, const HTag Tag);
//
//     bool GeteventSemiReader(hanalysis::Event &event, const HTag Tag);

};

#endif
