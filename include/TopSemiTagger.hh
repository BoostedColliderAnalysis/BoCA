#pragma once

#include "BottomTagger.hh"
#include "Triplet.hh"
#include "WSemiTagger.hh"
#include "Reader.hh"

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::vector<Triplet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int TopSemiId(const Event &event) const {
        return sgn(w_semi_reader_.tagger().WSemiId(event)) * to_int(Id::top);
    }

    std::string name() const final {
      return "TopSemi";
    }

private:

    bool Problematic(const Triplet &triplet, PreCuts &pre_cut, const Tag tag) const;

    bool boost_ = false;

    float top_mass_window_;

    Reader<BottomTagger> bottom_reader_;

    Reader<WSemiTagger> w_semi_reader_;

};

}
