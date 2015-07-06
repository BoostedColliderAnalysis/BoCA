#pragma once

#include "Septet.hh"
#include "TopPartnerSemiTagger.hh"
// #include "TopPartnerLeptonicTagger.hh"
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
class TopPartnerHiggsPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerHiggsPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Septet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(const Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

    std::string name() const {
      return "TopPartnerHiggsPair";
    }

private:

    ReaderTagger<TopPartnerSemiTagger> top_partner_hadronic_reader_;

    ReaderTagger<HiggsTagger> higgs_reader_;
};

}

}
