#pragma once

#include "TopPartnerHadronicNeutralTagger.hh"
#include "TopPartnerLeptonicNeutralTagger.hh"
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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Decuplet55> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Decuplet55> Decuplets(Event const& event, std::function<Decuplet55(Decuplet55&)> const& function) const;

    Reader<TopPartnerHadronicNeutralTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicNeutralTagger> top_partner_leptonic_reader_;
};

}

}
