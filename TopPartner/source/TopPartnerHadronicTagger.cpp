#include "TopPartnerHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace naturalness {

TopPartnerHadronicTagger::TopPartnerHadronicTagger()
{
  Info();
    DefineVariables();
}

int TopPartnerHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Error(triplets.size());
    std::vector<Doublet> doublets = boson_reader_.Multiplets(event);
    Error(doublets.size());
    std::vector<Quintet> quintets;
    for (auto const& doublet : doublets)
        for (auto const& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    Error(quintets.size());
    Jets top_partner = CopyIfParticle(event.Partons().GenParticles(), Id::top_partner);
    Error(top_partner.size());
    return SaveEntries(BestMatches(quintets, top_partner, tag), 1);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Doublet> doublets = boson_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (auto const& doublet : doublets)
        for (auto const& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetBdt(Bdt(quintet, reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}

}
