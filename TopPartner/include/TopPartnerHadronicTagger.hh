#pragma once

#include "TopPartnerHadronicChargedTagger.hh"
#include "TopPartnerHadronicNeutralTagger.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerHadronicTagger : public TaggerTemplate<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const&, Tag tag);

    std::vector<Quintet> Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const&) const{}

    std::vector<Quintet> Multiplets(const boca::Event& event, const boca::PreCuts&);

    std::vector<Quintet> Multiplets(const boca::Event& event);

    std::vector<Particle> Particles(Event const& event) const;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    Reader<TopPartnerHadronicChargedTagger> charged_;

    Reader<TopPartnerHadronicNeutralTagger> neutral_;

};

}

}
