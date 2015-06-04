# pragma once

# include "Tagger.hh"

namespace analysis {

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public Tagger
{

public:

    TauTagger();

    int Train(analysis::Event &event, const analysis::Object::Tag tag);

    Jets Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "TauTagger";
    }

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const analysis::Object::Tag Tag);

    TauBranch branch_;

};

}
