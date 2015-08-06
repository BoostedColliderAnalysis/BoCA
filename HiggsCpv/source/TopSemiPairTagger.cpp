#include "TopSemiPairTagger.hh"
#include "Predicate.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace higgscpv {

TopSemiPairTagger::TopSemiPairTagger()
{
  Info();
    DefineVariables();
}

int TopSemiPairTagger::Train(const analysis::Event& event, const analysis::PreCuts&, Tag tag) const
{
    Info();
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    Jets top_particles = event.Partons().GenParticles();
    top_particles = CopyIfParticle(top_particles, Id::top);
    if (top_particles.size() != 2 && tag == Tag::signal) Error(top_particles.size());
    std::vector<Triplet> final_triplets_hadronic;
    switch (tag) {
    case Tag::signal :
        for (const auto& triplet : triplets_hadronic) if (Close(top_particles.front())(triplet.Jet())) final_triplets_hadronic.emplace_back(triplet);
        break;
    case Tag::background      :
        final_triplets_hadronic = triplets_hadronic;
        break;
    }
    std::vector<Triplet> final_triplets_leptonic;
    switch (tag) {
    case Tag::signal :
        for (const auto& triplet : triplets_leptonic) if (Close(top_particles.front())(triplet.Jet())) final_triplets_leptonic.emplace_back(triplet);
        break;
    case Tag::background :
        final_triplets_leptonic = triplets_leptonic;
        break;
    }
    std::vector<Sextet> sextets;
    for (const auto& triplet_hadronic : final_triplets_hadronic)
        for (const auto& triplet_leptonic : final_triplets_leptonic) {
            Sextet sextet(triplet_hadronic, triplet_leptonic);
            if (sextet.Overlap()) continue;
            sextets.emplace_back(sextet);
        }
    Debug(sextets.size());
    if (tag == Tag::signal && sextets.size() > 1) {
        sextets = SortedByMaxDeltaRap(sextets);
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }
    return SaveEntries(sextets);
}

std::vector<Sextet> TopSemiPairTagger::Multiplets(const Event& event, const TMVA::Reader& reader) const
{
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Sextet>  sextets;
    for (const auto& triplet_hadronic : triplets_hadronic)
        for (const auto& triplet_leptonic : triplets_leptonic)  {
            Sextet sextet(triplet_hadronic, triplet_leptonic);
            if (sextet.Overlap()) continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}

}

}
