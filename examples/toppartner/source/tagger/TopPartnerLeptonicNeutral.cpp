#include "toppartner/tagger/TopPartnerLeptonicNeutral.hh"
#include "boca/plotting/Font.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/Exception.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

int TopPartnerLeptonicNeutral::Train(boca::Event const &event, PreCuts const &, Tag tag)
{
    INFO0;
    auto particles = Particles(event, tag);
    return (particles.empty() && tag == Tag::signal) ?  0 : SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), particles, tag);
}

std::vector<Quintet> TopPartnerLeptonicNeutral::Quintets(boca::Event const &event, std::function<Quintet(Quintet &)> const &function)
{
    return Pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Quintet> TopPartnerLeptonicNeutral::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Particle> TopPartnerLeptonicNeutral::Particles(boca::Event const &event, Tag tag) const
{
    INFO0;
    auto particles = event.GenParticles();
    auto leptons = CopyIfLepton(particles);
    auto candidates = CopyIfMother(leptons, Id::W);
    candidates = CopyIfGrandMother(candidates, Id::top);
    candidates = CopyIfGreatGrandMother(candidates, Id::top_partner);
    if (candidates.empty()) return {};
    auto position = 0;
    if (auto member = candidates.front().Info().Family().Member(Id::top_partner)) position = (*member).Position();
    else return {};
    auto top_partners = CopyIfPosition(particles, position);
    return top_partners;
}

std::string TopPartnerLeptonicNeutral::Name() const
{
    return "TopPartnerLeptonicNeutral";
}

latex::String TopPartnerLeptonicNeutral::LatexName() const
{
    return "T_{l}";
}

}

}

