/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Quartet.hh"
#include "standardmodel/tagger/TopHadronic.hh"

#include "heavyhiggs/branch/TripletJetPair.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPair : public Tagger<Quartet31, branch::TripletJetPair>
{

public:

    int Train(const boca::Event& event, boca::PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet31> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

};

}

}
