#pragma once

#include "include/tagger/TopPartnerHadronicCharged.hh"
#include "include/tagger/TopPartnerHadronicNeutral.hh"

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

    std::vector<Quintet> Multiplets(boca::Event const&, boca::PreCuts const&, TMVA::Reader const&) const {
        return {};
    }

    std::vector<Quintet> Multiplets(const boca::Event& event, const boca::PreCuts&);

    std::vector<Quintet> Multiplets(const boca::Event& event);

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<TopPartnerHadronicCharged> charged_;

    Reader<TopPartnerHadronicNeutral> neutral_;

};

}

}
