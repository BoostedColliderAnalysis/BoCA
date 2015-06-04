# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "File.hh"
# include "Analysis.hh"
// # include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "SubStructure.hh"
# include "Doublet.hh"
// # include "HMvaPairs.hh"
# include "Reader.hh"
# include "Factory.hh"
# include "BottomTagger.hh"
# include "TopLeptonicTagger.hh"
// # include "HMvaHiggsTagger.hh"



class HHiggsCpv
{

public:

  analysis::Doublet Higgs;
    analysis::Doublet Top;
    analysis::Doublet AntiTop;

    HHiggsCpv(const analysis::Doublet &NewHiggs, const analysis::Doublet &NewTop, const analysis::Doublet &NewAntiTop) {
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
class hhiggscpv::HAnalysis : public analysis::Analysis
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

    analysis::BottomTagger bottom_tagger_;
    analysis::TopLeptonicTagger LeptonicTopTagger;
//     analysis::HMvaHiggsTagger HiggsTagger;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<analysis::File * > GetFiles(const std::string &StudyName);

private:

    /**
     * @brief Branch to write Higgs info into
     *
     */

    exroot::TreeBranch *bottom_branch;
    exroot::TreeBranch *HiggsBranch;
    exroot::TreeBranch *constituentBranch;
    exroot::TreeBranch *TopBranch;
    exroot::TreeBranch *eventBranch;

    analysis::Reader BottomReader;
    analysis::Reader TopReader;
    analysis::Reader HiggsReader;

    inline int EventNumberMax() const {
        return 100000;
    }

    inline std::string ProjectName() const {
        return "HiggsCpv";
    }

    analysis::JetTag jet_tag;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int Analysis(analysis::Event &event, const std::string &NewStudyName);

    bool GetBottomTag(analysis::Event &, const std::string &StudyName);

    bool GetTopTag(analysis::Event &event, const std::string &NewStudyName);

    bool GetHiggsTag(analysis::Event &event, const std::string &NewStudyName);

    bool GetSignalTag(analysis::Event &event, const std::string &StudyName);

    std::vector<HHiggsCpv> GetHiggsCpvs(const analysis::Jets &jets, const analysis::Jets &Leptons);

    /**
     * @brief New Analysis
     *
     * @return void
     */
//     void NewBranches(exroot::TreeWriter *TreeWriter, const HTagger Tagger);

inline analysis::Strings GetStudyNames();

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


