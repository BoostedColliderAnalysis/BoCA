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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector< Quartet22 > Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

    std::string name() const final {
      return "TopPartnerLeptonic";
    }

private:

    Reader<TopLeptonicTagger> top_reader_;

    Reader<HiggsTagger> higgs_hadronic_reader_;
};

}

}
