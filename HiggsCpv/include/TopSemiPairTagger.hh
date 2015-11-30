#pragma once

#include "TopHadronicTagger.hh"
#include "TopLeptonicTagger.hh"
#include "multiplets/Sextet.hh"
#include "BranchesHiggsCpv.hh"
#include "Reader.hh"

namespace boca
{

namespace higgscpv
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopSemiPairTagger : public TaggerTemplate<Sextet, TripletPairBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

    Reader<standardmodel::TopHadronicTagger> top_hadronic_reader_;

};

}

}
