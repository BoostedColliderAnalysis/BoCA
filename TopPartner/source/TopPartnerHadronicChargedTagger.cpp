#include "TopPartnerHadronicChargedTagger.hh"

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
std::string TopPartnerHadronicChargedTagger::LatexName() const
{
    return "T_{h}";
}

}

}

