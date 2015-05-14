# pragma once

# include "Triplet.hh"
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

    int Train(hanalysis::Event &event, const hanalysis::HObject::Tag tag);

    std::vector<TopHadronicBranch> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag, float pre_cut = 0){
      Print(kError, "get branches", "depreciated");
    }

    std::vector<hanalysis::Triplet> GetTriplets(const std::vector<Doublet> &doublets, const std::vector<fastjet::PseudoJet> &jets, const fastjet::PseudoJet &quark, const Tag tag);

    std::vector<hanalysis::Triplet> GetTriplets(const Doublet &doublet, const fastjet::PseudoJet &jet, const fastjet::PseudoJet &quark, const Tag tag);

    bool Problematic(const Triplet &triplet, const fastjet::PseudoJet &quark, const Tag tag);

    std::vector<Triplet>  GetBdt(const std::vector< hanalysis::Doublet > &doublets, const Jets &jets, const TMVA::Reader &reader);

    std::vector<Triplet>  GetBdt(const std::vector< hanalysis::Doublet > &doublets, const Jets &jets, const Reader &reader){
      Print(kError, "get bdt", "depreciated");
    }

    Triplet GetBdt(hanalysis::Triplet &triplet, const hanalysis::Reader &TopHadronicReader);

    int GetBdt(Event &event, const TMVA::Reader &reader){
      return SaveEntries(GetTriplets(event,reader));
    }

    std::vector<Triplet> GetTriplets(Event &event, const TMVA::Reader &reader);

    std::vector<Triplet> GetBdt(const Jets &jets, const hanalysis::Reader &TopHadronicReader, hanalysis::HWHadronicTagger &WTagger, hanalysis::Reader &WReader, hanalysis::BottomTagger &BottomTagger, hanalysis::Reader &BottomReader){
      Print(kError, "get bdt", "depreciated");
    }

    float ReadBdt(const TClonesArray &clones_array, const int entry){
      return static_cast<TopHadronicBranch &>(* clones_array.At(entry)).Bdt;
    }

    BottomTagger bottom_tagger_;

    HWHadronicTagger w_hadronic_tagger_;

    Reader  bottom_reader_;

    Reader  w_hadronic_reader_;

    TopHadronicBranch GetBranch(const hanalysis::Triplet &triplet) const;

    int SaveEntries(const std::vector<Triplet> &triplets) {
      for (const auto & triplet : triplets) static_cast<TopHadronicBranch &>(*tree_branch().NewEntry()) = GetBranch(triplet);
      return triplets.size();
    }

    TClass &Class() const {
      return *TopHadronicBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HTopHadronicTagger";
    };

private:

    void DefineVariables();

    void GetBottomInfo(TopHadronicBranch &top_hadronic_branch, const fastjet::PseudoJet jet) const;

    TopHadronicBranch branch_;

    float top_mass_window_ ;

    float w_mass_window_ ;

    bool boost_ = false;

    void NSubJettiness(Triplet& triplet);

    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);

};

