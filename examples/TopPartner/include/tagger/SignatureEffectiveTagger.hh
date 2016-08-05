#pragma once

#include "boca/branch/ThreeBody.hh"

#include "include/tagger/TopPartnerLeptonicTagger.hh"
#include "include/tagger/TopPartnerHadronicTagger.hh"
#include "include/tagger/HiggsPairTagger.hh"
#include "include/multiplets/Quattuordecuplet.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureEffectiveTagger : public Tagger<Quattuordecuplet554, boca::branch::ThreeBody>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quattuordecuplet554> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Quattuordecuplet554> Quattuordecuplets(boca::Event const& event, std::function<Quattuordecuplet554(Quattuordecuplet554&)> const& function);

//     TopPartnerHadronicTagger top_partner_hadronic_reader_;
//     TopPartnerLeptonicTagger top_partner_leptonic_reader_;

    Reader<TopPartnerHadronicNeutralTagger> top_partner_hadronic_reader_;
    Reader<TopPartnerLeptonicNeutralTagger> top_partner_leptonic_reader_;
    Reader<HiggsPairTagger> higgs_pair_reader_;

};

}
