#include "HeavyHiggsSemiTagger.hh"


namespace analysis
{

namespace heavyhiggs
{

HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
    Note();
    DefineVariables();
}

int HeavyHiggsSemiTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info();

    float Mass = event.mass();

    Jets HiggsBoson = Particle_Higgs(event, tag);

    std::vector<Triplet> FinaltripletsHadronic = FinalTriplet(event, tag, -1);
    std::vector<Triplet> FinaltripletsLeptonic = FinalTriplet(event, tag, 1);

    std::vector<Sextet > sextets;
    for (const auto & triplet_leptonic : FinaltripletsLeptonic)
        for (const auto & triplet_hadronic : FinaltripletsHadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap()) continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }

    return SaveEntries(BestMatches(sextets, HiggsBoson, tag));
}

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Sextet > sextets;
    for (const auto & triplet_leptonic : triplets_leptonic)
        for (const auto & triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_leptonic, triplet_hadronic);
            if (sextet.Overlap()) continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}
std::vector< Triplet > HeavyHiggsSemiTagger::FinalTriplet(const Event &event, const Tag tag, int charge) const
{
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_leptonic = top_leptonic_reader_.Multiplets(event);
    Jets TopQuarkHad = Particles_Top(event, -1);
    Jets TopQuarkLep = Particles_Top(event, 1);
    std::vector<Triplet> FinaltripletsHadronic;
    std::vector<Triplet> FinaltripletsLeptonic;
    FinaltripletsHadronic = BestMatches(triplets_hadronic, TopQuarkHad, tag);
    FinaltripletsLeptonic = BestMatches(triplets_leptonic, TopQuarkLep, tag);
    switch (charge) {
    case 1:
        return FinaltripletsLeptonic;
    case -1:
        return FinaltripletsHadronic;
        break;
    }
}
Jets HeavyHiggsSemiTagger::Particle_Higgs(const Event &event, const Tag tag) const
{
    Jets Higgs;
    if (tag == Tag::signal) {
        Jets HiggsParticles = event.Partons().GenParticles();
        Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, Id::heavy_higgs, Id::gluon);
        Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, Id::CP_odd_higgs, Id::gluon);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        Higgs = HiggsParticles;
    }
    return Higgs;
}
Jets HeavyHiggsSemiTagger::Particles_Top(const Event &event, int charge) const
{
    fastjet::PseudoJet top;
    Jets particles = event.Partons().GenParticles();
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    int lepton_charge;
    if (leptons.size() == 0) lepton_charge = 1;
    else {
        lepton_charge = leptons.at(0).user_info<JetInfo>().Charge();
        Info(lepton_charge);
    }
    Jets tops = CopyIfParticle(particles, to_int(Id::top) * lepton_charge * charge);

    Jets HardTops = CopyIfAbsMother(tops, Id::heavy_higgs);
    Jets Hardtop = CopyIfAbsMother(tops, Id::CP_odd_higgs);
    HardTops.insert(HardTops.end(), Hardtop.begin(), Hardtop.end());
    return HardTops;
}

}

}
