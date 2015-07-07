#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "JetPairTagger.hh"
#include "Octet62.hh"

namespace analysis
{

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureNeutralTagger : public BranchTagger<OctetNeutralBranch>
{

public:

    SignatureNeutralTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector< Octet62 > Multiplets(const Event& event, PreCuts &pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "SignatureNeutral";
    }

private:

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    ReaderTagger<HeavyHiggsSemiTagger> heavy_higgs_semi_reader_;

    ReaderTagger<JetPairTagger> jet_pair_reader_;

};

}

}
