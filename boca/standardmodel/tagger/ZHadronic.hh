/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boost/optional.hpp"

#include "boca/Tagger.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/standardmodel/tagger/Bottom.hh"
#include "boca/standardmodel/branch/ZHadronic.hh"

namespace boca
{

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for hadroniccaly decaying Z bosons
 *
 */
class ZHadronic : public Tagger<Doublet, branch::ZHadronic>
{

public:

    ZHadronic();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Doublet> Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> function);

    std::vector<Particle> Particles(Event const& event) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    boost::optional<Doublet> SetTag(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    boost::optional<Doublet> Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader);

    Reader<tagger::Bottom> bottom_reader_;

    Mass z_mass_window;

};

}

}

}