/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "TaggerTemplate.hh"
#include "multiplets/Doublet.hh"
#include "Reader.hh"

namespace boca
{

class Doublet;

namespace standardmodel
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsTagger : public TaggerTemplate<Doublet, HiggsBranch>
{

public:

    HiggsTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, std::vector<Jet>& leptons, const boca::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    boost::optional<Doublet> SetTag(boca::Doublet& doublet, std::vector<Jet>& leptons, const boca::PreCuts& pre_cuts, boca::Tag tag) const;

    Doublet PrepareDoublet(boca::Doublet& doublet, std::vector<Jet>& leptons) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Doublet MassDrop(Doublet const& doublet) const;

    Reader<BottomTagger> bottom_reader_;

    Mass higgs_mass_window;

};

}

}
