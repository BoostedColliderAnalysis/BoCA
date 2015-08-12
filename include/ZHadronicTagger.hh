#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ZHadronicTagger : public BranchTagger<ZHadronicBranch> {

public:

    ZHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader) const
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "ZHadronic"; }

private:

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    Doublet Doublett(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    Doublet Multiplet(analysis::Doublet& doublet, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Reader<BottomTagger> bottom_reader_;

    float z_mass_window = 50;

};

}
