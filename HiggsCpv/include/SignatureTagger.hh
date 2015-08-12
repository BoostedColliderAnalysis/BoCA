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

    int Train(Event const& event, analysis::PreCuts const&,
              Tag tag) const override;

    std::vector< analysis::MultipletSignature< analysis::Octet62 > > Multiplets(analysis::Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
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
