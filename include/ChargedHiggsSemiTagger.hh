# pragma once

# include "Quartet31.hh"
# include "TopSemiTagger.hh"

namespace analysis{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public Tagger
{

public:

    ChargedHiggsSemiTagger();

    int Train(Event &event, const Tag tag);

    std::vector<Quartet31> Multiplets(analysis::Event& event, const TMVA::Reader& Reader);

protected:

    virtual inline std::string ClassName() const {
        return "ChargedHiggsSemiTagger";
    }

private:

    TClass &Class() const {
      return *ChargedHiggsSemiBranch::Class();
    }

    void DefineVariables();

    ChargedHiggsSemiBranch branch_;

    BottomTagger bottom_tagger_;

    TopSemiTagger top_semi_tagger_;

    Reader bottom_reader_;

    Reader top_semi_reader_;
};

}
