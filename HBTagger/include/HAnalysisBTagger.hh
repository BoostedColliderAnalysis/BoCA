# ifndef HAnalysisBTagger_hh
# define HAnalysisBTagger_hh

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchBTagger.hh"
# include "HDoublet.hh"

/**
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
// class hbtagger::HJetTag : public hanalysis::HJetTag
// {
//
// public:
//
//     int GetBranchId(const int ParticleId, int BranchId);
//
// //     const std::set<int> HeavyParticles {TopId, CpvHiggsId, HiggsId};
//     const std::set<int> HeavyParticles {BottomId};
//
// //     const std::set<int> IntermediateParticles {BottomId};
//
//     virtual inline std::string NameSpaceName() const {
//         return "hbtagger";
//     };
//
//     virtual inline std::string ClassName() const {
//         return "HJetTag";
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
class hbtagger::HAnalysis : public hanalysis::HAnalysis
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
    ExRootTreeBranch *BTaggerBranch;

//     ExRootTreeBranch *ConstituentBranch;


private:

    inline int EventNumberMax() const {
        return 10000;
    };

    inline std::string ProjectName() const {
        return "BTagger";
    };

    hanalysis::HJetTag JetTag;

    hanalysis::HDoublet *SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
//     HJets GetLeptonJets(hanalysis::HEvent *const Event);

//     template <typename T, typename U>
//     std::pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
//         return {l.first + r.first, l.second + r.second};
//     }

//     std::pair<float, float> GetPull(fastjet::PseudoJet &CandidateJet);

    /**
     * @brief Lepton event counter
     *
     */
//     int LeptonEventCounter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    bool Analysis(hanalysis::HEvent *const Event, const std::string& StudyName);

//     void FillCandidate(const HSuperStructure& JetPair, float*const InvMass, float*const DeltaR, float*const Pull1, float*const Pull2, float*const Vertex1, float*const Vertex2, float*const Mass1, float*const Mass2) const;

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const std::string &StudyName);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    inline HStrings GetStudyNames() const;

    virtual inline std::string NameSpaceName() const {
        return "hbtagger";
    };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    };

};

#endif


