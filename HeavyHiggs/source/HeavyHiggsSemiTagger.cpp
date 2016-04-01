#include "HeavyHiggsSemiTagger.hh"
#include "Event.hh"
#include "multiplets/Particles.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int HeavyHiggsSemiTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    std::vector<Particle> higgs_boson = HiggsParticle(event, tag);
    std::vector<Triplet> triplets_hadronic = FinalTriplet(event, tag, Decay::hadronic);
    std::vector<Triplet> triplets_leptonic = FinalTriplet(event, tag, Decay::leptonic);
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

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
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

std::vector<Triplet> HeavyHiggsSemiTagger::FinalTriplet(Event const& event, Tag tag, Decay decay) const
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
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    std::vector<Particle> odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return  Combine(even, odd);
}

std::string HeavyHiggsSemiTagger::Name() const
{
    return "HeavyHiggsSemi";
}

}

}
