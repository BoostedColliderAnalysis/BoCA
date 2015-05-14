# pragma once

# include "Tagger.hh"
# include "Reader.hh"

/**
 * @brief Bottom BDT tagger
 *
 */

namespace hbtagger{
class BottomTaggerSimple : public hanalysis::Tagger
{

public:

    BottomTaggerSimple();

    BottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    int Train(hanalysis::Event &event, const Tag tag);

    int GetBdt(hanalysis::Event &event, const TMVA::Reader &reader);

    float ReadBdt(const TClonesArray &clones_array, const int entry){
      return static_cast<BottomBranch &>(*clones_array.At(entry)).Bdt;
    }

    void SaveEntries(const Jets &jets){
      for (const auto & jet : jets) static_cast<BottomBranch &>(*tree_branch().NewEntry()) = GetBranch(jet);
    }

    virtual TClass &Class() const {
      return *BottomBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "BottomTaggerSimple";
    };

    virtual inline std::string NameSpaceName() const {
      return "btagger";
    }

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &particles, const hanalysis::HObject::Tag tag);

    Jets GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber);

    float DeltaR(const fastjet::PseudoJet &Jet) const;

    float Spread(const fastjet::PseudoJet &Jet) const;

    BottomBranch branch_;

};
}
