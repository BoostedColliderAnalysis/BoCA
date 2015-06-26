# pragma once

# include "Triplet.hh"
# include "WHadronicTagger.hh"

namespace analysis
{

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public BranchTagger<TopHadronicBranch>
{

public:

    TopHadronicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    analysis::Triplet Triplet(const Doublet &doublet, const fastjet::PseudoJet &jet, const Jets &leptons, PreCuts &pre_cuts, const Tag tag);

    int TopHadronicId(Event &event) const {
        return sgn(w_hadronic_tagger_.WHadronicId(event)) * to_int(Id::top);
    }

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<analysis::Triplet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

protected:

    virtual  std::string ClassName() const {
        return "TopHadronicTagger";
    }

private:

    std::vector< analysis::Triplet > Triplets(const std::vector< Doublet > &doublets, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const Tag tag);

    std::vector< analysis::Triplet > Triplets(const Doublet &doublet, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const Tag tag);

    std::vector<analysis::Triplet> Multiplets(Event &event, const TMVA::Reader &reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::vector<analysis::Triplet>  Multiplets(const std::vector< Doublet > &doublets, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader);

    std::vector<analysis::Triplet>  Multiplets(const Doublet &doublet, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader);

    analysis::Triplet Multiplet(const Doublet &doublet, const fastjet::PseudoJet &jet, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader);

    analysis::Triplet Multiplet(analysis::Triplet &triplet, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader);

    bool Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts, const Tag tag);

    bool Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts);

    void NSubJettiness(analysis::Triplet &triplet);

    SubJettiness NSubJettiness(const fastjet::PseudoJet &jet);

    float LeptonPt(const analysis::Triplet &triplet, const Jets &leptons);

    BottomTagger bottom_tagger_;

    WHadronicTagger w_hadronic_tagger_;

    Reader bottom_reader_;

    Reader w_hadronic_reader_;

    float top_mass_window_ ;

};

}

