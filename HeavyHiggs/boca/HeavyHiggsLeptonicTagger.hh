#pragma once

#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/multiplets/Sextet.hh"
#include "boca/BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public Tagger<Sextet, HeavyHiggsLeptonicBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
