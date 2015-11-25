#pragma once

#include "BottomTagger.hh"
#include "HeavyHiggsSemiTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis {

/**
 * @brief JetPair BDT tagger
 *
 */
class JetPairTagger : public BranchTagger<JetPairBranch> {

public:

    JetPairTagger();

    int Train(const Event &event, const PreCuts &pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts, const TMVA::Reader &reader) const final {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "JetPair"; }

    Jets PairBottomQuarks(const Event& event, Tag tag) const;
    
    bool CheckIfBadBottom(const analysis::Doublet& doublet, const Jets& jets) const;
    
    Jets TruthJetPair(Event const& event, Jets & jets, Tag tag) const; 
    
    std::vector<Doublet> TruthDoubletPairs(Event const& event, std::vector<Doublet> & doublets, Tag tag) const;
    
    Doublet TruthDoubletPair(Doublet const& doublet, Jets const& bottoms, Tag tag) const;

private:

    Reader<BottomTagger> bottom_reader_;
    
//     heavyhiggs::HeavyHiggsSemiTagger heavy_higgs_tagger_;
    
};

}
