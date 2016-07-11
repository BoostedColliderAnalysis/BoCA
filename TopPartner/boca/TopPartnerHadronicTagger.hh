#pragma once

#include "boca/TopPartnerHadronicChargedTagger.hh"
#include "boca/TopPartnerHadronicNeutralTagger.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Top partner to bottom and W BDT tagger
 *
 */
class TopPartnerHadronicTagger : public Tagger<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const&, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Quintet> Multiplets(Event const&, boca::PreCuts const&, TMVA::Reader const&) const{return {};}

    std::vector<Quintet> Multiplets(const boca::Event& event, const boca::PreCuts&);

    std::vector<Quintet> Multiplets(const boca::Event& event);

    std::vector<Particle> Particles(Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    Reader<TopPartnerHadronicChargedTagger> charged_;

    Reader<TopPartnerHadronicNeutralTagger> neutral_;

};

}

}
