# pragma once

# include "Doublet.hh"
# include "Tagger.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HWSemiTagger : public Tagger
{

public:

    HWSemiTagger();

    WSemiBranch GetBranch(const Doublet &doublet) const;

    int Train(Event &event, const Object::Tag tag);

    std::vector<Doublet> GetDoublets(Event &event, const TMVA::Reader &reader);

    int GetBdt(Event &event, const TMVA::Reader &reader) {
        std::vector<Doublet> doublets = GetDoublets(event, reader);
        SaveEntries(doublets);
        return doublets.size();
    }

    std::vector<Doublet> GetBdt(const Jets &, const fastjet::PseudoJet &, const Reader &) {
      Print(kError,"get bdt", "depreciated");
      return std::vector<Doublet>{};
    }

    std::vector<Doublet>  GetBdt(const Jets &, const fastjet::PseudoJet &, const TMVA::Reader &){
      Print(kError,"get bdt", "depreciated");
      return std::vector<Doublet>{};
    }

    void SaveEntries(const std::vector<Doublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<WSemiBranch &>(*tree_branch().NewEntry()) = GetBranch(doublet);
    }

    int WSemiId(Event &event) {
        return WSemiId(WSemiDaughters(event));
    }

    TClass &Class() const {
      return *WSemiBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HWSemiTagger";
    }

private:

    Jets WSemiDaughters(Event &event);

    int WSemiId(const Jets &jets);

    void DefineVariables();

    Tag GetTag(const Doublet &doublet) const;

    std::vector< Doublet > GetNeutrinos(const Doublet &doublet)const;

    std::vector<Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

    WSemiBranch branch_;

    float w_mass_window_;

};

}

