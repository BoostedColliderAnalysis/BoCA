#include "boca/TopPartnerHadronicChargedTagger.hh"

namespace boca
{

namespace toppartner
{

TopPartnerHadronicChargedTagger::TopPartnerHadronicChargedTagger() :
    standardmodel::TopHadronicTagger(Id::top_partner) {}

std::string TopPartnerHadronicChargedTagger::Name() const
{
    return "TopPartnerHadronicCharged";
}

latex::String TopPartnerHadronicChargedTagger::LatexName() const
{
    return {"T_{h}", true};
}

}

}

