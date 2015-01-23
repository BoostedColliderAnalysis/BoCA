# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger(
    hanalysis::HBottomTagger *const NewBottomTagger,
    hanalysis::HWSemiTagger *const NewWSemiTagger,
    hanalysis::HWTagger *const NewWTagger,
    hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new HReader(WSemiTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new HReader(TopSemiTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    SetTaggerName("HeavyHiggsSemi");

    Branch = new HHeavyHiggsSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsSemiTagger::~HHeavyHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
//     delete BottomReader;
//     delete WReader;
    delete WSemiReader;
    delete TopHadronicReader;
    delete TopSemiReader;

}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(HHeavyHiggsSemiBranch *HeavyHiggsBranch, const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());

    HeavyHiggsBranch->Mass = Sextet.Jet().m();
    HeavyHiggsBranch->Rap = Sextet.Jet().rap();
    HeavyHiggsBranch->Phi = Sextet.Jet().phi();
    HeavyHiggsBranch->Pt = Sextet.Jet().pt();
    HeavyHiggsBranch->Ht = Sextet.Ht();

    HeavyHiggsBranch->DeltaPt = Sextet.DeltaPt();
    HeavyHiggsBranch->DeltaR = Sextet.DeltaR();
    HeavyHiggsBranch->DeltaRap = Sextet.DeltaRap();
    HeavyHiggsBranch->DeltaPhi = Sextet.DeltaPhi();

    HeavyHiggsBranch->Bdt = Sextet.Bdt();
    HeavyHiggsBranch->Tag = Sextet.Tag();

}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(const hanalysis::HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());
    FillBranch(Branch, Sextet);
}


// struct SortSextetByMass {
//     inline bool operator()(const hanalysis::HSextet &Sextet1, const hanalysis::HSextet &Sextet2) {
//         return (Sextet1.GetSextetJet().m() > Sextet2.GetSextetJet().m());
//     }
// };

// struct SortSextetByMass {
//     SortSextetByMass(float NewMass) {
//         this->Mass = NewMass;
//     }
//     inline bool operator()(const hanalysis::HSextet &Sextet1, const hanalysis::HSextet &Sextet2) {
//         if (Sextet1.Jet().m() != Sextet2.Jet().m()) return std::abs(Sextet1.Jet().m() - Mass) < std::abs(Sextet2.Jet().m() - Mass);
//         else return Sextet1.Bdt() > Sextet2.Bdt();
//     }
//     float Mass;
// };

std::vector< HHeavyHiggsSemiBranch * > hanalysis::HHeavyHiggsSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    float Mass = Event->GetMass();

    JetTag->HeavyParticles = {TopId, HeavyHiggsId, CPOddHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = TopHadronicTagger->WTagger->BottomTagger->GetBdt(Jets, TopHadronicTagger->WTagger->BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets, MissingEt, TopSemiReader);
    Print(HDebug, "Number of Semi Tops", TripletsSemi.size());

    std::vector<HDoublet> DoubletsHadronic = TopHadronicTagger->WTagger->GetBdt(Jets, TopHadronicTagger->WReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
    Print(HDebug, "Number of Hadronic Tops", TripletsHadronic.size());


    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet() == TripletHadronic.Singlet()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet1()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet2()) continue;
            if (Tag == HSignal && TripletSemi.DeltaR() > 1.5) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
            Sextet.SetTag(GetTag(Sextet));
            if (Sextet.Tag() != Tag) continue;
            if (Tag == HSignal && Sextet.Jet().m() < Mass / 2)continue;
            Sextets.push_back(Sextet);
        }

    Print(HInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HNotification, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByMass<HSextet>(Mass));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

//     for (const auto & Sextet : Sextets) Print(HError, "Sextet Mass", Sextet.GetSextetJet().m(), Sextet.Triplet1().Bdt(), Sextet.Triplet2().Bdt());

    std::vector<HHeavyHiggsSemiBranch *> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) {
        HHeavyHiggsSemiBranch *HeavyHiggsSemiBranch = new HHeavyHiggsSemiBranch();
        FillBranch(HeavyHiggsSemiBranch, Sextet);
        HeavyHiggsBranches.push_back(HeavyHiggsSemiBranch);
    }

    return HeavyHiggsBranches;
}


hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet, const float Mass)
{
    Print(HInformation, "Get Sextet Tag");

    if (std::abs(Sextet.Jet().m() - Mass) > Mass / 2) return HBackground;
    if (Sextet.DeltaR() < 4) return HBackground;

    return HSignal;
}


hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get Sextet Tag");

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

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const HReader *const Reader)
{

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.Singlet() == TripletHadronic.Singlet()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet1()) continue;
            if (TripletSemi.Singlet() == TripletHadronic.Doublet().Singlet2()) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
//             if (Sextet.GetSextetJet().m() < 0)continue;
            FillBranch(Sextet);
            Sextet.SetBdt(Reader->Bdt());
            Sextets.push_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(MaxCombi, int(Sextets.size())), Sextets.end());
    return Sextets;
}


