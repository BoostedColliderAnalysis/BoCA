# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis
{

/**
 * @brief JetPair BDT tagger
 *
 */
class JetPairTagger : public Tagger
{

public:

    JetPairTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Doublet> Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "JetPairTagger";
    }

private:

    TClass &Class() const {
      return *JetPairBranch::Class();
    }

    void DefineVariables();

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    JetPairBranch branch_;

};

}
