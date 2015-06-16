# pragma once

# include "Reader.hh"
# include "Doublet.hh"
# include "BranchTagger.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class WSemiTagger : public BranchTagger<WSemiBranch>
{

public:

    WSemiTagger();

    int Train(Event &event, const Object::Tag tag);

    std::vector<Doublet> Multiplets(Event &event, const TMVA::Reader &reader);

    int GetBdt(Event &event, const TMVA::Reader &reader) {
        std::vector<Doublet> doublets = Multiplets(event, reader);
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

    int WSemiId(Event &event) {
        return WSemiId(WSemiDaughters(event));
    }

protected:

    virtual inline std::string ClassName() const {
        return "WSemiTagger";
    }

private:

//     TClass &Class() const {
//       return *WSemiBranch::Class();
//     }

    Jets WSemiDaughters(Event &event);

    int WSemiId(const Jets &jets);

    Tag GetTag(const Doublet &doublet) const;

    std::vector< Doublet > ReconstructNeutrino(const Doublet &doublet)const;

    std::vector<Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

//     WSemiBranch branch_;

    float w_mass_window_;

};

}

