# include "HeavyHiggsSemiTagger.hh"

heavyhiggs::HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_hadronic_reader_.set_tagger(top_hadronic_tagger);
    top_semi_reader_.set_tagger(top_semi_tagger);
    DefineVariables();
}

void heavyhiggs::HeavyHiggsSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

int heavyhiggs::HeavyHiggsSemiTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
      analysis::Jets HiggsParticles = event.Partons().GenParticles();
      analysis::Jets Even = analysis::RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
      analysis::Jets Odd = analysis::RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }
    std::vector<analysis::Triplet> triplets_semi = top_semi_reader_.Multiplets<analysis::TopSemiTagger>(event);
    Print(kDebug, "Number of Semi Tops", triplets_semi.size());

//     std::vector<Triplet> FinaltripletsSemi;
//     for (const auto tripletSemi : tripletsSemi) if (tripletSemi.singlet().pt() > pre_cuts / 2) FinaltripletsSemi.emplace_back(tripletSemi);

    std::vector<analysis::Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<analysis::TopHadronicTagger>(event);
    Print(kDebug, "Number of Hadronic Tops", triplets_hadronic.size());

    std::vector<analysis::Triplet> FinaltripletsHadronic;
    analysis::Jets TopParticles = event.Partons().GenParticles();
    int HadTopId = top_hadronic_tagger.TopHadronicId(event);
    TopParticles = analysis::RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    if (tag == kSignal) {
        for (const auto & triplet : triplets_hadronic) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) FinaltripletsHadronic.emplace_back(triplet);
    } else FinaltripletsHadronic = triplets_hadronic;
    Print(kDebug, "Number of truth Hadronic Tops", FinaltripletsHadronic.size());

    std::vector<analysis::Sextet > sextets;
    for (const auto & triplet_semi : triplets_semi)
        for (const auto & triplet_hadronic : FinaltripletsHadronic) {
          analysis::Sextet sextet(triplet_semi, triplet_hadronic);
            if (sextet.overlap()) continue;
            if (tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }

    std::size_t heavy_higgs_number = 1;
    if (tag == kSignal && sextets.size() > heavy_higgs_number) {
      std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsBoson));
        sextets.erase(sextets.begin() + heavy_higgs_number, sextets.end());
    }

    return SaveEntries<HeavyHiggsSemiBranch>(sextets);
}

std::vector<analysis::Sextet>  heavyhiggs::HeavyHiggsSemiTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  std::vector<analysis::Triplet> triplets_semi = top_semi_reader_.Multiplets<analysis::TopSemiTagger>(event);
  std::vector<analysis::Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<analysis::TopHadronicTagger>(event);
  std::vector<analysis::Sextet > sextets;
    for (const auto & triplet_semi : triplets_semi)
        for (const auto & triplet_hadronic : triplets_hadronic) {
          analysis::Sextet sextet(triplet_semi, triplet_hadronic);
            if (sextet.overlap()) continue;
            branch_ = branch<HeavyHiggsSemiBranch>(sextet);
            sextet.SetBdt(Bdt(reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}
