#include "boca/TopPartnerLeptonicChargedTagger.hh"

namespace boca
{

namespace toppartner
{

TopPartnerLeptonicChargedTagger::TopPartnerLeptonicChargedTagger() :
    standardmodel::tagger::TopLeptonic(Id::top_partner) {}

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

