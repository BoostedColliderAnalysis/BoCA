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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Sextet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
