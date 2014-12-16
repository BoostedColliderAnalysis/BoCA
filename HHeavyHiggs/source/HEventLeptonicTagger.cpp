# include "HEventLeptonicTagger.hh"

hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HTopLeptonicTagger *const NewTopTagger, hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    TopLeptonicTagger = NewTopTagger;
    TopLeptonicReader = new hanalysis::HReader(TopLeptonicTagger);
    HeavyHiggsLeptonicTagger = NewHeavyHiggsTagger;
    HeavyHiggsLeptonicReader = new hanalysis::HReader(HeavyHiggsLeptonicTagger);

    SetTaggerName("EventLeptonic");

    TestName = "EventLeptonic";

    Branch = new hheavyhiggs::HEventLeptonicBranch();

    DefineVariables();

}


hheavyhiggs::HEventLeptonicTagger::~HEventLeptonicTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete BottomReader;
    delete TopLeptonicReader;
    delete HeavyHiggsLeptonicReader;

}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.GetBdt());

    EventLeptonicBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventLeptonicBranch->JetNumber = Octet.GetJetNumber();
    EventLeptonicBranch->BottomNumber = Octet.GetBottomNumber();

    EventLeptonicBranch->ScalarHt = Octet.GetScalarHt();
    EventLeptonicBranch->HeavyParticleBdt = Octet.GetBdt();

    EventLeptonicBranch->HeavyHiggsBdt = Octet.GetSextet().GetBdt();
    EventLeptonicBranch->HeavyHiggsMass = Octet.GetSextet().GetSextetJet().m();
    EventLeptonicBranch->HeavyHiggsPt = Octet.GetSextet().GetSextetJet().pt();

    EventLeptonicBranch->BottomSumPt = Octet.GetDoubletJet().pt();
    EventLeptonicBranch->BottomDeltaPt = Octet.GetDoublet().GetDeltaPt();

    EventLeptonicBranch->BottomDeltaRap = Octet.GetDoublet().GetDeltaRap();
    EventLeptonicBranch->BottomDeltaPhi = Octet.GetDoublet().GetPhiDelta();
    EventLeptonicBranch->BottomDeltaR = Octet.GetDoublet().GetDeltaR();

    EventLeptonicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    EventLeptonicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    EventLeptonicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    EventLeptonicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    EventLeptonicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    EventLeptonicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventLeptonicBranch->EventTag = Octet.GetTag();
}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}

void hheavyhiggs::HEventLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

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

    Spectators.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));
    Spectators.push_back(NewObservable(&Branch->EventTag, "EventTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}

struct SortBySextetMass {
  inline bool operator()(const HOctet &Octet1, const HOctet &Octet2) {
    return (Octet1.GetSextet().GetSextetJet().m() > Octet2.GetSextet().GetSextetJet().m());
  }
};


std::vector<hheavyhiggs::HEventLeptonicBranch *> hheavyhiggs::HEventLeptonicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{

    HJets Jets = Event->GetJets()->GetStructuredJets();

    Jets = BottomTagger->GetTruthBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<hanalysis::HDoublet> TopDoublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger->GetBdt(TopDoublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<hanalysis::HDoublet> Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            hanalysis::HDoublet Doublet(*Jet1, *Jet2); // TODO Implemetn pair bdt here
            Doublets.push_back(Doublet);
        }

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.GetTriplet1().GetJet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet1().GetJet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetJet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetJet() == Doublet.GetJet2()) continue;
            HOctet Octet(Sextet, Doublet);
            Octets.push_back(Octet);
        }
    }

    if (Octets.size() > 1) {
        Print(HError, "more than one event");
        std::sort(Octets.begin(), Octets.end(), SortBySextetMass());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HEventLeptonicBranch *> EventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch = new hheavyhiggs::HEventLeptonicBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventLeptonicBranch, Octet);
        EventLeptonicBranches.push_back(EventLeptonicBranch);
    }

    return EventLeptonicBranches;

}



std::vector<int> hheavyhiggs::HEventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
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

            (*Branch) = *((HEventLeptonicBranch *) EventClonesArray->At(Entry));

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
                const float Cut = float(Step) / Steps2 / 2;
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






