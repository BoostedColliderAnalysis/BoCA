#pragma once

#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"
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
class TopSemiPairTagger : public Tagger<Sextet, TripletTwoBody>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

};

}

}
