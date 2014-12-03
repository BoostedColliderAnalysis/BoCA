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

    HMvaHiggsTagger(hanalysis::HBottomTagger *const NewBottomTagger);

    ~HMvaHiggsTagger();

    std::vector< HHiggsBranch * > GetBranches(HEvent *const Event, const HObject::HState State);

    std::vector<HParticleBranch *> GetConstituentBranches();

    void FillBranch(const HSuperStructure &Pair);

private:

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HHiggsBranch *Branch;

    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHiggsBranch * const HiggsBranch, const HSuperStructure &Pair);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    virtual inline std::string ClassName() const {
        return "HMvaHiggsTagger";
    };

};

#endif
