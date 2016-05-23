/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Doublet.hh"
#include "boca/standardmodel/Branches.hh"
#include "boca/Tagger.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief BDT tagger for leptonically decaying W bosons
 * neutrino momentum reconstruction from missing transverser energy
 *
 */
class WLeptonicTagger : public Tagger<Doublet, WLeptonicBranch>
{

public:

    WLeptonicTagger();

    int Train(Event const& event, PreCuts const& , Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Doublet> Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    std::vector<Particle> Particles(Event const& event) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    std::vector<Doublet> ReconstructNeutrino(Doublet const& doublet) const;

    Mass w_mass_window_;

};

}

}
