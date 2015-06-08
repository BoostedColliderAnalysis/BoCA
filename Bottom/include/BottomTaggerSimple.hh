# pragma once

# include "Tagger.hh"
# include "TClonesArray.h"

/**
 * @brief Bottom BDT tagger
 *
 */

namespace bottom{
class BottomTaggerSimple : public analysis::Tagger
{

public:

    BottomTaggerSimple();

    analysis::BottomBranch GetBranch(const fastjet::PseudoJet& jet) const;

    int Train(analysis::Event &event, const Tag tag);

    int GetBdt(analysis::Event &event, const TMVA::Reader &reader);

    float ReadBdt(const TClonesArray &clones_array, const int entry){
      return static_cast<analysis::BottomBranch &>(*clones_array.At(entry)).Bdt;
    }

    void SaveEntries(const analysis::Jets &jets){
      for (const auto & jet : jets) static_cast<analysis::BottomBranch &>(*tree_branch().NewEntry()) = GetBranch(jet);
    }

    virtual TClass &Class() const {
      return *analysis::BottomBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "BottomTaggerSimple";
    };

    virtual inline std::string NameSpaceName() const {
      return "bottom";
    }

private:

    void DefineVariables();

    analysis::Jets CleanJets(analysis::Jets &jets, const analysis::Jets &particles, const analysis::Object::Tag tag);

    analysis::Jets GetSubJets(const analysis::Jets &jets, const analysis::Jets &Particles, const Tag Tag, const int SubJetNumber);

    float DeltaR(const fastjet::PseudoJet &Jet) const;

    float Spread(const fastjet::PseudoJet &Jet) const;

    analysis::BottomBranch branch_;

};
}
