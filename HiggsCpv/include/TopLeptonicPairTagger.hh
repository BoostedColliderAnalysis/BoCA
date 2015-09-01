#pragma once

#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"

namespace boca {

namespace higgscpv {

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPairTagger : public BranchTagger<TopLeptonicPairBranch> {

public:

    TopLeptonicPairTagger();

    int Train(Event const& event, boca::PreCuts const&,
              Tag tag) const override;

    std::vector<Sextet> Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader)
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final { return "TopLeptonicPair"; }

    std::vector<Sextet> TruthLevel(boca::Event const& event, std::vector< boca::Sextet > sextets, Tag tag) const;

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

};

}

}
