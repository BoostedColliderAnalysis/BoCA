/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Doublet.hh"
#include "boca/tagger/Tagger.hh"

#include "standardmodel/branch/WLeptonic.hh"

namespace boca
{
class Event;
}

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for leptonically decaying W bosons
 * neutrino momentum reconstruction from missing transverser energy
 *
 */
class WLeptonic : public Tagger<boca::Doublet, branch::WLeptonic>
{

public:

    WLeptonic();

    int Train(boca::Event const &event, PreCuts const &, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    void DoNeutrinoReconstruction(bool do_it);

private:

    std::vector<Doublet> Doublets(boca::Event const &event, std::function<boost::optional<Doublet>(Doublet &)> const &function) const;

    std::vector<Particle> Particles(boca::Event const &event) const;

    bool Problematic(Doublet const &doublet, PreCuts const &pre_cuts, Tag tag) const;

    bool Problematic(Doublet const &doublet, PreCuts const &pre_cuts) const;

    std::vector<Doublet> ReconstructNeutrino(Lepton const& lepton,  MissingEt const& missing_et) const;

    Mass w_mass_window_;

    bool reconstruct_neutrino_;

};

}

}
