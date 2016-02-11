#pragma once

#include "TopLeptonicTagger.hh"
#include "multiplets/Sextet.hh"
#include "Branch.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public TaggerTemplate<Sextet, HeavyHiggsLeptonicBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
