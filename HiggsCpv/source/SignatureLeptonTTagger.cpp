#include "../include/SignatureLeptonTTagger.hh"
#include "Event.hh"
#include "Exeption.hh"
#define DEBUG
#include "Debug.hh"

namespace boca
{

namespace higgscpv
{

SignatureLeptonTTagger::SignatureLeptonTTagger()
{
    Info();
    DefineVariables();
}

int SignatureLeptonTTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info();
    Jets triplets = event.Leptons().leptons();
    if (tag == Tag::signal) {
        Jets leptons = Leptons(event);
        triplets = BestMatches(triplets, leptons, tag);
        Debug(triplets.size(), leptons.size());
    }

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    if (tag == Tag::signal) {
        Jets particles = event.Partons().GenParticles();
        Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
        doublets = BestMatches(doublets, higgses, tag);
        Debug(doublets.size(), higgses.size());
    }

    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](auto const & triplet_1, auto const & triplet_2, auto const & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    Debug(octets.size());
    return SaveEntries(octets, 1);
}

Jets SignatureLeptonTTagger::Leptons(Event const& event) const
{
    Jets particles = event.Partons().GenParticles();
    particles = CopyIfLepton(particles);
    return CopyIfGrandMother(particles, Id::top);
}

MultipletSignature<Octet332> SignatureLeptonTTagger::Signature(Triplet const& triplet_1, Triplet const& triplet_2, Doublet const& doublet) const
{
    Octet332 octet;
    if ((triplet_1.Jet() + doublet.Jet()).m() > (triplet_2.Jet() + doublet.Jet()).m()) octet.SetMultiplets(triplet_1, triplet_2, doublet);
    else octet.SetMultiplets(triplet_2, triplet_1, doublet);
    if (octet.Overlap()) throw Overlap();
    return MultipletSignature<Octet332>(octet);
}

std::vector<MultipletSignature<Octet332>> SignatureLeptonTTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    Jets triplets = event.Leptons().leptons();
    Info(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](auto const & triplet_1, auto const & triplet_2, auto const & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    Debug(octets.size());
    return ReduceResult(octets);
}

}

}
