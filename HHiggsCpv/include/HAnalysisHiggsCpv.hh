# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "File.hh"
# include "HAnalysis.hh"
// # include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "HSubStructure.hh"
# include "Doublet.hh"
// # include "HMvaPairs.hh"
# include "Reader.hh"
# include "Factory.hh"
# include "BottomTagger.hh"
# include "HTopLeptonicTagger.hh"
# include "HMvaHiggsTagger.hh"



class HHiggsCpv
{

public:

  hanalysis::Doublet Higgs;
    hanalysis::Doublet Top;
    hanalysis::Doublet AntiTop;

    HHiggsCpv(const hanalysis::Doublet &NewHiggs, const hanalysis::Doublet &NewTop, const hanalysis::Doublet &NewAntiTop) {
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

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HTopLeptonicTagger LeptonicTopTagger;
    hanalysis::HMvaHiggsTagger HiggsTagger;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::File * > GetFiles(const std::string &StudyName);

private:

    /**
     * @brief Branch to write Higgs info into
     *
     */

    ExRootTreeBranch *bottom_branch;
    ExRootTreeBranch *HiggsBranch;
    ExRootTreeBranch *constituentBranch;
    ExRootTreeBranch *TopBranch;
    ExRootTreeBranch *eventBranch;

    hanalysis::Reader BottomReader;
    hanalysis::Reader TopReader;
    hanalysis::Reader HiggsReader;

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
    int Analysis(hanalysis::Event &event, const std::string &NewStudyName);

    bool GetBottomTag(hanalysis::Event &, const std::string &StudyName);

    bool GetTopTag(hanalysis::Event &event, const std::string &NewStudyName);

    bool GetHiggsTag(hanalysis::Event &event, const std::string &NewStudyName);

    bool GetSignalTag(hanalysis::Event &event, const std::string &StudyName);

    std::vector<HHiggsCpv> GetHiggsCpvs(const Jets &jets, const Jets &Leptons);

    /**
     * @brief New Analysis
     *
     * @return void
     */
//     void NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger);

    inline Strings GetStudyNames();

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


