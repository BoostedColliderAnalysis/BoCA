#pragma once

#include "boca/standardmodel/BottomTagger.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/EventMultiplet.hh"
#include "boca/GlobalObservables.hh"

namespace boca
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
template<typename Tagger_>
class EventTagger : public TaggerTemplate<EventMultiplet, EventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<GlobalObservables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<Tagger_> signature_reader_;

    Reader<GlobalObservables> global_reader_;

};

}
