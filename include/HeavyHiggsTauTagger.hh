# pragma once

# include "Doublet.hh"
# include "TauTagger.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public Tagger
{

public:

    HeavyHiggsTauTagger();

    int Train(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector<Doublet>  Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsTauTagger";
    };

private:

    void DefineVariables();

    HeavyHiggsTauBranch branch_;

    TauTagger tau_tagger_;

    Reader tau_reader_;

};

}
