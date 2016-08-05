#include "include/tagger/TopPartnerTopPairTagger.hh"
#include "boca/generic/DEBUG.hh"

namespace toppartner {

int TopPartnerTopPairTagger::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto quintets = top_partner_reader_.Multiplets(event);
    auto triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (auto const& quintet :  quintets) {
        for (auto const& triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap())
                continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    return SaveEntries(octets);
}

std::vector<Octet53> TopPartnerTopPairTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    auto quintets = top_partner_reader_.Multiplets(event);
    auto triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (auto const& quintet :  quintets) {
        for (auto const& triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return octets;
}

std::string TopPartnerTopPairTagger::Name() const
{
    return "TopPartnerTopPair";
}

}
