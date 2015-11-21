/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "WLeptonicTagger.hh"
#include "Triplet.hh"
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

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    Jet FakeLepton(Jet const& jet) const;

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    bool use_w_ = false;

    Reader<BottomTagger> bottom_reader_;

    Reader<WLeptonicTagger> w_leptonic_reader_;

    Mass top_mass_window;

    Stage InitializeLeptonicReader();

   std::vector<Jet> Leptons(Event const& event,std::vector<Jet> const& jets) const;

};

}

}
