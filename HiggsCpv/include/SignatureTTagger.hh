#pragma once

#include "MultipletSignature.hh"
#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "Octet.hh"

namespace boca {

namespace higgscpv {

/**
 *
 * @brief event BDT for
 *
 */
class SignatureTTagger : public BranchTagger<SignatureTTaggerBranch> {

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const override;

    std::vector< MultipletSignature< Octet332 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "TChannel"; }

private:

  MultipletSignature<Octet332> Signature(boca::Triplet const& triplet_1, boca::Triplet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<HiggsTagger> higgs_reader_;

    Reader<TopLeptonicTagger> top_reader_;

};

}

}
