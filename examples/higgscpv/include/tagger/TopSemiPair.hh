#pragma once

#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Sextet.hh"
#include "boca/multivariant/Reader.hh"

#include "include/branch/TripletTwoBody.hh"

namespace higgscpv
{

namespace tagger
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopSemiPair : public Tagger<Sextet, branch::TripletTwoBody>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Sextet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

    Reader<standardmodel::tagger::TopHadronic> top_hadronic_reader_;

};

}

}
