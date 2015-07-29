#pragma once

#include "TopHadronicTagger.hh"
#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"
#include "Reader.hh"

namespace analysis {

namespace higgscpv {

/**
 * @brief JetPair BDT tagger
 *
 */
class TopSemiPairTagger : public BranchTagger<TripletPairBranch> {

public:

    TopSemiPairTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final override;

    std::vector<Sextet> Multiplets(const Event& event, const TMVA::Reader& reader) const;

    std::string Name() const final override { return "TopSemiPair"; }

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

    Reader<TopHadronicTagger> top_hadronic_reader_;

};

}

}
