#pragma once

#include "SignatureEffectiveTagger.hh"
#include "GlobalTagger.hh"
#include "EventMultiplet.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffectiveTagger : public TaggerTemplate<EventMultiplet<Quattuordecuplet554>, NewEventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<EventMultiplet<Quattuordecuplet554>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;


private:

    std::vector<EventMultiplet<Quattuordecuplet554>> Events(Event const& event, std::function< EventMultiplet<Quattuordecuplet554>(EventMultiplet<Quattuordecuplet554>&)> const& function) const;

    Reader<SignatureEffectiveTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}

}
