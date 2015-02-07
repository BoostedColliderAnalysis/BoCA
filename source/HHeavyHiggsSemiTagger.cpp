# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();
}

hanalysis::HHeavyHiggsSemiTagger::~HHeavyHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
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
    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

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

    JetTag.HeavyParticles = {HeavyHiggsId, CPOddHiggsId};
    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
    Print(HDebug, "Number of Semi Tops", TripletsSemi.size());

    std::vector<HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
    Print(HDebug, "Number of Hadronic Tops", TripletsHadronic.size());


    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet() == TripletHadronic.Singlet()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet1()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet2()) continue;
//             if (Tag == HSignal && TripletSemi.DeltaR() > 1.5) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
//             Sextet.SetTag(GetTag(Sextet));
//             if (Sextet.Tag() != Tag) continue;
//             if (Tag == HSignal && Sextet.Jet().m() < Mass / 2)continue;
//             if (Tag == HSignal && Sextet.DeltaPhi() < 1 )continue;
            Sextets.push_back(Sextet);
        }

    HJets HiggsParticles = Event.GetParticles()->GetGeneratorJets();
    HJets Even = HiggsParticles;
    Even.erase(std::remove_if(Even.begin(), Even.end(), WrongAbsFamily(HeavyHiggsId, GluonId)), Even.end());
    HJets Odd = HiggsParticles;
    Odd.erase(std::remove_if(Odd.begin(), Odd.end(), WrongAbsFamily(CPOddHiggsId, GluonId)), Odd.end());
    HiggsParticles=Even;
    HiggsParticles.insert(HiggsParticles.end(),Odd.begin(),Odd.end());
    if (HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsParticles.front()));
    if (Tag == HSignal && Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    if (Tag == HBackground && Sextets.size() > 0) Sextets.erase(Sextets.begin());




//     Print(HInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByMass(Mass));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsSemiBranch> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) HeavyHiggsBranches.push_back(GetBranch(Sextet));

    return HeavyHiggsBranches;
}


hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get boosted Sextet Tag");

    HJetInfo JetInfoB1 = Sextet.Triplet1().Singlet().user_info<HJetInfo>();
    JetInfoB1.ExtractFraction(TopId);
    HJetInfo JetInfoL = Sextet.Triplet1().Doublet().Singlet1().user_info<HJetInfo>();
    JetInfoL.ExtractFraction(TopId);
    HJetInfo JetInfoB2 = Sextet.Triplet2().Singlet().user_info<HJetInfo>();
    JetInfoB2.ExtractFraction(TopId);
    HJetInfo JetInfoW1 = Sextet.Triplet2().Doublet().Singlet1().user_info<HJetInfo>();
    JetInfoW1.ExtractFraction(TopId);
    HJetInfo JetInfoW2 = Sextet.Triplet2().Doublet().Singlet2().user_info<HJetInfo>();
    JetInfoW2.ExtractFraction(TopId);

    if (std::abs(JetInfoB1.MaximalId()) != TopId) return HBackground;
    if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return HBackground;

    if (std::abs(JetInfoL.MaximalId()) != TopId) return HBackground;
    if (sgn(JetInfoL.MaximalId()) != sgn(JetInfoB1.MaximalId())) return HBackground;

    if (std::abs(JetInfoW1.MaximalId()) != TopId) return HBackground;
    if (JetInfoW1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;
    if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB2.MaximalId())) return HBackground;

    return HSignal;
}


// hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet)
// {
//     Print(HInformation, "Get Sextet Tag");
//
//     HJetInfo JetInfoB1 = Sextet.Triplet1().GetSinglet().user_info<HJetInfo>();
//     JetInfoB1.ExtractFraction(BottomId);
//     HJetInfo JetInfoL = Sextet.Triplet1().GetDoublet().GetJet1().user_info<HJetInfo>();
//     JetInfoL.ExtractFraction(TopId);
//     HJetInfo JetInfoB2 = Sextet.Triplet2().GetSinglet().user_info<HJetInfo>();
//     JetInfoB2.ExtractFraction(BottomId);
//     HJetInfo JetInfoW1 = Sextet.Triplet2().GetDoublet().GetJet1().user_info<HJetInfo>();
//     JetInfoW1.ExtractFraction(WId);
//     HJetInfo JetInfoW2 = Sextet.Triplet2().GetDoublet().GetJet2().user_info<HJetInfo>();
//     JetInfoW2.ExtractFraction(WId);
//
//     if (std::abs(JetInfoB1.MaximalId()) != BottomId) return HBackground;
//     if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return HBackground;
//
//     if (std::abs(JetInfoL.MaximalId()) != TopId) return HBackground;
//     if (sgn(JetInfoL.MaximalId()) != sgn(JetInfoB1.MaximalId())) return HBackground;
//
//     if (std::abs(JetInfoW1.MaximalId()) != WId) return HBackground;
//     if (JetInfoW1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;
//     if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB2.MaximalId())) return HBackground;
//
//     return HSignal;
// }

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const HReader &Reader)
{

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet() == TripletHadronic.Singlet()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet1()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet2()) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
//             if (Sextet.GetSextetJet().m() < 0)continue;
            Branch = GetBranch(Sextet);
            Sextet.SetBdt(Reader.Bdt());
            Sextets.push_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(MaxCombi, int(Sextets.size())), Sextets.end());
    return Sextets;
}


