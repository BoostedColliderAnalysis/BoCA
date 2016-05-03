#pragma once

#include "boca/TopPartnerPairTagger.hh"
#include "boca/GlobalTagger.hh"
#include "boca/EventMultiplet.hh"
#include "boca/AnalysisBase.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventPairTagger : public TaggerTemplate<EventMultiplet<Decuplet55>,NewEventBranch4>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet55>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet55>> Events(Event const& event, std::function<EventMultiplet<Decuplet55>(EventMultiplet<Decuplet55> &)> const& function);

    Reader<TopPartnerPairTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}

}
