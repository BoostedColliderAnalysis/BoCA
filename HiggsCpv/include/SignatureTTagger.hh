#pragma once

#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "MultipletSignature.hh"
#include "Octet.hh"

namespace analysis {

namespace higgscpv {

/**
 *
 * @brief event BDT for
 *
 */
class SignatureTTagger : public BranchTagger<SignatureTTaggerBranch> {

public:

    SignatureTTagger();

    int Train(const Event &event, const analysis::PreCuts &, Tag tag) const override;

    std::vector< MultipletSignature< Octet332 > > Multiplets(const analysis::Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts, const TMVA::Reader &reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "TChannel"; }

private:

  MultipletSignature<Octet332> Signature(const analysis::Triplet& triplet_1, const analysis::Triplet& triplet_2, const analysis::Doublet& doublet) const;

    Reader<HiggsTagger> higgs_reader_;

    Reader<TopLeptonicTagger> top_tagger_;

};

}

}
