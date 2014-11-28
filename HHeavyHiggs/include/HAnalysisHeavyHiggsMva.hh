# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
// # include "HSubStructure.hh"
# include "HSuperStructure.hh"
// # include "HMvaBTagger.hh"
// # include "HMvaPairs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HBottomTagger.hh"
# include "HLeptonicTopTagger.hh"
# include "HHeavyHiggsTagger.hh"
# include "HPairPair.hh"



class HHeavyHiggsEvent
{

public:

    fastjet::PseudoJet Bottom;
    fastjet::PseudoJet AntiBottom;
    hanalysis::HPairPair HeavyHiggs;

    HHeavyHiggsEvent(const hanalysis::HPairPair &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
        HeavyHiggs = NewHeavyHiggs;
        Bottom = NewBottom;
        AntiBottom = NewAntiBottom;
    }

    float GetBdt() const {
        return (HeavyHiggs.GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt());
    }

    float GetDeltaRap() const {
        return (Bottom.rap() - AntiBottom.rap());
    }

    float GetDeltaPhi() const {
        return Bottom.delta_phi_to(AntiBottom);
    }

    float GetDeltaR() const {
        return Bottom.delta_R(AntiBottom);
    }

};


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
    ExRootTreeBranch *EventBranch;

    ExRootTreeBranch *HiggsBranch;

//     ExRootTreeBranch *ConstituentBranch;

    ExRootTreeBranch *BottomBranch;

    ExRootTreeBranch *TopBranch;

//     template<typename TMva>
//     void SetMva(TMva *NewMva) {
// 
//         Print(HNotification, "Set Mva", NewMva->GetTaggerName());
// 
//         Mva = NewMva;
//         TopReader = new hmva::HReader(Mva);
//         TopReader->AddVariable();
//         TopReader->BookMVA();
// 
//     }

    hdelphes::HBottomTagger *BottomTagger;
    hdelphes::HLeptonicTopTagger *LeptonicTopTagger;
    hdelphes::HHeavyHiggsTagger *HeavyHiggsTagger;

private:


//     std::string TaggerName;



    hmva::HMva *Mva;

    hmva::HReader *BottomReader;
    
    hmva::HReader *TopReader;
    
    hmva::HReader *HeavyHiggsReader;

    inline int GetEventNumberMax() const {
        return 10000;
    };

    inline std::string GetProjectName() const {
        return "HeavyHiggsMva";
    };

    hanalysis::HJetTag *JetTag;

//     hdelphes::HSubStructure *SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    HJets GetLeptonJets(hanalysis::HEvent *const Event);

//     template <typename T, typename U>
//     std::pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
//         return {l.first + r.first, l.second + r.second};
//     }

    std::pair<float, float> GetPull(fastjet::PseudoJet &CandidateJet);

    /**
     * @brief Lepton event counter
     *
     */
    int LeptonEventCounter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger);

    bool GetBottomTag(hanalysis::HEvent *const Event, const std::string &StudyName);
//     void FillBottomBranch(const fastjet::PseudoJet& Jet, HBottomBranch* BTagger);
//     float GetDeltaR(const fastjet::PseudoJet& Jet);
//     float GetBottomBdt(const fastjet::PseudoJet &Bottom);

    bool GetTopTag(hanalysis::HEvent *const Event, const std::string &StudyName);
//     void FillTopBranch(const hdelphes::HSuperStructure &Pair, HLeptonicTopBranch *TopTagger);
//     float GetTopBdt(const hdelphes::HSuperStructure &Top);

    bool GetHeavyHiggsTag(hanalysis::HEvent *const Event, const std::string &StudyName);
//     void FillHiggsBranch(const hdelphes::HSuperStructure &Pair, HHiggsBranch *PairTagger);
//     float GetHiggsBdt(const hdelphes::HSuperStructure &Higgs);


    bool GetSignalTag(hanalysis::HEvent *const Event, const std::string &StudyName);

    std::vector<HHeavyHiggsEvent> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    std::vector<hanalysis::HPairPair> GetHeavyHiggses(const HJets &Jets, const HJets &Leptons);

    std::vector<hanalysis::HPairPair> GetTops(const HJets &Jets, const HJets &Leptons);

//     void FillCandidate(const hdelphes::HSuperStructure &JetPair, float *const InvMass, float *const DeltaR, float *const Pull, float *const BTag) const;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
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


