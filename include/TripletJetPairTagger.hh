#pragma once

#include "TopHadronicTagger.hh"
#include "Quartet.hh"

namespace analysis
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TripletJetPairTagger : public BranchTagger<TripletJetPairBranch>
{

public:

    TripletJetPairTagger();

    int Train(const analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const;

    std::vector< Quartet31 > Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final {
      return "TripletJetJetPair";
    }

private:

    Reader<BottomTagger> bottom_reader_;

    Reader<TopHadronicTagger> top_hadronic_reader_;

};

}
