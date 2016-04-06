#pragma once

#include "MultipletSignature.hh"
#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "multiplets/Octet.hh"

namespace boca
{

namespace higgscpv
{

/**
 *
 * @brief event BDT for
 *
 */
class SignatureTagger : public TaggerTemplate<boca::MultipletSignature< boca::Octet62 >, SignatureLeptonicBranch>
{

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector< boca::MultipletSignature< boca::Octet62 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<TopLeptonicPairTagger> triplet_pair_reader_;

};

}

}
