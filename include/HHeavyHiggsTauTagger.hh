# ifndef HHeavyHiggsTauTagger_hh
# define HHeavyHiggsTauTagger_hh

# include "Doublet.hh"
# include "TauTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class analysis::HHeavyHiggsTauTagger : public Tagger
{

public:

    HHeavyHiggsTauTagger();

    ~HHeavyHiggsTauTagger();

    void SetTagger(const analysis::TauTagger &tau_tagger);

    std::vector<HHeavyHiggsTauBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector<Doublet>  GetBdt(const Jets &jets, const fastjet::PseudoJet &MissingEt, const analysis::Reader &Reader);

    HHeavyHiggsTauBranch GetBranch(const analysis::Doublet& doublet) const;

    TauTagger tau_tagger_;

    Reader TauReader;

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTauTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const analysis::Doublet& doublet) const;

    std::vector< Doublet > GetNeutrinos(const analysis::Doublet& doublet)const;

    std::vector<analysis::Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

    std::vector<analysis::Doublet> GetDoublets(const analysis::Doublet &doublet, const Jets &Neutrinos, const analysis::Object::Tag tag);

    HHeavyHiggsTauBranch Branch;

    JetTag jet_tag;

//     float WMassWindow;

};

#endif
