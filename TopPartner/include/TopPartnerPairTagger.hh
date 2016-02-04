#pragma once

#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "Decuplet.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public TaggerTemplate<Decuplet55, MultiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Decuplet55> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string LatexName() const final;

private:

    Reader<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicTagger> top_partner_leptonic_reader_;
};

}

}
