# ifndef HMvaHiggsTagger_hh
# define HMvaHiggsTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hanalysis::HMvaHiggsTagger : public HMva
{

public:

    HMvaHiggsTagger();

    HMvaHiggsTagger(const hanalysis::HBottomTagger &NewBottomTagger);

    ~HMvaHiggsTagger();

    std::vector< HHiggsBranch * > GetBranches(HEvent *const Event, const HObject::HTag State);

    std::vector<HParticleBranch *> GetConstituentBranches();

    void FillBranch(const HDoublet &Pair);

private:

    HBottomTagger BottomTagger;

    HReader BottomReader;

    HHiggsBranch Branch;

    HJetTag JetTag;

    void DefineVariables();

    void FillBranch(HHiggsBranch * const HiggsBranch, const HDoublet &Pair);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    virtual inline std::string ClassName() const {
        return "HMvaHiggsTagger";
    };

};

#endif
