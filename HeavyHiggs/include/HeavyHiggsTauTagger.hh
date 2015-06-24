# pragma once

# include "Doublet.hh"
# include "TauTagger.hh"
# include "Reader.hh"
# include "Branch.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class HeavyHiggsTauTagger : public BranchTagger<HeavyHiggsTauBranch>
{

public:

    HeavyHiggsTauTagger();

    int Train(Event &event, const Object::Tag tag);

    std::vector<Doublet>  Multiplets(Event &event, const TMVA::Reader &reader);

protected:

    virtual  std::string ClassName() const {
        return "HeavyHiggsTauTagger";
    };

private:
    TauTagger tau_tagger_;

    Reader tau_reader_;

};

}

}
