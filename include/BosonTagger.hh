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
  class BosonTagger : public BranchTagger<PairBranch>
  {

  public:

    BosonTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector< Doublet > Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string name() const {
      return "Boson";
    }

  protected:

  private:

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag) const;

    bool Problematic(const Doublet &doublet, PreCuts &pre_cuts) const;

    ReaderTagger<BottomTagger> bottom_reader_;

    float boson_mass_window = 80;

  };

}
