# pragma once

# include "HTriplet.hh"
# include "BottomTagger.hh"
# include "HWHadronicTagger.hh"

#include "fastjet/contrib/MeasureFunction.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class hanalysis::HTopHadronicTagger : public Tagger
{

public:

    HTopHadronicTagger();

    int Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag);

    std::vector<HTopHadronicBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, float pre_cut = 0){
      Print(HError, "get branches", "depreciated");
    }

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const Jets &jets, const TMVA::Reader &reader);

    std::vector<HTriplet>  GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const Jets &jets, const Reader &reader){
      Print(HError, "get bdt", "depreciated");
    }

    HTriplet GetBdt(hanalysis::HTriplet &Triplet, const hanalysis::Reader &TopHadronicReader);

    int GetBdt(HEvent &event, const TMVA::Reader &reader){
      return SaveEntries(GetTriplets(event,reader));
    }

    std::vector<HTriplet> GetTriplets(HEvent &event, const TMVA::Reader &reader);

    std::vector<HTriplet> GetBdt(const Jets &jets, const hanalysis::Reader &TopHadronicReader, hanalysis::HWHadronicTagger &WTagger, hanalysis::Reader &WReader, hanalysis::BottomTagger &BottomTagger, hanalysis::Reader &BottomReader){
      Print(HError, "get bdt", "depreciated");
    }

    float ReadBdt(const TClonesArray &clones_array, const int entry){
      return static_cast<HTopHadronicBranch &>(* clones_array.At(entry)).Bdt;
    }

    BottomTagger bottom_tagger_;

    HWHadronicTagger w_hadronic_tagger_;

    Reader  bottom_reader_;

    Reader  w_hadronic_reader_;

    HTopHadronicBranch GetBranch(const hanalysis::HTriplet &triplet) const;

    int SaveEntries(const std::vector<HTriplet> &triplets) {
      for (const auto & triplet : triplets) static_cast<HTopHadronicBranch &>(*tree_branch().NewEntry()) = GetBranch(triplet);
      return triplets.size();
    }

    TClass &Class() const {
      return *HTopHadronicBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

private:

    void DefineVariables();

    void GetBottomInfo(HTopHadronicBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronicBranch branch_;

    float top_mass_window_ ;

    float w_mass_window_ ;

    bool boost_ = false;

    void NSubJettiness(HTriplet& triplet);

    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);

};

