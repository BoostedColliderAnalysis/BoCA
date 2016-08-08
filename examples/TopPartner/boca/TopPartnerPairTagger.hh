#pragma once

#include "boca/TopPartnerHadronicNeutralTagger.hh"
#include "boca/TopPartnerLeptonicNeutralTagger.hh"
#include "boca/Decuplet.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public Tagger<Decuplet55, branch::Multi>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet55> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Decuplet55> Decuplets(Event const& event, std::function<Decuplet55(Decuplet55&)> const& function);

    Reader<TopPartnerHadronicNeutralTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicNeutralTagger> top_partner_leptonic_reader_;
};

}

}
