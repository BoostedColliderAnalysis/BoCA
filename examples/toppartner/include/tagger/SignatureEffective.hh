#pragma once

#include "boca/branch/ThreeBody.hh"

#include "include/tagger/TopPartnerLeptonic.hh"
#include "include/tagger/TopPartnerHadronic.hh"
#include "include/tagger/HiggsPair.hh"
#include "include/multiplets/Quattuordecuplet.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureEffective : public Tagger<Quattuordecuplet554, boca::branch::ThreeBody>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quattuordecuplet554> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Quattuordecuplet554> Quattuordecuplets(boca::Event const& event, std::function<Quattuordecuplet554(Quattuordecuplet554&)> const& function);

    Reader<TopPartnerHadronicNeutral> top_partner_hadronic_reader_;
    Reader<TopPartnerLeptonicNeutral> top_partner_leptonic_reader_;
    Reader<HiggsPair> higgs_pair_reader_;

};

}

}
