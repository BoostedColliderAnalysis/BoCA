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

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Quintet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    TopSemiTagger top_tagger_;

    ZHadronicTagger z_hadronic_tagger;

    Reader top_reader_;

    Reader z_hadronic_reader_;
};

}

}
