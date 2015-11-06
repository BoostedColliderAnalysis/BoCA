#pragma once

#include "MultipletSignature.hh"
#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "Octet.hh"

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

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const final;

    std::vector< boca::MultipletSignature< boca::Octet62 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<TopLeptonicPairTagger> triplet_pair_reader_;

};

}

}
