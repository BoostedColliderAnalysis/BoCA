/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>

#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"
#include "standardmodel/tagger/Bottom.hh"
#include "standardmodel/branch/WHadronic.hh"

namespace standardmodel
{

namespace tagger {

/**
 * @brief BDT tagger for hadronically decaying W bosons
 *
 */
class WHadronic : public Tagger<Doublet, branch::WHadronic>
{

  using Function = std::function<boost::optional<Doublet>(Doublet&)>;

public:

    WHadronic();

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag Tag) override;

    using Tagger::Multiplets;

    std::vector<Doublet> Multiplets(std::vector<boca::Jet> const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    boost::optional<Doublet> Multiplet(boca::Jet const& jet, const TMVA::Reader& reader);

    boost::optional<Doublet> Multiplet(boca::Jet const& jet_1, boca::Jet const& jet_2, TMVA::Reader const& reader);

    boost::optional<Doublet> SubMultiplet(boca::Jet const& jet, TMVA::Reader const& reader);

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::vector<Doublet> Doublets(boca::Event const& event, PreCuts const& pre_cuts, Function const& function);

    std::vector<Doublet> Doublets(std::vector<boca::Jet> const& jets, Function const& function) const;

    boost::optional<Doublet> CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Doublet> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    boost::optional<Doublet> SubDoublet(boca::Jet const& jet, const Function& function);

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader);

    Reader<tagger::Bottom> bottom_reader_;

    Mass w_mass_window_;
};

}

}
