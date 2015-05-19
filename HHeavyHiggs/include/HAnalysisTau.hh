# ifndef HAnalysisTau_hh
# define HAnalysisTau_hh

# include "File.hh"
# include "Analysis.hh"
// # include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "Reader.hh"
# include "Factory.hh"
# include "HJetTag.hh"

# include "HEventLeptonicTagger.hh"
# include "HEventHadronicTagger.hh"
# include "HEventSemiTagger.hh"

// # include "HChargedSemiTagger.hh"
# include "HChargedJetPairTagger.hh"
# include "TauTagger.hh"
# include "HHeavyHiggsTauTagger.hh"




/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisTau : public analysis::Analysis
{

public:

  using analysis::Analysis::Analysis;
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

    analysis::TauTagger tau_tagger;
    analysis::HHeavyHiggsTauTagger Higgstau_tagger;
//     analysis::HWTagger w_hadronic_tagger;
//
//     analysis::HTopLeptonicTagger TopLeptonicTagger;
//     analysis::TopHadronicTagger top_hadronic_tagger;
//     analysis::HTopSemiTagger top_semi_tagger;
//
//     analysis::HHiggsTauSemiTagger HiggsTauSemiTagger;
//     analysis::HChargedJetPairTagger JetPairTagger;
//
//     hheavyhiggs::HChargedSemiTagger eventSemiTagger;

    std::vector< analysis::File > Files(const analysis::Object::Tag tag);

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

//     std::string StudyName(const analysis::HAnalysis::HTagger Tagger) const;

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
    analysis::HJetTag JetTag;

    analysis::Reader TauReader;
//     analysis::Reader JetPairReader;
    analysis::Reader HeavyHiggsTauReader;
//     analysis::Reader WHadronicReader;
//     analysis::Reader TopLeptonicReader;
//     analysis::Reader TopHadronicReader;
//     analysis::Reader TopSemiReader;
//     analysis::Reader HiggsTauSemiReader;
//     analysis::Reader eventSemiReader;

    inline int EventNumberMax() const {
//         return 100000;
//         return 10000;
        return 1000;
//         return 100;
//         return 500;
    };

//     void NewBranches(ExRootTreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger);

//     void PrepareReader(const analysis::HAnalysis::HTagger Tagger, const analysis::Object::Tag Tag);

    /**
     * @brief Main Analysis function
     *
     */
    int RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag);

//     bool GetTauTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetTauReader(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetHeavyHiggsTauTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetHeavyHiggsTauReader(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWTag(analysis::Event &event, const analysis::Object::HTag Tag);
//     bool GetWReader(analysis::Event &event, const HTag Tag);
//     bool GetJetPairTag(analysis::Event &event, const analysis::Object::HTag Tag);
//     bool GetJetPairReader(analysis::Event &event, const HTag Tag);
//     bool GetTopLeptonicTag(analysis::Event &event, analysis::Object::HTag Tag);
//     bool GetTopLeptonicReader(analysis::Event &event, const HTag Tag);
//     bool GetTopHadronicTag(analysis::Event &event, const analysis::Object::HTag Tag);
//     bool GetTopSemiTag(analysis::Event &event, analysis::Object::HTag Tag);
//     bool GetTopHadronicReader(analysis::Event &event, const HTag Tag);
//     bool GetTopSemiReader(analysis::Event &event, const HTag Tag);
//     bool GetHiggsTauSemiTag(analysis::Event &event, const analysis::Object::HTag Tag);
//     bool GetChargdHiggsSemiReader(analysis::Event &event, const HTag Tag);
//     bool GeteventSemiTag(analysis::Event &event, const HTag Tag);
//
//     bool GeteventSemiReader(analysis::Event &event, const HTag Tag);

};

#endif
