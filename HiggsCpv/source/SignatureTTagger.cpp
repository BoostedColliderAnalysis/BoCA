#include "../include/SignatureTTagger.hh"
#include "Event.hh"
// #define DEBUG
#include "Debug.hh"

namespace analysis
{

namespace higgscpv
{

SignatureTTagger::SignatureTTagger()
{
    Info();
    DefineVariables();
}

int SignatureTTagger::Train(Event const& event, analysis::PreCuts const&, Tag tag) const
{
    Info();
    Jets particles = event.Partons().GenParticles();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Debug(triplets.size());
    Jets tops = CopyIfParticle(particles, Id::top);
    Debug(tops.size());
    std::vector<Triplet> final_triplets = BestMatches(triplets, tops, tag);
//     std::vector<Triplet> final_triplets = ReduceResult(triplets, 2);
//     std::vector<Triplet> final_triplets = triplets;
    Debug(final_triplets.size());

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Debug(doublets.size());
    Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
    Debug(higgses.size());
    std::vector<Doublet> final_doublets = BestMatches(doublets, higgses, tag);
    Debug(final_doublets.size());

    std::vector<MultipletSignature<Octet332>> octets = triples(final_triplets, final_doublets, [&](auto const& triplet_1, auto const& triplet_2, auto const& doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    Debug(octets.size());
    if (tag == Tag::signal) octets = ReduceResult(octets, 1);
    Debug(octets.size());
    return  SaveEntries(octets);
}

std::vector<MultipletSignature<Octet332>> SignatureTTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Info(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](auto const& triplet_1, auto const& triplet_2, auto const& doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    return ReduceResult(octets);
}

MultipletSignature<Octet332> SignatureTTagger::Signature(Triplet const& triplet_1, Triplet const& triplet_2, Doublet const& doublet) const
{
    Octet332 octet;
    if ((triplet_1.Jet() + doublet.Jet()).m() > (triplet_2.Jet() + doublet.Jet()).m()) octet.SetMultiplets(triplet_1, triplet_2, doublet);
    else octet.SetMultiplets(triplet_2, triplet_1, doublet);
    if (octet.Overlap()) throw "overlap";
    return MultipletSignature<Octet332>(octet);
}

}

}
