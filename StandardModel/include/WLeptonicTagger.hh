/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "multiplets/Doublet.hh"
#include "BranchesSm.hh"
#include "TaggerTemplate.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class WLeptonicTagger : public TaggerTemplate<Doublet, WLeptonicBranch>
{

public:

    WLeptonicTagger();

    int Train(Event const& event, PreCuts const& , Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string LatexName() const final;

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
