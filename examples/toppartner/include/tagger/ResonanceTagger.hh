#pragma once

#include "boca/Tagger.hh"
#include "boca/multiplets/Doublet.hh"

#include "include/branch/TopPartner.hh"

namespace toppartner
{

using namespace boca;

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ResonanceTagger : public Tagger<Doublet, branch::TopPartnerBranch>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Doublet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::vector<Doublet> Doublets(boca::Event const& event, std::function<Doublet(Doublet&)> const& function) const;

};

}
