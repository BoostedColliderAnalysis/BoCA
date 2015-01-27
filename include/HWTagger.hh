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

    HWTagger();

    ~HWTagger();

    void SetTagger(const HBottomTagger &NewBottomTagger);

    std::vector< HWBranch > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    std::vector<HParticleBranch *> GetConstituentBranches();

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::HReader & WReader);

    HBottomTagger BottomTagger;

    HReader BottomReader;

    HWBranch GetBranch(const HDoublet &Doublet) const;

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

    HWBranch Branch;

    HJetTag JetTag;

    float WMassWindow;

    float JetRadiusParameter;
};

#endif
