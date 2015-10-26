#pragma once

#include "TopPartnerLeptonicTagger.hh"
#include "TopPartnerHadronicTagger.hh"
#include "HiggsPairTagger.hh"
#include "Quattuordecuplet.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureEffectiveTagger : public TaggerTemplate<Quattuordecuplet554, SignatureBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Quattuordecuplet554> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    std::vector<Quattuordecuplet554> Quattuordecuplets(Event const& event, std::function<Quattuordecuplet554(Quattuordecuplet554&)> const& function) const;

    Reader<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    Reader<TopPartnerLeptonicTagger> top_partner_leptonic_reader_;

    Reader<HiggsPairTagger> higgs_pair_reader_;
};

}

}
