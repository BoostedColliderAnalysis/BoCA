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
class JetPairTagger : public BranchTagger<JetPairBranch>
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

    void DefineVariables();

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

};

}
