#include "boca/HeavyHiggsSemiTagger.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int HeavyHiggsSemiTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto higgs_boson = HiggsParticle(event, tag);
    auto triplets_hadronic = FinalTriplet(event, tag, Decay::hadronic);
    auto triplets_leptonic = FinalTriplet(event, tag, Decay::leptonic);
    std::vector<Sextet> sextets;
    for (auto const & triplet_leptonic : triplets_leptonic)
        for (auto const & triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap()) continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }
    return SaveEntries(sextets, higgs_boson, tag);
}

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    auto triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    auto triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Sextet> sextets;
    for (auto const & triplet_leptonic : triplets_leptonic)
        for (auto const & triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap())
                continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return sextets;
}

std::vector<Triplet> HeavyHiggsSemiTagger::FinalTriplet(Event const& event, Tag tag, Decay decay)
{
    std::vector<Triplet> triplets;
    std::vector<Particle> tops;
    switch (decay) {
    case Decay::leptonic:
        triplets = top_leptonic_reader_.Multiplets(event);
        tops = top_leptonic_reader_.Particles(event);
        break;
    case Decay::hadronic:
        triplets = top_hadronic_reader_.Multiplets(event);
        tops = top_hadronic_reader_.Particles(event);
        break;
    }
    return BestMatches(triplets, tops, tag);
}

std::vector<Particle> HeavyHiggsSemiTagger::HiggsParticle(Event const& event, Tag tag)
{
    if (tag == Tag::background) return std::vector<Particle> {};
    auto particles = event.GenParticles();
    auto even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    auto odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return  Combine(even, odd);
}

std::string HeavyHiggsSemiTagger::Name() const
{
    return "HeavyHiggsSemi";
}

}

}
