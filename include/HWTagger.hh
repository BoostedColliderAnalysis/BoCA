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

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::HReader *const WReader);

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    void FillBranch(HWBranch *const WBranch, const HDoublet &Doublet);

protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    };

private:

    void DefineVariables();

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    hanalysis::HObject::HTag GetTag(const HDoublet &Doublet);

    hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Singlet);

    HWBranch *Branch;

    HJetTag *JetTag;


    float WMassWindow;
    float JetRadiusParameter;
};

#endif
