#pragma once

#include "BottomTagger.hh"
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

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<Doublet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "JetPair"; }

    Jets PairBottomQuarks(const Event& event, Tag tag) const;
    bool CheckIfBadBottom(const analysis::Doublet& doublet, const Jets& jets) const;
    Jets HiggsParticle(const Event& event, Tag tag) const;


private:

    Reader<BottomTagger> bottom_reader_;

};

}
