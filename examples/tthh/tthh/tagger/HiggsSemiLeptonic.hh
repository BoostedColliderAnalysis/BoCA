/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/multivariant/Reader.hh"
#include "standardmodel/tagger/WLeptonic.hh"
#include "standardmodel/tagger/WHadronic.hh"
#include "standardmodel/branch/Higgs.hh"

namespace tthh
{

using namespace boca;

namespace tagger
{

/**
 * @brief BDT tagger for higgs bosons decaying to jet pairs
 *
 */
class HiggsSemiLeptonic : public Tagger<Quartet22, standardmodel::branch::Higgs>
{

public:

    HiggsSemiLeptonic();

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Quartet22> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(boca::Event const& event) const;

private:

    std::vector<Quartet22> Quartets(boca::Event const& event, std::function<boost::optional<Quartet22>(Quartet22&)> const& function);

    boost::optional<Quartet22> Multiplet(boca::Quartet22& quartet, const boca::PreCuts& pre_cuts, TMVA::Reader const& reader);

    boost::optional<Quartet22> SetTag(boca::Quartet22& quartet, const boca::PreCuts& pre_cuts, boca::Tag tag);

    bool Problematic(Quartet22 const& quartet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Quartet22 const& quartet, PreCuts const& pre_cuts) const;


    Reader<standardmodel::tagger::WHadronic> w_hadronic_reader_;

    Reader<standardmodel::tagger::WLeptonic> w_leptonic_reader_;

};

}

}
