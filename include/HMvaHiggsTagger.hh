# ifndef HMvaHiggsTagger_hh
# define HMvaHiggsTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HSuperStructure.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hanalysis::HMvaHiggsTagger : public HMva
{

public:

    HMvaHiggsTagger(HBottomTagger *NewBottomTagger);

    ~HMvaHiggsTagger();

    std::vector< HHiggsBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    std::vector<HParticleBranch *> GetConstituentBranches();

    void FillBranch(const HSuperStructure &Pair);

private:

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HHiggsBranch *Branch;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHiggsBranch * const HiggsBranch, const HSuperStructure &Pair);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HMvaHiggsTagger";
    };

};

#endif
