#include "boca/TopPartnerLeptonicTagger.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerLeptonicTagger::Train(Event const&, PreCuts const&, Tag )
{
    INFO0;
    //     return SaveEntries(Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event)), Particles(event), tag);
      return 1;
}

std::vector<Quintet> TopPartnerLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const&)
{
    INFO0;
    return Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event));
}

std::vector<Particle> TopPartnerLeptonicTagger::Particles(Event const& event) const
{
  return Combine(charged_.Tagger().Particles(event), neutral_.Tagger().Particles(event));
}

std::string TopPartnerLeptonicTagger::Name() const
{
    return "TopPartnerLeptonic";
}

std::string TopPartnerLeptonicTagger::LatexName() const
{
    return "T_{h}";
}

std::vector< Quintet > TopPartnerLeptonicTagger::Multiplets(const Event& event)
{
    PreCuts pre_cuts;
    return Multiplets(event, pre_cuts);
}

}

}

