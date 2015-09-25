#include "TopPartnerHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

TopPartnerHadronicTagger::TopPartnerHadronicTagger()
{
    Info();
    DefineVariables();
}

int TopPartnerHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Debug(triplets.size());
    std::vector<Doublet> doublets = boson_reader_.Multiplets(event);
    Debug(doublets.size());
    std::vector<Quintet> quintets;
    for (auto const & doublet : doublets)
        for (auto const & triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    Debug(quintets.size());
    return SaveEntries(quintets, CopyIfParticle(event.Partons().GenParticles(), Id::top_partner), tag);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Quintet> quintets = pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw "overlap";
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
    return ReduceResult(quintets);
}

}

}
