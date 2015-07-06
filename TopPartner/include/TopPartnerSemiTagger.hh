#pragma once

#include "TopSemiTagger.hh"
#include "ZHadronicTagger.hh"
#include "Quintet.hh"
#include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerSemiTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerSemiTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Quintet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    ReaderTagger<TopSemiTagger> top_reader_;

    ReaderTagger<ZHadronicTagger> z_hadronic_reader_;
};

}

}
