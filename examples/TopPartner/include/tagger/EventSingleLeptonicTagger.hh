/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/GlobalTagger.hh"
#include "boca/multiplets/EventMultiplet.hh"

#include "include/branch/NewEvent.hh"
#include "include/tagger/SignatureSingleLeptonicTagger.hh"


namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleLeptonicTagger : public Tagger<EventMultiplet<Decuplet532>, branch::NewEvent>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet532>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet532>> Events(boca::Event const& event, std::function<EventMultiplet<Decuplet532>(boca::EventMultiplet<Decuplet532> &)> const& function);

    Reader<SignatureSingleLeptonicTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}
