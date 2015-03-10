# include "HEventHadronicTagger.hh"

hheavyhiggs::HEventHadronicTagger::HEventHadronicTagger()
{
  Print(HNotification , "Constructor");
  SetTaggerName("HadronicEvent");
}

hheavyhiggs::HEventHadronicTagger::HEventHadronicTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWTagger &NewWTagger, const hanalysis::HTopHadronicTagger &NewTopTagger,const  hanalysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader.SetMva(BottomTagger);
    WTagger = NewWTagger;
    WReader.SetMva(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.SetMva(TopHadronicTagger);
    HeavyHiggsHadronicTagger = NewHeavyHiggsTagger;
    HeavyHiggsHadronicReader.SetMva(HeavyHiggsHadronicTagger);

    SetTaggerName("HadronicEvent");

//     Branch = new hheavyhiggs::HEventHadronicBranch();

    DefineVariables();

}

hheavyhiggs::HEventHadronicTagger::~HEventHadronicTagger()
{

    Print(HNotification , "Constructor");

    // delete Branch;
//     delete BottomReader;
//     delete TopHadronicReader;
//     delete HeavyHiggsHadronicReader;

}

void hheavyhiggs::HEventHadronicTagger::FillBranch(hheavyhiggs::HEventHadronicBranch *EventHadronicBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

//     EventHadronicBranch->LeptonNumber = Octet.LeptonNumber();
//     EventHadronicBranch->JetNumber = Octet.JetNumber();
//     EventHadronicBranch->BottomNumber = Octet.BottomNumber();

//     EventHadronicBranch->ScalarHt = Octet.ScalarHt();
    EventHadronicBranch->HeavyParticleBdt = Octet.Bdt();

    EventHadronicBranch->HeavyHiggsBdt = Octet.Sextet().Bdt();
    EventHadronicBranch->HeavyHiggsMass = Octet.Sextet().Jet().m();
    EventHadronicBranch->HeavyHiggsPt = Octet.Sextet().Jet().pt();

    EventHadronicBranch->BottomSumPt = Octet.DoubletJet().pt();
    EventHadronicBranch->BottomDeltaPt = Octet.Doublet().DeltaPt();

    EventHadronicBranch->BottomDeltaRap = Octet.Doublet().DeltaRap();
    EventHadronicBranch->BottomDeltaPhi = Octet.Doublet().DeltaPhi();
    EventHadronicBranch->BottomDeltaR = Octet.Doublet().DeltaR();

    EventHadronicBranch->HbSumDeltaRap = Octet.DeltaRap();
    EventHadronicBranch->HbSumDeltaPhi = Octet.DeltaPhi();
    EventHadronicBranch->HbSumDeltaR = Octet.DeltaR();

    EventHadronicBranch->HbDeltaDeltaRap = Octet.HbDeltaDeltaRap();
    EventHadronicBranch->HbDeltaDeltaPhi = Octet.HbDeltaDeltaPhi();
    EventHadronicBranch->HbDeltaDeltaR = Octet.HbDeltaDeltaR();

    EventHadronicBranch->EventTag = Octet.Tag();
}

void hheavyhiggs::HEventHadronicTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

void hheavyhiggs::HEventHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch.LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch.JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch.BottomNumber, "BottomNumber"));

    Observables.push_back(NewObservable(&Branch.ScalarHt, "ScalarHt"));
    Observables.push_back(NewObservable(&Branch.HeavyParticleBdt, "HeavyParticleBdt"));

    Observables.push_back(NewObservable(&Branch.HeavyHiggsBdt, "HeavyHiggsBdt"));
    Observables.push_back(NewObservable(&Branch.HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch.BottomSumPt, "BottomSumPt"));
    Observables.push_back(NewObservable(&Branch.BottomDeltaPt, "BottomDeltaPt"));

    Observables.push_back(NewObservable(&Branch.BottomDeltaRap, "BottomDeltaRap"));
    Observables.push_back(NewObservable(&Branch.BottomDeltaPhi, "BottomDeltaPhi"));
    Observables.push_back(NewObservable(&Branch.BottomDeltaR, "BottomDeltaR"));

    Observables.push_back(NewObservable(&Branch.HbSumDeltaRap, "HbSumDeltaRap"));
    Observables.push_back(NewObservable(&Branch.HbSumDeltaPhi, "HbSumDeltaPhi"));
    Observables.push_back(NewObservable(&Branch.HbSumDeltaR, "HbSumDeltaR"));

    Observables.push_back(NewObservable(&Branch.HbDeltaDeltaRap, "HbDeltaDeltaRap"));
    Observables.push_back(NewObservable(&Branch.HbDeltaDeltaPhi, "HbDeltaDeltaPhi"));
    Observables.push_back(NewObservable(&Branch.HbDeltaDeltaR, "HbDeltaDeltaR"));

    Spectators.push_back(NewObservable(&Branch.EventTag, "EventTag"));
    Spectators.push_back(NewObservable(&Branch.HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}

std::vector<hheavyhiggs::HEventHadronicBranch * > hheavyhiggs::HEventHadronicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::HTag Tag)
{
    std::vector<hheavyhiggs::HEventHadronicBranch *> EventHadronicBranches;

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);
    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsHadronicTagger.GetBdt(Triplets, HeavyHiggsHadronicReader);

    std::vector<HOctet> Octets;

    for (const auto & Jet1 : Jets)
        for (const auto & Jet2 : Jets) {
            if (Jet1 == Jet2) continue;
            hanalysis::HDoublet Doublet(Jet1,Jet2);
            for (const auto & Sextet : Sextets) {
                if (Jet1 == Sextet.Triplet1().Singlet()) continue;
                if (Jet1 == Sextet.Triplet1().Doublet().Singlet1()) continue;
                if (Jet1 == Sextet.Triplet1().Doublet().Singlet2()) continue;
                if (Jet1 == Sextet.Triplet2().Singlet()) continue;
                if (Jet1 == Sextet.Triplet2().Doublet().Singlet1()) continue;
                if (Jet1 == Sextet.Triplet2().Doublet().Singlet2()) continue;
                if (Jet2 == Sextet.Triplet1().Singlet()) continue;
                if (Jet2 == Sextet.Triplet1().Doublet().Singlet1()) continue;
                if (Jet2 == Sextet.Triplet1().Doublet().Singlet2()) continue;
                if (Jet2 == Sextet.Triplet2().Singlet()) continue;
                if (Jet2 == Sextet.Triplet2().Doublet().Singlet1()) continue;
                if (Jet2 == Sextet.Triplet2().Doublet().Singlet2()) continue;
                Octets.push_back(HOctet(Sextet, Doublet));
            }
        }

    if (Octets.size() > 1) {
      std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & Octet : Octets) {
        hheavyhiggs::HEventHadronicBranch *EventHadronicBranch = new hheavyhiggs::HEventHadronicBranch();
//         Octet.SetLeptonNumber(Event.GetLeptons()->GetLeptonJets().size());
//         Octet.SetJetNumber(Event.GetJets()->GetJets().size());
//         Octet.SetBottomNumber(Event.GetJets()->GetBottomJets().size());
//         Octet.SetScalarHt(Event.GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventHadronicBranch, Octet);
        EventHadronicBranches.push_back(EventHadronicBranch);
    }

    return EventHadronicBranches;

}
