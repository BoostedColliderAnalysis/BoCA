#include "boca/multiplets/Sort.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"

#include "include/tagger/TopSemiPair.hh"

#include "boca/generic/DEBUG.hh"

namespace higgscpv
{

namespace tagger
{

int TopSemiPair::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    auto triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    auto top_particles = event.GenParticles();
    top_particles = CopyIfParticle(top_particles, Id::top);
    if (top_particles.size() != 2 && tag == Tag::signal) ERROR(top_particles.size());
    std::vector<Triplet> final_triplets_hadronic;
    switch (tag) {
    case Tag::signal :
        for (auto const & triplet : triplets_hadronic) if (Close<boca::Jet>(top_particles.front())(triplet)) final_triplets_hadronic.emplace_back(triplet);
        break;
    case Tag::background      :
        final_triplets_hadronic = triplets_hadronic;
        break;
    }
    std::vector<Triplet> final_triplets_leptonic;
    switch (tag) {
    case Tag::signal :
        for (auto const & triplet : triplets_leptonic) if (Close<boca::Jet>(top_particles.front())(triplet)) final_triplets_leptonic.emplace_back(triplet);
        break;
    case Tag::background :
        final_triplets_leptonic = triplets_leptonic;
        break;
    }
    std::vector<Sextet> sextets;
    for (auto const & triplet_hadronic : final_triplets_hadronic)
        for (auto const & triplet_leptonic : final_triplets_leptonic) {
            Sextet sextet(triplet_hadronic, triplet_leptonic);
            if (sextet.Overlap()) continue;
            sextets.emplace_back(sextet);
        }
    DEBUG(sextets.size());
    if (tag == Tag::signal && sextets.size() > 1) {
        sextets = SortedByMaxDeltaRap(sextets);
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }
    return SaveEntries(sextets);
}

std::vector<Sextet> TopSemiPair::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    auto triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    auto triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Sextet>  sextets;
    for (auto const & triplet_hadronic : triplets_hadronic)
        for (auto const & triplet_leptonic : triplets_leptonic)  {
            Sextet sextet(triplet_hadronic, triplet_leptonic);
            if (sextet.Overlap()) continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return sextets;
}
std::string TopSemiPair::Name() const
{
    return "TopSemiPair";
}

}

}
