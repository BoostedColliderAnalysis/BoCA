# include "HeavyHiggsSemiTagger.hh"

analysis::HeavyHiggsSemiTagger::HeavyHiggsSemiTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_hadronic_reader_.set_tagger(top_hadronic_tagger);
    top_semi_reader_.set_tagger(top_semi_tagger);
    DefineVariables();
}

// void analysis::HeavyHiggsSemiTagger::SetTagger(
//     const BottomTagger &NewBottomTagger,
//     const WSemiTagger &Neww_semi_tagger,
//     const WHadronicTagger &NewWTagger,
//     const TopSemiTagger &Newtop_semi_tagger,
//     const TopHadronicTagger &Newtop_hadronic_tagger)
// {
//     Print(kNotification, "Constructor");

//     bottom_tagger_ = NewBottomTagger;
//     w_semi_tagger = Neww_semi_tagger;
//     WTagger = NewWTagger;
//     top_semi_tagger = Newtop_semi_tagger;
//     top_hadronic_tagger = Newtop_hadronic_tagger;
//     DefineVariables();
// }

void analysis::HeavyHiggsSemiTagger::DefineVariables()
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

analysis::HeavyHiggsSemiBranch analysis::HeavyHiggsSemiTagger::GetBranch(const Sextet &sextet) const
{
    Print(kInformation, "FillPairTagger", sextet.Bdt());
    HeavyHiggsSemiBranch branch;
    branch.Fill(sextet);
    return branch;
}

int analysis::HeavyHiggsSemiTagger::Train(analysis::Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Get Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
        Jets HiggsParticles = event.partons().Generator();
        Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
        Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }
    std::vector<Triplet> triplets_semi = static_cast<TopSemiTagger &>(top_semi_reader_.tagger()).GetTriplets(event, top_semi_reader_.reader());
    Print(kDebug, "Number of Semi Tops", triplets_semi.size());

//     std::vector<Triplet> FinaltripletsSemi;
//     for (const auto tripletSemi : tripletsSemi) if (tripletSemi.singlet().pt() > pre_cuts / 2) FinaltripletsSemi.emplace_back(tripletSemi);

    std::vector<Triplet> triplets_hadronic = static_cast<TopHadronicTagger &>(top_hadronic_reader_.tagger()).GetTriplets(event, top_hadronic_reader_.reader());
    Print(kDebug, "Number of Hadronic Tops", triplets_hadronic.size());

    std::vector<Triplet> FinaltripletsHadronic;
    Jets TopParticles = event.partons().Generator();
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
    for (const auto & tripletSemi : triplets_semi)
        for (const auto & triplet_hadronic : FinaltripletsHadronic) {
            if (tripletSemi.singlet().delta_R(triplet_hadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.Jet()) < detector_geometry().JetConeSize) continue;
            Sextet sextet(tripletSemi, triplet_hadronic);
            if (tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            if (tag == kSignal && sextet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
//             if (Tag == HBackground && sextet.Jet().delta_R(HiggsBoson) < 2 * detector_geometry().JetConeSize) continue;
        sextet.SetTag(tag);
            sextets.emplace_back(sextet);
        }

    if (tag == kSignal && sextets.size() > 1) {
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsBoson));
        sextets.erase(sextets.begin() + 1, sextets.end());
    }
//     if (Tag == HBackground && sextets.size() > 0) sextets.erase(sextets.begin());

//     Print(kInformation, "Number of Heavy Higgses", sextets.size());

    if (tag == kSignal && sextets.size() > 1) {
        Print(kInformation, "Higgs Candidates", sextets.size());
        std::sort(sextets.begin(), sextets.end(), SortByMass(Mass));
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    return SaveEntries(sextets);

}

std::vector<analysis::Sextet>  analysis::HeavyHiggsSemiTagger::Sextets(Event &event, const TMVA::Reader &reader)
{
  std::vector<Triplet> triplets_semi = static_cast<TopSemiTagger&>(top_semi_reader_.tagger()).GetTriplets(event,top_semi_reader_.reader());
  std::vector<Triplet> triplets_hadronic = static_cast<TopHadronicTagger&>(top_hadronic_reader_.tagger()).GetTriplets(event,top_hadronic_reader_.reader());
    std::vector<Sextet > sextets;
    for (const auto & triplet_semi : triplets_semi)
        for (const auto & triplet_hadronic : triplets_hadronic) {
            if (triplet_semi.singlet().delta_R(triplet_hadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (triplet_semi.singlet().delta_R(triplet_hadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (triplet_semi.singlet().delta_R(triplet_hadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (triplet_semi.singlet().delta_R(triplet_hadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (triplet_semi.singlet().delta_R(triplet_hadronic.Jet()) < detector_geometry().JetConeSize) continue;
            Sextet sextet(triplet_semi, triplet_hadronic);
            branch_ = GetBranch(sextet);
            sextet.SetBdt(Bdt(reader));
            sextets.emplace_back(sextet);
        }
    std::sort(sextets.begin(), sextets.end());
    sextets.erase(sextets.begin() + std::min(max_combi(), int(sextets.size())), sextets.end());
    return sextets;
}

std::vector<analysis::Sextet>  analysis::HeavyHiggsSemiTagger::GetBdt(const std::vector<Triplet> &tripletsSemi, const std::vector<Triplet> &tripletsHadronic, const Reader &Reader, const int Mass)
{

    std::vector<Sextet > sextets;
    for (const auto & tripletSemi : tripletsSemi)
        for (const auto & triplet_hadronic : tripletsHadronic) {
            if (tripletSemi.singlet().delta_R(triplet_hadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(triplet_hadronic.Jet()) < detector_geometry().JetConeSize) continue;
            Sextet sextet(tripletSemi, triplet_hadronic);
            if (sextet.Jet().m() < Mass / 2)continue;
            if (sextet.Jet().m() > Mass * 3 / 2)continue;
            branch_ = GetBranch(sextet);
            sextet.SetBdt(Reader.Bdt());
            sextets.emplace_back(sextet);
        }
    std::sort(sextets.begin(), sextets.end());
    sextets.erase(sextets.begin() + std::min(max_combi(), int(sextets.size())), sextets.end());
    return sextets;
}


