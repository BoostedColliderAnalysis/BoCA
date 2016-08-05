/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/GlobalTagger.hh"
#include "boca/multiplets/EventMultiplet.hh"

#include "include/branch/NewEvent3.hh"
#include "include/tagger/SignatureEffectiveTagger.hh"

namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffectiveTagger : public Tagger<EventMultiplet<Quattuordecuplet554>, branch::NewEvent3>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Quattuordecuplet554>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Quattuordecuplet554>> Events(boca::Event const& event, std::function< EventMultiplet<Quattuordecuplet554>(boca::EventMultiplet<Quattuordecuplet554>&)> const& function);

    Reader<SignatureEffectiveTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}
