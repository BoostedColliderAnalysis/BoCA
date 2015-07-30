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
class SignatureTagger : public BranchTagger<SignatureLeptonicBranch> {

public:

    SignatureTagger();

    int Train(const Event &event, const analysis::PreCuts &,
              Tag tag) const override;

    std::vector< analysis::MultipletSignature< analysis::Octet62 > > Multiplets(const analysis::Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "Signature"; }

private:

    Reader<HiggsTagger> higgs_reader_;

    Reader<TopLeptonicPairTagger> triplet_pair_reader_;

};

}

}
