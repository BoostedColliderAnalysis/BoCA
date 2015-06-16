# pragma once

# include "BranchTagger.hh"
# include "TClonesArray.h"
# include "Branches.hh"

namespace analysis
{

namespace bottom{

/**
 * @brief Bottom BDT tagger
 *
 */
class BottomTaggerSimple : public BranchTagger<BottomBranch>
{

public:

    BottomTaggerSimple();

    int Train(Event &event, const Tag tag);

    int GetBdt(Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "BottomTaggerSimple";
    };

    virtual inline std::string NameSpaceName() const {
      return "bottom";
    }

private:

    Jets CleanJets(Jets &jets, const Jets &particles, const Object::Tag tag);

};


}

}
