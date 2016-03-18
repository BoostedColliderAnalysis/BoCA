#pragma once

#include "HeavyHiggsSemiTagger.hh"
#include "HeavyHiggsSemiTagger.hh"
#include "JetPairTagger.hh"
#include "multiplets/Octet.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureNeutralTagger : public TaggerTemplate<Octet62, OctetNeutralBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Octet62> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::vector<Octet62> CleanOctets(Event const& event, std::vector<Octet62> const& octets, Tag tag) const;

private:

    std::vector<Octet62> GetHeavyHiggsevents(std::vector<Jet>& jets);

    Reader<HeavyHiggsSemiTagger> heavy_higgs_semi_reader_;

    Reader<JetPairTagger> jet_pair_reader_;

};

}

}
