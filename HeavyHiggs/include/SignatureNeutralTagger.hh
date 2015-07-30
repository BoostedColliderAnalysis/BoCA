#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "HeavyHiggsSemiTagger.hh"
#include "JetPairTagger.hh"
#include "Octet.hh"

namespace analysis {

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureNeutralTagger : public BranchTagger<OctetNeutralBranch> {

public:

    SignatureNeutralTagger();

    int Train(const Event &event, const PreCuts &pre_cuts,
              Tag tag) const final;

    std::vector<Octet62> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    int GetBdt(const Event &event, const PreCuts &pre_cuts,
               const TMVA::Reader &reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string Name() const final { return "SignatureNeutral"; }

private:

    std::vector<Octet62> GetHeavyHiggsevents(Jets& jets);

    Reader<HeavyHiggsSemiTagger> heavy_higgs_semi_reader_;

    Reader<JetPairTagger> jet_pair_reader_;

};

}

}
