# ifndef HHadronicWTagger_hh
# define HHadronicWTagger_hh

# include "HBottomTagger.hh"
# include "Doublet.hh"

/**
 * @brief W BDT tagger
 *
 */
class hanalysis::HWTagger : public Tagger
{

public:

    HWTagger();

    void SetTagger(const HBottomTagger &NewBottomTagger);

    std::vector< WHadronicBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

//     std::vector<ParticleBranch> GetconstituentBranches();

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::HReader &WReader);
    std::vector<Doublet> GetPairBdt(const Jets &jets, const hanalysis::HReader &WReader);
    std::vector<Doublet> GetSingletBdt(const Jets &jets, const hanalysis::HReader &WReader);

    Doublet GetBdt(Doublet &doublet, const hanalysis::HReader &WReader);

    HBottomTagger BottomTagger;

    HReader BottomReader;

    WHadronicBranch GetBranch(const Doublet &doublet) const;

    int GetWHadId(hanalysis::HEvent &Event) {
      return GetWHadId(GetWDaughters(Event));
    };

protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    }

private:

    Jets GetWDaughters(hanalysis::HEvent &Event);

    int GetWHadId(const Jets &jets);

    void DefineVariables();

//     ParticleBranch GetBranch(const HKinematics &Vector);

//     hanalysis::HObject::HTag GetTag(const Doublet &doublet);

//     hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Singlet);

    WHadronicBranch Branch;
    HJetTag JetTag;
    float WMassWindow;
};

#endif
