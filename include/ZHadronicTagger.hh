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
class ZHadronicTagger : public BranchTagger<ZHadronicBranch>
{

public:

    ZHadronicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector< Doublet > Multiplets(analysis::Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual inline std::string ClassName() const {
        return "ZHadronicTagger";
    }

private:
  
    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    float z_mass_window = 20;

};

}
