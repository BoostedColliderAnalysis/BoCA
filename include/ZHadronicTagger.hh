/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "BranchTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace boca
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ZHadronicTagger : public BranchTagger<ZHadronicBranch>
{

public:

    ZHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    auto Multiplets(Event const& event, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    std::vector<Doublet> Doublets(Event const& event, std::function<Doublet(Doublet&)> function) const;

    Jets Particles(Event const& event) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Doublet CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    Doublet Multiplet(boca::Doublet& doublet, const boca::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Mass z_mass_window;

};

}
