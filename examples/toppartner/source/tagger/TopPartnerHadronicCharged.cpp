#include "toppartner/tagger/TopPartnerHadronicCharged.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

TopPartnerHadronicCharged::TopPartnerHadronicCharged() :
    standardmodel::tagger::TopHadronic(Id::top_partner) {}

std::string TopPartnerHadronicCharged::Name() const
{
    return "TopPartnerHadronicCharged";
}

latex::String TopPartnerHadronicCharged::LatexName() const
{
    return {"T_{h}", true};
}

std::vector<Particle> TopPartnerHadronicCharged::Particles(boca::Event const& event) const
{
    auto particles = event.GenParticles();
    auto quarks = CopyIfQuark(particles);
    auto candidates = CopyIfMother(quarks, Id::W);
    candidates = CopyIfGrandMother(candidates, Id::top_partner);
    if (candidates.empty()) return {};
    auto position = 0;
    if (auto member = candidates.front().Info().Family().Member(Id::top_partner)) position = (*member).Position();
    else return {};
    auto top_partners = CopyIfPosition(particles, position);
    return top_partners;
}

}

}
