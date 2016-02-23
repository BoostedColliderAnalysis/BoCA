#pragma once

#include "TopPartnerLeptonicChargedTagger.hh"
#include "TopPartnerLeptonicNeutralTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerLeptonicTagger : public TaggerTemplate<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const&, Tag tag) const;

    std::vector<Quintet> Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const&) const{}

    std::vector<Quintet> Multiplets(Event const& event, boca::PreCuts const&) const;

    std::vector<Quintet> Multiplets(Event const& event) const;

    std::vector<Particle> Particles(Event const& event) const;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    Reader<TopPartnerLeptonicChargedTagger> charged_;

    Reader<TopPartnerLeptonicNeutralTagger> neutral_;

};

}

}
