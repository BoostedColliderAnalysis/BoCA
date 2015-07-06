#pragma once

#include "ChargedHiggsSemiTagger.hh"
#include "TripletJetPairTagger.hh"
#include "Octet44.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureChargedTagger : public BranchTagger<OctetChargedBranch>
{

public:

    SignatureChargedTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Octet44> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "SignatureCharged";
    }

private:

    ReaderTagger<ChargedHiggsSemiTagger> charged_higgs_semi_reader_;

    ReaderTagger<TripletJetPairTagger> triplet_jet_pair_reader_;


};

}

}
