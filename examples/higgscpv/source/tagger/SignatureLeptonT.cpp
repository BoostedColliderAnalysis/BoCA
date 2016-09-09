#include "boca/Event.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"

#include "higgscpv/tagger/SignatureLeptonT.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace higgscpv
{

namespace tagger
{

int SignatureLeptonT::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto singlets = event.Leptons();
    if (tag == Tag::signal) {
        singlets = BestMatches(singlets, Leptons(event), tag);
        DEBUG(singlets.size());
    }

    auto doublets = higgs_reader_.Multiplets(event);
    if (tag == Tag::signal) {
        std::vector<Particle> particles = event.GenParticles();
        std::vector<Particle> higgses = CopyIfParticles(particles, {Id::higgs, Id::CP_violating_higgs});
        doublets = BestMatches(doublets, higgses, tag);
        DEBUG(doublets.size(), higgses.size());
    }

    auto octets = Triples(singlets, doublets, [&](Singlet const & triplet_1, Singlet const & triplet_2, Doublet const & doublet) {
        auto octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    DEBUG(octets.size());
    return SaveEntries(octets, 1);
}

std::vector<Particle>SignatureLeptonT::Leptons(boca::Event const& event) const
{
    std::vector<Particle> particles = event.GenParticles();
    particles = CopyIfLepton(particles);
    return CopyIfGrandMother(particles, Id::top);
}

MultipletSignature<Octet332> SignatureLeptonT::Signature(boca::Jet const& triplet_1, boca::Jet const& triplet_2, Doublet const& doublet) const
{
    Octet332 octet;
    Triplet trip_1;
    Triplet trip_2;

    if (boca::Jet(triplet_1 + doublet.Jet()).Mass() > boca::Jet(triplet_2 + doublet.Jet()).Mass()) {
        trip_1.Enforce(triplet_1);
        trip_2.Enforce(triplet_2);
    } else {
        trip_1.Enforce(triplet_2);
        trip_2.Enforce(triplet_1);
    }
        octet.SetMultiplets(trip_1, trip_2, doublet);
    if (octet.Overlap()) throw Overlap();
    return MultipletSignature<Octet332>(octet);
}

std::vector<MultipletSignature<Octet332>> SignatureLeptonT::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    auto singlets = event.Leptons();
    INFO(singlets.size());
    std::vector<MultipletSignature<Octet332>> octets = Triples(singlets, doublets, [&](Singlet const & triplet_1, Singlet const & triplet_2, Doublet const & doublet) {
        auto octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    DEBUG(octets.size());
    return octets;
}

std::string SignatureLeptonT::Name() const
{
    return "LeptonTChannel";
}

}

}
