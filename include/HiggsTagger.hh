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

    std::vector< Doublet > Multiplets(analysis::Event &event, const TMVA::Reader &reader);

  protected:

    virtual inline std::string ClassName() const {
      return "HiggsTagger";
    }

  private:

    void DefineVariables();

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

  };

}
