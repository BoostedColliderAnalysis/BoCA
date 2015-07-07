#pragma once

#include "TopLeptonicTagger.hh"
#include "Quartet.hh"
#include "Sextet.hh"
#include "Branch.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public BranchTagger<HeavyHiggsLeptonicBranch>
{

public:

    HeavyHiggsLeptonicTagger();

    int Train(const Event &event, const Tag tag);

    std::vector<Sextet> Multiplets(const Event &event, const TMVA::Reader &reader) const;

    std::string name() const {
      return "HeavyHiggsLeptonic";
    }

private:

    ReaderTagger<TopLeptonicTagger> top_leptonic_reader_;

};

}

}
