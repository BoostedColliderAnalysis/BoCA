# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "HSubStructure.hh"
# include "HSuperStructure.hh"
// # include "HMvaBTagger.hh"
// # include "HMvaPairs.hh"
# include "HReader.hh"
# include "HFactory.hh"



class HHiggsCpv
{

public:

  hdelphes::HSuperStructure Higgs;
  hdelphes::HSuperStructure Top;
  hdelphes::HSuperStructure AntiTop;

  HHiggsCpv(const hdelphes::HSuperStructure &NewHiggs, const hdelphes::HSuperStructure &NewTop, const hdelphes::HSuperStructure &NewAntiTop) {
    Higgs = NewHiggs;
    Higgs.SetBTag(Higgs.GetJet1().user_info<hanalysis::HJetInfo>().GetBTag(), Higgs.GetJet1().user_info<hanalysis::HJetInfo>().GetBTag());
    Top = NewTop;
    Top.SetBTag(Top.GetJet1().user_info<hanalysis::HJetInfo>().GetBTag());
    AntiTop = NewAntiTop;
    AntiTop.SetBTag(AntiTop.GetJet1().user_info<hanalysis::HJetInfo>().GetBTag());
  };

  float GetBdt() const {
    return (Higgs.Tag * Top.Tag * AntiTop.Tag);
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

    /**
     * @brief Branch to write Higgs info into
     *
     */
    ExRootTreeBranch *EventBranch;

    ExRootTreeBranch *HiggsBranch;

//     ExRootTreeBranch *ConstituentBranch;

    ExRootTreeBranch *BottomBranch;

    ExRootTreeBranch *TopBranch;

    template<typename TMva>
    void SetMva(TMva *NewMva) {

        Print(HNotification,"Set Mva",NewMva->TaggerName);

        Mva = NewMva;
        Reader = new hmva::HReader(Mva);
        Reader->AddVariable();
        Reader->BookMVA();

    }
    

private:
    

//     std::string TaggerName;
    

    hmva::HMva *Mva;

    hmva::HReader *Reader;

    inline int GetEventNumberMax() const {
        return 100000;
    };

    inline std::string GetProjectName() const {
        return "HiggsCpv";
    };

    hanalysis::HJetTag *JetTag;

    hdelphes::HSubStructure *SubStructure;

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
    bool Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const hhiggscpv::HAnalysis::HTagger Tagger);

    bool GetBottomTag(hanalysis::HEvent*const Event, const std::string& StudyName);
    void FillBottomBranch(const fastjet::PseudoJet& Jet, hhiggscpv::HBottomBranch* BTagger);
    float GetDeltaR(const fastjet::PseudoJet& Jet);
    float GetBottomBdt(const fastjet::PseudoJet &Bottom);

    bool GetTopTag(hanalysis::HEvent*const Event, const std::string& StudyName);
    void FillTopBranch(const hdelphes::HSuperStructure &Pair, hhiggscpv::HTopBranch *TopTagger);
    float GetTopBdt(const hdelphes::HSuperStructure &Top);

    bool GetHiggsTag(hanalysis::HEvent*const Event, const std::string& StudyName);
    void FillHiggsBranch(const hdelphes::HSuperStructure &Pair, hhiggscpv::HHiggsBranch *PairTagger);
    float GetHiggsBdt(const hdelphes::HSuperStructure &Higgs);


    bool GetSignalTag(hanalysis::HEvent*const Event, const std::string& StudyName);

    std::vector<HHiggsCpv> GetHiggsCpvs(const HJets &Jets, const HJets &Leptons);

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
    void NewBranches(ExRootTreeWriter *TreeWriter,const HTagger Tagger);

    inline HStrings GetStudyNames(const hhiggscpv::HAnalysis::HTagger NewTagger);

    virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


