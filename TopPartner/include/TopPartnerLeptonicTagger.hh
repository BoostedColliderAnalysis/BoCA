#pragma once

#include "Quartet.hh"
#include "TopLeptonicTagger.hh"
#include "HiggsTagger.hh"
#include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerLeptonicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerLeptonicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector< Quartet22 > Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    TopLeptonicTagger top_tagger_;

    HiggsTagger z_hadronic_tagger;

    Reader top_reader_;

    Reader z_hadronic_reader_;
};

}

}
