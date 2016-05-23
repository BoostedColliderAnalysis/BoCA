/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/standardmodel/TopHadronicTagger.hh"
#include "boca/multiplets/Quartet.hh"

namespace boca
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

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<standardmodel::TopHadronicTagger> top_hadronic_reader_;

};

}
