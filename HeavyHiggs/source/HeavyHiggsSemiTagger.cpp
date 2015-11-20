#include "HeavyHiggsSemiTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
  Info();
    DefineVariables();
}

int HeavyHiggsSemiTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    Jets higgs_boson = HiggsParticle(event, tag);
    std::vector<Triplet> triplets_hadronic = FinalTriplet(event, tag, TopProcess::hadronic);
    std::vector<Triplet> triplets_leptonic = FinalTriplet(event, tag, TopProcess::leptonic);
    std::vector<Sextet> sextets;
    for (const auto& triplet_leptonic : triplets_leptonic)
        for (const auto& triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap()) continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }
//     return SaveEntries(BestMatches(sextets, higgs_boson, tag));
    return SaveEntries(sextets, higgs_boson, tag, Id::empty);
}

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Sextet> sextets;
    for (const auto& triplet_leptonic : triplets_leptonic)
        for (const auto& triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap())
                continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}

std::vector<Triplet> HeavyHiggsSemiTagger::FinalTriplet(const Event& event, Tag tag, TopProcess top_process) const
{
    std::vector<Triplet> triplets;
    Jets tops;
    switch (top_process) {
      case TopProcess::leptonic:
        triplets = top_leptonic_reader_.Multiplets(event);
        tops = top_leptonic_reader_.Tagger().Particles(event);
        break;
      case TopProcess::hadronic:
        triplets = top_hadronic_reader_.Multiplets(event);
        tops = top_hadronic_reader_.Tagger().Particles(event);
        break;
    default:
        Error("not a charge");
    }
    return BestMatches(triplets, tops, tag);
}

Jets HeavyHiggsSemiTagger::HiggsParticle(const Event& event, Tag tag)
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    Jets odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return  Join(even, odd);
}

}

}
