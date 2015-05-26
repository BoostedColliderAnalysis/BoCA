# pragma once

# include "Triplet.hh"
# include "BottomTagger.hh"
# include "WSemiTagger.hh"
# include "Reader.hh"

namespace analysis
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class TopSemiTagger : public Tagger
{

public:

    TopSemiTagger();

    int Train(Event &event, const Object::Tag tag);

    int Train(Event &, const Object::Tag, float pre_cut = 0){
      Print(kError, "train", "depreciated");
      return 0;
    }

    std::vector<Triplet> CleanTriplets(const Triplet &triplet, Jets TopQuarks, float pre_cut, const Tag tag);

    std::vector<Triplet> CleanTriplet(const Triplet &triplet, fastjet::PseudoJet particle, float pre_cut, const Tag tag);

    int GetBdt(Event &event, const TMVA::Reader &reader){
      return SaveEntries<TopSemiBranch>(Multiplets(event,reader));
    }

    std::vector<Triplet> Multiplets(Event &event, const TMVA::Reader &reader);

    std::vector<Triplet> GetBdt(const std::vector< Doublet > &, const Jets &, const Reader &) {
        Print(kError, "get bdt", "depreciated");
    }

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<TopSemiBranch &>(*clones_array.At(entry)).Bdt;
    }

    int TopSemiId(Event &event){
      return sgn(w_semi_tagger_.WSemiId(event)) * std::abs(TopId);
    }

protected:

    virtual inline std::string ClassName() const {
        return "TopSemiTagger";
    }

private:

    TClass &Class() const {
        return *TopSemiBranch::Class();
    }

    bool boost_ = false;

    void DefineVariables();

    TopSemiBranch branch_;

    float top_mass_window_;

    BottomTagger bottom_tagger_;

    WSemiTagger w_semi_tagger_;

    Reader bottom_reader_;

    Reader w_semi_reader_;

};

}
