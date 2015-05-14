# pragma once

# include "Triplet.hh"
# include "WHadronicTagger.hh"

/**
 * @brief Hadronic top BDT tagger
 *
 */
class hanalysis::TopHadronicTagger : public Tagger
{

public:

    TopHadronicTagger();

    int Train(hanalysis::Event &event, PreCuts &pre_cuts, const hanalysis::HObject::Tag tag);

    int Train(hanalysis::Event &event, const hanalysis::HObject::Tag tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, tag);
    }

    std::vector<TopHadronicBranch> GetBranches(hanalysis::Event &, const hanalysis::HObject::Tag, float) {
        Print(kError, "get branches", "depreciated");
    }

    std::vector<hanalysis::Triplet> GetTriplets(const std::vector<Doublet> &doublets, const std::vector<fastjet::PseudoJet> &jets, const Jets&quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<hanalysis::Triplet> GetTriplets(const hanalysis::Doublet& doublet, const Jets& jets, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<hanalysis::Triplet> GetTriplets(const hanalysis::Doublet& doublet, const fastjet::PseudoJet& jet, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    bool Problematic(const hanalysis::Triplet& triplet, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet>  GetBdt(const std::vector< hanalysis::Doublet >& doublets, const Jets& jets, PreCuts &pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  GetBdt(const hanalysis::Doublet& doublet, const Jets& jets, PreCuts &pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  GetBdt(const hanalysis::Doublet& doublet, const fastjet::PseudoJet& jet, PreCuts &pre_cuts, const TMVA::Reader& reader);

    Triplet GetBdt(hanalysis::Triplet& triplet, PreCuts& pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  GetBdt(const std::vector< hanalysis::Doublet > &, const Jets &, const Reader &) {
        Print(kError, "get bdt", "depreciated");
    }

    Triplet GetBdt(hanalysis::Triplet &, const hanalysis::Reader &){
      Print(kError, "get bdt", "depreciated");
      return Triplet();
    }

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(GetTriplets(event,pre_cuts, reader));
    }

    int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Triplet> GetTriplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    std::vector<Triplet> GetTriplets(Event &event, const TMVA::Reader &reader){
        PreCuts pre_cuts;
        return GetTriplets(event, pre_cuts, reader);
    }

    std::vector<Triplet> GetBdt(const Jets &, const hanalysis::Reader &, hanalysis::WHadronicTagger &, hanalysis::Reader &, hanalysis::BottomTagger &, hanalysis::Reader &) {
        Print(kError, "get bdt", "depreciated");
        return std::vector<Triplet>{};
    }

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<TopHadronicBranch &>(* clones_array.At(entry)).Bdt;
    }

    BottomTagger bottom_tagger_;

    WHadronicTagger w_hadronic_tagger_;

    Reader bottom_reader_;

    Reader w_hadronic_reader_;

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
        return "TopHadronicTagger";
    }

private:

    void DefineVariables();

    TopHadronicBranch branch_;

    float top_mass_window_ ;

    bool boost_ = false;

    void NSubJettiness(Triplet &triplet);

    SubJettiness NSubJettiness(const fastjet::PseudoJet &jet);

};

