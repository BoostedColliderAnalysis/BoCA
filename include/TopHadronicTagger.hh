# pragma once

# include "Triplet.hh"
# include "WHadronicTagger.hh"

namespace analysis {

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public Tagger
{

public:

    TopHadronicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    int Train(Event &event, const Object::Tag tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, tag);
    }

    std::vector<TopHadronicBranch> GetBranches(Event &, const Object::Tag, float) {
        Print(kError, "get branches", "depreciated");
        return std::vector<TopHadronicBranch>{};
    }

    std::vector<Triplet> GetTriplets(const std::vector<Doublet> &doublets, const std::vector<fastjet::PseudoJet> &jets, const Jets&quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet> GetTriplets(const Doublet& doublet, const Jets& jets, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet> GetTriplets(const Doublet& doublet, const fastjet::PseudoJet& jet, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    bool Problematic(const Triplet& triplet, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet>  GetBdt(const std::vector< Doublet >& doublets, const Jets& jets, PreCuts &pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  GetBdt(const Doublet& doublet, const Jets& jets, PreCuts &pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  GetBdt(const Doublet& doublet, const fastjet::PseudoJet& jet, PreCuts &pre_cuts, const TMVA::Reader& reader);

    Triplet GetBdt(Triplet& triplet, PreCuts& pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  GetBdt(const std::vector< Doublet > &, const Jets &, const Reader &) {
        Print(kError, "get bdt", "depreciated");
    }

    int TopHadronicId(Event &event) const {
      return sgn(w_hadronic_tagger_.GetWHadId(event)) * std::abs(TopId);

    }

    Triplet GetBdt(Triplet &, const Reader &){
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

    std::vector<Triplet> GetBdt(const Jets &, const Reader &, WHadronicTagger &, Reader &, BottomTagger &, Reader &) {
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

    TopHadronicBranch GetBranch(const Triplet &triplet) const;

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

}

