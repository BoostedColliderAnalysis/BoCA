#pragma once

#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Triplet.hh"
#include "standardmodel/branch/TopHadronicHep.hh"

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for hadronically decaying top quarks based on the HEP top tagger
 *
 */
class TopHadronicHep : public Tagger<Triplet, branch::TopHadronicHep>
{

public:

    TopHadronicHep();

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Triplet> Multiplets(boca::Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(boca::Event const& event) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    std::vector<Triplet> Triplets(boca::Event const& event, PreCuts const& pre_cuts, std::function<Triplet(Triplet&)> const& function) const;

    Mass top_mass_window_;

};

}

}
