# include "HEventTtSemiTagger.hh"

hheavyhiggs::HEventTtSemiTagger::HEventTtSemiTagger()
{
    //   DebugLevel = HDebug;

    Print(HNotification , "Constructor");
    SetTaggerName("EventSemi");
    DefineVariables();

}

hheavyhiggs::HEventTtSemiTagger::~HEventTtSemiTagger()
{
    Print(HNotification , "Constructor");
}

void hheavyhiggs::HEventTtSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;

    WSemiTagger = NewWSemiTagger;

    WTagger = NewWTagger;

    TopSemiTagger = NewTopSemiTagger;

    TopHadronicTagger = NewTopHadronicTagger;

    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;

    SetTaggerName("EventSemi");
    DefineVariables();

}

void hheavyhiggs::HEventTtSemiTagger::DefineVariables()
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

//     Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
//     Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
//     Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
//     Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

//     Observables.push_back(NewObservable(&Branch.DeltaPt1, "DeltaPt1"));
//     Observables.push_back(NewObservable(&Branch.DeltaRap1, "DeltaRap1"));
//     Observables.push_back(NewObservable(&Branch.DeltaPhi1, "DeltaPhi1"));
//     Observables.push_back(NewObservable(&Branch.DeltaR1, "DeltaR1"));

//     Observables.push_back(NewObservable(&Branch.DeltaPt2, "DeltaPt2"));
//     Observables.push_back(NewObservable(&Branch.DeltaRap2, "DeltaRap2"));
//     Observables.push_back(NewObservable(&Branch.DeltaPhi2, "DeltaPhi2"));
//     Observables.push_back(NewObservable(&Branch.DeltaR2, "DeltaR2"));

    Observables.push_back(NewObservable(&Branch.HiggsMass, "HiggsMass"));
//     Observables.push_back(NewObservable(&Branch.PairRap, "PairRap"));

    Observables.push_back(NewObservable(&Branch.RestM, "RestM"));
    Observables.push_back(NewObservable(&Branch.RestPt, "RestPt"));
    Observables.push_back(NewObservable(&Branch.RestHt, "RestHt"));
    Observables.push_back(NewObservable(&Branch.RestPhi, "RestPhi"));
    Observables.push_back(NewObservable(&Branch.RestRap, "RestRap"));
    Observables.push_back(NewObservable(&Branch.RestBBdt, "RestBBdt"));
    Observables.push_back(NewObservable(&Branch.MaxBBdt, "MaxBBdt"));
    Observables.push_back(NewObservable(&Branch.TotalBBdt, "TotalBBdt"));
    Observables.push_back(NewObservable(&Branch.ThirdBBdt, "ThirdBBdt"));
    Observables.push_back(NewObservable(&Branch.LeptonPt, "LeptonPt"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));


    Print(HNotification, "Variables defined");

}

hheavyhiggs::HEventTtSemiBranch hheavyhiggs::HEventTtSemiTagger::GetBranch(const HSextetEvent &Event) const
{
    Print(HInformation, "FillPairTagger", Event.Bdt());

    HEventTtSemiBranch EventSemiBranch;
    EventSemiBranch.LeptonNumber = Event.LeptonNumber();
    EventSemiBranch.JetNumber = Event.JetNumber();
    EventSemiBranch.BottomNumber = Event.BottomNumber();
    EventSemiBranch.ScalarHt = Event.ScalarHt();

    EventSemiBranch.Mass = Event.Jet().m();
    EventSemiBranch.Rap = Event.Jet().rap();
    EventSemiBranch.Phi = Event.Jet().phi();
    EventSemiBranch.Pt = Event.Jet().pt();

//     EventSemiBranch.DeltaPt = Octet.DeltaPt();
//     EventSemiBranch.DeltaRap = Octet.DeltaRap();
//     EventSemiBranch.DeltaPhi = Octet.DeltaPhi();
//     EventSemiBranch.DeltaR = Octet.DeltaR();
//
//     EventSemiBranch.DeltaPt1 = Octet.GetDeltaPt1();
//     EventSemiBranch.DeltaRap1 = Octet.GetDeltaRap1();
//     EventSemiBranch.DeltaPhi1 = Octet.GetDeltaPhi1();
//     EventSemiBranch.DeltaR1 = Octet.GetDeltaR1();
//
//     EventSemiBranch.DeltaPt2 = Octet.GetDeltaPt2();
//     EventSemiBranch.DeltaRap2 = Octet.GetDeltaRap2();
//     EventSemiBranch.DeltaPhi2 = Octet.GetDeltaPhi2();
//     EventSemiBranch.DeltaR2 = Octet.GetDeltaR2();

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.HiggsMass = Event.Sextet().Jet().m();
//     EventSemiBranch.PairRap = Octet.Doublet().DeltaRap();

    EventSemiBranch.RestM = Event.EventStruct().RestM;
    EventSemiBranch.RestPt = Event.EventStruct().RestPt;
    EventSemiBranch.RestHt = Event.EventStruct().RestHt;
    EventSemiBranch.RestRap = Event.EventStruct().RestRap;
    EventSemiBranch.RestPhi = Event.EventStruct().RestPhi;
//     EventSemiBranch.RestBTag = Octet.EventStruct().RestBTag;
//     Print(HError,"Rest B Tag",EventSemiBranch.RestBTag,Octet.GetEventStruct().RestBTag);
    EventSemiBranch.RestBBdt = Event.EventStruct().RestBBdt;
    EventSemiBranch.MaxBBdt = Event.EventStruct().MaxBBdt;
    EventSemiBranch.TotalBBdt = Event.EventStruct().TotalBBdt;
    EventSemiBranch.ThirdBBdt = Event.EventStruct().ThirdBBdt;
    EventSemiBranch.LeptonPt = Event.EventStruct().LeptonPt;

    return EventSemiBranch;

}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};

std::vector<hheavyhiggs::HEventTtSemiBranch> hheavyhiggs::HEventTtSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<hheavyhiggs::HEventTtSemiBranch> EventSemiBranches;
    if(Sextets.size()<1) return EventSemiBranches;

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HInformation, "more than one event", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i) {
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));
        Print(HInformation, "BDt", Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt(), MaxBBdt);
    }

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    HSextetEvent SextetEvent(Sextets.front());
//     for (auto & SextetEvent : Sextets) {
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
        if (SextetEvent.Sextet().Triplet1().Singlet() == Jet) continue;
        if (SextetEvent.Sextet().Triplet2().Singlet() == Jet) continue;
        if (SextetEvent.Sextet().Triplet2().Doublet().Singlet1() == Jet) continue;
        if (SextetEvent.Sextet().Triplet2().Doublet().Singlet2() == Jet) continue;
        ++RestNumber;
        EventStruct.RestHt += Jet.pt();
//             EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
//             Print(HInformation, "Rest BTag", EventStruct.RestBTag);
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
    SextetEvent.SetEventStruct(EventStruct);
    SextetEvent.SetTag(Tag);
//     }

//     std::vector<hheavyhiggs::HEventTtSemiBranch> EventSemiBranches;
//     for (const auto & Sextet : SextetE)
    EventSemiBranches.push_back(GetBranch(SextetEvent));

    return EventSemiBranches;
}


hanalysis::HObject::HTag hheavyhiggs::HEventTtSemiTagger::GetTag(const HSextetEvent &Octet)
{
    Print(HInformation, "Get Sextet Tag");

//     hanalysis::HJetInfo JetInfoB1 = Octet.Sextet().Triplet1().Singlet().user_info<hanalysis::HJetInfo>();
//     JetInfoB1.ExtractFraction(BottomId, TopId);
//     if (std::abs(JetInfoB1.MaximalId()) != BottomId) return HBackground;
//
//     hanalysis::HJetInfo JetInfoL = Octet.Sextet().Triplet1().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
//     JetInfoL.ExtractFraction(WId);
//     if (std::abs(JetInfoL.MaximalId()) != WId) return HBackground;
//     if (sgn(JetInfoL.MaximalId()) != sgn(JetInfoB1.MaximalId())) return HBackground;
//
//     hanalysis::HJetInfo JetInfoB2 = Octet.Sextet().Triplet2().Singlet().user_info<hanalysis::HJetInfo>();
//     JetInfoB2.ExtractFraction(BottomId, TopId);
//     if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return HBackground;
//
//     hanalysis::HJetInfo JetInfoW1 = Octet.Sextet().Triplet2().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
//     JetInfoW1.ExtractFraction(WId, TopId);
//     if (std::abs(JetInfoW1.MaximalId()) != WId) return HBackground;
//     if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB2.MaximalId())) return HBackground;
//
//     hanalysis::HJetInfo JetInfoW2 = Octet.Sextet().Triplet2().Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
//     JetInfoW2.ExtractFraction(WId, TopId);
//     if (JetInfoW1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;
//
//     hanalysis::HJetInfo JetInfoB3 = Octet.Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
//     JetInfoB3.ExtractFraction(BottomId, GluonId);
//     if (std::abs(JetInfoB3.MaximalId()) != BottomId) return HBackground;
//
//     hanalysis::HJetInfo JetInfoB4 = Octet.Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
//     JetInfoB4.ExtractFraction(BottomId, GluonId);
//     if (JetInfoB3.MaximalId() != -JetInfoB4.MaximalId()) return HBackground;

    return HSignal;
}


// hanalysis::HObject::HTag hheavyhiggs::HEventTtSemiTagger::GetTag(const HSextetEvent &Octet)
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


std::vector<HSextetEvent> hheavyhiggs::HEventTtSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, std::vector<fastjet::PseudoJet> &Jets, HEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HSextetEvent> Octets;
//     for (const auto & Doublet : Doublets) {
    for (const auto & Sextet : Sextets) {
//             if (Sextet.Triplet1().Singlet() == Doublet.Singlet1()) continue;
//             if (Sextet.Triplet1().Singlet() == Doublet.Singlet2()) continue;
//             if (Sextet.Triplet2().Singlet() == Doublet.Singlet1()) continue;
//             if (Sextet.Triplet2().Singlet() == Doublet.Singlet2()) continue;
//             if (Sextet.Triplet2().Doublet().Singlet1() == Doublet.Singlet1()) continue;
//             if (Sextet.Triplet2().Doublet().Singlet1() == Doublet.Singlet2()) continue;
//             if (Sextet.Triplet2().Doublet().Singlet2() == Doublet.Singlet1()) continue;
//             if (Sextet.Triplet2().Doublet().Singlet2() == Doublet.Singlet2()) continue;
        HSextetEvent SextetEvent(Sextet, EventStruct);
        Branch = GetBranch(SextetEvent);
        SextetEvent.SetBdt(EventSemiReader.Bdt());
        Octets.push_back(SextetEvent);
    }
//     }

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
            ++RestNumber;
            Octet.EventM.RestHt += Jet.pt();
//             Octet.EventM.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
            Octet.EventM.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            Octet.EventM.MaxBBdt = MaxBBdt;
            RestJet += Jet;
        }
        Octet.EventM.RestBBdt /= RestNumber;
        Octet.EventM.ThirdBBdt = ThirdBBdt;
//         if (Octet.EventStruct.RestBBdt == 1)Octet.EventStruct.RestBBdt = 0;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            Octet.EventM.RestM = RestJet.m();
            Octet.EventM.RestPt = RestJet.pt();
            Octet.EventM.RestRap = RestJet.rap();
            Octet.EventM.RestPhi = RestJet.phi();
        }

    }


    return Octets;
}




std::vector<int> hheavyhiggs::HEventTtSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
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
