# pragma once

# include "Triplet.hh"
# include "WHadronicTagger.hh"

namespace analysis {

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public BranchTagger<TopHadronicBranch>
{

public:

    TopHadronicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    int Train(Event &event, const Object::Tag tag) {
        PreCuts pre_cuts;
        return Train(event, pre_cuts, tag);
    }

    std::vector<Triplet> Multiplets(const std::vector<Doublet> &doublets, const std::vector<fastjet::PseudoJet> &jets, const Jets&quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet> Multiplets(const Doublet& doublet, const Jets& jets, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet> Multiplets(const Doublet& doublet, const fastjet::PseudoJet& jet, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    bool Problematic(const Triplet& triplet, const Jets& quarks, PreCuts &pre_cuts, const Tag tag);

    std::vector<Triplet>  Multiplets(const std::vector< Doublet >& doublets, const Jets& jets, PreCuts &pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  Multiplets(const Doublet& doublet, const Jets& jets, PreCuts &pre_cuts, const TMVA::Reader& reader);

    std::vector<Triplet>  Multiplets(const Doublet& doublet, const fastjet::PseudoJet& jet, PreCuts &pre_cuts, const TMVA::Reader& reader);

    Triplet Multiplet(Triplet& triplet, PreCuts& pre_cuts, const TMVA::Reader& reader);

    int TopHadronicId(Event &event) const {
      return sgn(w_hadronic_tagger_.GetWHadId(event)) * std::abs(TopId);

    }

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    int GetBdt(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return GetBdt(event, pre_cuts, reader);
    }

    std::vector<Triplet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    std::vector<Triplet> Multiplets(Event &event, const TMVA::Reader &reader){
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual inline std::string ClassName() const {
        return "TopHadronicTagger";
    }

private:

    BottomTagger bottom_tagger_;

    WHadronicTagger w_hadronic_tagger_;

    Reader bottom_reader_;

    Reader w_hadronic_reader_;

    TClass &Class() const {
        return *TopHadronicBranch::Class();
    }

    void DefineVariables();

    TopHadronicBranch branch_;

    float top_mass_window_ ;

    bool boost_ = false;

    void NSubJettiness(Triplet &triplet);

    SubJettiness NSubJettiness(const fastjet::PseudoJet &jet);

};

}

