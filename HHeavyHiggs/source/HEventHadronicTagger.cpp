# include "HEventHadronicTagger.hh"

hheavyhiggs::HEventHadronicTagger::HEventHadronicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopHadronicTagger *const NewTopTagger, hanalysis::HHeavyHiggsHadronicTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new hanalysis::HReader(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
    HeavyHiggsHadronicTagger = NewHeavyHiggsTagger;
    HeavyHiggsHadronicReader = new hanalysis::HReader(HeavyHiggsHadronicTagger);

    SetTaggerName("HadronicEvent");

    Branch = new hheavyhiggs::HEventHadronicBranch();

    DefineVariables();

}

hheavyhiggs::HEventHadronicTagger::~HEventHadronicTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete BottomReader;
    delete TopHadronicReader;
    delete HeavyHiggsHadronicReader;

}

void hheavyhiggs::HEventHadronicTagger::FillBranch(hheavyhiggs::HEventHadronicBranch *EventHadronicBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.GetBdt());

    EventHadronicBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventHadronicBranch->JetNumber = Octet.GetJetNumber();
    EventHadronicBranch->BottomNumber = Octet.GetBottomNumber();

    EventHadronicBranch->ScalarHt = Octet.GetScalarHt();
    EventHadronicBranch->HeavyParticleBdt = Octet.GetBdt();

    EventHadronicBranch->HeavyHiggsBdt = Octet.GetSextet().GetBdt();
    EventHadronicBranch->HeavyHiggsMass = Octet.GetSextet().GetSextetJet().m();
    EventHadronicBranch->HeavyHiggsPt = Octet.GetSextet().GetSextetJet().pt();

    EventHadronicBranch->BottomSumPt = Octet.GetDoubletJet().pt();
    EventHadronicBranch->BottomDeltaPt = Octet.GetDoublet().GetDeltaPt();

    EventHadronicBranch->BottomDeltaRap = Octet.GetDoublet().GetDeltaRap();
    EventHadronicBranch->BottomDeltaPhi = Octet.GetDoublet().GetPhiDelta();
    EventHadronicBranch->BottomDeltaR = Octet.GetDoublet().GetDeltaR();

    EventHadronicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    EventHadronicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    EventHadronicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    EventHadronicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    EventHadronicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    EventHadronicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventHadronicBranch->EventTag = Octet.GetTag();
}

void hheavyhiggs::HEventHadronicTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}

void hheavyhiggs::HEventHadronicTagger::DefineVariables()
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

std::vector<hheavyhiggs::HEventHadronicBranch * > hheavyhiggs::HEventHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    std::vector<hheavyhiggs::HEventHadronicBranch *> EventHadronicBranches;

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetTruthBdt(Jets, BottomReader);
    if (Jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger->GetBdt(Doublets, Jets, TopHadronicReader);
    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsHadronicTagger->GetBdt(Triplets, HeavyHiggsHadronicReader);

    std::vector<HOctet> Octets;

    for (const auto & Jet1 : Jets)
        for (const auto & Jet2 : Jets) {
            if (Jet1 == Jet2) continue;
            hanalysis::HDoublet Doublet(Jet1,Jet2);
            for (const auto & Sextet : Sextets) {
                if (Jet1 == Sextet.GetTriplet1().GetJet()) continue;
                if (Jet1 == Sextet.GetTriplet1().GetDoublet().GetJet1()) continue;
                if (Jet1 == Sextet.GetTriplet1().GetDoublet().GetJet2()) continue;
                if (Jet1 == Sextet.GetTriplet2().GetJet()) continue;
                if (Jet1 == Sextet.GetTriplet2().GetDoublet().GetJet1()) continue;
                if (Jet1 == Sextet.GetTriplet2().GetDoublet().GetJet2()) continue;
                if (Jet2 == Sextet.GetTriplet1().GetJet()) continue;
                if (Jet2 == Sextet.GetTriplet1().GetDoublet().GetJet1()) continue;
                if (Jet2 == Sextet.GetTriplet1().GetDoublet().GetJet2()) continue;
                if (Jet2 == Sextet.GetTriplet2().GetJet()) continue;
                if (Jet2 == Sextet.GetTriplet2().GetDoublet().GetJet1()) continue;
                if (Jet2 == Sextet.GetTriplet2().GetDoublet().GetJet2()) continue;
                Octets.push_back(HOctet(Sextet, Doublet));
            }
        }

    if (Octets.size() > 1) {
      std::sort(Octets.begin(), Octets.end(), SortByBdt());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & Octet : Octets) {
        hheavyhiggs::HEventHadronicBranch *EventHadronicBranch = new hheavyhiggs::HEventHadronicBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventHadronicBranch, Octet);
        EventHadronicBranches.push_back(EventHadronicBranch);
    }

    return EventHadronicBranches;

}
