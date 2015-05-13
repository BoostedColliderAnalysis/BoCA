# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger()
{
//         DebugLevel = hanalysis::HObject::kDetailed;
    Print(kNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HHeavyHiggsSemiTagger::SetTagger(
    const BottomTagger &NewBottomTagger,
    const HWSemiTagger &NewWSemiTagger,
    const WHadronicTagger &NewWTagger,
    const HTopSemiTagger &NewTopSemiTagger,
    const TopHadronicTagger &Newtop_hadronic_tagger)
{
    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    DefineVariables();
}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
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

HHeavyHiggsSemiBranch hanalysis::HHeavyHiggsSemiTagger::GetBranch(const HSextet &Sextet) const
{
    Print(kInformation, "FillPairTagger", Sextet.Bdt());

    HHeavyHiggsSemiBranch HeavyHiggsBranch;
    HeavyHiggsBranch.Mass = Sextet.Jet().m();
    HeavyHiggsBranch.Rap = Sextet.Jet().rap();
    HeavyHiggsBranch.Phi = Sextet.Jet().phi();
    HeavyHiggsBranch.Pt = Sextet.Jet().pt();
    HeavyHiggsBranch.Ht = Sextet.Ht();

    HeavyHiggsBranch.DeltaPt = Sextet.DeltaPt();
    HeavyHiggsBranch.DeltaM = Sextet.DeltaM();
    HeavyHiggsBranch.DeltaHt = Sextet.DeltaHt();
    HeavyHiggsBranch.DeltaR = Sextet.DeltaR();
    HeavyHiggsBranch.DeltaRap = Sextet.DeltaRap();
    HeavyHiggsBranch.DeltaPhi = Sextet.DeltaPhi();

    HeavyHiggsBranch.Bdt = Sextet.Bdt();
    HeavyHiggsBranch.Tag = Sextet.Tag();
    return HeavyHiggsBranch;
}

std::vector< HHeavyHiggsSemiBranch> hanalysis::HHeavyHiggsSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const float pre_cut)
{
    Print(kInformation, "Get Higgs Tags");

    float Mass = Event.GetMass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        Jets HiggsParticles = Event.GetParticles()->Generator();
        Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
        Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (Tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    Print(kDebug, "Number of Semi W", doubletsSemi.size());
    std::vector<Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    Print(kDebug, "Number of Semi Tops", tripletsSemi.size());

    std::vector<Triplet> FinaltripletsSemi;
    for (const auto tripletSemi : tripletsSemi) if (tripletSemi.singlet().pt() > pre_cut / 2) FinaltripletsSemi.emplace_back(tripletSemi);

//     std::vector<Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    Print(kDebug, "Number of Hadronic Tops", tripletsHadronic.size());

    std::vector<Triplet> FinaltripletsHadronic;
    int WHadId = WTagger.GetWHadId(Event);
    Jets TopParticles = Event.GetParticles()->Generator();
    int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    if (Tag == kSignal) {
        for (const auto & triplet : tripletsHadronic) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) FinaltripletsHadronic.emplace_back(triplet);
    } else FinaltripletsHadronic = tripletsHadronic;
    Print(kDebug, "Number of truth Hadronic Tops", FinaltripletsHadronic.size());

    std::vector<HSextet > Sextets;
    for (const auto & tripletSemi : FinaltripletsSemi)
        for (const auto & tripletHadronic : FinaltripletsHadronic) {
            if (tripletSemi.singlet().delta_R(tripletHadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            HSextet Sextet(tripletSemi, tripletHadronic);
            if (Tag == kSignal && Sextet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && Sextet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == kSignal && Sextet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
//             if (Tag == HBackground && Sextet.Jet().delta_R(HiggsBoson) < 2 * detector_geometry().JetConeSize) continue;
            Sextets.emplace_back(Sextet);
        }

    if (Tag == kSignal && Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end(), MinDeltaRTo(HiggsBoson));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }
//     if (Tag == HBackground && Sextets.size() > 0) Sextets.erase(Sextets.begin());

//     Print(kInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == kSignal && Sextets.size() > 1) {
        Print(kInformation, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByMass(Mass));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsSemiBranch> HeavyHiggsBranches;
    for (auto & Sextet : Sextets) {
        Sextet.SetTag(Tag);
        HeavyHiggsBranches.emplace_back(GetBranch(Sextet));
    }

    return HeavyHiggsBranches;
}


hanalysis::HObject::Tag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &)
{
    Print(kInformation, "Get boosted Sextet Tag");

    return kSignal;
}


std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<Triplet> &tripletsSemi, const std::vector<Triplet> &tripletsHadronic, const Reader &Reader)
{

    std::vector<HSextet > Sextets;
    for (const auto & tripletSemi : tripletsSemi)
        for (const auto & tripletHadronic : tripletsHadronic) {
            if (tripletSemi.singlet().delta_R(tripletHadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            HSextet Sextet(tripletSemi, tripletHadronic);
            Branch = GetBranch(Sextet);
            Sextet.SetBdt(Reader.Bdt());
            Sextets.emplace_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(max_combi(), int(Sextets.size())), Sextets.end());
    return Sextets;
}

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<Triplet> &tripletsSemi, const std::vector<Triplet> &tripletsHadronic, const Reader &Reader, const int Mass)
{

    std::vector<HSextet > Sextets;
    for (const auto & tripletSemi : tripletsSemi)
        for (const auto & tripletHadronic : tripletsHadronic) {
            if (tripletSemi.singlet().delta_R(tripletHadronic.singlet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.doublet_jet()) < detector_geometry().JetConeSize) continue;
            if (tripletSemi.singlet().delta_R(tripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            HSextet Sextet(tripletSemi, tripletHadronic);
            if (Sextet.Jet().m() < Mass / 2)continue;
            if (Sextet.Jet().m() > Mass * 3 / 2)continue;
            Branch = GetBranch(Sextet);
            Sextet.SetBdt(Reader.Bdt());
            Sextets.emplace_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(max_combi(), int(Sextets.size())), Sextets.end());
    return Sextets;
}


