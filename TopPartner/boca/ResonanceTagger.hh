#pragma once

#include "boca/multiplets/Doublet.hh"
#include "boca/BranchesTopPartner.hh"
#include "boca/TaggerTemplate.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ResonanceTagger : public TaggerTemplate<Doublet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    Latex LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const;

};

}

}
