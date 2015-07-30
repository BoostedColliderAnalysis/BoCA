#pragma once

#include "TopLeptonicTagger.hh"
#include "Sextet.hh"
#include "Branch.hh"

namespace analysis {

namespace heavyhiggs {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public BranchTagger<HeavyHiggsLeptonicBranch> {

public:

    HeavyHiggsLeptonicTagger();

    int Train(const Event& event, const Tag tag);

    std::vector<Sextet> Multiplets(const Event& event, const TMVA::Reader& reader) const;

    std::string Name() const final
    {
        return "HeavyHiggsLeptonic";
    }

private:

    Reader<TopLeptonicTagger> top_leptonic_reader_;

};

}

}
