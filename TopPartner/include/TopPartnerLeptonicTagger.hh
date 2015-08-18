#pragma once

#include "TopLeptonicTagger.hh"
#include "HiggsTagger.hh"
#include "Quintet.hh"
#include "BranchesTopPartner.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerLeptonicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerLeptonicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader) {
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
