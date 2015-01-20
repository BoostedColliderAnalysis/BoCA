# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger(
    hanalysis::HBottomTagger *const NewBottomTagger,
    hanalysis::HWSemiTagger *const NewWSemiTagger,
    hanalysis::HWTagger *const NewWTagger,
    hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

//     BottomTagger = NewBottomTagger;
//     BottomReader = new HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new HReader(WSemiTagger);
//     WTagger = NewWTagger;
//     WReader = new HReader(WTagger);
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

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(const hanalysis::HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.GetBdt());
    FillBranch(Branch, Sextet);
}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(HHeavyHiggsSemiBranch *HeavyHiggsBranch, const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.GetBdt());

    HeavyHiggsBranch->Mass = Sextet.GetSextetJet().m();
    HeavyHiggsBranch->Pt = Sextet.GetSextetJet().pt();
    HeavyHiggsBranch->Rap = Sextet.GetSextetJet().rap();
    HeavyHiggsBranch->Phi = Sextet.GetSextetJet().phi();

    HeavyHiggsBranch->DeltaPt = Sextet.GetDeltaPt();
    HeavyHiggsBranch->DeltaR = Sextet.GetDeltaR();
    HeavyHiggsBranch->DeltaRap = Sextet.GetDeltaRap();
    HeavyHiggsBranch->DeltaPhi = Sextet.GetDeltaPhi();

    HeavyHiggsBranch->Bdt = Sextet.GetBdt();
    HeavyHiggsBranch->Tag = Sextet.GetTag();

}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}


// struct SortSextetByMass {
//     inline bool operator()(const hanalysis::HSextet &Sextet1, const hanalysis::HSextet &Sextet2) {
//         return (Sextet1.GetSextetJet().m() > Sextet2.GetSextetJet().m());
//     }
// };

struct SortSextetByMass {
    SortSextetByMass(float Mass) {
        this->Mass = Mass;
    }
    inline bool operator()(const hanalysis::HSextet &Sextet1, const hanalysis::HSextet &Sextet2) {
        if (Sextet1.GetSextetJet().m() != Sextet2.GetSextetJet().m()) return std::abs(Sextet1.GetSextetJet().m() - Mass) < std::abs(Sextet2.GetSextetJet().m() - Mass);
        else return Sextet1.GetBdt() > Sextet2.GetBdt();
    }
    float Mass;
};

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
            if (TripletSemi.GetSinglet() == TripletHadronic.GetSinglet()) continue;
            if (TripletSemi.GetSinglet() == TripletHadronic.GetDoublet().GetJet1()) continue;
            if (TripletSemi.GetSinglet() == TripletHadronic.GetDoublet().GetJet2()) continue;
            if (Tag == HSignal && TripletSemi.GetDeltaR() > 1.5) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
            Sextet.SetTag(GetTag(Sextet));
            if (Sextet.GetTag() != Tag) continue;
            if (Tag == HSignal && Sextet.GetSextetJet().m() < Mass / 2)continue;
            Sextets.push_back(Sextet);
        }

    Print(HInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HNotification, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortSextetByMass(Mass));
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

//     for (const auto & Sextet : Sextets) Print(HError, "Sextet Mass", Sextet.GetSextetJet().m(), Sextet.GetTriplet1().GetBdt(), Sextet.GetTriplet2().GetBdt());

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

    if (std::abs(Sextet.GetSextetJet().m() - Mass) > Mass / 2) return HBackground;
    if (Sextet.GetDeltaR() < 4) return HBackground;

    return HSignal;
}


hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get Sextet Tag");

    HJetInfo JetInfoB1 = Sextet.GetTriplet1().GetSinglet().user_info<HJetInfo>();
    JetInfoB1.ExtractFraction(TopId);
    HJetInfo JetInfoL = Sextet.GetTriplet1().GetDoublet().GetJet1().user_info<HJetInfo>();
    JetInfoL.ExtractFraction(TopId);
    HJetInfo JetInfoB2 = Sextet.GetTriplet2().GetSinglet().user_info<HJetInfo>();
    JetInfoB2.ExtractFraction(TopId);
    HJetInfo JetInfoW1 = Sextet.GetTriplet2().GetDoublet().GetJet1().user_info<HJetInfo>();
    JetInfoW1.ExtractFraction(TopId);
    HJetInfo JetInfoW2 = Sextet.GetTriplet2().GetDoublet().GetJet2().user_info<HJetInfo>();
    JetInfoW2.ExtractFraction(TopId);

    if (std::abs(JetInfoB1.GetMaximalId()) != TopId) return HBackground;
    if (JetInfoB1.GetMaximalId() != -JetInfoB2.GetMaximalId()) return HBackground;

    if (std::abs(JetInfoL.GetMaximalId()) != TopId) return HBackground;
    if (sgn(JetInfoL.GetMaximalId()) != sgn(JetInfoB1.GetMaximalId())) return HBackground;

    if (std::abs(JetInfoW1.GetMaximalId()) != TopId) return HBackground;
    if (JetInfoW1.GetMaximalId() != JetInfoW2.GetMaximalId()) return HBackground;
    if (sgn(JetInfoW1.GetMaximalId()) != sgn(JetInfoB2.GetMaximalId())) return HBackground;

    return HSignal;
}


// hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet)
// {
//     Print(HInformation, "Get Sextet Tag");
//
//     HJetInfo JetInfoB1 = Sextet.GetTriplet1().GetSinglet().user_info<HJetInfo>();
//     JetInfoB1.ExtractFraction(BottomId);
//     HJetInfo JetInfoL = Sextet.GetTriplet1().GetDoublet().GetJet1().user_info<HJetInfo>();
//     JetInfoL.ExtractFraction(TopId);
//     HJetInfo JetInfoB2 = Sextet.GetTriplet2().GetSinglet().user_info<HJetInfo>();
//     JetInfoB2.ExtractFraction(BottomId);
//     HJetInfo JetInfoW1 = Sextet.GetTriplet2().GetDoublet().GetJet1().user_info<HJetInfo>();
//     JetInfoW1.ExtractFraction(WId);
//     HJetInfo JetInfoW2 = Sextet.GetTriplet2().GetDoublet().GetJet2().user_info<HJetInfo>();
//     JetInfoW2.ExtractFraction(WId);
//
//     if (std::abs(JetInfoB1.GetMaximalId()) != BottomId) return HBackground;
//     if (JetInfoB1.GetMaximalId() != -JetInfoB2.GetMaximalId()) return HBackground;
//
//     if (std::abs(JetInfoL.GetMaximalId()) != TopId) return HBackground;
//     if (sgn(JetInfoL.GetMaximalId()) != sgn(JetInfoB1.GetMaximalId())) return HBackground;
//
//     if (std::abs(JetInfoW1.GetMaximalId()) != WId) return HBackground;
//     if (JetInfoW1.GetMaximalId() != JetInfoW2.GetMaximalId()) return HBackground;
//     if (sgn(JetInfoW1.GetMaximalId()) != sgn(JetInfoB2.GetMaximalId())) return HBackground;
//
//     return HSignal;
// }

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(const std::vector<HTriplet> &TripletsSemi, const std::vector<HTriplet> &TripletsHadronic, const HReader *const Reader)
{

    std::vector<HSextet > Sextets;
    for (const auto & TripletSemi : TripletsSemi)
        for (const auto & TripletHadronic : TripletsHadronic) {
            if (TripletSemi.GetSinglet() == TripletHadronic.GetSinglet()) continue;
            if (TripletSemi.GetSinglet() == TripletHadronic.GetDoublet().GetJet1()) continue;
            if (TripletSemi.GetSinglet() == TripletHadronic.GetDoublet().GetJet2()) continue;
            HSextet Sextet(TripletSemi, TripletHadronic);
//             if (Sextet.GetSextetJet().m() < 0)continue;
            FillBranch(Sextet);
            Sextet.SetBdt(Reader->GetBdt());
            Sextets.push_back(Sextet);
        }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(MaxCombi, int(Sextets.size())), Sextets.end());
    return Sextets;
}


