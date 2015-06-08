# pragma once

# include "Doublet.hh"
# include "TauTagger.hh"
# include "Reader.hh"
# include "Branch.hh"

namespace heavyhiggs
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public analysis::Tagger
{

public:

    HeavyHiggsTauTagger();

    int Train(analysis::Event &event, const analysis::Object::Tag tag);

    std::vector<analysis::Doublet>  Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsTauTagger";
    };

private:

    TClass &Class() const {
        return *HeavyHiggsTauBranch::Class();
    }

    void DefineVariables();

    HeavyHiggsTauBranch branch_;

    analysis::TauTagger tau_tagger_;

    analysis::Reader tau_reader_;

};

}
