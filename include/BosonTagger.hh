#pragma once

#include "BottomTagger.hh"
#include "Reader.hh"

namespace analysis {

class Doublet;

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class BosonTagger : public BranchTagger<PairBranch> {

public:

    BosonTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final { return "Boson"; }

protected:

private:

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Reader<BottomTagger> bottom_reader_;

    float boson_mass_window = 80;

};

}
