/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Doublet.hh"
#include "Branches.hh"
#include "TaggerTemplate.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class WLeptonicTagger : public TaggerTemplate<Doublet, WSemiBranch>
{

public:

    WLeptonicTagger();

    int Train(Event const& event, PreCuts const& , Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    int WLeptonicId(Event const& event) const {
        return WLeptonicId(WLeptonicDaughters(event));
    }

    std::string Name() const final {
        return "WLeptonic";
    }

private:

    Jets WLeptonicDaughters(Event const& event) const;

    int WLeptonicId(Jets const& jets) const;

    Tag GetTag(Doublet const& doublet) const;

    std::vector<Doublet> ReconstructNeutrino(Doublet const& doublet) const;

    std::vector<Doublet> GetNeutrino(Doublet const& doublet, Jets const& Neutrinos, const Tag Tag) const;

    Mass w_mass_window_;

};

}

}
