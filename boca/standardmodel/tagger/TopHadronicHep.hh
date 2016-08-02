#pragma once

#include "boca/Tagger.hh"
#include "boca/multiplets/Triplet.hh"
#include "boca/standardmodel/branch/TopHadronicHep.hh"

namespace boca
{

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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Triplet> Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(boca::Event const& event) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    std::vector<Triplet> Triplets(Event const& event, PreCuts const& pre_cuts, std::function<Triplet(Triplet&)> const& function) const;

    Mass top_mass_window_;

};

}

}

}