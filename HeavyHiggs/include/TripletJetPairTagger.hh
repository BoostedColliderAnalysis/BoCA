/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TopHadronicTagger.hh"
#include "multiplets/Quartet.hh"

namespace boca
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPairTagger : public TaggerTemplate<Quartet31, TripletJetPairBranch>
{

public:

    int Train(const boca::Event& event, boca::PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<standardmodel::TopHadronicTagger> top_hadronic_reader_;

};

}
