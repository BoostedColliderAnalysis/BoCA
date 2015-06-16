# include "HeavyHiggsSemiTagger.hh"

namespace analysis
{

namespace heavyhiggs
{

HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
//         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_hadronic_reader_.set_tagger(top_hadronic_tagger);
    top_semi_reader_.set_tagger(top_semi_tagger);
    DefineVariables();
}

int HeavyHiggsSemiTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
        Jets HiggsParticles = event.Partons().GenParticles();
        Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
        Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets<TopSemiTagger>(event);
    Print(kDebug, "Number of Semi Tops", triplets_semi.size());

//     std::vector<Triplet> FinaltripletsSemi;
//     for (const auto tripletSemi : tripletsSemi) if (tripletSemi.singlet().pt() > pre_cuts / 2) FinaltripletsSemi.emplace_back(tripletSemi);

    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    Print(kDebug, "Number of Hadronic Tops", triplets_hadronic.size());

    std::vector<Triplet> FinaltripletsHadronic;
    Jets TopParticles = event.Partons().GenParticles();
    int HadTopId = top_hadronic_tagger.TopHadronicId(event);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    if (tag == kSignal) {
        for (const auto & triplet : triplets_hadronic) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) FinaltripletsHadronic.emplace_back(triplet);
    } else FinaltripletsHadronic = triplets_hadronic;
    Print(kDebug, "Number of truth Hadronic Tops", FinaltripletsHadronic.size());

    std::vector<Sextet > sextets;
    for (const auto & triplet_semi : triplets_semi)
        for (const auto & triplet_hadronic : FinaltripletsHadronic) {
            Sextet sextet(triplet_semi, triplet_hadronic);
            if (sextet.Overlap()) continue;
            if (tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }

    std::size_t heavy_higgs_number = 1;
    if (tag == kSignal && sextets.size() > heavy_higgs_number) {
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsBoson));
        sextets.erase(sextets.begin() + heavy_higgs_number, sextets.end());
    }

    return SaveEntries(sextets);
}

std::vector<Sextet>  HeavyHiggsSemiTagger::Multiplets(Event &event, const TMVA::Reader &reader)
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
