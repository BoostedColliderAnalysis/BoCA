#pragma once

#include "boca/multiplets/EventMultiplet.hh"

#include "heavyhiggs/branch/EventFusion.hh"
#include "heavyhiggs/tagger/HeavyHiggsSemi.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusion : public boca::Tagger<boca::EventMultiplet<boca::Sextet33>, branch::EventFusion>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Sextet33>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<HeavyHiggsSemi> heavy_higgs_semi_reader_;

};

}

}
