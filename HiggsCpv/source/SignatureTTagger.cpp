#include "../include/SignatureTTagger.hh"
#include "Event.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace higgscpv
{

int SignatureTTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info0;
    Jets particles = event.Partons().GenParticles();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Jets tops = CopyIfParticle(particles, Id::top);

    std::vector<Triplet> final_triplets = triplets;
//     std::vector<Triplet> final_triplets = BestMatches(triplets, tops, tag);
    Debug(triplets.size(), tops.size(), final_triplets.size());

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
    std::vector<Doublet> final_doublets = doublets;
//     std::vector<Doublet> final_doublets = BestMatches(doublets, higgses, tag);
    Debug(doublets.size(), higgses.size(), final_doublets.size());

    std::vector<MultipletSignature<Octet332>> octets = triples(final_triplets, final_doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    Debug(octets.size());
    return SaveEntries(octets, 1);
}

MultipletSignature<Octet332> SignatureTTagger::Signature(Triplet const& triplet_1, Triplet const& triplet_2, Doublet const& doublet) const
{
    Octet332 octet;
    if ((triplet_1.Jet() + doublet.Jet()).m() > (triplet_2.Jet() + doublet.Jet()).m()) octet.SetMultiplets(triplet_1, triplet_2, doublet);
    else octet.SetMultiplets(triplet_2, triplet_1, doublet);
    if (octet.Overlap()) throw Overlap();
    return MultipletSignature<Octet332>(octet);
}

std::vector<MultipletSignature<Octet332>> SignatureTTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Info(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    Debug(octets.size());
    return ReduceResult(octets);
}

}

}
