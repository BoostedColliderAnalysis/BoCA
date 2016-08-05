#include "include/tagger/TopPartnerLeptonicTagger.hh"
#include "boca/generic/DEBUG.hh"

namespace toppartner
{

int TopPartnerLeptonicTagger::Train(boca::Event const&, PreCuts const&, Tag )
{
    INFO0;
    //     return SaveEntries(Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event)), Particles(event), tag);
      return 1;
}

std::vector<Quintet> TopPartnerLeptonicTagger::Multiplets(boca::Event const& event, boca::PreCuts const&)
{
    INFO0;
    return Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event));
}

std::vector<Particle> TopPartnerLeptonicTagger::Particles(boca::Event const& event) const
{
  return Combine(charged_.Tagger().Particles(event), neutral_.Tagger().Particles(event));
}

std::string TopPartnerLeptonicTagger::Name() const
{
    return "TopPartnerLeptonic";
}

latex::String TopPartnerLeptonicTagger::LatexName() const
{
    return "T_{h}";
}

std::vector< Quintet > TopPartnerLeptonicTagger::Multiplets(boca::Event const& event)
{
    PreCuts pre_cuts;
    return Multiplets(event, pre_cuts);
}

}
