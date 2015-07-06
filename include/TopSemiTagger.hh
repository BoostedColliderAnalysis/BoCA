#pragma once

#include "BottomTagger.hh"
#include "Triplet.hh"
#include "WSemiTagger.hh"
#include "ReaderTagger.hh"

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::vector<Triplet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int TopSemiId(const Event &event) const {
        return sgn(w_semi_reader_.tagger().WSemiId(event)) * to_int(Id::top);
    }

    std::string name() const {
      return "TopSemi";
    }

private:

    bool Problematic(const Triplet &triplet, PreCuts &pre_cut, const Tag tag) const;

    bool boost_ = false;

    float top_mass_window_;

    ReaderTagger<BottomTagger> bottom_reader_;

    ReaderTagger<WSemiTagger> w_semi_reader_;

};

}
