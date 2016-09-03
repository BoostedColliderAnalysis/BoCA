#pragma once

#include "boca/multiplets/Octet.hh"

#include "heavyhiggs/tagger/ChargedHiggsSemi.hh"
#include "heavyhiggs/tagger/TripletJetPair.hh"
#include "heavyhiggs/branch/OctetCharged.hh"

namespace heavyhiggs {

namespace tagger {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureCharged : public Tagger<Octet44, branch::OctetCharged> {

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Octet44> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<ChargedHiggsSemi> charged_higgs_semi_reader_;

    Reader<TripletJetPair> triplet_jet_pair_reader_;


};

}

}
