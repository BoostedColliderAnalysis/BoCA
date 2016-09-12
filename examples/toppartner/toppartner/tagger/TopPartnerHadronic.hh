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

    std::vector<Quintet> Multiplets(boca::Event const&, boca::PreCuts const&, TMVA::Reader const&);

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Quintet> Quintets(const boca::Event& event, const std::function< Quintet(Quintet&) >& function_1, const standardmodel::tagger::TopHadronic::Function& function_2);

    Reader<TopPartnerHadronicCharged> charged_;

    Reader<TopPartnerHadronicNeutral> neutral_;

};

}

}
