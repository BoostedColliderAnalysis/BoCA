#pragma once

#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"

namespace analysis {

namespace higgscpv {

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPairTagger : public BranchTagger<TopLeptonicPairBranch> {

public:

    TopLeptonicPairTagger();

    int Train(const Event& event, analysis::PreCuts&, const analysis::Tag tag) const;

    std::vector<Sextet> Multiplets(const Event& event, analysis::PreCuts&, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final
    {
        return "TopLeptonicPair";
    }

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

};

}

}
