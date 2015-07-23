#include "TopPartnerTopPairTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

TopPartnerTopPairTagger::TopPartnerTopPairTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerTopPairTagger::Train(const Event& event, const PreCuts& pre_cuts, const Tag tag) const
{
    Info();
    std::vector<Quintet> quintets = top_partner_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (const auto& quintet :  quintets) {
        for (const auto& triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap())
                continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    return SaveEntries(octets);
}

std::vector<Octet53> TopPartnerTopPairTagger::Multiplets(const Event& event, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    std::vector<Quintet> quintets = top_partner_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Octet53> octets;
    for (const auto& quintet :  quintets) {
        for (const auto& triplet : triplets) {
            Octet53 octet(quintet, triplet);
            if (octet.Overlap())
                continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}

}
