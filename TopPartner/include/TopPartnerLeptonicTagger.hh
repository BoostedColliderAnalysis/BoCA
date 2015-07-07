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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector< Quartet22 > Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

    std::string name() const {
      return "TopPartnerLeptonic";
    }

private:

    ReaderTagger<TopLeptonicTagger> top_reader_;

    ReaderTagger<HiggsTagger> higgs_hadronic_reader_;
};

}

}
