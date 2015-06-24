# pragma once

# include "BranchTagger.hh"
# include "Branches.hh"

namespace analysis
{

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public BranchTagger<TauBranch>
{

public:

    TauTagger();

    int Train(analysis::Event &event, PreCuts &pre_cuts, const analysis::Object::Tag tag);

    Jets Multiplets(analysis::Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

protected:

    virtual  std::string ClassName() const {
        return "TauTagger";
    }

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const analysis::Object::Tag Tag);

};

}
