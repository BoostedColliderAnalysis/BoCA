#include "HeavyHiggsSemiTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
    Note();
    DefineVariables();
}

int HeavyHiggsSemiTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    Jets higgs_boson = HiggsParticle(event, tag);
    std::vector<Triplet> triplets_hadronic = FinalTriplet(event, tag, -1);
    std::vector<Triplet> triplets_leptonic = FinalTriplet(event, tag, 1);
    std::vector<Sextet> sextets;
    for (const auto& triplet_leptonic : triplets_leptonic)
        for (const auto& triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap())
                continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }
//     Error(sextets.size(), triplets_hadronic.size(), triplets_leptonic.size());
    return SaveEntries(BestMatches(sextets, higgs_boson, tag));
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

std::vector<Triplet> HeavyHiggsSemiTagger::FinalTriplet(const Event& event, Tag tag, int charge) const
{
    std::vector<Triplet> triplets;
    switch (charge) {
    case 1:
        triplets = top_leptonic_reader_.Multiplets(event);
        break;
    case -1:
        triplets = top_hadronic_reader_.Multiplets(event);
        break;
    default:
        Error("not a charge");
    }
//     Error(triplets.size());
    Jets tops = TopParticles(event, charge);
    return BestMatches(triplets, tops, tag);
}

Jets HeavyHiggsSemiTagger::HiggsParticle(const Event& event, Tag tag) const
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    Jets odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return  Join(even, odd);
}

Jets HeavyHiggsSemiTagger::TopParticles(const Event& event, int charge) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    int lepton_charge = 1;
    if (!leptons.empty()) lepton_charge = leptons.at(0).user_info<JetInfo>().Charge();
    Info(lepton_charge);
    Jets tops = CopyIfExactParticle(particles, to_int(Id::top) * lepton_charge * charge);
    Jets tops_even = CopyIfMother(tops, Id::heavy_higgs);
    Jets tops_odd = CopyIfMother(tops, Id::CP_odd_higgs);
    return Join(tops_even, tops_odd);
}

}

}
