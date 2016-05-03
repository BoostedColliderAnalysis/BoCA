#include "boca/TopPartnerLeptonicChargedTagger.hh"

namespace boca
{

namespace naturalness
{

TopPartnerLeptonicChargedTagger::TopPartnerLeptonicChargedTagger() :
    standardmodel::TopLeptonicTagger(Id::top_partner) {}

std::string TopPartnerLeptonicChargedTagger::Name() const
{
    return "TopPartnerLeptonicCharged";
}

latex::String TopPartnerLeptonicChargedTagger::LatexName() const
{
    return {"T_{l}", true};
}

}

}

