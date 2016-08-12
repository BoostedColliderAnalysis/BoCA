#include "include/tagger/TopPartnerTopPair.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

int TopPartnerTopPair::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto quintets = top_partner_reader_.Multiplets(event);
    auto triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (auto const & quintet :  quintets) {
        for (auto const & triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap())
                continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    return SaveEntries(octets);
}

std::vector<Octet53> TopPartnerTopPair::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    auto quintets = top_partner_reader_.Multiplets(event);
    auto triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (auto const & quintet :  quintets) {
        for (auto const & triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return octets;
}

std::string TopPartnerTopPair::Name() const
{
    return "TopPartnerTopPair";
}

}

}
