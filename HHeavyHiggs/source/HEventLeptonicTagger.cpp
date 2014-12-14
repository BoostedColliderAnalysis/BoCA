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


std::vector<hheavyhiggs::HEventLeptonicBranch*> hheavyhiggs::HEventLeptonicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{

    HJets Jets = Event->GetJets()->GetStructuredJets();

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger->GetBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<HOctet> Octets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
          hanalysis::HDoublet Doublet(*Jet1,*Jet2);
            for (const auto & Sextet : Sextets) {
              if (Sextet.GetTriplet1().GetJet() == *Jet1) continue;
                if (Sextet.GetTriplet1().GetJet() == *Jet2) continue;
                if (Sextet.GetTriplet2().GetJet() == *Jet1) continue;
                if (Sextet.GetTriplet2().GetJet() == *Jet2) continue;
                HOctet Octet(Sextet, Doublet);
                Octets.push_back(Octet);
            }
        }
    }


    if (Octets.size() > 1) {
      Print(HError,"more than one event");
        std::sort(Octets.begin(), Octets.end(), SortByBdt());
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
