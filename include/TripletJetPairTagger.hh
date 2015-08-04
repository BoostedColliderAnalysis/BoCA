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

    int Train(const analysis::Event &event, const analysis::PreCuts &pre_cuts,
              Tag tag) const override;

    std::vector<Quartet31> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "TripletJetJetPair"; }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<TopHadronicTagger> top_hadronic_reader_;

};

}
