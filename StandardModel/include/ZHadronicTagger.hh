/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "boost/optional.hpp"

#include "BottomTagger.hh"
#include "TaggerTemplate.hh"
#include "multiplets/Doublet.hh"
#include "Reader.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ZHadronicTagger : public TaggerTemplate<Doublet, ZHadronicBranch>
{

public:

    ZHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Doublet> Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> function) const;

    std::vector<Particle> Particles(Event const& event) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    boost::optional<Doublet> SetTag(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    boost::optional<Doublet> Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Mass z_mass_window;

};

}

}
