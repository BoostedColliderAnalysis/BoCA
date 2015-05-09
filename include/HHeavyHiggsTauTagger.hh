# ifndef HHeavyHiggsTauTagger_hh
# define HHeavyHiggsTauTagger_hh

# include "HDoublet.hh"
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

    std::vector<HHeavyHiggsTauBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag tag);

    std::vector<HDoublet>  GetBdt(const Jets &jets, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader &Reader);

    HHeavyHiggsTauBranch GetBranch(const hanalysis::HDoublet& Doublet) const;

    HTauTagger TauTagger;

    Reader TauReader;

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTauTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const hanalysis::HDoublet& Doublet) const;

    std::vector< HDoublet > GetNeutrinos(const hanalysis::HDoublet& Doublet)const;

    std::vector<hanalysis::HDoublet> GetNeutrino(const HDoublet &Doublet, const Jets &Neutrinos, const Tag Tag)const;

    std::vector<hanalysis::HDoublet> GetDoublets(const hanalysis::HDoublet &Doublet, const Jets &Neutrinos, const hanalysis::HObject::Tag tag);

    HHeavyHiggsTauBranch Branch;

    HJetTag JetTag;

//     float WMassWindow;

};

#endif
