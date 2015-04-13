# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger()
{
//         DebugLevel = hanalysis::HObject::HDetailed;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HHeavyHiggsSemiTagger::SetTagger(
    const HBottomTagger &NewBottomTagger,
    const HWSemiTagger &NewWSemiTagger,
    const HWTagger &NewWTagger,
    const HTopSemiTagger &NewTopSemiTagger,
    const HTopHadronicTagger &NewTopHadronicTagger)
{
    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    DefineVariables();
}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("HeavyHiggsSemi");
    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaR, "DeltaR");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");

    AddObservable(Branch.Bdt, "Bdt");
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

std::vector< HHeavyHiggsSemiBranch> hanalysis::HHeavyHiggsSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    float Mass = Event.GetMass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == HSignal) {
        HJets HiggsParticles = Event.GetParticles()->Generator();
        HJets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
        HJets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
        HiggsParticles = Even;
        HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
        if (Tag == HSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
    Print(HDebug, "Number of Semi Tops", TripletsSemi.size());

//     std::vector<HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//     std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WTagger, WReader,BottomTagger,BottomReader);
    Print(HDebug, "Number of Hadronic Tops", TripletsHadronic.size());

    std::vector<HTriplet> FinalTripletsHadronic;
    int WHadId = WTagger.GetWHadId(Event);
    HJets TopParticles = Event.GetParticles()->Generator();
    int HadTopId = sgn(WHadId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, HadTopId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());
    if (Tag == HSignal) {
        for (const auto & Triplet : TripletsHadronic) if (Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) FinalTripletsHadronic.push_back(Triplet);
    } else FinalTripletsHadronic = TripletsHadronic;

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : FinalTripletsHadronic) {
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.DoubletJet()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Jet()) < DetectorGeometry.JetConeSize) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
            if (Tag == HSignal && Sextet.Jet().m() < Mass / 2)continue;
            if (Tag == HSignal && Sextet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == HSignal && Sextet.Jet().delta_R(HiggsBoson) > 2 * DetectorGeometry.JetConeSize) continue;
//             if (Tag == HBackground && Sextet.Jet().delta_R(HiggsBoson) < 2 * DetectorGeometry.JetConeSize) continue;
            Sextets.push_back(Sextet);
        }

    if (Tag == HSignal && Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsBoson));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }
//     if (Tag == HBackground && Sextets.size() > 0) Sextets.erase(Sextets.begin());

//     Print(HInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByMass(Mass));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsSemiBranch> HeavyHiggsBranches;
    for (auto & Sextet : Sextets) {
        Sextet.SetTag(Tag);
        HeavyHiggsBranches.push_back(GetBranch(Sextet));
    }

    return HeavyHiggsBranches;
}


hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &)
{
    Print(HInformation, "Get boosted Sextet Tag");

    return HSignal;
}


std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const HReader &Reader)
{

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.DoubletJet()) < DetectorGeometry.JetConeSize) continue;
            if (TripletSemi.Singlet().delta_R(TripletHadronic.Jet()) < DetectorGeometry.JetConeSize) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
            Branch = GetBranch(Sextet);
            Sextet.SetBdt(Reader.Bdt());
            Sextets.push_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(max_combi(), int(Sextets.size())), Sextets.end());
    return Sextets;
}

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const HReader &Reader, const int Mass)
{

  std::vector<HSextet > Sextets;
  for (const auto & TripletSemi : TripletsSemi)
    for (const auto & TripletHadronic : TripletsHadronic) {
      if (TripletSemi.Singlet().delta_R(TripletHadronic.Singlet()) < DetectorGeometry.JetConeSize) continue;
      if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
      if (TripletSemi.Singlet().delta_R(TripletHadronic.Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
      if (TripletSemi.Singlet().delta_R(TripletHadronic.DoubletJet()) < DetectorGeometry.JetConeSize) continue;
      if (TripletSemi.Singlet().delta_R(TripletHadronic.Jet()) < DetectorGeometry.JetConeSize) continue;
      HSextet Sextet(TripletSemi, TripletHadronic);
      if (Sextet.Jet().m() < Mass / 2)continue;
      if (Sextet.Jet().m() > Mass * 3 / 2)continue;
      Branch = GetBranch(Sextet);
      Sextet.SetBdt(Reader.Bdt());
      Sextets.push_back(Sextet);
    }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(max_combi(), int(Sextets.size())), Sextets.end());
    return Sextets;
}


