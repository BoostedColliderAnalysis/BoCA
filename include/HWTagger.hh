# ifndef HHadronicWTagger_hh
# define HHadronicWTagger_hh

# include "HBottomTagger.hh"
# include "Doublet.hh"

/**
 * @brief W BDT tagger
 *
 */
class analysis::HWTagger : public Tagger
{

public:

    HWTagger();

    void SetTagger(const HBottomTagger &NewBottomTagger);

    std::vector< WHadronicBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

//     std::vector<ParticleBranch> GetconstituentBranches();

    std::vector<Doublet> GetBdt(const Jets &jets, const analysis::HReader &WReader, analysis::HBottomTagger &BottomTagger, analysis::HReader &BottomReader);

    std::vector<Doublet> GetBdt(const Jets &jets, const analysis::HReader &WReader);
    std::vector<Doublet> GetPairBdt(const Jets &jets, const analysis::HReader &WReader);
    std::vector<Doublet> GetSingletBdt(const Jets &jets, const analysis::HReader &WReader);

    Doublet GetBdt(Doublet &doublet, const analysis::HReader &WReader);

    HBottomTagger BottomTagger;

    HReader BottomReader;

    WHadronicBranch GetBranch(const Doublet &doublet) const;

    int GetWHadId(analysis::Event &event) {
      return GetWHadId(GetWDaughters(event));
    };

protected:

    virtual inline std::string ClassName() const {
        return "HHadronicWTagger";
    }

private:

    Jets GetWDaughters(analysis::Event &event);

    int GetWHadId(const Jets &jets);

    void DefineVariables();

//     ParticleBranch GetBranch(const HKinematics &Vector);

//     analysis::Object::HTag GetTag(const Doublet &doublet);

//     analysis::Object::HTag GetTag(const fastjet::PseudoJet &Singlet);

    WHadronicBranch Branch;
    HJetTag JetTag;
    float WMassWindow;
};

#endif
