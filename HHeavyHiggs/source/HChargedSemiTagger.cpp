# include "HChargedSemiTagger.hh"

hheavyhiggs::HChargedSemiTagger::HChargedSemiTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    SetTaggerName("ChargedSemi");
    DefineVariables();
}

hheavyhiggs::HChargedSemiTagger::~HChargedSemiTagger()
{
    Print(HNotification , "Constructor");
}

void hheavyhiggs::HChargedSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger)
{

    BottomTagger = NewBottomTagger;
    BottomTagger.SetTagger();
    BottomReader.SetMva(BottomTagger);

    WSemiTagger = NewWSemiTagger;
    WSemiTagger.SetTagger();
    WSemiReader.SetMva(WSemiTagger);

    WTagger = NewWTagger;
    WTagger.SetTagger(BottomTagger);
    WReader.SetMva(WTagger);

    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicTagger.SetTagger(BottomTagger, WTagger);
    TopHadronicReader.SetMva(TopHadronicTagger);

    TopSemiTagger = NewTopSemiTagger;
    TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
    TopSemiReader.SetMva(TopSemiTagger);

    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger);
    ChargedJetPairReader.SetMva(ChargedJetPairTagger);


    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger);
    ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);

    SetTaggerName("EventSemi");
    DefineVariables();

}

void hheavyhiggs::HChargedSemiTagger::DefineVariables()
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

//   Observables.push_back(NewObservable(&Branch.DeltaPt1, "DeltaPt1"));
//   Observables.push_back(NewObservable(&Branch.DeltaRap1, "DeltaRap1"));
//   Observables.push_back(NewObservable(&Branch.DeltaPhi1, "DeltaPhi1"));
//   Observables.push_back(NewObservable(&Branch.DeltaR1, "DeltaR1"));
//
//   Observables.push_back(NewObservable(&Branch.DeltaPt2, "DeltaPt2"));
//   Observables.push_back(NewObservable(&Branch.DeltaRap2, "DeltaRap2"));
//   Observables.push_back(NewObservable(&Branch.DeltaPhi2, "DeltaPhi2"));
//   Observables.push_back(NewObservable(&Branch.DeltaR2, "DeltaR2"));

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

hheavyhiggs::HChargedSemiBranch hheavyhiggs::HChargedSemiTagger::GetBranch(const HOctet44 &Octet) const
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

    EventSemiBranch.DeltaPt = Octet.DeltaPt();
    EventSemiBranch.DeltaRap = Octet.DeltaRap();
    EventSemiBranch.DeltaPhi = Octet.DeltaPhi();
    EventSemiBranch.DeltaR = Octet.DeltaR();

//     EventSemiBranch.DeltaPt1 = Octet.GetDeltaPt1();
//     EventSemiBranch.DeltaRap1 = Octet.DeltaRap();
//     EventSemiBranch.DeltaPhi1 = Octet.DeltaPhi();
//     EventSemiBranch.DeltaR1 = Octet.DeltaR();
//
//     EventSemiBranch.DeltaPt2 = Octet.GetDeltaPt2();
//     EventSemiBranch.DeltaRap2 = Octet.GetDeltaRap2();
//     EventSemiBranch.DeltaPhi2 = Octet.GetDeltaPhi2();
//     EventSemiBranch.DeltaR2 = Octet.GetDeltaR2();

    EventSemiBranch.Bdt = Octet.Bdt();
    EventSemiBranch.Tag = Octet.Tag();

    EventSemiBranch.HiggsMass = Octet.Quartet1().Jet().m();
    EventSemiBranch.PairRap = Octet.Quartet2().DeltaRap();

    EventSemiBranch.RestM = Octet.EventStruct().RestM;
    EventSemiBranch.RestPt = Octet.EventStruct().RestPt;
    EventSemiBranch.RestHt = Octet.EventStruct().RestHt;
    EventSemiBranch.RestRap = Octet.EventStruct().RestRap;
    EventSemiBranch.RestPhi = Octet.EventStruct().RestPhi;
    EventSemiBranch.RestBTag = Octet.EventStruct().RestBTag;
    //     Print(HError,"Rest B Tag",EventSemiBranch.RestBTag,Octet.GetEventStruct().RestBTag);
    EventSemiBranch.RestBBdt = Octet.EventStruct().RestBBdt;
    EventSemiBranch.MaxBBdt = Octet.EventStruct().MaxBBdt;
    EventSemiBranch.TotalBBdt = Octet.EventStruct().TotalBBdt;
    EventSemiBranch.ThirdBBdt = Octet.EventStruct().ThirdBBdt;
    EventSemiBranch.LeptonPt = Octet.EventStruct().LeptonPt;

    EventSemiBranch.EventTag = Octet.Tag();
}


struct SortByQuartetBdt {
    inline bool operator()(const HOctet44 &Octet1, const HOctet44 &Octet2) {
        return (Octet1.Quartet1().Bdt() > Octet2.Quartet1().Bdt());
    }
};

std::vector<hheavyhiggs::HChargedSemiBranch> hheavyhiggs::HChargedSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = Event->GetJets()->GetStructuredJets();

    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);

    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);


    std::vector<HOctet44> Octets;
    for (const auto Jet : Jets) {
        for (const auto Triplet  : TripletsHadronic) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            hanalysis::HQuartet31 Quartet2(Triplet, Jet);
            for (const auto & Quartet1 : Quartets) {
                if (Quartet1.Singlet() == Quartet2.Singlet()) continue;
                if (Quartet1.Singlet() == Quartet2.Triplet().Singlet()) continue;
                if (Quartet1.Singlet() == Quartet2.Triplet().Doublet().Singlet1()) continue;
                if (Quartet1.Singlet() == Quartet2.Triplet().Doublet().Singlet2()) continue;
                if (Quartet1.Triplet().Singlet() == Quartet2.Singlet()) continue;
                if (Quartet1.Triplet().Singlet() == Quartet2.Triplet().Singlet()) continue;
                if (Quartet1.Triplet().Singlet() == Quartet2.Triplet().Doublet().Singlet1()) continue;
                if (Quartet1.Triplet().Singlet() == Quartet2.Triplet().Doublet().Singlet2()) continue;
                HOctet44 Octet(Quartet1, Quartet2);
                Octets.push_back(Octet);
            }
        }
    }

    if (Octets.size() > 1) {
        Print(HError, "more than one event");
        std::sort(Octets.begin(), Octets.end(), SortByQuartetBdt());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HChargedSemiBranch> ChargedSemiBranches;
    for (auto & Octet : Octets) {
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        ChargedSemiBranches.push_back(GetBranch(Octet));
    }

    return ChargedSemiBranches;

}

struct SortJetsByBdt {
  inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
    return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
  }
};


std::vector<HOctet44> hheavyhiggs::HChargedSemiTagger::GetBdt(
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



std::vector<int> hheavyhiggs::HChargedSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
{
    Print(HNotification, "Apply Bdt", EventBranchName);

    const int Steps2 = 10;
    std::vector<int> EventNumbers(Steps2);


    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *BdtBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HBdtBranch::Class());

    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {

            (Branch) = *((HChargedSemiBranch *) EventClonesArray->At(Entry)); // used to be (*Branch)

            HBdtBranch *Export = static_cast<HBdtBranch *>(BdtBranch->NewEntry());

            const float Bdt = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(BdtMethodName);
            const float Error = const_cast<TMVA::Reader *>(&Reader)->GetMVAError();
            const float Rarity = const_cast<TMVA::Reader *>(&Reader)->GetRarity(GetBdtMethodName());
            const int Steps = 10;
            std::vector<float> Probabilities;
            for (int Step = Steps; Step > 0; --Step) {
                const float SignalFraction = float(Step) / Steps;
                const float Probability = const_cast<TMVA::Reader *>(&Reader)->GetProba(GetBdtMethodName(), SignalFraction);
                Probabilities.push_back(Probability);
            }
            Print(HDebug, "Bdt", Bdt, Error, Rarity);
//             Export->Mass = Branch.HeavyHiggsMass;
            Export->EventTag = Branch.EventTag;
            Export->Bdt = Bdt;
            Export->Error = Error;
            Export->Rarity = Rarity;
            Export->Probability01 = Probabilities.at(0);
            Export->Probability02 = Probabilities.at(1);
            Export->Probability03 = Probabilities.at(2);
            Export->Probability04 = Probabilities.at(3);
            Export->Probability05 = Probabilities.at(4);
            Export->Probability06 = Probabilities.at(5);
            Export->Probability07 = Probabilities.at(6);
            Export->Probability08 = Probabilities.at(7);
            Export->Probability09 = Probabilities.at(8);
            Export->Probability10 = Probabilities.at(9);


            for (int Step = 0; Step < Steps2; ++Step) {
                const float CutValue = float(Step - 5) / Steps2 / 2;
                if (Bdt > CutValue) ++EventNumbers.at(Step);
            }


        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;

    return EventNumbers;


}
