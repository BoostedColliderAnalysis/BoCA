#pragma once

#include "boca/NewPartnerHadronicTagger.hh"
#include "boca/NewPartnerLeptonicTagger.hh"
#include "boca/Decuplet.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class NewPartnerPairTagger : public TaggerTemplate<Decuplet55, MultiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet55> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    Reader<NewPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<NewPartnerLeptonicTagger> top_partner_leptonic_reader_;
};

}

}
