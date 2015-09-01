#pragma once

#include "TopHadronicTagger.hh"
#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"
#include "Reader.hh"

namespace boca {

namespace higgscpv {

/**
 * @brief JetPair BDT tagger
 *
 */
class TopSemiPairTagger : public BranchTagger<TripletPairBranch> {

public:

    TopSemiPairTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Sextet> Multiplets(Event const& event, TMVA::Reader const& reader) const;

    std::string Name() const final { return "TopSemiPair"; }

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

    Reader<TopHadronicTagger> top_hadronic_reader_;

};

}

}
