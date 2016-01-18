#pragma once

#include "NewPartnerHadronicTagger.hh"
#include "NewPartnerLeptonicTagger.hh"
#include "BranchesTopPartner.hh"
#include "Decuplet.hh"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Decuplet55> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string LatexName() const final;

private:

    Reader<NewPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<NewPartnerLeptonicTagger> top_partner_leptonic_reader_;
};

}

}