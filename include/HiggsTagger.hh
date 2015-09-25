/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace boca
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

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
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

    Doublet CheckDoublet(boca::Doublet doublet, const boca::PreCuts& pre_cuts, boca::Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Doublet MassDrop(Doublet const& doublet) const;

    Reader<BottomTagger> bottom_reader_;

    Mass higgs_mass_window;

};

}
