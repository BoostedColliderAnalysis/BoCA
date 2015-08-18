/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TopHadronicTagger.hh"
#include "Quartet.hh"

namespace analysis {

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPairTagger : public BranchTagger<TripletJetPairBranch> {

public:

    TripletJetPairTagger();

    int Train(const analysis::Event &event, analysis::PreCuts const&pre_cuts,
              Tag tag) const override;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "TripletJetJetPair"; }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<TopHadronicTagger> top_hadronic_reader_;

};

}
