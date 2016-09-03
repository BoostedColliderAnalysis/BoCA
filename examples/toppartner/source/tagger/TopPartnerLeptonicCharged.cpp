#include "toppartner/tagger/TopPartnerLeptonicCharged.hh"

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

}

}
