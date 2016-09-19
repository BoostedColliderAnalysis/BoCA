#pragma once

#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Sextet.hh"

#include "higgscpv/branch/TopLeptonicTwoBody.hh"

namespace higgscpv
{

using namespace boca;

namespace tagger
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPair : public Tagger<Sextet33, branch::TopLeptonicTwoBody>
{

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<Sextet33> Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Sextet33> Truth(boca::Event const& event, std::vector< boca::Sextet33 > sextets, Tag tag) const;

private:

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;

};

}

}
