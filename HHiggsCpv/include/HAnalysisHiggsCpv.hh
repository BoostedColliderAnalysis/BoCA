# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHiggsCpv.hh"
# include "HSubStructure.hh"

/**
 * \class HDiscriminatorJetTag
 *
 * @brief HJetTag subclass for HDiscriminator
 *
 */
class hhiggscpv::HJetTag : public hanalysis::HJetTag
{

public:

    int GetBranchId(const int ParticleId, int BranchId);

    const set<int> HeavyParticles {TopId, CpvHiggsId, HiggsId};

    virtual inline string ClassName() const {

        return "HiggsCPV: HJetTag";

    };

};

/**
 * \class HAnalysisDiscriminator
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
    ExRootTreeBranch *CandidateBranch;


private:

    inline int GetEventNumberMax() const {

        return 10000;

    };

    inline string GetProjectName()const {

        return "HiggsCpv";

    };

    hhiggscpv::HJetTag *JetTag;

    hanalysis::HSubStructure *SubStructure;

    /**
     * @brief Lepton calculations
     *
     * @param Event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    vector<PseudoJet> GetLeptonJets(hanalysis::HEvent *const Event);

//     template <typename T, typename U>
//     std::pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
//         return {l.first + r.first, l.second + r.second};
//     }

    pair<float, float> GetPull(PseudoJet &CandidateJet);

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
    bool Analysis(hanalysis::HEvent *const Event, const string StudyName);

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    std::vector<hanalysis::HFile * > GetFiles(const string StudyName) const;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(ExRootTreeWriter *TreeWriter);

    inline vector<string> GetStudyNames() const;

    virtual inline string ClassName() const {

        return "HiggsCPV: HAnalysis";

    };

};

#endif


