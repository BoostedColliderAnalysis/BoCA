# pragma once

# include "Tagger.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
namespace hanalysis{
class BottomTagger : public Tagger
{

public:

    BottomTagger();

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    int Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag);

    Jets GetMultiJetBdt(Jets &jets, const TMVA::Reader &reader);

    Jets GetJetBdt(HEvent &event, const TMVA::Reader &reader);

    Jets GetSubBdt(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

//     Jets GetMultiplets(HEvent &event, const TMVA::Reader &reader) {
//       GetJetBdt(event)
//     }

    int GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader){
      Jets jets = GetJetBdt(event,reader);
      SaveEntries(jets);
      return jets.size();
    }

    Jets GetMultiJetBdt(Jets &jets, const Reader &reader) {
        Print(HError, "Bdt", "depreciated");
    }

    Jets GetJetBdt(const Jets &jets, const Reader &reader) {
        Print(HError, "Bdt", "depreciated");
    }

    Jets GetJetBdt(const Jets &jets, const TMVA::Reader &reader) {
      Print(HError, "Bdt", "depreciated");
    }

    Jets GetSubBdt(const Jets &jets, const Reader &reader, const int sub_jet_number) {
        Print(HError, "Bdt", "depreciated");
    }

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<HBottomBranch &>(*clones_array.At(entry)).Bdt;
    }

    void SaveEntries(const Jets &jets) {
        for (const auto & jet : jets) static_cast<HBottomBranch &>(*tree_branch().NewEntry()) = GetBranch(jet);
    }

    TClass &Class() const {
        return *HBottomBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "BottomTagger";
    };

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &particles, const hanalysis::HObject::Tag tag);

    Jets GetSubJets(const Jets &jets, const Jets &particles, const hanalysis::HObject::Tag tag, const int sub_jet_number);

    float GetDeltaR(const fastjet::PseudoJet &jet) const;

    float GetSpread(const fastjet::PseudoJet &jet) const;

    HBottomBranch branch_;

};
}
