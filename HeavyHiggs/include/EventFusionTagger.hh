#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "MultipletEvent.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public BranchTagger<EventFusionBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventFusionTagger();

    int Train(Event &event, const Tag tag);

    std::vector< MultipletEvent<Sextet> > Multiplets(Event &event, TMVA::Reader &reader);

protected:

    virtual  std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual  std::string ClassName() const {
        return "EventFusionTagger";
    }

private:

    BottomTagger bottom_tagger_;

    HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;

    Reader bottom_reader_;

    Reader heavy_higgs_semi_reader_;

};

}

}
