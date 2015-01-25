# include "HChargedHadronicTagger.hh"

hheavyhiggs::HChargedHadronicTagger::HChargedHadronicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HWTagger *const NewWTagger, hanalysis::HTopHadronicTagger *const NewTopTagger, hanalysis::HChargedHiggsHadronicTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new hanalysis::HReader(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
    ChargedHiggsHadronicTagger = NewHeavyHiggsTagger;
    ChargedHiggsHadronicReader = new hanalysis::HReader(ChargedHiggsHadronicTagger);

    SetTaggerName("ChargedHadronic");

    Branch = new hheavyhiggs::HChargedHadronicBranch();

    DefineVariables();

}

hheavyhiggs::HChargedHadronicTagger::~HChargedHadronicTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete BottomReader;
    delete TopHadronicReader;
    delete ChargedHiggsHadronicReader;

}

void hheavyhiggs::HChargedHadronicTagger::FillBranch(hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch, const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    EventHadronicBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventHadronicBranch->JetNumber = Octet.GetJetNumber();
    EventHadronicBranch->BottomNumber = Octet.GetBottomNumber();

    EventHadronicBranch->ScalarHt = Octet.GetScalarHt();
    EventHadronicBranch->HeavyParticleBdt = Octet.Bdt();

    EventHadronicBranch->HeavyHiggsBdt = Octet.GetQuartet1().Bdt();
    EventHadronicBranch->HeavyHiggsMass = Octet.GetQuartet1Jet().m();
    EventHadronicBranch->HeavyHiggsPt = Octet.GetQuartet1Jet().pt();

    EventHadronicBranch->BottomSumPt = Octet.GetQuartet2Jet().pt();
    EventHadronicBranch->BottomDeltaPt = Octet.GetQuartet2().DeltaPt();

    EventHadronicBranch->BottomDeltaRap = Octet.GetQuartet2().DeltaRap();
    EventHadronicBranch->BottomDeltaPhi = Octet.GetQuartet2().DeltaPhi();
    EventHadronicBranch->BottomDeltaR = Octet.GetQuartet2().DeltaR();

    EventHadronicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    EventHadronicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    EventHadronicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    EventHadronicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    EventHadronicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    EventHadronicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventHadronicBranch->EventTag = Octet.Tag();
}

void hheavyhiggs::HChargedHadronicTagger::FillBranch(const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}

void hheavyhiggs::HChargedHadronicTagger::DefineVariables()
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

std::vector<hheavyhiggs::HChargedHadronicBranch * > hheavyhiggs::HChargedHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    std::vector<hheavyhiggs::HChargedHadronicBranch *> EventHadronicBranches;

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    if (Jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger->GetBdt(Doublets, Jets, TopHadronicReader);
    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsHadronicTagger->GetBdt(Triplets, Jets, ChargedHiggsHadronicReader);

    std::vector<HOctet44> Octets;

    for (const auto Quartet1 : Quartets) {
        for (const auto Quartet2 :  Quartets) {
            if (Quartet1.Singlet() == Quartet2.Singlet()) continue;
            if (Quartet1.Singlet() == Quartet2.Triplet().Singlet()) continue;
            if (Quartet1.Singlet() == Quartet2.Triplet().Doublet().Singlet1()) continue;
            if (Quartet1.Singlet() == Quartet2.Triplet().Doublet().Singlet2()) continue;
            if (Quartet1.Triplet().Singlet() == Quartet2.Singlet()) continue;
            if (Quartet1.Triplet().Singlet() == Quartet2.Triplet().Singlet()) continue;
            if (Quartet1.Triplet().Singlet() == Quartet2.Triplet().Doublet().Singlet1()) continue;
            if (Quartet1.Triplet().Singlet() == Quartet2.Triplet().Doublet().Singlet2()) continue;
            if (Quartet1.Triplet().Doublet().Singlet1() == Quartet2.Singlet()) continue;
            if (Quartet1.Triplet().Doublet().Singlet1() == Quartet2.Triplet().Singlet()) continue;
            if (Quartet1.Triplet().Doublet().Singlet1() == Quartet2.Triplet().Doublet().Singlet1()) continue;
            if (Quartet1.Triplet().Doublet().Singlet1() == Quartet2.Triplet().Doublet().Singlet2()) continue;
            if (Quartet1.Triplet().Doublet().Singlet2() == Quartet2.Singlet()) continue;
            if (Quartet1.Triplet().Doublet().Singlet2() == Quartet2.Triplet().Singlet()) continue;
            if (Quartet1.Triplet().Doublet().Singlet2() == Quartet2.Triplet().Doublet().Singlet1()) continue;
            if (Quartet1.Triplet().Doublet().Singlet2() == Quartet2.Triplet().Doublet().Singlet2()) continue;
            Octets.push_back(HOctet44(Quartet1, Quartet2));
        }
    }

    if (Octets.size() > 1) {
        std::sort(Octets.begin(), Octets.end(), SortByBdt());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & Octet : Octets) {
        hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch = new hheavyhiggs::HChargedHadronicBranch();
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
