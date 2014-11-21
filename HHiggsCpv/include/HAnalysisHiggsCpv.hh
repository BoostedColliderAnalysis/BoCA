# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "HSubStructure.hh"
# include "HSuperStructure.hh"
# include "HMvaBTagger.hh"
// # include "HMvaPairs.hh"
# include "HReader.hh"
# include "HFactory.hh"

/**
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
// class hhiggscpv::HBottomTag : public hanalysis::HJetTag
// {
//
// public:
//
//     const std::set<int> HeavyParticles {BottomId};
//
//     virtual inline std::string NameSpaceName() const {
//         return "HiggsCPV";
//     };
//
//     virtual inline std::string ClassName() const {
//         return "HBottomTag";
//     };
//
// };

/**
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
// class hhiggscpv::HPairTag : public hanalysis::HJetTag
// {
//
// public:
//
//     const std::set<int> HeavyParticles {TopId, CpvHiggsId, HiggsId};
//
//     virtual inline std::string NameSpaceName() const {
//         return "HiggsCPV";
//     };
//
//     virtual inline std::string ClassName() const {
//         return "HPairTag";
//     };
//
// };

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

    ExRootTreeBranch *PairBranch;

    ExRootTreeBranch *ConstituentBranch;

    ExRootTreeBranch *BTaggerBranch;

    template<typename TMva>
    void SetMva(TMva *NewMva) {

        Print(HNotification,"Set Mva",NewMva->TaggerName);

        Mva = NewMva;
        Reader = new hmva::HReader(Mva);
        Reader->AddVariable();
        Reader->BookMVA();

    }

private:

    std::string TaggerName;

    hmva::HMva *Mva;

    hmva::HReader *Reader;

    void FillBTagger(const fastjet::PseudoJet& Jet, hhiggscpv::HBTaggerBranch* BTagger);

    void FillPairTagger(const hdelphes::HSuperStructure& Pair, HPairBranch *PairTagger);

    inline int GetEventNumberMax() const {
        return 10000;
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
    bool Analysis(hanalysis::HEvent *const Event, const std::string& StudyName);

    bool GetEvent(hanalysis::HEvent*const Event, const std::string& StudyName);

    bool GetPair(hanalysis::HEvent*const Event, const std::string& StudyName);

    bool GetBTag(hanalysis::HEvent*const Event, const std::string& StudyName);

    void FillCandidate(const hdelphes::HSuperStructure &JetPair, float *const InvMass, float *const DeltaR, float *const Pull, float *const BTag) const;

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
    void NewBranches(ExRootTreeWriter *TreeWriter);

    inline std::vector<std::string> GetStudyNames(const std::string& NewTaggerName);

    virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


