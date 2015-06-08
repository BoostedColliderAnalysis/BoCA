# pragma once

# include "HeavyHiggsSemiTagger.hh"
# include "MultipletEvent.hh"

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusionTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventFusionTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector< analysis::MultipletEvent<analysis::Sextet> > Multiplets(analysis::Event& event, TMVA::Reader& eventSemiReader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventFusionTagger";
    }

private:

    void DefineVariables();

    std::vector<analysis::MultipletEvent<analysis::Sextet>> GetHeavyHiggsevents(analysis::Jets &jets);

    EventFusionBranch branch_;

    analysis::BottomTagger bottom_tagger_;

    HeavyHiggsSemiTagger heavy_higgs_semi_tagger_;

    analysis::Reader bottom_reader_;

    analysis::Reader heavy_higgs_semi_reader_;

};

}
