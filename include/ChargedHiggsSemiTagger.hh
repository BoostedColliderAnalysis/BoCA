# pragma once

# include "Quartet31.hh"
# include "TopSemiTagger.hh"
# include "TopHadronicTagger.hh"

namespace analysis{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public Tagger
{

public:

    ChargedHiggsSemiTagger();

    std::vector< ChargedHiggsSemiBranch > GetBranches(Event &, const Tag){
      Print(kError, "get branches", "depreciated");
      return std::vector< ChargedHiggsSemiBranch >{};
    }

    int Train(Event &event, const Tag tag);

    ChargedHiggsSemiBranch GetBranch(const Quartet31 &quartet) const;

    std::vector< Quartet31 > GetBdt(const std::vector< Triplet > , const std::vector< fastjet::PseudoJet > , const Reader &){
      Print(kError, "get bdt", "depreciated");
      return std::vector< Quartet31>{};
    }

    std::vector<Quartet31> Quartets(analysis::Event& event, const TMVA::Reader& Reader);

    std::vector< Quartet31 > Getquartets(const Reader &Reader);

    BottomTagger bottom_tagger_;
    TopSemiTagger top_semi_tagger_;

    Reader bottom_reader_;
    Reader top_semi_reader_;


    TClass &Class() const {
      return *ChargedHiggsSemiBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "ChargedHiggsSemiTagger";
    }

private:

  int SaveEntries(const std::vector<Quartet31> &quartets) {
    for (const auto & quartet : quartets) static_cast<ChargedHiggsSemiBranch&>(*tree_branch().NewEntry()) = GetBranch(quartet);
    return quartets.size();
  }

    void DefineVariables();

    ChargedHiggsSemiBranch branch_;
};

}
