#include "toppartner/tagger/TopPartnerLeptonicCharged.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

TopPartnerLeptonicCharged::TopPartnerLeptonicCharged() :
    standardmodel::tagger::TopLeptonic(Id::top_partner) {}

std::string TopPartnerLeptonicCharged::Name() const
{
    return "TopPartnerLeptonicCharged";
}

latex::String TopPartnerLeptonicCharged::LatexName() const
{
    return {"T_{l}", true};
}

std::vector<Particle> TopPartnerLeptonicCharged::Particles(boca::Event const & event) const
{
    INFO0;
    auto particles = event.GenParticles();
    auto candidates = CopyIfLepton(particles);
    candidates = CopyIfMother(candidates, Id::W);
    candidates = CopyIfGrandMother(candidates, Id::top_partner);
    if (candidates.empty()) return {};
    auto position = 0;
    if(auto member = candidates.front().Info().Family().Member(Id::top_partner)) position = (*member).Position();
    else return {};
    return CopyIfPosition(particles, position);
}

}

}
