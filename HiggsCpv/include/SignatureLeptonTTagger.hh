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
class SignatureLeptonTTagger : public TaggerTemplate<MultipletSignature< Octet332 >,SignatureLeptonTTaggerBranch>
{

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const final;

    std::vector< MultipletSignature< Octet332 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const final;

    std::string Name() const final;

   std::vector<Jet> Leptons(Event const& event) const;

private:

    MultipletSignature<Octet332> Signature(boca::Triplet const& triplet_1, boca::Triplet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

};

}

}
