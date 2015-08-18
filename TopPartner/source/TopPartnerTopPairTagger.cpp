#include "TopPartnerTopPairTagger.hh"
#include "Debug.hh"

namespace boca {

namespace toppartner {

TopPartnerTopPairTagger::TopPartnerTopPairTagger()
{
  Info();
    DefineVariables();
}

int TopPartnerTopPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Quintet> quintets = top_partner_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
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

std::vector<Octet53> TopPartnerTopPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Quintet> quintets = top_partner_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (auto const& quintet :  quintets) {
        for (auto const& triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}

}
