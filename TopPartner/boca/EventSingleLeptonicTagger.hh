/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/SignatureSingleLeptonicTagger.hh"
#include "boca/GlobalTagger.hh"
#include "boca/EventMultiplet.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleLeptonicTagger : public TaggerTemplate<EventMultiplet<Decuplet532>, NewEventBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet532>> Events(Event const& event, std::function<EventMultiplet<Decuplet532>(EventMultiplet<Decuplet532> &)> const& function);

    Reader<SignatureSingleLeptonicTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}

}
