# ifndef HMvaHiggsTagger_hh
# define HMvaHiggsTagger_hh

# include "Tagger.hh"
# include "Branch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "Reader.hh"
# include "BottomTagger.hh"
# include "Doublet.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hanalysis::HMvaHiggsTagger : public Tagger
{

public:

    HMvaHiggsTagger();

    HMvaHiggsTagger(const hanalysis::BottomTagger &NewBottomTagger);

    ~HMvaHiggsTagger();

    std::vector< HHiggsBranch * > GetBranches(HEvent &Event, const HObject::Tag State);

    std::vector<ParticleBranch *> GetconstituentBranches();

    void FillBranch(const Doublet &Pair);

private:

    BottomTagger bottom_tagger_;

    Reader BottomReader;

    HHiggsBranch Branch;

    HJetTag JetTag;

    void DefineVariables();

    void FillBranch(HHiggsBranch * const HiggsBranch, const Doublet &Pair);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(ParticleBranch *const constituentBranch, const HKinematics &Vector);

    virtual inline std::string ClassName() const {
        return "HMvaHiggsTagger";
    };

};

#endif
