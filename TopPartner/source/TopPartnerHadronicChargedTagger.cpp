#include "boca/TopPartnerHadronicChargedTagger.hh"

namespace boca
{

namespace naturalness
{

TopPartnerHadronicChargedTagger::TopPartnerHadronicChargedTagger() :
    standardmodel::TopHadronicTagger(Id::top_partner) {}

std::string TopPartnerHadronicChargedTagger::Name() const
{
    return "TopPartnerHadronicCharged";
}

Latex TopPartnerHadronicChargedTagger::LatexName() const
{
    return {"T_{h}", true};
}

}

}

