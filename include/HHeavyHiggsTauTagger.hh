# ifndef HHeavyHiggsTauTagger_hh
# define HHeavyHiggsTauTagger_hh

# include "Doublet.hh"
# include "HTauTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HHeavyHiggsTauTagger : public Tagger
{

public:

    HHeavyHiggsTauTagger();

    ~HHeavyHiggsTauTagger();

    void SetTagger(const HTauTagger &NewTauTagger);

    std::vector<HHeavyHiggsTauBranch> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag tag);

    std::vector<Doublet>  GetBdt(const Jets &jets, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader &Reader);

    HHeavyHiggsTauBranch GetBranch(const hanalysis::Doublet& doublet) const;

    HTauTagger TauTagger;

    Reader TauReader;

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTauTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const hanalysis::Doublet& doublet) const;

    std::vector< Doublet > GetNeutrinos(const hanalysis::Doublet& doublet)const;

    std::vector<hanalysis::Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

    std::vector<hanalysis::Doublet> GetDoublets(const hanalysis::Doublet &doublet, const Jets &Neutrinos, const hanalysis::HObject::Tag tag);

    HHeavyHiggsTauBranch Branch;

    HJetTag JetTag;

//     float WMassWindow;

};

#endif
