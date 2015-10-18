/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "Reader.hh"

namespace boca
{

class Doublet;

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HiggsTagger : public BranchTagger<HiggsBranch>
{

public:

    HiggsTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    Jets Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const;

    Doublet Multiplet(boca::Doublet& doublet, boca::Jets& leptons, const boca::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet CheckDoublet(boca::Doublet& doublet, boca::Jets& leptons, const boca::PreCuts& pre_cuts, boca::Tag tag) const;

    Doublet PrepareDoublet(boca::Doublet& doublet, boca::Jets& leptons, const boca::PreCuts& pre_cuts) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Doublet MassDrop(Doublet const& doublet) const;

    Reader<BottomTagger> bottom_reader_;

    Mass higgs_mass_window;

};

}
