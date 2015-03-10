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

    void SetTagger(const HBottomTagger &NewBottomTagger);

    std::vector< HWBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

//     std::vector<HParticleBranch> GetConstituentBranches();

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::HReader &WReader);

    HDoublet GetBdt(HDoublet &Doublet, const hanalysis::HReader &WReader);

    HBottomTagger BottomTagger;

    HReader BottomReader;

    HWBranch GetBranch(const HDoublet &Doublet) const;

    int GetWHadId(hanalysis::HEvent &Event) {
      return GetWHadId(GetWDaughters(Event));
    };

protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    }

private:

    HJets GetWDaughters(hanalysis::HEvent &Event);

    int GetWHadId(const HJets &Jets);

    void DefineVariables();

//     HParticleBranch GetBranch(const HKinematics &Vector);

//     hanalysis::HObject::HTag GetTag(const HDoublet &Doublet);

//     hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Singlet);

    HWBranch Branch;
    HJetTag JetTag;
    float WMassWindow;
};

#endif
