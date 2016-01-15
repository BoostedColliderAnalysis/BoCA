/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "WLeptonicTagger.hh"
#include "multiplets/Triplet.hh"
#include "Reader.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief Top leptonic BDT tagger
 *
 */
class TopLeptonicTagger : public TaggerTemplate<Triplet, TopLeptonicBranch>
{

public:

    TopLeptonicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Triplet> Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const final;

    std::string LatexName() const final;

    boca::Filter Filter() const final;

private:

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    std::vector<Triplet> Triplets(Event const& event, std::function<Triplet(Triplet&)> const& function) const;

    Stage InitializeLeptonicReader();

    bool use_w_;

    Reader<BottomTagger> bottom_reader_;

    Reader<WLeptonicTagger> w_leptonic_reader_;

    Mass top_mass_window_;

    Mass top_mass_shift_;

};

}

}
