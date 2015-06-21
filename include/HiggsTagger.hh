# pragma once

# include "Doublet.hh"
# include "BottomTagger.hh"
# include "Reader.hh"

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

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector< Doublet > Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

protected:

    virtual inline std::string ClassName() const {
        return "HiggsTagger";
    }

private:

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Object::Tag tag);

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts);

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    float higgs_mass_window = 40;

};

}
