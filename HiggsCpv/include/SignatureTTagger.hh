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
class SignatureTTagger : public TaggerTemplate<MultipletSignature< Octet332 >, SignatureTTaggerBranch>
{

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const override;

    std::vector< MultipletSignature< Octet332 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const override;

    std::string Name() const override {
        return "TChannel";
    }

private:

    MultipletSignature<Octet332> Signature(boca::Triplet const& triplet_1, boca::Triplet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

};

}

}
