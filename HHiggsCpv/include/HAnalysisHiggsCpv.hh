# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "HSubStructure.hh"
# include "HDoublet.hh"
// # include "HMvaPairs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HBottomTagger.hh"
# include "HTopLeptonicTagger.hh"
# include "HMvaHiggsTagger.hh"



class HHiggsCpv
{

public:

  hanalysis::HDoublet Higgs;
    hanalysis::HDoublet Top;
    hanalysis::HDoublet AntiTop;

    HHiggsCpv(const hanalysis::HDoublet &NewHiggs, const hanalysis::HDoublet &NewTop, const hanalysis::HDoublet &NewAntiTop) {
        Higgs = NewHiggs;
        Top = NewTop;
        AntiTop = NewAntiTop;
    };

    float Bdt() const {
        return (Higgs.Bdt() * Top.Bdt() * AntiTop.Bdt());
    }

    float GetTopDeltaRap() const {
        return (Top.Singlet1().rap() - AntiTop.Singlet1().rap());
    }

    float GetTopDeltaPhi() const {
        return (Top.Singlet1().delta_phi_to(AntiTop.Singlet1()));
    }

    float GetTopDeltaR() const {
        return (Top.Singlet1().delta_R(AntiTop.Singlet1()));
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

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HTopLeptonicTagger LeptonicTopTagger;
    hanalysis::HMvaHiggsTagger HiggsTagger;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName);

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

    hanalysis::HReader BottomReader;
    hanalysis::HReader TopReader;
    hanalysis::HReader HiggsReader;

    inline int EventNumberMax() const {
        return 100000;
    }

    inline std::string ProjectName() const {
        return "HiggsCpv";
    }

    hanalysis::HJetTag JetTag;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int Analysis(hanalysis::HEvent &Event, const std::string &NewStudyName);

    bool GetBottomTag(hanalysis::HEvent &, const std::string &StudyName);

    bool GetTopTag(hanalysis::HEvent &Event, const std::string &NewStudyName);

    bool GetHiggsTag(hanalysis::HEvent &Event, const std::string &NewStudyName);

    bool GetSignalTag(hanalysis::HEvent &Event, const std::string &StudyName);

    std::vector<HHiggsCpv> GetHiggsCpvs(const HJets &Jets, const HJets &Leptons);

    /**
     * @brief New Analysis
     *
     * @return void
     */
//     void NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger);

    inline HStrings GetStudyNames();

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


