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

    std::vector<Quintet> Multiplets(boca::Event const&, boca::PreCuts const&, TMVA::Reader const&) override;

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Quintet> Quintets(boca::Event const& event, std::function< Quintet(Quintet&) > const& function_1, std::function<Triplet(Triplet&)> const& function_2);

    TopPartnerLeptonicCharged charged_;

    TopPartnerLeptonicNeutral neutral_;

};

}

}
