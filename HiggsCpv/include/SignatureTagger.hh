#pragma once

#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "Octet62.hh"

namespace analysis
{

namespace higgscpv {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureTagger : public BranchTagger<SignatureLeptonicBranch>
{

public:

    SignatureTagger();

    int Train(const Event &event, analysis::PreCuts &, const analysis::Tag tag) const;

    std::vector< Octet62 > Multiplets(const analysis::Event &event, analysis::PreCuts &, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader) {
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    ReaderTagger<HiggsTagger> higgs_reader_;

    ReaderTagger<TopLeptonicPairTagger> triplet_pair_reader_;

};

}

}
