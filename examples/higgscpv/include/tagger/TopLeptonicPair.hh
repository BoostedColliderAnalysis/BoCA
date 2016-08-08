#pragma once

#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Sextet.hh"

#include "include/branch/TopLeptonicTwoBody.hh"

namespace higgscpv
{

using namespace boca;

namespace tagger
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPair : public Tagger<Sextet, branch::TopLeptonicTwoBody>
{

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<Sextet> Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Sextet> Truth(boca::Event const& event, std::vector< boca::Sextet > sextets, Tag tag) const;

private:

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

};

}

}
