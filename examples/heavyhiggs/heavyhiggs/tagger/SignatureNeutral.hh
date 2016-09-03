#pragma once

#include "boca/multiplets/Octet.hh"

#include "heavyhiggs/tagger/HeavyHiggsSemi.hh"
#include "heavyhiggs/tagger/JetPair.hh"
#include "heavyhiggs/branch/OctetNeutral.hh"

namespace heavyhiggs
{

namespace tagger
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureNeutral : public boca::Tagger<boca::Octet62, branch::OctetNeutral>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Octet62> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Octet62> CleanOctets(boca::Event const& event, std::vector<Octet62> const& octets, Tag tag) const;

private:

    std::vector<Octet62> GetHeavyHiggsevents(std::vector<boca::Jet>& jets);

    Reader<HeavyHiggsSemi> heavy_higgs_semi_reader_;

    Reader<JetPair> jet_pair_reader_;

};

}

}
