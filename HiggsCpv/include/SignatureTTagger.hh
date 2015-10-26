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
class SignatureTTagger : public TaggerTemplate<MultipletSignature< Octet332 >, SignatureTTaggerBranch>
{

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const final;

    std::vector< MultipletSignature< Octet332 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const final;

    std::string Name() const final {
        return "TChannel";
    }

private:

    MultipletSignature<Octet332> Signature(boca::Triplet const& triplet_1, boca::Triplet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<HiggsTagger> higgs_reader_;

    Reader<TopLeptonicTagger> top_reader_;

};

}

}
