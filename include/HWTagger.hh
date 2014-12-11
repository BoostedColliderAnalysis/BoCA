# ifndef HHadronicWTagger_hh
# define HHadronicWTagger_hh

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
class hanalysis::HWTagger : public HMva
{

public:

    HWTagger(HBottomTagger *NewBottomTagger);

    ~HWTagger();

    std::vector< HHadronicWBranch * > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State);

    std::vector<HParticleBranch *> GetConstituentBranches();

    void FillBranch(const HDoublet &Pair);

private:

    HBottomTagger *BottomTagger;
    HReader *BottomReader;
    HHadronicWBranch *Branch;
    HJetTag *JetTag;

    void DefineVariables();

    void FillBranch(HHadronicWBranch * const HiggsBranch, const HDoublet &Pair);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    virtual inline std::string NameSpaceName() const {
        return "hdelphes";
    };

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    };

};

#endif
