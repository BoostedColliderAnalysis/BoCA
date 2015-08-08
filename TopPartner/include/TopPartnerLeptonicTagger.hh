#pragma once

#include "TopLeptonicTagger.hh"
#include "HiggsTagger.hh"
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
class TopPartnerLeptonicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerLeptonicTagger();

    int Train(const Event& event, const PreCuts& pre_cuts,
              Tag tag) const final;

    std::vector<Quintet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts,
               const TMVA::Reader& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "TopPartnerSemi";
    }

    std::string NiceName() const final {
      return "#tilde t_{l}";
    }

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

    Reader<HiggsTagger> higgs_hadronic_reader_;
};

}

}
