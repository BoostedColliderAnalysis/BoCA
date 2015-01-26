# include "HEventSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger()
{
    //   DebugLevel = HDebug;

    Print(HNotification , "Constructor");
    SetTaggerName("EventSemi");
    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{
    Print(HNotification , "Constructor");
}

void hheavyhiggs::HEventSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomTagger.SetTagger();
    BottomReader.SetMva(BottomTagger);

    WSemiTagger = NewWSemiTagger;
    WSemiTagger.SetTagger();
    WSemiReader.SetMva(WSemiTagger);

    WTagger = NewWTagger;
    WTagger.SetTagger(BottomTagger);
    WReader.SetMva(WTagger);

    TopSemiTagger = NewTopSemiTagger;
    TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
    TopSemiReader.SetMva(TopSemiTagger);

    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicTagger.SetTagger(BottomTagger, WTagger);
    TopHadronicReader.SetMva(TopHadronicTagger);

    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger);
    HeavyHiggsSemiReader.SetMva(HeavyHiggsSemiTagger);

    JetPairTagger = NewJetPairTagger;
    JetPairTagger.SetTagger(BottomTagger);
    JetPairReader.SetMva(JetPairTagger);

    SetTaggerName("EventSemi");
    DefineVariables();

}

void hheavyhiggs::HEventSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Spectators.push_back(NewObservable(&Branch.LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch.JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch.BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&Branch.ScalarHt, "ScalarHt"));

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.DeltaPt1, "DeltaPt1"));
    Observables.push_back(NewObservable(&Branch.DeltaRap1, "DeltaRap1"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi1, "DeltaPhi1"));
    Observables.push_back(NewObservable(&Branch.DeltaR1, "DeltaR1"));

    Observables.push_back(NewObservable(&Branch.DeltaPt2, "DeltaPt2"));
    Observables.push_back(NewObservable(&Branch.DeltaRap2, "DeltaRap2"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi2, "DeltaPhi2"));
    Observables.push_back(NewObservable(&Branch.DeltaR2, "DeltaR2"));

    Observables.push_back(NewObservable(&Branch.HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch.PairRap, "PairRap"));

    Observables.push_back(NewObservable(&Branch.RestM, "RestM"));
    Observables.push_back(NewObservable(&Branch.RestPt, "RestPt"));
    Observables.push_back(NewObservable(&Branch.RestHt, "RestHt"));
    Observables.push_back(NewObservable(&Branch.RestPhi, "RestPhi"));
    Observables.push_back(NewObservable(&Branch.RestRap, "RestRap"));
    Observables.push_back(NewObservable(&Branch.RestBTag, "RestBTag"));
    Observables.push_back(NewObservable(&Branch.RestBBdt, "RestBBdt"));
    Observables.push_back(NewObservable(&Branch.MaxBBdt, "MaxBBdt"));
    Observables.push_back(NewObservable(&Branch.TotalBBdt, "TotalBBdt"));
    Observables.push_back(NewObservable(&Branch.ThirdBBdt, "ThirdBBdt"));
    Observables.push_back(NewObservable(&Branch.LeptonPt, "LeptonPt"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));


    Print(HNotification, "Variables defined");

}

void hheavyhiggs::HEventSemiTagger::FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    EventSemiBranch->LeptonNumber = Octet.LeptonNumber();
    EventSemiBranch->JetNumber = Octet.JetNumber();
    EventSemiBranch->BottomNumber = Octet.BottomNumber();
    EventSemiBranch->ScalarHt = Octet.ScalarHt();

    EventSemiBranch->Mass = Octet.Jet().m();
    EventSemiBranch->Rap = Octet.Jet().rap();
    EventSemiBranch->Phi = Octet.Jet().phi();
    EventSemiBranch->Pt = Octet.Jet().pt();

    EventSemiBranch->DeltaPt = Octet.DeltaPt();
    EventSemiBranch->DeltaRap = Octet.DeltaRap();
    EventSemiBranch->DeltaPhi = Octet.DeltaPhi();
    EventSemiBranch->DeltaR = Octet.DeltaR();

    EventSemiBranch->DeltaPt1 = Octet.GetDeltaPt1();
    EventSemiBranch->DeltaRap1 = Octet.GetDeltaRap1();
    EventSemiBranch->DeltaPhi1 = Octet.GetDeltaPhi1();
    EventSemiBranch->DeltaR1 = Octet.GetDeltaR1();

    EventSemiBranch->DeltaPt2 = Octet.GetDeltaPt2();
    EventSemiBranch->DeltaRap2 = Octet.GetDeltaRap2();
    EventSemiBranch->DeltaPhi2 = Octet.GetDeltaPhi2();
    EventSemiBranch->DeltaR2 = Octet.GetDeltaR2();

    EventSemiBranch->Bdt = Octet.Bdt();
    EventSemiBranch->Tag = Octet.Tag();

    EventSemiBranch->HiggsMass = Octet.Sextet().Jet().m();
    EventSemiBranch->PairRap = Octet.Doublet().DeltaRap();

    EventSemiBranch->RestM = Octet.EventStruct().RestM;
    EventSemiBranch->RestPt = Octet.EventStruct().RestPt;
    EventSemiBranch->RestHt = Octet.EventStruct().RestHt;
    EventSemiBranch->RestRap = Octet.EventStruct().RestRap;
    EventSemiBranch->RestPhi = Octet.EventStruct().RestPhi;
    EventSemiBranch->RestBTag = Octet.EventStruct().RestBTag;
//     Print(HError,"Rest B Tag",EventSemiBranch->RestBTag,Octet.GetEventStruct().RestBTag);
    EventSemiBranch->RestBBdt = Octet.EventStruct().RestBBdt;
    EventSemiBranch->MaxBBdt = Octet.EventStruct().MaxBBdt;
    EventSemiBranch->TotalBBdt = Octet.EventStruct().TotalBBdt;
    EventSemiBranch->ThirdBBdt = Octet.EventStruct().ThirdBBdt;
    EventSemiBranch->LeptonPt = Octet.EventStruct().LeptonPt;

}

void hheavyhiggs::HEventSemiTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::HEventSemiBranch * > hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    JetTag.HeavyParticles = {GluonId, TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Doublet().Singlet1() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Doublet().Singlet1() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Doublet().Singlet2() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Doublet().Singlet2() == Doublet.Singlet2()) continue;
            HOctet Octet(Sextet, Doublet);
            Octets.push_back(Octet);
        }
    }

    if (Tag == HSignal && Octets.size() > 1) {
        Print(HInformation, "more than one event", Octets.size());
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
//     float MaxBBdt = 1;
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i) {
//         MaxBBdt *= Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt();
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));
        Print(HInformation, "BDt", Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt(), MaxBBdt);
    }

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Octet : Octets) {
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event->GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
        EventStruct.MaxBBdt = MaxBBdt;
        EventStruct.ThirdBBdt = ThirdBBdt;
        if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets()).front().pt();
//         EventStruct.RestBBdt = 1;
//         EventStruct.TotalBBdt = 1;
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int  RestNumber = 0;
        for (const auto & Jet : Jets) {
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt() / Jets.size();
            if (Octet.Sextet().Triplet1().Singlet() == Jet) continue;
            if (Octet.Sextet().Triplet2().Singlet() == Jet) continue;
            if (Octet.Sextet().Triplet2().Doublet().Singlet1() == Jet) continue;
            if (Octet.Sextet().Triplet2().Doublet().Singlet2() == Jet) continue;
            if (Octet.Doublet().Singlet1() == Jet) continue;
            if (Octet.Doublet().Singlet2() == Jet) continue;
            ++RestNumber;
            EventStruct.RestHt += Jet.pt();
            EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
            Print(HInformation, "Rest BTag", EventStruct.RestBTag);
            EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            RestJet += Jet;
        }
        EventStruct.RestBBdt /= RestNumber;
//         if (EventStruct.RestBBdt == 1)EventStruct.RestBBdt = 0;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            EventStruct.RestM = RestJet.m();
            EventStruct.RestPt = RestJet.pt();
            EventStruct.RestRap = RestJet.rap();
            EventStruct.RestPhi = RestJet.phi();
        }
        Octet.SetEventStruct(EventStruct);
    }

    std::vector<hheavyhiggs::HEventSemiBranch *> EventSemiBranches;
    for (auto & Octet : Octets) {
        Octet.SetTag(Tag);
        hheavyhiggs::HEventSemiBranch *EventSemiBranch = new hheavyhiggs::HEventSemiBranch();
        FillBranch(EventSemiBranch, Octet);
        EventSemiBranches.push_back(EventSemiBranch);
    }

    return EventSemiBranches;

}


hanalysis::HObject::HTag hheavyhiggs::HEventSemiTagger::GetTag(const HOctet &Octet)
{
    Print(HInformation, "Get Sextet Tag");

    hanalysis::HJetInfo JetInfoB1 = Octet.Sextet().Triplet1().Singlet().user_info<hanalysis::HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(JetInfoB1.MaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoL = Octet.Sextet().Triplet1().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoL.ExtractFraction(WId);
    if (std::abs(JetInfoL.MaximalId()) != WId) return HBackground;
    if (sgn(JetInfoL.MaximalId()) != sgn(JetInfoB1.MaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoB2 = Octet.Sextet().Triplet2().Singlet().user_info<hanalysis::HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId, TopId);
    if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoW1 = Octet.Sextet().Triplet2().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoW1.ExtractFraction(WId, TopId);
    if (std::abs(JetInfoW1.MaximalId()) != WId) return HBackground;
    if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB2.MaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoW2 = Octet.Sextet().Triplet2().Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
    JetInfoW2.ExtractFraction(WId, TopId);
    if (JetInfoW1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoB3 = Octet.Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(JetInfoB3.MaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoB4 = Octet.Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
    JetInfoB4.ExtractFraction(BottomId, GluonId);
    if (JetInfoB3.MaximalId() != -JetInfoB4.MaximalId()) return HBackground;

    return HSignal;
}


// hanalysis::HObject::HTag hheavyhiggs::HEventSemiTagger::GetTag(const HOctet &Octet)
// {
//   Print(HInformation, "Get Sextet Tag");
//
//   hanalysis::HJetInfo JetInfoB1 = Octet.Sextet().Triplet1().Singlet().user_info<hanalysis::HJetInfo>();
//   JetInfoB1.ExtractFraction(BottomId, TopId);
//   if (std::abs(JetInfoB1.MaximalId()) != BottomId) return HBackground;
//
//   hanalysis::HJetInfo JetInfoL = Octet.Sextet().Triplet1().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
//   JetInfoL.ExtractFraction(WId);
//   if (std::abs(JetInfoL.MaximalId()) != WId) return HBackground;
//   if (sgn(JetInfoL.MaximalId()) != sgn(JetInfoB1.MaximalId())) return HBackground;
//
//   hanalysis::HJetInfo JetInfoB2 = Octet.Sextet().Triplet2().Singlet().user_info<hanalysis::HJetInfo>();
//   JetInfoB2.ExtractFraction(BottomId, TopId);
//   if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return HBackground;
//
//   hanalysis::HJetInfo JetInfoW1 = Octet.Sextet().Triplet2().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
//   JetInfoW1.ExtractFraction(WId, TopId);
//   if (std::abs(JetInfoW1.MaximalId()) != WId) return HBackground;
//   if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB2.MaximalId())) return HBackground;
//
//   hanalysis::HJetInfo JetInfoW2 = Octet.Sextet().Triplet2().Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
//   JetInfoW2.ExtractFraction(WId, TopId);
//   if (JetInfoW1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;
//
//   hanalysis::HJetInfo JetInfoB3 = Octet.Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
//   JetInfoB3.ExtractFraction(BottomId, GluonId);
//   if (std::abs(JetInfoB3.MaximalId()) != BottomId) return HBackground;
//
//   hanalysis::HJetInfo JetInfoB4 = Octet.Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
//   JetInfoB4.ExtractFraction(BottomId, GluonId);
//   if (JetInfoB3.MaximalId() != -JetInfoB4.MaximalId()) return HBackground;
//
//   return HSignal;
// }


std::vector<HOctet> hheavyhiggs::HEventSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector<fastjet::PseudoJet> &Jets, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Doublet().Singlet1() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Doublet().Singlet1() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Doublet().Singlet2() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Doublet().Singlet2() == Doublet.Singlet2()) continue;
            HOctet Octet(Sextet, Doublet, EventStruct);
            FillBranch(Octet);
            Octet.SetBdt(EventSemiReader.Bdt());
            Octets.push_back(Octet);
        }
    }

    std::sort(Octets.begin(), Octets.end());
    if (Octets.size() > 1)Octets.erase(Octets.begin() + 1, Octets.end());
    Print(HInformation, "Event Number", Octets.size(), Jets.size());

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
//     float MaxBBdt = 1;
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i)
//       MaxBBdt *= Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Octet : Octets) {
//         Octet.EventStruct.RestBBdt = 1;
//         Octet.EventStruct.TotalBBdt = 1;
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int RestNumber = 0;
        for (const auto & Jet : Jets) {
//             EventStruct.TotalBBdt  *= Jet.user_info<hanalysis::HJetInfo>().Bdt();
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            if (Octet.Sextet().Triplet1().Singlet() == Jet) continue;
            if (Octet.Sextet().Triplet2().Singlet() == Jet) continue;
            if (Octet.Sextet().Triplet2().Doublet().Singlet1() == Jet) continue;
            if (Octet.Sextet().Triplet2().Doublet().Singlet2() == Jet) continue;
            if (Octet.Doublet().Singlet1() == Jet) continue;
            if (Octet.Doublet().Singlet2() == Jet) continue;
            ++RestNumber;
            Octet.EventStructM.RestHt += Jet.pt();
            Octet.EventStructM.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
            Octet.EventStructM.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            Octet.EventStructM.MaxBBdt = MaxBBdt;
            RestJet += Jet;
        }
        Octet.EventStructM.RestBBdt /= RestNumber;
        Octet.EventStructM.ThirdBBdt = ThirdBBdt;
//         if (Octet.EventStruct.RestBBdt == 1)Octet.EventStruct.RestBBdt = 0;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            Octet.EventStructM.RestM = RestJet.m();
            Octet.EventStructM.RestPt = RestJet.pt();
            Octet.EventStructM.RestRap = RestJet.rap();
            Octet.EventStructM.RestPhi = RestJet.phi();
        }

    }


    return Octets;
}




std::vector<int> hheavyhiggs::HEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HResultBranch::Class());

    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {


            HEventSemiBranch *Test = (HEventSemiBranch *) EventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;

            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;


            for (int Step = 0; Step < Steps; ++Step) {
                const float CutValue = (float(Step) / Steps + 1);
                if (Bdt > CutValue) ++EventNumbers.at(Step);
            }


        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;
    EventBranchName = Temp;

    return EventNumbers;

}
