/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis
{

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

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final {
        return "Higgs";
    }

    std::string NiceName() const final {
        return "h";
    }

protected:

private:

    Doublet Multiplet(Doublet& doublet, Jets const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Doublet CheckDoublet(analysis::Doublet doublet, const analysis::PreCuts& pre_cuts, analysis::Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Doublet MassDrop(Doublet const& doublet) const;

    Reader<BottomTagger> bottom_reader_;

    float higgs_mass_window = 70;

};

}
