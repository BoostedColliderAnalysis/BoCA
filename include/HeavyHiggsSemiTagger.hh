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

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Sextet> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsSemiTagger";
    }

private:

    TClass &Class() const {
      return *HeavyHiggsSemiBranch::Class();
    }

    void DefineVariables();

    HeavyHiggsSemiBranch branch_;

    TopHadronicTagger top_hadronic_tagger;

    TopSemiTagger top_semi_tagger;

    Reader top_hadronic_reader_;

    Reader top_semi_reader_;
};

}
