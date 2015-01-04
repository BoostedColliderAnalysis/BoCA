# include "HEventSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWSemiTagger *const NewWSemiTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopSemiTagger *const NewTopSemiTagger, hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HHeavyHiggsSemiTagger *const NewHeavyHiggsMixedTagger)
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

    SetTaggerName("EventSemi");

    Branch = new hheavyhiggs::HEventSemiBranch();

    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::HEventSemiTagger()
{
    //   DebugLevel = HDebug;

    Print(HNotification , "Constructor");

    SetTaggerName("EventSemi");
    Branch = new hheavyhiggs::HEventSemiBranch();

    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete WSemiReader;
    delete WReader;
    delete BottomReader;
    delete TopHadronicReader;
    delete TopSemiReader;
    delete HeavyHiggsSemiReader;

}

void hheavyhiggs::HEventSemiTagger::FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.GetBdt());

    EventSemiBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventSemiBranch->JetNumber = Octet.GetJetNumber();
    EventSemiBranch->BottomNumber = Octet.GetBottomNumber();

    EventSemiBranch->ScalarHt = Octet.GetScalarHt();
    EventSemiBranch->HeavyParticleBdt = Octet.GetBdt();

    EventSemiBranch->HeavyHiggsBdt = Octet.GetSextet().GetBdt();
    EventSemiBranch->HeavyHiggsMass = Octet.GetSextet().GetSextetJet().m();
    EventSemiBranch->HeavyHiggsPt = Octet.GetSextet().GetSextetJet().pt();

    EventSemiBranch->BottomSumPt = Octet.GetDoubletJet().pt();
    EventSemiBranch->BottomDeltaPt = Octet.GetDoublet().GetDeltaPt();

    EventSemiBranch->BottomDeltaRap = Octet.GetDoublet().GetDeltaRap();
    EventSemiBranch->BottomDeltaPhi = Octet.GetDoublet().GetPhiDelta();
    EventSemiBranch->BottomDeltaR = Octet.GetDoublet().GetDeltaR();

    EventSemiBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    EventSemiBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    EventSemiBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    EventSemiBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    EventSemiBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    EventSemiBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventSemiBranch->EventTag = Octet.GetTag();
}

void hheavyhiggs::HEventSemiTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}

void hheavyhiggs::HEventSemiTagger::DefineVariables()
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


struct SortBySextetMass {
    inline bool operator()(const HOctet &Octet1, const HOctet &Octet2) {
        return (Octet1.GetSextet().GetSextetJet().m() > Octet2.GetSextet().GetSextetJet().m());
    }
};

std::vector<hheavyhiggs::HEventSemiBranch * > hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");
    std::vector<hheavyhiggs::HEventSemiBranch *> EventSemiBranches;

    HJets Jets = Event->GetJets()->GetStructuredJets();

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);

    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger->GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);


    std::vector<HOctet> Octets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            hanalysis::HDoublet Doublet(*Jet1, *Jet2);
            for (const auto & Sextet : Sextets) {
                if (Sextet.GetTriplet1().GetJet() == *Jet1) continue;
                if (Sextet.GetTriplet1().GetJet() == *Jet2) continue;
                if (Sextet.GetTriplet2().GetJet() == *Jet1) continue;
                if (Sextet.GetTriplet2().GetJet() == *Jet2) continue;
                if (Sextet.GetTriplet2().GetDoublet().GetJet1() == *Jet1) continue;
                if (Sextet.GetTriplet2().GetDoublet().GetJet1() == *Jet2) continue;
                if (Sextet.GetTriplet2().GetDoublet().GetJet2() == *Jet1) continue;
                if (Sextet.GetTriplet2().GetDoublet().GetJet2() == *Jet2) continue;
                HOctet Octet(Sextet, Doublet);
                Octets.push_back(Octet);
            }
        }
    }

    if (Octets.size() > 1) {
        Print(HError, "more than one event");
        std::sort(Octets.begin(), Octets.end(), SortBySextetMass());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & Octet : Octets) {
        hheavyhiggs::HEventSemiBranch *EventSemiBranch = new hheavyhiggs::HEventSemiBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventSemiBranch, Octet);
        EventSemiBranches.push_back(EventSemiBranch);
    }

    return EventSemiBranches;

}

std::vector<int> hheavyhiggs::HEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt", EventBranchName);

    const int Steps = 10;
    std::vector<int> EventNumbers(Steps);


    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *BdtBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HBdtBranch::Class());

    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {

            (*Branch) = *((HEventSemiBranch *) EventClonesArray->At(Entry));

            HBdtBranch *Export = static_cast<HBdtBranch *>(BdtBranch->NewEntry());

            const float Bdt = Reader->EvaluateMVA(BdtMethodName);
            const float Error = Reader->GetMVAError();
            const float Rarity = Reader->GetRarity(GetBdtMethodName());
            const int Steps1 = 10;
            std::vector<float> Probabilities;
            for (int Step = Steps1; Step > 0; --Step) {
                const float SignalFraction = float(Step) / Steps1;
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


            for (int Step = 0; Step < Steps; ++Step) {
                const float Cut = (float(Step) / Steps - 0.5) * 2;
                if (Bdt > Cut) ++EventNumbers.at(Step);
            }


        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;

    return EventNumbers;


}
