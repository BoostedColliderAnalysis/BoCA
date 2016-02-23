#include "TopPartnerLeptonicChargedTagger.hh"

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
std::string TopPartnerLeptonicChargedTagger::LatexName() const
{
    return "T_{l}";
}

}

}

