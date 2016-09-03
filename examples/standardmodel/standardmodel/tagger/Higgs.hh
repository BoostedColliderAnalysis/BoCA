/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"
#include "standardmodel/tagger/Boson.hh"
#include "standardmodel/branch/Higgs.hh"

namespace boca
{
class Doublet;
}

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for higgs bosons decaying to jet pairs
 *
 */
class Higgs : public Tagger<Doublet, branch::Higgs>
{

public:

    Higgs();

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(boca::Event const& event) const;

private:

    std::vector<Doublet> Doublets(boca::Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, std::vector<Lepton>& leptons, const boca::PreCuts& pre_cuts, TMVA::Reader const& reader);

    boost::optional<Doublet> SetTag(boca::Doublet& doublet, std::vector<Lepton>& leptons, const boca::PreCuts& pre_cuts, boca::Tag tag);

    Doublet PrepareDoublet(const boca::Doublet& doublet, std::vector< boca::Lepton >& leptons);

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    boost::optional<Doublet> MassDrop(const boca::Doublet& doublet);

    Reader<tagger::Bottom> bottom_reader_;

    Mass higgs_mass_window;

};

}

}
