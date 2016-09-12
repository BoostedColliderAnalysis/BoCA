/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Triplet.hh"
#include "boca/multivariant/Reader.hh"
#include "standardmodel/tagger/Bottom.hh"
#include "standardmodel/tagger/WLeptonic.hh"
#include "standardmodel/branch/TopLeptonic.hh"

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for leptonically decaying top quarks
 *
 */
class TopLeptonic : public Tagger<Triplet, branch::TopLeptonic>
{

public:

    TopLeptonic(Id id = Id::top);

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Triplet> Multiplets(boca::Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

    boca::Filter Filter() const override;

    std::vector<Triplet> Triplets(boca::Event const& event, std::function<Triplet(Triplet&)> const& function);

private:

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    Stage InitializeLeptonicReader();

    Id id_;

    bool use_w_;

    Reader<tagger::Bottom> bottom_reader_;

    Reader<tagger::WLeptonic> w_leptonic_reader_;

    Mass top_mass_window_;

    Mass top_mass_shift_;

};

}

}
