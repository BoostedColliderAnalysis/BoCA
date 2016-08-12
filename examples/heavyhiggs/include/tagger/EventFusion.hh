#pragma once

#include "boca/MultipletEvent.hh"

#include "include/branch/EventFusion.hh"
#include "include/tagger/HeavyHiggsSemi.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventFusion : public boca::Tagger<boca::MultipletEvent<boca::Sextet>, branch::EventFusion>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<MultipletEvent<Sextet>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<HeavyHiggsSemi> heavy_higgs_semi_reader_;

};

}

}
