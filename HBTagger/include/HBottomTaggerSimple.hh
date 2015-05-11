# pragma once

# include "Tagger.hh"
# include "Reader.hh"

/**
 * @brief Bottom BDT tagger
 *
 */

namespace hbtagger{
class HBottomTaggerSimple : public hanalysis::Tagger
{

public:

    HBottomTaggerSimple();

    int Train(hanalysis::HEvent &event, const Tag tag);

    BottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    int GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return static_cast<BottomBranch &>(*EventClonesArray.At(Entry)).Bdt;
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
