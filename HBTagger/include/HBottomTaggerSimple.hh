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

    int GetBranches(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag);

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::Tag GetTag(const fastjet::PseudoJet &Jet) const;

    int GetJetBdt(hanalysis::HEvent &event);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return static_cast<HBottomBranch &>(*EventClonesArray.At(Entry)).Bdt;
    }

    void SaveEntries(const HJets &jets){
      for (const auto & jet : jets) static_cast<HBottomBranch &>(*TreeBranch().NewEntry()) = GetBranch(jet);
    }

protected:

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

private:

    void DefineVariables();

    HJets CleanJets(HJets &Jets, const HJets &Particles, const hanalysis::HObject::Tag Tag);

    HJets GetSubJets(const HJets &Jets, const HJets &Particles, const Tag Tag, const int SubJetNumber);

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HBottomBranch branch_;

};
}
