# pragma once

# include "Tagger.hh"
# include "HReader.hh"

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

//     float Bdt(hanalysis::HEvent &event, const TMVA::Reader &reader) const;

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::Tag GetTag(const fastjet::PseudoJet &Jet) const;

    int GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return static_cast<HBottomBranch &>(*EventClonesArray.At(Entry)).Bdt;
    }

    void SaveEntries(const HJets &jets){
      for (const auto & jet : jets) static_cast<HBottomBranch &>(*TreeBranch().NewEntry()) = GetBranch(jet);
    }

//     void NewBranch(ExRootTreeWriter &tree_writer){
//       TreeBranch() = *tree_writer.NewBranch(tagger_name().c_str(),HBottomBranch::Class());
//     }



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

    HJets CleanJets(HJets &Jets, const HJets &Particles, const hanalysis::HObject::Tag Tag);

    HJets GetSubJets(const HJets &Jets, const HJets &Particles, const Tag Tag, const int SubJetNumber);

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HBottomBranch branch_;

};
}
