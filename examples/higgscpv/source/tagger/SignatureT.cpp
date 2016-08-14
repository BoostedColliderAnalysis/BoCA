#include "boca/Event.hh"
#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"

#include "include/tagger/SignatureT.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace higgscpv
{

namespace tagger
{

int SignatureT::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto particles = event.GenParticles();
    auto triplets = top_reader_.Multiplets(event);
    auto tops = CopyIfParticle(particles, Id::top);

    auto final_triplets = triplets;
//     auto final_triplets = BestMatches(triplets, tops, tag);
    DEBUG(triplets.size(), tops.size(), final_triplets.size());

    auto doublets = higgs_reader_.Multiplets(event);
    auto higgses = CopyIfParticles(particles, {Id::higgs, Id::CP_violating_higgs});
    auto final_doublets = doublets;
//     auto final_doublets = BestMatches(doublets, higgses, tag);
    DEBUG(doublets.size(), higgses.size(), final_doublets.size());

    auto octets = Triples(final_triplets, final_doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        auto octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetTag(tag);
        return octet;
    });
    DEBUG(octets.size());
    return SaveEntries(octets, 1);
}

MultipletSignature<Octet332> SignatureT::Signature(Triplet const& triplet_1, Triplet const& triplet_2, Doublet const& doublet) const
{
    Octet332 octet;
    if (boca::Jet((triplet_1.Jet() + doublet.Jet())).Mass() > boca::Jet(triplet_2.Jet() + doublet.Jet()).Mass()) octet.SetMultiplets(triplet_1, triplet_2, doublet);
    else octet.SetMultiplets(triplet_2, triplet_1, doublet);
    if (octet.Overlap()) throw Overlap();
    return MultipletSignature<Octet332>(octet);
}

std::vector<MultipletSignature<Octet332>> SignatureT::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    auto triplets = top_reader_.Multiplets(event);
    INFO(triplets.size());
    auto octets = Triples(triplets, doublets, [&](Triplet const & triplet_1, Triplet const & triplet_2, Doublet const & doublet) {
        auto octet = Signature(triplet_1, triplet_2, doublet);
        octet.SetBdt(Bdt(octet, reader));
        return octet;
    });
    DEBUG(octets.size());
    return octets;
}

}

}
