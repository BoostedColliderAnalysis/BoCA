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

int SignatureTTagger::Train(const Event& event, const analysis::PreCuts&, Tag tag) const
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

    std::vector<MultipletSignature<Octet332>> octets = triples(final_triplets, final_doublets, [&](const auto & triplet_1, const auto & triplet_2, const auto & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    Debug(octets.size());
    if (tag == Tag::signal) octets = ReduceResult(octets, 1);
    Debug(octets.size());
    return  SaveEntries(octets);
}

std::vector<MultipletSignature<Octet332>> SignatureTTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Info(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](const auto & triplet_1, const auto & triplet_2, const auto & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    return ReduceResult(octets);
}

MultipletSignature<Octet332> SignatureTTagger::Signature(const Triplet& triplet_1, const Triplet& triplet_2, const Doublet& doublet) const
{
    Octet332 octet;
    if ((triplet_1.Jet() + doublet.Jet()).m() > (triplet_2.Jet() + doublet.Jet()).m()) octet.SetMultiplets(triplet_1, triplet_2, doublet);
    else octet.SetMultiplets(triplet_2, triplet_1, doublet);
    if (octet.Overlap()) throw "overlap";
    return MultipletSignature<Octet332>(octet);
}

}

}
