#pragma once

#include "boca/multiplets/EventMultiplet.hh"
#include "boca/analysis/AnalysisBase.hh"
#include "boca/branch/Event.hh"

#include "toppartner/tagger/NewPartnerPair.hh"

namespace toppartner
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventNewPair : public Tagger<EventMultiplet<Decuplet55>, boca::branch::Event>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet55>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<NewPartnerPair> signature_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
