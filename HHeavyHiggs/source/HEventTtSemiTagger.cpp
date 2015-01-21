# include "HEventTtSemiTagger.hh"

hheavyhiggs::HEventTtSemiTagger::HEventTtSemiTagger(
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

hheavyhiggs::HEventTtSemiTagger::~HEventTtSemiTagger()
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

void hheavyhiggs::HEventTtSemiTagger::DefineVariables()
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

void hheavyhiggs::HEventTtSemiTagger::FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());

    EventSemiBranch->LeptonNumber = Sextet.GetLeptonNumber();
    EventSemiBranch->JetNumber = Sextet.GetJetNumber();
    EventSemiBranch->BottomNumber = Sextet.GetBottomNumber();
    EventSemiBranch->ScalarHt = Sextet.GetScalarHt();

    EventSemiBranch->Mass = Sextet.Jet().m();
    EventSemiBranch->Rap = Sextet.Jet().rap();
    EventSemiBranch->Phi = Sextet.Jet().phi();
    EventSemiBranch->Pt = Sextet.Jet().pt();

    EventSemiBranch->DeltaPt = Sextet.GetDeltaPt();
    EventSemiBranch->DeltaRap = Sextet.GetDeltaRap();
    EventSemiBranch->DeltaPhi = Sextet.GetDeltaPhi();
    EventSemiBranch->DeltaR = Sextet.GetDeltaR();

    EventSemiBranch->DeltaPt1 = Sextet.GetDeltaPt1();
    EventSemiBranch->DeltaRap1 = Sextet.GetDeltaRap1();
    EventSemiBranch->DeltaPhi1 = Sextet.GetDeltaPhi1();
    EventSemiBranch->DeltaR1 = Sextet.GetDeltaR1();

    EventSemiBranch->DeltaPt2 = Sextet.GetDeltaPt2();
    EventSemiBranch->DeltaRap2 = Sextet.GetDeltaRap2();
    EventSemiBranch->DeltaPhi2 = Sextet.GetDeltaPhi2();
    EventSemiBranch->DeltaR2 = Sextet.GetDeltaR2();

    EventSemiBranch->Bdt = Sextet.Bdt();
    EventSemiBranch->Tag = Sextet.Tag();

    EventSemiBranch->HiggsMass = Sextet.GetSextet().GetJet().m();
    EventSemiBranch->PairRap = Sextet.GetDoublet().GetDeltaRap();

    EventSemiBranch->RestM = Sextet.GetEventStruct().RestM;
    EventSemiBranch->RestPt = Sextet.GetEventStruct().RestPt;
    EventSemiBranch->RestHt = Sextet.GetEventStruct().RestHt;
    EventSemiBranch->RestRap = Sextet.GetEventStruct().RestRap;
    EventSemiBranch->RestPhi = Sextet.GetEventStruct().RestPhi;
    EventSemiBranch->RestBTag = Sextet.GetEventStruct().RestBTag;
//     Print(HError,"Rest B Tag",EventSemiBranch->RestBTag,Sextet.GetEventStruct().RestBTag);
    EventSemiBranch->RestBBdt = Sextet.GetEventStruct().RestBBdt;
    EventSemiBranch->MaxBBdt = Sextet.GetEventStruct().MaxBBdt;
    EventSemiBranch->TotalBBdt = Sextet.GetEventStruct().TotalBBdt;
    EventSemiBranch->ThirdBBdt = Sextet.GetEventStruct().ThirdBBdt;

}

void hheavyhiggs::HEventTtSemiTagger::FillBranch(const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Sextet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::HEventSemiBranch * > hheavyhiggs::HEventTtSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
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
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt() / Jets.size();
            if (Sextet.GetSextet().Triplet1().GetSinglet() == Jet) continue;
            if (Sextet.GetSextet().Triplet2().GetSinglet() == Jet) continue;
            if (Sextet.GetSextet().Triplet2().GetDoublet().Singlet1() == Jet) continue;
            if (Sextet.GetSextet().Triplet2().GetDoublet().Singlet2() == Jet) continue;
            if (Sextet.GetDoublet().Singlet1() == Jet) continue;
            if (Sextet.GetDoublet().Singlet2() == Jet) continue;
            ++RestNumber;
            EventStruct.RestHt += Jet.pt();
            EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
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
        Sextet.SetEventStruct(EventStruct);
    }

    std::vector<hheavyhiggs::HEventSemiBranch *> EventSemiBranches;
    for (auto & Sextet : Sextets) {
        Sextet.SetTag(Tag);
        hheavyhiggs::HEventSemiBranch *EventSemiBranch = new hheavyhiggs::HEventSemiBranch();
        FillBranch(EventSemiBranch, Sextet);
        EventSemiBranches.push_back(EventSemiBranch);
    }

    return EventSemiBranches;

}


hanalysis::HObject::HTag hheavyhiggs::HEventTtSemiTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get Sextet Tag");

    hanalysis::HJetInfo JetInfoB1 = Sextet.GetSextet().Triplet1().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(JetInfoB1.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoL = Sextet.GetSextet().Triplet1().GetDoublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoL.ExtractFraction(WId);
    if (std::abs(JetInfoL.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoL.GetMaximalId()) != sgn(JetInfoB1.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoB2 = Sextet.GetSextet().Triplet2().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId, TopId);
    if (JetInfoB1.GetMaximalId() != -JetInfoB2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoW1 = Sextet.GetSextet().Triplet2().GetDoublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoW1.ExtractFraction(WId, TopId);
    if (std::abs(JetInfoW1.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoW1.GetMaximalId()) != sgn(JetInfoB2.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoW2 = Sextet.GetSextet().Triplet2().GetDoublet().Singlet2().user_info<hanalysis::HJetInfo>();
    JetInfoW2.ExtractFraction(WId, TopId);
    if (JetInfoW1.GetMaximalId() != JetInfoW2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoB3 = Sextet.GetDoublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(JetInfoB3.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoB4 = Sextet.GetDoublet().Singlet2().user_info<hanalysis::HJetInfo>();
    JetInfoB4.ExtractFraction(BottomId, GluonId);
    if (JetInfoB3.GetMaximalId() != -JetInfoB4.GetMaximalId()) return HBackground;

    return HSignal;
}




std::vector<HSextet> hheavyhiggs::HEventTtSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector<fastjet::PseudoJet> &Jets, HEventStruct &EventStruct, const hanalysis::HReader *const EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HSextet> Sextets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().GetSinglet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet1().GetSinglet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().GetSinglet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().GetSinglet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().GetDoublet().Singlet1() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().GetDoublet().Singlet1() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().GetDoublet().Singlet2() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().GetDoublet().Singlet2() == Doublet.Singlet2()) continue;
            HSextet Sextet(Sextet, Doublet, EventStruct);
            FillBranch(Sextet);
            Sextet.SetBdt(EventSemiReader->Bdt());
            Sextets.push_back(Sextet);
        }
    }

    std::sort(Sextets.begin(), Sextets.end());
    if (Sextets.size() > 1)Sextets.erase(Sextets.begin() + 1, Sextets.end());
    Print(HInformation, "Event Number", Sextets.size(), Jets.size());

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
//     float MaxBBdt = 1;
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i)
//       MaxBBdt *= Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));

        float ThirdBBdt=0;
        if(Jets.size()>2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Sextet : Sextets) {
//         Sextet.EventStruct.RestBBdt = 1;
//         Sextet.EventStruct.TotalBBdt = 1;
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int RestNumber = 0;
        for (const auto & Jet : Jets) {
//             EventStruct.TotalBBdt  *= Jet.user_info<hanalysis::HJetInfo>().Bdt();
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            if (Sextet.GetSextet().Triplet1().GetSinglet() == Jet) continue;
            if (Sextet.GetSextet().Triplet2().GetSinglet() == Jet) continue;
            if (Sextet.GetSextet().Triplet2().GetDoublet().Singlet1() == Jet) continue;
            if (Sextet.GetSextet().Triplet2().GetDoublet().Singlet2() == Jet) continue;
            if (Sextet.GetDoublet().Singlet1() == Jet) continue;
            if (Sextet.GetDoublet().Singlet2() == Jet) continue;
            ++RestNumber;
            Sextet.EventStruct.RestHt += Jet.pt();
            Sextet.EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
            Sextet.EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            Sextet.EventStruct.MaxBBdt = MaxBBdt;
            RestJet += Jet;
        }
        Sextet.EventStruct.RestBBdt /= RestNumber;
            Sextet.EventStruct.ThirdBBdt = ThirdBBdt;
//         if (Sextet.EventStruct.RestBBdt == 1)Sextet.EventStruct.RestBBdt = 0;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            Sextet.EventStruct.RestM = RestJet.m();
            Sextet.EventStruct.RestPt = RestJet.pt();
            Sextet.EventStruct.RestRap = RestJet.rap();
            Sextet.EventStruct.RestPhi = RestJet.phi();
        }

    }


    return Sextets;
}




std::vector<int> hheavyhiggs::HEventTtSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
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
