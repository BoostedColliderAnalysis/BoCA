#include "../include/SignatureLeptonTTagger.hh"
#include "Event.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace higgscpv
{

int SignatureLeptonTTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info0;
    std::vector<Lepton> triplets = event.Leptons().leptons();
    if (tag == Tag::signal) {
        std::vector<Particle> leptons = Leptons(event);
        triplets = BestMatches(triplets, leptons, tag);
        Debug(triplets.size(), leptons.size());
    }

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    if (tag == Tag::signal) {
        std::vector<Particle> particles = event.Partons().GenParticles();
        std::vector<Particle> higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
        doublets = BestMatches(doublets, higgses, tag);
        Debug(doublets.size(), higgses.size());
    }

    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    Debug(octets.size());
    return SaveEntries(octets, 1);
}

std::vector<Particle>SignatureLeptonTTagger::Leptons(Event const& event) const
{
    std::vector<Particle> particles = event.Partons().GenParticles();
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
    Info0;
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    std::vector<Jet> triplets = event.Leptons().leptons();
    INFO(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        MultipletSignature<Octet332> octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    Debug(octets.size());
    return ReduceResult(octets);
}
std::string SignatureLeptonTTagger::Name() const
{
    return "LeptonTChannel";
}

}

}
