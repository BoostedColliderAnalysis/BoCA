#pragma once

#include "boca/standardmodel/TopHadronicTagger.hh"
#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/multiplets/Sextet.hh"
#include "boca/BranchesHiggsCpv.hh"
#include "boca/multivariant/Reader.hh"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

    Reader<standardmodel::TopHadronicTagger> top_hadronic_reader_;

};

}

}
