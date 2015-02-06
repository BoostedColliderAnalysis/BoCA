# include "HChargedSemiTagger.hh"

hheavyhiggs::HChargedEventSemiTagger::HChargedSemiTagger()
{
//       DebugLevel = HDebug;
  Print(HInformation , "Constructor");
    SetTaggerName("ChargedSemi");
    DefineVariables();
}

hheavyhiggs::HChargedEventSemiTagger::~HChargedSemiTagger()
{
  Print(HInformation , "Destructor");
}

void hheavyhiggs::HChargedEventSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger)
{
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    TopSemiTagger = NewTopSemiTagger;
    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    SetTaggerName("ChargedSemi");
    DefineVariables();
}

void hheavyhiggs::HChargedEventSemiTagger::DefineVariables()
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

    Observables.push_back(NewObservable(&Branch.HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch.PairRap, "PairRap"));

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

hheavyhiggs::HChargedSemiBranch hheavyhiggs::HChargedEventSemiTagger::GetBranch(const HOctet44 &Octet) const
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    HChargedSemiBranch EventSemiBranch;
    EventSemiBranch.LeptonNumber = Octet.LeptonNumber();
    EventSemiBranch.JetNumber = Octet.JetNumber();
    EventSemiBranch.BottomNumber = Octet.BottomNumber();
    EventSemiBranch.ScalarHt = Octet.ScalarHt();

    EventSemiBranch.Mass = Octet.Jet().m();
    EventSemiBranch.Rap = Octet.Jet().rap();
    EventSemiBranch.Phi = Octet.Jet().phi();
    EventSemiBranch.Pt = Octet.Jet().pt();
//     EventSemiBranch.Ht = Octet.Ht();

    EventSemiBranch.DeltaPt = Octet.DeltaPt();
    EventSemiBranch.DeltaRap = Octet.DeltaRap();
    EventSemiBranch.DeltaPhi = Octet.DeltaPhi();
    EventSemiBranch.DeltaR = Octet.DeltaR();

    EventSemiBranch.Bdt = Octet.Bdt();
    EventSemiBranch.Tag = Octet.Tag();

    EventSemiBranch.HiggsMass = Octet.Quartet1().Jet().m();
    EventSemiBranch.PairRap = Octet.Quartet2().DeltaRap();

    EventSemiBranch.RestM = Octet.EventStruct().RestM;
    EventSemiBranch.RestPt = Octet.EventStruct().RestPt;
    EventSemiBranch.RestHt = Octet.EventStruct().RestHt;
    EventSemiBranch.RestRap = Octet.EventStruct().RestRap;
    EventSemiBranch.RestPhi = Octet.EventStruct().RestPhi;
    EventSemiBranch.RestBBdt = Octet.EventStruct().RestBBdt;
    EventSemiBranch.MaxBBdt = Octet.EventStruct().MaxBBdt;
    EventSemiBranch.TotalBBdt = Octet.EventStruct().TotalBBdt;
    EventSemiBranch.ThirdBBdt = Octet.EventStruct().ThirdBBdt;
    EventSemiBranch.LeptonPt = Octet.EventStruct().LeptonPt;
    EventSemiBranch.EventTag = Octet.Tag();

    return EventSemiBranch;
}

struct SortJetsByBdt {
  inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
    return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
  }
};

std::vector<hheavyhiggs::HChargedSemiBranch> hheavyhiggs::HChargedEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);
    std::vector<hanalysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(TripletsHadronic, Jets, ChargedJetPairReader);

    std::vector<HOctet44> Octets;
    for (const auto HiggsQuartet  : HiggsQuartets)
        for (const auto & JetQuartet : JetQuartets) {
            if (HiggsQuartet.Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Octets.push_back(Octet);
        }

    if (Tag == HSignal && Octets.size() > 1) {
        Print(HInformation, "more than one event");
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i) {
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));
        Print(HInformation, "BDt", Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt(), MaxBBdt);
    }

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Octet : Octets) {
        HChargedEventStruct EventStruct;
        EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event->GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
        EventStruct.MaxBBdt = MaxBBdt;
        EventStruct.ThirdBBdt = ThirdBBdt;
        if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets()).front().pt();
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int  RestNumber = 0;
        for (const auto & Jet : Jets) {
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt() / Jets.size();
            if (Octet.Quartet1().Singlet() == Jet) continue;
            if (Octet.Quartet1().Triplet().Singlet() == Jet) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet1() == Jet) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet2() == Jet) continue;
            if (Octet.Quartet2().Singlet() == Jet) continue;
            if (Octet.Quartet2().Triplet().Singlet() == Jet) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet1() == Jet) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet2() == Jet) continue;
            ++RestNumber;
            EventStruct.RestHt += Jet.pt();
//             EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
            Print(HInformation, "Rest BTag", EventStruct.RestBTag);
            EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            RestJet += Jet;
        }
        EventStruct.RestBBdt /= RestNumber;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            EventStruct.RestM = RestJet.m();
            EventStruct.RestPt = RestJet.pt();
            EventStruct.RestRap = RestJet.rap();
            EventStruct.RestPhi = RestJet.phi();
        }
        Octet.SetEventStruct(EventStruct);
        Octet.SetTag(Tag);
    }

    std::vector<hheavyhiggs::HChargedSemiBranch> EventSemiBranches;
    for (const auto & Octet : Octets) EventSemiBranches.push_back(GetBranch(Octet));

    return EventSemiBranches;

}


std::vector<HOctet44> hheavyhiggs::HChargedEventSemiTagger::GetBdt(
    const std::vector< hanalysis::HQuartet31 > &HiggsQuartets, const std::vector< hanalysis::HQuartet31 > &JetQuartets, HJets &Jets, HChargedEventStruct &EventStruct, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet44> Octets;
    for (const auto & JetQuartet : JetQuartets) {
        for (const auto & HiggsQuartet : HiggsQuartets) {
            if (HiggsQuartet.Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet, EventStruct);
            Branch = GetBranch(Octet);
            Octet.SetBdt(EventSemiReader.Bdt());
            Octets.push_back(Octet);
        }
    }

    std::sort(Octets.begin(), Octets.end());
    if (Octets.size() > 1)Octets.erase(Octets.begin() + 1, Octets.end());
    Print(HInformation, "Event Number", Octets.size(), Jets.size());

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i)
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Octet : Octets) {
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int RestNumber = 0;
        for (const auto & Jet : Jets) {
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            if (Octet.Quartet1().Singlet() == Jet) continue;
            if (Octet.Quartet1().Triplet().Singlet() == Jet) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet1() == Jet) continue;
            if (Octet.Quartet1().Triplet().Doublet().Singlet2() == Jet) continue;
            if (Octet.Quartet2().Singlet() == Jet) continue;
            if (Octet.Quartet2().Triplet().Singlet() == Jet) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet1() == Jet) continue;
            if (Octet.Quartet2().Triplet().Doublet().Singlet2() == Jet) continue;
            ++RestNumber;
            Octet.EventStructM.RestHt += Jet.pt();
            Octet.EventStructM.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
            Octet.EventStructM.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
            Octet.EventStructM.MaxBBdt = MaxBBdt;
            RestJet += Jet;
        }
        Octet.EventStructM.RestBBdt /= RestNumber;
        Octet.EventStructM.ThirdBBdt = ThirdBBdt;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            Octet.EventStructM.RestM = RestJet.m();
            Octet.EventStructM.RestPt = RestJet.pt();
            Octet.EventStructM.RestRap = RestJet.rap();
            Octet.EventStructM.RestPhi = RestJet.phi();
        }

    }

    return Octets;
}

std::vector<int> hheavyhiggs::HChargedEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
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
      HChargedSemiBranch *Test = (HChargedSemiBranch *) EventClonesArray->At(Entry);
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
