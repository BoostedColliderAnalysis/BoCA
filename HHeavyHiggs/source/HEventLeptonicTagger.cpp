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

    TaggerName = "EventLeptonic";
    SignalNames = {"EventLeptonic"};
    BackgroundNames = {"NotEventLeptonic"};
    CandidateBranchName = "EventLeptonic";


    Branch = new hheavyhiggs::HEventLeptonicBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}


hheavyhiggs::HEventLeptonicTagger::~HEventLeptonicTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;
    delete HeavyHiggsLeptonicReader;

}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(hheavyhiggs::HEventLeptonicBranch *EventBranch, const HOctet &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger", HeavyHiggsEvent.GetBdt());

    EventBranch->LeptonNumber = HeavyHiggsEvent.GetLeptonNumber();
    EventBranch->JetNumber = HeavyHiggsEvent.GetJetNumber();
    EventBranch->BottomNumber = HeavyHiggsEvent.GetBottomNumber();

    EventBranch->ScalarHt = HeavyHiggsEvent.GetScalarHt();
    EventBranch->HeavyParticleBdt = HeavyHiggsEvent.GetBdt();

    EventBranch->HeavyHiggsBdt = HeavyHiggsEvent.GetSextet().GetBdt();
    EventBranch->HeavyHiggsMass = HeavyHiggsEvent.GetSextet().GetSextetJet().m();
    EventBranch->HeavyHiggsPt = HeavyHiggsEvent.GetSextet().GetSextetJet().pt();

    EventBranch->BottomSumPt = HeavyHiggsEvent.GetJetsJet().pt();
    EventBranch->BottomDeltaPt = HeavyHiggsEvent.GetBottomDeltaPt();

    EventBranch->BottomDeltaRap = HeavyHiggsEvent.GetBottomDeltaRap();
    EventBranch->BottomDeltaPhi = HeavyHiggsEvent.BottomDeltaPhi();
    EventBranch->BottomDeltaR = HeavyHiggsEvent.GetBottomDeltaR();

    EventBranch->HbSumDeltaRap = HeavyHiggsEvent.GetHbSumDeltaRap();
    EventBranch->HbSumDeltaPhi = HeavyHiggsEvent.GetHbSumDeltaPhi();
    EventBranch->HbSumDeltaR = HeavyHiggsEvent.GetHbSumDeltaR();

    EventBranch->HbDeltaDeltaRap = HeavyHiggsEvent.GetHbDeltaDeltaRap();
    EventBranch->HbDeltaDeltaPhi = HeavyHiggsEvent.GetHbDeltaDeltaPhi();
    EventBranch->HbDeltaDeltaR = HeavyHiggsEvent.GetHbDeltaDeltaR();

    EventBranch->EventTag = HeavyHiggsEvent.GetTag();
}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(const HOctet &HeavyHiggsEvent)
{
    Print(HInformation, "FillPairTagger");

    FillBranch(Branch, HeavyHiggsEvent);

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



struct SortHeavyHiggsEvents {
    inline bool operator()(const HOctet &Event1, const HOctet &Event2) {
        return (Event1.GetBdt() > Event2.GetBdt());
    }
};

std::vector<hheavyhiggs::HEventLeptonicBranch * > hheavyhiggs::HEventLeptonicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HState State)
{
    JetTag->HeavyParticles = {TopId, HeavyHiggsId, WId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBottomBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger->GetTopLeptonicBdt(Jets, Leptons, TopLeptonicReader, State);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger->GetHeavyHiggsLeptonicBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader, State);

    std::vector<HOctet> Octets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            for (const auto & Sextet : Sextets) {
              if (Sextet.GetTriplet1().GetJet() == *Jet1) continue;
                if (Sextet.GetTriplet1().GetJet() == *Jet2) continue;
                if (Sextet.GetTriplet2().GetJet() == *Jet1) continue;
                if (Sextet.GetTriplet2().GetJet() == *Jet2) continue;
                HOctet Octet(Sextet, *Jet1, *Jet2);
//                 Octet.SetTag(GetOctetTag(Octet));
//                 if(Octet.GetTag() != State) continue;
                Octets.push_back(Octet);
            }
        }
    }


    if (State == HSignal && Octets.size() > 1) {
      Print(HError,"more than one event");
        std::sort(Octets.begin(), Octets.end(), SortHeavyHiggsEvents());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HEventLeptonicBranch *> EventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch = new hheavyhiggs::HEventLeptonicBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(State);
        FillBranch(EventLeptonicBranch, Octet);
        EventLeptonicBranches.push_back(EventLeptonicBranch);
    }

    return EventLeptonicBranches;

}

hanalysis::HObject::HState hheavyhiggs::HEventLeptonicTagger::GetOctetTag(const HOctet &Octet)
{
    Print(HInformation, "Get Octet Tag");
    if (Octet.GetSextet().GetTag() == HBackground) return HBackground;
    if (std::abs(Octet.GetJet1().user_index()) != BottomId) return HBackground;
    if (Octet.GetJet1().user_index() != -Octet.GetJet1().user_index()) return HBackground;

    return HSignal;
}
