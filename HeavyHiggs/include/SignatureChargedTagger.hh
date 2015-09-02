#pragma once

#include "ChargedHiggsSemiTagger.hh"
#include "TripletJetPairTagger.hh"
#include "Octet.hh"

namespace boca {

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureChargedTagger : public BranchTagger<OctetChargedBranch> {

public:

    SignatureChargedTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Octet44> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts,
               TMVA::Reader const& reader) const final {
                 return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::string Name() const final { return "SignatureCharged"; }

private:

    Reader<ChargedHiggsSemiTagger> charged_higgs_semi_reader_;

    Reader<TripletJetPairTagger> triplet_jet_pair_reader_;


};

}

}
