# include "HHeavyHiggsSemiTagger.hh"

analysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    DefineVariables();
}

void analysis::HHeavyHiggsSemiTagger::SetTagger(
    const BottomTagger &NewBottomTagger,
    const WSemiTagger &Neww_semi_tagger,
    const WHadronicTagger &NewWTagger,
    const TopSemiTagger &Newtop_semi_tagger,
    const TopHadronicTagger &Newtop_hadronic_tagger)
{
    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_semi_tagger = Newtop_semi_tagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    DefineVariables();
}

void analysis::HHeavyHiggsSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("HeavyHiggsSemi");
    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaR, "DeltaR");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

analysis::HHeavyHiggsSemiBranch analysis::HHeavyHiggsSemiTagger::GetBranch(const Sextet &sextet) const
{
    Print(kInformation, "FillPairTagger", sextet.Bdt());

    HHeavyHiggsSemiBranch HeavyHiggsBranch;
    HeavyHiggsBranch.Mass = sextet.Jet().m();
    HeavyHiggsBranch.Rap = sextet.Jet().rap();
    HeavyHiggsBranch.Phi = sextet.Jet().phi();
    HeavyHiggsBranch.Pt = sextet.Jet().pt();
    HeavyHiggsBranch.Ht = sextet.Ht();

    HeavyHiggsBranch.DeltaPt = sextet.DeltaPt();
    HeavyHiggsBranch.DeltaM = sextet.DeltaM();
    HeavyHiggsBranch.DeltaHt = sextet.DeltaHt();
    HeavyHiggsBranch.DeltaR = sextet.DeltaR();
    HeavyHiggsBranch.DeltaRap = sextet.DeltaRap();
    HeavyHiggsBranch.DeltaPhi = sextet.DeltaPhi();

    HeavyHiggsBranch.Bdt = sextet.Bdt();
    HeavyHiggsBranch.Tag = sextet.Tag();
    return HeavyHiggsBranch;
}

std::vector< analysis::HHeavyHiggsSemiBranch> analysis::HHeavyHiggsSemiTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag, const float pre_cut)
{
    Print(kInformation, "Get Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        Jets HiggsParticles = event.partons().Generator();
        Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
        Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (Tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = event.leptons().GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    Print(kDebug, "Number of Semi W", doubletsSemi.size());
    std::vector<Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    Print(kDebug, "Number of Semi Tops", tripletsSemi.size());

    std::vector<Triplet> FinaltripletsSemi;
    for (const auto tripletSemi : tripletsSemi) if (tripletSemi.singlet().pt() > pre_cut / 2) FinaltripletsSemi.emplace_back(tripletSemi);

//     std::vector<Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    Print(kDebug, "Number of Hadronic Tops", tripletsHadronic.size());

    std::vector<Triplet> FinaltripletsHadronic;
    int WHadId = WTagger.GetWHadId(event);
    Jets TopParticles = event.partons().Generator();
    int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    if (Tag == kSignal) {
        for (const auto & triplet : tripletsHadronic) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) FinaltripletsHadronic.emplace_back(triplet);
    } else FinaltripletsHadronic = tripletsHadronic;
    Print(kDebug, "Number of truth Hadronic Tops", FinaltripletsHadronic.size());

    std::vector<Sextet > sextets;
    for (const auto & tripletSemi : FinaltripletsSemi)
        for (const auto & tripletHadronic : FinaltripletsHadronic) {
            if (tripletSemi.singlet().delta_R(tripletHadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            Sextet sextet(tripletSemi, tripletHadronic);
            if (Tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == kSignal && sextet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
//             if (Tag == HBackground && sextet.Jet().delta_R(HiggsBoson) < 2 * detector_geometry().JetConeSize) continue;
            sextets.emplace_back(sextet);
        }

    if (Tag == kSignal && sextets.size() > 1) {
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsBoson));
        sextets.erase(sextets.begin() + 1, sextets.end());
    }
//     if (Tag == HBackground && sextets.size() > 0) sextets.erase(sextets.begin());

//     Print(kInformation, "Number of Heavy Higgses", sextets.size());

    if (Tag == kSignal && sextets.size() > 1) {
        Print(kInformation, "Higgs Candidates", sextets.size());
        std::sort(sextets.begin(), sextets.end(), SortByMass(Mass));
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<HHeavyHiggsSemiBranch> HeavyHiggsBranches;
    for (auto & sextet : sextets) {
        sextet.SetTag(Tag);
        HeavyHiggsBranches.emplace_back(GetBranch(sextet));
    }

    return HeavyHiggsBranches;
}


analysis::Object::Tag analysis::HHeavyHiggsSemiTagger::GetTag(const Sextet &)
{
    Print(kInformation, "Get boosted sextet Tag");

    return kSignal;
}


std::vector<analysis::Sextet>  analysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<Triplet> &tripletsSemi, const std::vector<Triplet> &tripletsHadronic, const Reader &Reader)
{

    std::vector<Sextet > sextets;
    for (const auto & tripletSemi : tripletsSemi)
        for (const auto & tripletHadronic : tripletsHadronic) {
            if (tripletSemi.singlet().delta_R(tripletHadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            Sextet sextet(tripletSemi, tripletHadronic);
            Branch = GetBranch(sextet);
            sextet.SetBdt(Reader.Bdt());
            sextets.emplace_back(sextet);
        }
    std::sort(sextets.begin(), sextets.end());
    sextets.erase(sextets.begin() + std::min(max_combi(), int(sextets.size())), sextets.end());
    return sextets;
}

std::vector<analysis::Sextet>  analysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<Triplet> &tripletsSemi, const std::vector<Triplet> &tripletsHadronic, const Reader &Reader, const int Mass)
{

    std::vector<Sextet > sextets;
    for (const auto & tripletSemi : tripletsSemi)
        for (const auto & tripletHadronic : tripletsHadronic) {
            if (tripletSemi.singlet().delta_R(tripletHadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            Sextet sextet(tripletSemi, tripletHadronic);
            if (sextet.Jet().m() < Mass / 2)continue;
            if (sextet.Jet().m() > Mass * 3 / 2)continue;
            Branch = GetBranch(sextet);
            sextet.SetBdt(Reader.Bdt());
            sextets.emplace_back(sextet);
        }
    std::sort(sextets.begin(), sextets.end());
    sextets.erase(sextets.begin() + std::min(max_combi(), int(sextets.size())), sextets.end());
    return sextets;
}


