#pragma once

#include "toppartner/tagger/TopPartnerLeptonicCharged.hh"
#include "toppartner/tagger/TopPartnerLeptonicNeutral.hh"
#include "toppartner/branch/TopPartner.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerLeptonic : public Tagger<Quintet, branch::TopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const&, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Quintet> Multiplets(boca::Event const&, boca::PreCuts const&, TMVA::Reader const&) const {
        return {};
    }

    std::vector<Quintet> Multiplets(const boca::Event& event, const boca::PreCuts&);

    std::vector<Quintet> Multiplets(boca::Event const& event);

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<TopPartnerLeptonicCharged> charged_;

    Reader<TopPartnerLeptonicNeutral> neutral_;

};

}

}
