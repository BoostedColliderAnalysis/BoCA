# pragma once

# include "Triplet.hh"
# include "BottomTagger.hh"
# include "HWSemiTagger.hh"
# include "Reader.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HTopSemiTagger : public Tagger
{

public:

    HTopSemiTagger();

    HTopSemiBranch GetBranch(const hanalysis::Triplet &triplet) const;

//     void SetTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger);

//     std::vector<HTopSemiBranch> GetBranches(HEvent &Event, const HObject::Tag State, float pre_cut = 0);

    int Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag);

    int Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag, float pre_cut = 0){
      Print(kError, "train", "depreciated");
    }

    int GetBdt(HEvent &event, const TMVA::Reader &reader){
      return SaveEntries(GetTriplets(event,reader));
    }

    std::vector<hanalysis::Triplet> GetTriplets(HEvent &event, const TMVA::Reader &reader);

    std::vector<Triplet> GetBdt(const std::vector< hanalysis::Doublet > &doublets, const Jets &jets, const hanalysis::Reader &Reader) {
        Print(kError, "get bdt", "depreciated");
    }

    BottomTagger bottom_tagger_;

    HWSemiTagger w_semi_tagger_;

    Reader bottom_reader_;

    Reader w_semi_reader_;

    void GetBottomInfo(HTopSemiBranch &top_hadronic_branch, const fastjet::PseudoJet jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<HTopSemiBranch &>(*clones_array.At(entry)).Bdt;
    }

    int SaveEntries(const std::vector<Triplet> &triplets) {
        for (const auto & triplet : triplets) static_cast<HTopSemiBranch &>(*tree_branch().NewEntry()) = GetBranch(triplet);
        return triplets.size();
    }

    TClass &Class() const {
        return *HTopSemiBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HTopSemiTagger";
    }

private:

    bool boost_ = false;

    void DefineVariables();

    HTopSemiBranch branch_;

    float top_mass_window_;

};
