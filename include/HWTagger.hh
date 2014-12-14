# ifndef HHadronicWTagger_hh
# define HHadronicWTagger_hh

# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief W BDT tagger
 *
 */
class hanalysis::HWTagger : public HMva
{

public:

    HWTagger(HBottomTagger *NewBottomTagger);

    ~HWTagger();

    void FillBranch(const HDoublet &Pair);

    std::vector< HWBranch * > GetBranches(HEvent *const Event, const HObject::HTag Tag);

    std::vector<HParticleBranch *> GetConstituentBranches();

    std::vector<HDoublet> GetBdt(HJets &Jets, const hanalysis::HReader *const WReader);

protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    };

private:

    void DefineVariables();

    void FillBranch(HWBranch *const WBranch, const HDoublet &Doublet);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    hanalysis::HObject::HTag GetTag(const HDoublet &Doublet);

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HWBranch *Branch;

    HJetTag *JetTag;

};

#endif
