#pragma once

#include "include/tagger/NewPartnerHadronicTagger.hh"
#include "include/tagger/NewPartnerLeptonicTagger.hh"
#include "include/multiplets/Decuplet.hh"


namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class NewPartnerPairTagger : public Tagger<Decuplet55, boca::branch::Multi>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Decuplet55> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<NewPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<NewPartnerLeptonicTagger> top_partner_leptonic_reader_;
};

}
