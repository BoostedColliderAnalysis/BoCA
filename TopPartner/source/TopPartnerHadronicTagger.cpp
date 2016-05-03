#include "boca/TopPartnerHadronicTagger.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerHadronicTagger::Train(Event const&, PreCuts const&, Tag )
{
    INFO0;
    //     return SaveEntries(Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event)), Particles(event), tag);
    return {};
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&)
{
    INFO0;
    return Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event));
}

std::vector<Particle> TopPartnerHadronicTagger::Particles(Event const& event) const
{
  return Combine(charged_.Tagger().Particles(event), neutral_.Tagger().Particles(event));
}

std::string TopPartnerHadronicTagger::Name() const
{
    return "TopPartnerHadronic";
}

latex::String TopPartnerHadronicTagger::LatexName() const
{
    return {"T_{h}", true};
}

std::vector< Quintet > TopPartnerHadronicTagger::Multiplets(const Event& event)
{
    PreCuts pre_cuts;
    return Multiplets(event, pre_cuts);
}

}

}

