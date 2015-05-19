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

    TopSemiBranch GetBranch(const Triplet &triplet) const;

    int Train(Event &event, const Object::Tag tag);

    int Train(Event &, const Object::Tag, float pre_cut = 0){
      Print(kError, "train", "depreciated");
      return 0;
    }

    int GetBdt(Event &event, const TMVA::Reader &reader){
      return SaveEntries(GetTriplets(event,reader));
    }

    std::vector<Triplet> GetTriplets(Event &event, const TMVA::Reader &reader);

    std::vector<Triplet> GetBdt(const std::vector< Doublet > &, const Jets &, const Reader &) {
        Print(kError, "get bdt", "depreciated");
    }

    BottomTagger bottom_tagger_;

    WSemiTagger w_semi_tagger_;

    Reader bottom_reader_;

    Reader w_semi_reader_;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<TopSemiBranch &>(*clones_array.At(entry)).Bdt;
    }

    int SaveEntries(const std::vector<Triplet> &triplets) {
        for (const auto & triplet : triplets) static_cast<TopSemiBranch &>(*tree_branch().NewEntry()) = GetBranch(triplet);
        return triplets.size();
    }

    TClass &Class() const {
        return *TopSemiBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "TopSemiTagger";
    }

private:

    bool boost_ = false;

    void DefineVariables();

    TopSemiBranch branch_;

    float top_mass_window_;

};

}
