#include "TopPartnerHadronicTagger.hh"
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    //     return SaveEntries(Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event)), Particles(event), tag);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&) const
{
    INFO0;
    return ReduceResult(Combine(neutral_.Multiplets(event), charged_.Transform<Quintet>(event)));
}

std::vector<Particle> TopPartnerHadronicTagger::Particles(Event const& event) const
{
  return Combine(charged_.Tagger().Particles(event), neutral_.Tagger().Particles(event));
}

std::string TopPartnerHadronicTagger::Name() const
{
    return "TopPartnerHadronic";
}

std::string TopPartnerHadronicTagger::LatexName() const
{
    return "T_{h}";
}

std::vector< Quintet > TopPartnerHadronicTagger::Multiplets(const Event& event) const
{
    PreCuts pre_cuts;
    return Multiplets(event, pre_cuts);
}

}

}

