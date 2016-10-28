#include "boca/Event.hh"
#include "boca/generic/Exception.hh"
#include "boca/fastjet/Particles.hh"
#include "boca/generic/DEBUG_MACROS.hh"

#include "toppartner/tagger/TopPartnerHadronicNeutral.hh"

namespace toppartner
{

namespace tagger
{

int TopPartnerHadronicNeutral::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto particles = Particles(event);
    return (particles.empty() && tag == Tag::signal) ?  0 : SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), particles, tag);
}

std::vector<Quintet> TopPartnerHadronicNeutral::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Quintet> TopPartnerHadronicNeutral::Quintets(boca::Event const& event, std::function<Quintet(Quintet&)> const& function)
{
    INFO0;
    return Pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Particle> TopPartnerHadronicNeutral::Particles(boca::Event const& event) const
{
    INFO0;
    auto particles = event.GenParticles();
    auto quarks = CopyIfQuark(particles);
    auto candidates = CopyIfMother(quarks, Id::W);
    candidates = CopyIfGrandMother(candidates, Id::top);
    candidates = CopyIfGreatGrandMother(candidates, Id::top_partner);
    if (candidates.empty()) return {};
    auto position = 0;
    if (auto member = candidates.front().Info().Family().Member(Id::top_partner)) position = (*member).Position();
    else return {};
    auto top_partners = CopyIfPosition(particles, position);
    return top_partners;
}

std::string TopPartnerHadronicNeutral::Name() const
{
    return "TopPartnerHadronicNeutral";
}

latex::String TopPartnerHadronicNeutral::LatexName() const
{
    return "T_{h}";
}

}

}
