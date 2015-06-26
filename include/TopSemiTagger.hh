# pragma once

# include "Triplet.hh"
# include "BottomTagger.hh"
# include "WSemiTagger.hh"

namespace analysis
{

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class TopSemiTagger : public BranchTagger<TopSemiBranch>
{

public:

    TopSemiTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::vector<Triplet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int TopSemiId(Event &event) {
        return sgn(w_semi_tagger_.WSemiId(event)) * to_int(Id::top);
    }

protected:

    virtual  std::string ClassName() const {
        return "TopSemiTagger";
    }

private:

    bool Problematic(const Triplet &triplet, PreCuts &pre_cut, const Tag tag);

    bool boost_ = false;

    float top_mass_window_;

    BottomTagger bottom_tagger_;

    WSemiTagger w_semi_tagger_;

    Reader bottom_reader_;

    Reader w_semi_reader_;

};

}
