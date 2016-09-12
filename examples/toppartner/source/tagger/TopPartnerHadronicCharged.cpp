#include "toppartner/tagger/TopPartnerHadronicCharged.hh"

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

std::vector<Particle> TopPartnerHadronicCharged::Particles(boca::Event const&) const
{
    return {};
}

}

}
