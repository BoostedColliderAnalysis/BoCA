/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Sextet.hh"
#include "boca/multivariant/Reader.hh"

#include "standardmodel/tagger/Higgs.hh"

#include "tthh/branch/Higgs.hh"
#include "tthh/tagger/HiggsSemiLeptonic.hh"

namespace tthh
{

using namespace boca;

namespace tagger
{

/**
 * @brief BDT tagger for higgs bosons decaying to jet pairs
 *
 */
class HiggsToHiggs : public Tagger<Sextet42, tthh::branch::Higgs>
{

public:

    int Train(boca::Event const &event, PreCuts const &pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Sextet42> Multiplets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(boca::Event const &event) const;

private:

    std::vector<Sextet42> Quartets(boca::Event const &event, std::function<boost::optional<Sextet42>(Sextet42 &)> const &function);

    bool Problematic(Sextet42 const &sextet, PreCuts const &pre_cuts, Tag tag) const;

    bool Problematic(Sextet42 const &sextet, PreCuts const &pre_cuts) const;

    Reader<HiggsSemiLeptonic> higgs_to_ww;

    Reader<standardmodel::tagger::Higgs> higgs_to_bb_;

};

}

}
