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

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    int Train(hanalysis::HEvent &event, const Tag tag);

    int GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader);

    float ReadBdt(const TClonesArray &clones_array, const int entry){
      return static_cast<HBottomBranch &>(*clones_array.At(entry)).Bdt;
    }

    void SaveEntries(const HJets &jets){
      for (const auto & jet : jets) static_cast<HBottomBranch &>(*tree_branch().NewEntry()) = GetBranch(jet);
    }

    virtual TClass &Class() const {
      return *HBottomBranch::Class();
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

    HJets CleanJets(HJets &jets, const HJets &particles, const hanalysis::HObject::Tag tag);

    HJets GetSubJets(const HJets &Jets, const HJets &Particles, const Tag Tag, const int SubJetNumber);

    float DeltaR(const fastjet::PseudoJet &Jet) const;

    float Spread(const fastjet::PseudoJet &Jet) const;

    HBottomBranch branch_;

};
}
