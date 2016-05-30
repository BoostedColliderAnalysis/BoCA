/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/SignatureSingleHadronicTagger.hh"
#include "boca/GlobalTagger.hh"
#include "boca/multiplets/EventMultiplet.hh"

namespace boca
{

namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleHadronicTagger : public Tagger<EventMultiplet<Decuplet532>, NewEvent2>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet532>> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet532>> Events(Event const& event, std::function<EventMultiplet<Decuplet532>(EventMultiplet<Decuplet532> &)> const& function);

    Reader<SignatureSingleHadronicTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}

}
