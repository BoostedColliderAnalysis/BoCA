# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger()
{
//         DebugLevel = hanalysis::HObject::HDetailed;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HHeavyHiggsSemiTagger::SetTagger(
    const BottomTagger &NewBottomTagger,
    const HWSemiTagger &NewWSemiTagger,
    const HWHadronicTagger &NewWTagger,
    const HTopSemiTagger &NewTopSemiTagger,
    const HTopHadronicTagger &NewTopHadronicTagger)
{
    Print(HNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    DefineVariables();
}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
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

    Print(HNotification, "Variables defined");

}

HHeavyHiggsSemiBranch hanalysis::HHeavyHiggsSemiTagger::GetBranch(const HSextet &Sextet) const
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());

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
    Print(HInformation, "Get Higgs Tags");

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
            else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    Print(HDebug, "Number of Semi W", DoubletsSemi.size());
    std::vector<HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, jets, TopSemiReader);
    Print(HDebug, "Number of Semi Tops", TripletsSemi.size());

    std::vector<HTriplet> FinalTripletsSemi;
    for (const auto TripletSemi : TripletsSemi) if (TripletSemi.Singlet().pt() > pre_cut / 2) FinalTripletsSemi.emplace_back(TripletSemi);

//     std::vector<HDoublet> DoubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, jets, TopHadronicReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    Print(HDebug, "Number of Hadronic Tops", TripletsHadronic.size());

    std::vector<HTriplet> FinalTripletsHadronic;
    int WHadId = WTagger.GetWHadId(Event);
    Jets TopParticles = Event.GetParticles()->Generator();
    int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());
    if (Tag == kSignal) {
        for (const auto & Triplet : TripletsHadronic) if (Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) FinalTripletsHadronic.emplace_back(Triplet);
    } else FinalTripletsHadronic = TripletsHadronic;
    Print(HDebug, "Number of truth Hadronic Tops", FinalTripletsHadronic.size());

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : FinalTripletsSemi)
        for (const auto & TripletHadronic : FinalTripletsHadronic) {
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Singlet()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.DoubletJet()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
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

//     Print(HInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == kSignal && Sextets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Sextets.size());
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
    Print(HInformation, "Get boosted Sextet Tag");

    return kSignal;
}


std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const Reader &Reader)
{

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Singlet()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.DoubletJet()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
            Branch = GetBranch(Sextet);
            Sextet.SetBdt(Reader.Bdt());
            Sextets.emplace_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(max_combi(), int(Sextets.size())), Sextets.end());
    return Sextets;
}

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const Reader &Reader, const int Mass)
{

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Singlet()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.DoubletJet()) < detector_geometry().JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Jet()) < detector_geometry().JetConeSize) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
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


