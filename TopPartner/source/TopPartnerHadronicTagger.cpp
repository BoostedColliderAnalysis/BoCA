#include "TopPartnerHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

TopPartnerHadronicTagger::TopPartnerHadronicTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerHadronicTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Doublet> doublets = boson_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (const auto& doublet : doublets)
        for (const auto& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap())
                continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    Jets top_partner = CopyIfParticle(event.Partons().GenParticles(), Id::top_partner);
    return SaveEntries(BestMatches(quintets, top_partner, tag), 1);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Doublet> doublets = boson_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (const auto& doublet : doublets)
        for (const auto& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap())
                continue;
            quintet.SetBdt(Bdt(quintet, reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}

}
