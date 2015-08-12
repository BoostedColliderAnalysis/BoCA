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

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
    }

    std::string Name() const final {
        return "Higgs";
    }

    std::string NiceName() const final {
      return "h";
    }

protected:

private:

    bool Problematic(const Doublet& doublet, const PreCuts& pre_cuts, Tag tag) const;

    bool Problematic(const Doublet& doublet, const PreCuts& pre_cuts) const;

    Doublet MassDrop(const Doublet& doublet) const;

    Reader<BottomTagger> bottom_reader_;

    float higgs_mass_window = 70;

};

}
