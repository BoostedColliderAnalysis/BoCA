#include "HeavyHiggsSemiTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace heavyhiggs {

HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
  Info();
    DefineVariables();
}

int HeavyHiggsSemiTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    Jets higgs_boson = HiggsParticle(event, tag);
    std::vector<Triplet> triplets_hadronic = FinalTriplet(event, tag, Decay::hadronic);
    std::vector<Triplet> triplets_leptonic = FinalTriplet(event, tag, Decay::leptonic);
    std::vector<Sextet> sextets;
    for (auto const& triplet_leptonic : triplets_leptonic)
        for (auto const& triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap())
                continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }
//     Error(sextets.size(), triplets_hadronic.size(), triplets_leptonic.size());
    return SaveEntries(BestMatches(sextets, higgs_boson, tag));
}

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Sextet> sextets;
    for (auto const& triplet_leptonic : triplets_leptonic)
        for (auto const& triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap())
                continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}

std::vector<Triplet> HeavyHiggsSemiTagger::FinalTriplet(Event const& event, Tag tag, Decay decay) const
{
    std::vector<Triplet> triplets;
    switch (decay) {
      case Decay::leptonic:
        triplets = top_leptonic_reader_.Multiplets(event);
        break;
      case Decay::hadronic:
        triplets = top_hadronic_reader_.Multiplets(event);
        break;
    }
//     Error(triplets.size());
    Jets tops = TopParticles(event, decay);
    return BestMatches(triplets, tops, tag);
}

Jets HeavyHiggsSemiTagger::HiggsParticle(Event const& event, Tag tag) const
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    Jets odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return  Join(even, odd);
}

Jets HeavyHiggsSemiTagger::TopParticles(Event const& event, Decay decay) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    int lepton_charge = leptons.empty() ? 1 : leptons.at(0).user_info<JetInfo>().Charge();
    Info(lepton_charge);
    switch (decay) {
      case Decay::leptonic: break;
      case Decay::hadronic: lepton_charge *= -1;
        break;
    }
    Jets tops = CopyIfExactParticle(particles, to_int(Id::top) * lepton_charge);
    Jets tops_even = CopyIfMother(tops, Id::heavy_higgs);
    Jets tops_odd = CopyIfMother(tops, Id::CP_odd_higgs);
    return Join(tops_even, tops_odd);
}

}

}
