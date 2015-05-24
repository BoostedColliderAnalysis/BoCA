# pragma once

# include "Sextet.hh"
# include "TopSemiTagger.hh"
# include "TopHadronicTagger.hh"

namespace analysis {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public Tagger
{

public:

    HeavyHiggsSemiTagger();

    std::vector< HeavyHiggsSemiBranch > GetBranches(Event &, const Tag, const float){
      Print(kError, "get branches","depreciated");
      return std::vector< HeavyHiggsSemiBranch >{};
    }
    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Sextet> Sextets(analysis::Event& event, const TMVA::Reader& reader);

    std::vector<Sextet>  GetBdt(const std::vector< Triplet > &, const std::vector<Triplet > &, const Reader & ){
      Print(kError, "get bdt","depreciated");
      return std::vector< Sextet >{};
    }

    std::vector<Sextet>  GetBdt(const std::vector< Triplet > &tripletsSemi, const std::vector< Triplet > &tripletsHadronic, const Reader & Reader, const int Mass);

    HeavyHiggsSemiBranch GetBranch(const Sextet& sextet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsSemiTagger";
    }

private:

  int SaveEntries(const std::vector<Sextet> &sextets) {
    for (const auto & sextet : sextets) static_cast<HeavyHiggsSemiBranch &>(*tree_branch().NewEntry()) = GetBranch(sextet);
    return sextets.size();
  }

    void DefineVariables();

    HeavyHiggsSemiBranch branch_;

    TopHadronicTagger top_hadronic_tagger;

    TopSemiTagger top_semi_tagger;

    Reader top_hadronic_reader_;

    Reader top_semi_reader_;
};

}
