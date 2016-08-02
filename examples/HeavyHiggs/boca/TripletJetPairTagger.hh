/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Quartet.hh"
#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPairTagger : public Tagger<Quartet31, TripletJetPairBranch>
{

public:

    int Train(const boca::Event& event, boca::PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

};

}

}
