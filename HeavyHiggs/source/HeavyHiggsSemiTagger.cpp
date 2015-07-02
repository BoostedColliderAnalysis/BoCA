#include "HeavyHiggsSemiTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
    Note();
    set_tagger_name("HeavyHiggsSemi");
    top_hadronic_reader_.SetTagger(top_hadronic_tagger);
    top_semi_reader_.SetTagger(top_semi_tagger);
    DefineVariables();
}

int HeavyHiggsSemiTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == Tag::signal) {
        Jets HiggsParticles = event.Partons().GenParticles();
        Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, Id::heavy_higgs, Id::gluon);
        Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, Id::CP_odd_higgs, Id::gluon);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (tag == Tag::signal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Error("Where is the Higgs?", HiggsParticles.size());
        }
    }
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets<TopSemiTagger>(event);
    Debug("Number of Semi Tops", triplets_semi.size());

//     std::vector<Triplet> FinaltripletsSemi;
//     for (const auto tripletSemi : tripletsSemi) if (tripletSemi.singlet().pt() > pre_cuts / 2) FinaltripletsSemi.emplace_back(tripletSemi);

    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    Debug("Number of Hadronic Tops", triplets_hadronic.size());

    std::vector<Triplet> FinaltripletsHadronic;
    Jets TopParticles = event.Partons().GenParticles();
    int TopHadId = top_hadronic_tagger.TopHadronicId(event);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopHadId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Error("Where is the Top?", TopParticles.size());
    if (tag == Tag::signal) {
      for (const auto & triplet : triplets_hadronic) if (triplet.Jet().delta_R(TopQuark) < DetectorGeometry().JetConeSize) FinaltripletsHadronic.emplace_back(triplet);
    } else FinaltripletsHadronic = triplets_hadronic;
    Debug("Number of truth Hadronic Tops", FinaltripletsHadronic.size());

    std::vector<Sextet > sextets;
    for (const auto & triplet_semi : triplets_semi)
        for (const auto & triplet_hadronic : FinaltripletsHadronic) {
            Sextet sextet(triplet_semi, triplet_hadronic);
            if (sextet.Overlap()) continue;
            if (tag == Tag::signal && sextet.Jet().m() < Mass / 2)continue;
            if (tag == Tag::signal && sextet.Jet().m() > Mass * 3 / 2)continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }

    std::size_t heavy_higgs_number = 1;
    if (tag == Tag::signal && sextets.size() > heavy_higgs_number) {
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsBoson));
        sextets.erase(sextets.begin() + heavy_higgs_number, sextets.end());
    }

    return SaveEntries(sextets);
}

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets<TopSemiTagger>(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector<Sextet > sextets;
    for (const auto & triplet_semi : triplets_semi)
        for (const auto & triplet_hadronic : triplets_hadronic) {
            Sextet sextet(triplet_semi, triplet_hadronic);
            if (sextet.Overlap()) continue;
            sextet.SetBdt(Bdt(sextet, reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}

}

}
