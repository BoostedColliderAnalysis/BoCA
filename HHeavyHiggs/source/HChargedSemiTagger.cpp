# include "HChargedSemiTagger.hh"

hheavyhiggs::HChargedSemiTagger::HChargedSemiTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWSemiTagger *const NewWSemiTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HChargedHiggsSemiTagger *const NewChargedHiggsMixedTagger)
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
    ChargedHiggsSemiTagger = NewChargedHiggsMixedTagger;
    ChargedHiggsSemiReader = new hanalysis::HReader(ChargedHiggsSemiTagger);

    SetTaggerName("EventSemi");

    Branch = new hheavyhiggs::HChargedSemiBranch();

    DefineVariables();

}

hheavyhiggs::HChargedSemiTagger::HChargedSemiTagger()
{
    //   DebugLevel = HDebug;

    Print(HNotification , "Constructor");

    SetTaggerName("ChargedSemi");
    Branch = new hheavyhiggs::HChargedSemiBranch();

    DefineVariables();

}

hheavyhiggs::HChargedSemiTagger::~HChargedSemiTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete BottomReader;
    delete WSemiReader;
    delete WReader;
    delete TopHadronicReader;
    delete TopSemiReader;
    delete ChargedHiggsSemiReader;

}

void hheavyhiggs::HChargedSemiTagger::FillBranch(hheavyhiggs::HChargedSemiBranch *EventSemiBranch, const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    EventSemiBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventSemiBranch->JetNumber = Octet.GetJetNumber();
    EventSemiBranch->BottomNumber = Octet.GetBottomNumber();

    EventSemiBranch->ScalarHt = Octet.GetScalarHt();
    EventSemiBranch->HeavyParticleBdt = Octet.Bdt();

    EventSemiBranch->HeavyHiggsBdt = Octet.GetQuartet1().Bdt();
    EventSemiBranch->HeavyHiggsMass = Octet.GetQuartet1Jet().m();
    EventSemiBranch->HeavyHiggsPt = Octet.GetQuartet1Jet().pt();

    EventSemiBranch->BottomSumPt = Octet.GetQuartet2Jet().pt();
    EventSemiBranch->BottomDeltaPt = Octet.GetQuartet2().GetDeltaPt();

    EventSemiBranch->BottomDeltaRap = Octet.GetQuartet2().GetDeltaRap();
    EventSemiBranch->BottomDeltaPhi = Octet.GetQuartet2().GetDeltaPhi();
    EventSemiBranch->BottomDeltaR = Octet.GetQuartet2().GetDeltaR();

    EventSemiBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    EventSemiBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    EventSemiBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    EventSemiBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    EventSemiBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    EventSemiBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventSemiBranch->EventTag = Octet.Tag();
}

void hheavyhiggs::HChargedSemiTagger::FillBranch(const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}

void hheavyhiggs::HChargedSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch->BottomNumber, "BottomNumber"));

    Observables.push_back(NewObservable(&Branch->ScalarHt, "ScalarHt"));
    Observables.push_back(NewObservable(&Branch->HeavyParticleBdt, "HeavyParticleBdt"));

    Observables.push_back(NewObservable(&Branch->HeavyHiggsBdt, "HeavyHiggsBdt"));
    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->BottomSumPt, "BottomSumPt"));
    Observables.push_back(NewObservable(&Branch->BottomDeltaPt, "BottomDeltaPt"));

    Observables.push_back(NewObservable(&Branch->BottomDeltaRap, "BottomDeltaRap"));
    Observables.push_back(NewObservable(&Branch->BottomDeltaPhi, "BottomDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->BottomDeltaR, "BottomDeltaR"));

    Observables.push_back(NewObservable(&Branch->HbSumDeltaRap, "HbSumDeltaRap"));
    Observables.push_back(NewObservable(&Branch->HbSumDeltaPhi, "HbSumDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->HbSumDeltaR, "HbSumDeltaR"));

    Observables.push_back(NewObservable(&Branch->HbDeltaDeltaRap, "HbDeltaDeltaRap"));
    Observables.push_back(NewObservable(&Branch->HbDeltaDeltaPhi, "HbDeltaDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->HbDeltaDeltaR, "HbDeltaDeltaR"));

    Spectators.push_back(NewObservable(&Branch->EventTag, "EventTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}


struct SortByQuartetBdt {
    inline bool operator()(const HOctet44 &Octet1, const HOctet44 &Octet2) {
        return (Octet1.GetQuartet1().Bdt() > Octet2.GetQuartet1().Bdt());
    }
};

std::vector<hheavyhiggs::HChargedSemiBranch * > hheavyhiggs::HChargedSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");
    std::vector<hheavyhiggs::HChargedSemiBranch *> ChargedSemiBranches;

    HJets Jets = Event->GetJets()->GetStructuredJets();

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);

    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets,MissingEt, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsSemiTagger->GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);


    std::vector<HOctet44> Octets;
    for (const auto Jet : Jets) {
        for (const auto Triplet  : TripletsHadronic) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            hanalysis::HQuartet31 Quartet2(Triplet, Jet);
            for (const auto & Quartet1 : Quartets) {
                if (Quartet1.GetSinglet() == Quartet2.GetSinglet()) continue;
                if (Quartet1.GetSinglet() == Quartet2.GetTriplet().Singlet()) continue;
                if (Quartet1.GetSinglet() == Quartet2.GetTriplet().Doublet().Singlet1()) continue;
                if (Quartet1.GetSinglet() == Quartet2.GetTriplet().Doublet().Singlet2()) continue;
                if (Quartet1.GetTriplet().Singlet() == Quartet2.GetSinglet()) continue;
                if (Quartet1.GetTriplet().Singlet() == Quartet2.GetTriplet().Singlet()) continue;
                if (Quartet1.GetTriplet().Singlet() == Quartet2.GetTriplet().Doublet().Singlet1()) continue;
                if (Quartet1.GetTriplet().Singlet() == Quartet2.GetTriplet().Doublet().Singlet2()) continue;
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

    for (auto & Octet : Octets) {
      hheavyhiggs::HChargedSemiBranch *EventSemiBranch = new hheavyhiggs::HChargedSemiBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventSemiBranch, Octet);
        ChargedSemiBranches.push_back(EventSemiBranch);
    }

    return ChargedSemiBranches;

}

std::vector<int> hheavyhiggs::HChargedSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
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

            (*Branch) = *((HChargedSemiBranch *) EventClonesArray->At(Entry));

            HBdtBranch *Export = static_cast<HBdtBranch *>(BdtBranch->NewEntry());

            const float Bdt = Reader->EvaluateMVA(BdtMethodName);
            const float Error = Reader->GetMVAError();
            const float Rarity = Reader->GetRarity(GetBdtMethodName());
            const int Steps = 10;
            std::vector<float> Probabilities;
            for (int Step = Steps; Step > 0; --Step) {
                const float SignalFraction = float(Step) / Steps;
                const float Probability = Reader->GetProba(GetBdtMethodName(), SignalFraction);
                Probabilities.push_back(Probability);
            }
            Print(HDebug, "Bdt", Bdt, Error, Rarity);
            Export->Mass = Branch->HeavyHiggsMass;
            Export->EventTag = Branch->EventTag;
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
