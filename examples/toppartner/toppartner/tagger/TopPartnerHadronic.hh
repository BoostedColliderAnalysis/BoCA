#pragma once

#include "toppartner/tagger/TopPartnerHadronicCharged.hh"
#include "toppartner/tagger/TopPartnerHadronicNeutral.hh"

namespace toppartner
{

namespace tagger
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerHadronic : public Tagger<Quintet, branch::TopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const&, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Quintet> Multiplets(boca::Event const&, boca::PreCuts const&, TMVA::Reader const&) override;

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Quintet> Quintets(boca::Event const& event, std::function< Quintet(Quintet&) > const& function_1, standardmodel::tagger::TopHadronic::Function const& function_2);

    TopPartnerHadronicCharged charged_;

    TopPartnerHadronicNeutral neutral_;

};

}

}
