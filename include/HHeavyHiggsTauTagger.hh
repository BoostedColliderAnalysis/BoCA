# pragma once

# include "Doublet.hh"
# include "TauTagger.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HHeavyHiggsTauTagger : public Tagger
{

public:

    HHeavyHiggsTauTagger();

    ~HHeavyHiggsTauTagger();

    void SetTagger(const TauTagger &tau_tagger);

    std::vector<HHeavyHiggsTauBranch> GetBranches(Event &event, const Object::Tag tag);

    std::vector<Doublet>  GetBdt(const Jets &jets, const fastjet::PseudoJet &MissingEt, const Reader &Reader);

    HHeavyHiggsTauBranch GetBranch(const Doublet& doublet) const;

    TauTagger tau_tagger_;

    Reader TauReader;

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTauTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const Doublet& doublet) const;

    std::vector< Doublet > GetNeutrinos(const Doublet& doublet)const;

    std::vector<Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

    std::vector<Doublet> GetDoublets(const Doublet &doublet, const Jets &Neutrinos, const Object::Tag tag);

    HHeavyHiggsTauBranch Branch;

    JetTag jet_tag;

//     float Mass(WId)Window;

};

}
