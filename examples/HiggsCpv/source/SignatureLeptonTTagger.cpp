#include "boca/../boca/SignatureLeptonTTagger.hh"
#include "boca/Event.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace higgscpv
{

int SignatureLeptonTTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    std::vector<Lepton> triplets = event.Leptons();
    if (tag == Tag::signal) {
        std::vector<Particle> leptons = Leptons(event);
        triplets = BestMatches(triplets, leptons, tag);
        DEBUG(triplets.size(), leptons.size());
    }

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    if (tag == Tag::signal) {
        std::vector<Particle> particles = event.GenParticles();
        std::vector<Particle> higgses = CopyIfParticles(particles, {Id::higgs, Id::CP_violating_higgs});
        doublets = BestMatches(doublets, higgses, tag);
        DEBUG(doublets.size(), higgses.size());
    }

    std::vector<MultipletSignature<Octet332>> octets = Triples(triplets, doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        auto octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    DEBUG(octets.size());
    return SaveEntries(octets, 1);
}

std::vector<Particle>SignatureLeptonTTagger::Leptons(boca::Event const& event) const
{
    std::vector<Particle> particles = event.GenParticles();
    particles = CopyIfLepton(particles);
    return CopyIfGrandMother(particles, Id::top);
}

MultipletSignature<Octet332> SignatureLeptonTTagger::Signature(Triplet const& triplet_1, Triplet const& triplet_2, Doublet const& doublet) const
{
    Octet332 octet;
    if ((triplet_1.Jet() + doublet.Jet()).Mass() > (triplet_2.Jet() + doublet.Jet()).Mass()) octet.SetMultiplets(triplet_1, triplet_2, doublet);
    else octet.SetMultiplets(triplet_2, triplet_1, doublet);
    if (octet.Overlap()) throw Overlap();
    return MultipletSignature<Octet332>(octet);
}

std::vector<MultipletSignature<Octet332>> SignatureLeptonTTagger::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    std::vector<Jet> triplets = event.Leptons();
    INFO(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = Triples(triplets, doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        auto octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    DEBUG(octets.size());
    return octets;
}
std::string SignatureLeptonTTagger::Name() const
{
    return "LeptonTChannel";
}

}

}
