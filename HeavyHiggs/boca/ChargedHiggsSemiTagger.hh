#pragma once

#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public Tagger<Quartet31, ChargedHiggsSemiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_leptonic_reader_;
};

}

}
