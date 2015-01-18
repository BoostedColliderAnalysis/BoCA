# include "HEventTtSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger(
    hanalysis::HBottomTagger *const NewBottomTagger,
    hanalysis::HWSemiTagger *const NewWSemiTagger,
    hanalysis::HWTagger *const NewWTagger,
    hanalysis::HTopSemiTagger *const NewTopSemiTagger,
    hanalysis::HTopHadronicTagger *const NewTopHadronicTagger,
    hanalysis::HHeavyHiggsSemiTagger *const NewHeavyHiggsMixedTagger)
{
//   DebugLevel = HDebug;

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new hanalysis::HReader(WSemiTagger);
    WTagger = NewWTagger;
    WReader = new hanalysis::HReader(WTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new hanalysis::HReader(TopSemiTagger);
    HeavyHiggsSemiTagger = NewHeavyHiggsMixedTagger;
    HeavyHiggsSemiReader = new hanalysis::HReader(HeavyHiggsSemiTagger);

    SetTaggerName("EventTtSemi");

    Branch = new hheavyhiggs::HEventSemiBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete WSemiReader;
    delete WReader;
    delete BottomReader;
    delete TopHadronicReader;
    delete TopSemiReader;
    delete HeavyHiggsSemiReader;

}

void hheavyhiggs::HEventSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Spectators.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch->BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&Branch->ScalarHt, "ScalarHt"));

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->DeltaPt1, "DeltaPt1"));
    Observables.push_back(NewObservable(&Branch->DeltaRap1, "DeltaRap1"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi1, "DeltaPhi1"));
    Observables.push_back(NewObservable(&Branch->DeltaR1, "DeltaR1"));

    Observables.push_back(NewObservable(&Branch->DeltaPt2, "DeltaPt2"));
    Observables.push_back(NewObservable(&Branch->DeltaRap2, "DeltaRap2"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi2, "DeltaPhi2"));
    Observables.push_back(NewObservable(&Branch->DeltaR2, "DeltaR2"));

    Observables.push_back(NewObservable(&Branch->HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch->PairRap, "PairRap"));

    Observables.push_back(NewObservable(&Branch->RestM, "RestM"));
    Observables.push_back(NewObservable(&Branch->RestPt, "RestPt"));
    Observables.push_back(NewObservable(&Branch->RestHt, "RestHt"));
    Observables.push_back(NewObservable(&Branch->RestPhi, "RestPhi"));
    Observables.push_back(NewObservable(&Branch->RestRap, "RestRap"));
    Observables.push_back(NewObservable(&Branch->RestBTag, "RestBTag"));
    Observables.push_back(NewObservable(&Branch->RestBBdt, "RestBBdt"));
    Observables.push_back(NewObservable(&Branch->MaxBBdt, "MaxBBdt"));
    Observables.push_back(NewObservable(&Branch->TotalBBdt, "TotalBBdt"));
    Observables.push_back(NewObservable(&Branch->ThirdBBdt, "ThirdBBdt"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));


    Print(HNotification, "Variables defined");

}

void hheavyhiggs::HEventSemiTagger::FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.GetBdt());

    EventSemiBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventSemiBranch->JetNumber = Octet.GetJetNumber();
    EventSemiBranch->BottomNumber = Octet.GetBottomNumber();
    EventSemiBranch->ScalarHt = Octet.GetScalarHt();

    EventSemiBranch->Mass = Octet.GetOctetJet().m();
    EventSemiBranch->Rap = Octet.GetOctetJet().rap();
    EventSemiBranch->Phi = Octet.GetOctetJet().phi();
    EventSemiBranch->Pt = Octet.GetOctetJet().pt();

    EventSemiBranch->DeltaPt = Octet.GetDeltaPt();
    EventSemiBranch->DeltaRap = Octet.GetDeltaRap();
    EventSemiBranch->DeltaPhi = Octet.GetDeltaPhi();
    EventSemiBranch->DeltaR = Octet.GetDeltaR();

    EventSemiBranch->DeltaPt1 = Octet.GetDeltaPt1();
    EventSemiBranch->DeltaRap1 = Octet.GetDeltaRap1();
    EventSemiBranch->DeltaPhi1 = Octet.GetDeltaPhi1();
    EventSemiBranch->DeltaR1 = Octet.GetDeltaR1();

    EventSemiBranch->DeltaPt2 = Octet.GetDeltaPt2();
    EventSemiBranch->DeltaRap2 = Octet.GetDeltaRap2();
    EventSemiBranch->DeltaPhi2 = Octet.GetDeltaPhi2();
    EventSemiBranch->DeltaR2 = Octet.GetDeltaR2();

    EventSemiBranch->Bdt = Octet.GetBdt();
    EventSemiBranch->Tag = Octet.GetTag();

    EventSemiBranch->HiggsMass = Octet.GetSextet().GetSextetJet().m();
    EventSemiBranch->PairRap = Octet.GetDoublet().GetDeltaRap();

    EventSemiBranch->RestM = Octet.GetEventStruct().RestM;
    EventSemiBranch->RestPt = Octet.GetEventStruct().RestPt;
    EventSemiBranch->RestHt = Octet.GetEventStruct().RestHt;
    EventSemiBranch->RestRap = Octet.GetEventStruct().RestRap;
    EventSemiBranch->RestPhi = Octet.GetEventStruct().RestPhi;
    EventSemiBranch->RestBTag = Octet.GetEventStruct().RestBTag;
//     Print(HError,"Rest B Tag",EventSemiBranch->RestBTag,Octet.GetEventStruct().RestBTag);
    EventSemiBranch->RestBBdt = Octet.GetEventStruct().RestBBdt;
    EventSemiBranch->MaxBBdt = Octet.GetEventStruct().MaxBBdt;
    EventSemiBranch->TotalBBdt = Octet.GetEventStruct().TotalBBdt;
    EventSemiBranch->ThirdBBdt = Octet.GetEventStruct().ThirdBBdt;

}

void hheavyhiggs::HEventSemiTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().GetBdt() > Jet2.user_info<hanalysis::HJetInfo>().GetBdt());
    }
};


std::vector<hheavyhiggs::HEventSemiBranch * > hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets,MissingEt, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger->GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    if (Tag == HSignal && Sextets.size() > 1) {
      Print(HInformation, "more than one event", Sextets.size());
      std::sort(Sextets.begin(), Sextets.end());
      Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (auto & Sextet : Sextets) {
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event->GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int  RestNumber = 0;
        for (const auto & Jet : Jets) {
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().GetBdt() / Jets.size();
            if (Sextet.GetSextet().GetTriplet1().GetSinglet() == Jet) continue;
            if (Sextet.GetSextet().GetTriplet2().GetSinglet() == Jet) continue;
            if (Sextet.GetSextet().GetTriplet2().GetDoublet().GetJet1() == Jet) continue;
            if (Sextet.GetSextet().GetTriplet2().GetDoublet().GetJet2() == Jet) continue;
            if (Sextet.GetDoublet().GetJet1() == Jet) continue;
            if (Sextet.GetDoublet().GetJet2() == Jet) continue;
            ++RestNumber;
            EventStruct.RestHt += Jet.pt();
            EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
            Print(HInformation, "Rest BTag", EventStruct.RestBTag);
            EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().GetBdt();
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
        Sextet.SetEventStruct(EventStruct);
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

    hanalysis::HJetInfo JetInfoB1 = Octet.GetSextet().GetTriplet1().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(JetInfoB1.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoL = Octet.GetSextet().GetTriplet1().GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoL.ExtractFraction(WId);
    if (std::abs(JetInfoL.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoL.GetMaximalId()) != sgn(JetInfoB1.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoB2 = Octet.GetSextet().GetTriplet2().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId, TopId);
    if (JetInfoB1.GetMaximalId() != -JetInfoB2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoW1 = Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoW1.ExtractFraction(WId, TopId);
    if (std::abs(JetInfoW1.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoW1.GetMaximalId()) != sgn(JetInfoB2.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoW2 = Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2().user_info<hanalysis::HJetInfo>();
    JetInfoW2.ExtractFraction(WId, TopId);
    if (JetInfoW1.GetMaximalId() != JetInfoW2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoB3 = Octet.GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(JetInfoB3.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoB4 = Octet.GetDoublet().GetJet2().user_info<hanalysis::HJetInfo>();
    JetInfoB4.ExtractFraction(BottomId, GluonId);
    if (JetInfoB3.GetMaximalId() != -JetInfoB4.GetMaximalId()) return HBackground;

    return HSignal;
}




std::vector<HOctet> hheavyhiggs::HEventSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector<fastjet::PseudoJet> &Jets, HEventStruct &EventStruct, const hanalysis::HReader *const EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet1() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet1() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet2() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet2() == Doublet.GetJet2()) continue;
            HOctet Octet(Sextet, Doublet, EventStruct);
            FillBranch(Octet);
            Octet.SetBdt(EventSemiReader->GetBdt());
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
//       MaxBBdt *= Jets.at(i).user_info<hanalysis::HJetInfo>().GetBdt() / std::min(3, int(Jets.size()));
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().GetBdt() / std::min(3, int(Jets.size()));

        float ThirdBBdt=0;
        if(Jets.size()>2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().GetBdt();

    for (auto & Octet : Octets) {
//         Octet.EventStruct.RestBBdt = 1;
//         Octet.EventStruct.TotalBBdt = 1;
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int RestNumber = 0;
        for (const auto & Jet : Jets) {
//             EventStruct.TotalBBdt  *= Jet.user_info<hanalysis::HJetInfo>().GetBdt();
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().GetBdt();
            if (Octet.GetSextet().GetTriplet1().GetSinglet() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetSinglet() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2() == Jet) continue;
            if (Octet.GetDoublet().GetJet1() == Jet) continue;
            if (Octet.GetDoublet().GetJet2() == Jet) continue;
            ++RestNumber;
            Octet.EventStruct.RestHt += Jet.pt();
            Octet.EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
            Octet.EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().GetBdt();
            Octet.EventStruct.MaxBBdt = MaxBBdt;
            RestJet += Jet;
        }
        Octet.EventStruct.RestBBdt /= RestNumber;
            Octet.EventStruct.ThirdBBdt = ThirdBBdt;
//         if (Octet.EventStruct.RestBBdt == 1)Octet.EventStruct.RestBBdt = 0;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            Octet.EventStruct.RestM = RestJet.m();
            Octet.EventStruct.RestPt = RestJet.pt();
            Octet.EventStruct.RestRap = RestJet.rap();
            Octet.EventStruct.RestPhi = RestJet.phi();
        }

    }


    return Octets;
}




std::vector<int> hheavyhiggs::HEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps,0);

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
                const float Cut = float(2 * Step) / Steps;
                if (Bdt > Cut) ++EventNumbers.at(Step);
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
