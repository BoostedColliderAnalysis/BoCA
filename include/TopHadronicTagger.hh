#pragma once

#include "WHadronicTagger.hh"
#include "Triplet.hh"

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

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    int TopHadronicId(const Event &event) const {
        return sgn(w_hadronic_reader_.tagger().WHadronicId(event)) * to_int(Id::top);
    }

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<analysis::Triplet> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

private:

  analysis::Triplet Triplet(const Doublet &doublet, const fastjet::PseudoJet &jet, const Jets &leptons, PreCuts &pre_cuts, const Tag tag) const;

  analysis::Triplet Triplet(analysis::Triplet &triplet, const analysis::Jets &leptons, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const;

  std::vector< analysis::Triplet > Triplets(const std::vector< Doublet > &doublets, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const Tag tag) const;

  std::vector< analysis::Triplet > Triplets(const Doublet &doublet, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const Tag tag) const;

  std::vector<analysis::Triplet> Multiplets(const Event &event, const TMVA::Reader &reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::vector<analysis::Triplet>  Multiplets(const std::vector< Doublet > &doublets, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    std::vector<analysis::Triplet>  Multiplets(const Doublet &doublet, const Jets &jets, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    analysis::Triplet Multiplet(const Doublet &doublet, const fastjet::PseudoJet &jet, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    analysis::Triplet Multiplet(analysis::Triplet &triplet, const Jets &leptons, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    bool Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts, const Tag tag) const;

    bool Problematic(const analysis::Triplet &triplet, PreCuts &pre_cuts) const;

    void NSubJettiness(analysis::Triplet &triplet) const;

    SubJettiness NSubJettiness(const fastjet::PseudoJet &jet) const;

    float LeptonPt(const analysis::Triplet &triplet, const Jets &leptons) const;

    ReaderTagger<BottomTagger> bottom_reader_;

    ReaderTagger<WHadronicTagger> w_hadronic_reader_;

    float top_mass_window_ ;

};

}

