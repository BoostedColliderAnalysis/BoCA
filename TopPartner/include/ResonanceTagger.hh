#pragma once

#include "multiplets/Doublet.hh"
#include "BranchesTopPartner.hh"
#include "TaggerTemplate.hh"

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string LatexName() const final;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const;

};

}

}
