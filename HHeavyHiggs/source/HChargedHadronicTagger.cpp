# include "HChargedHadronicTagger.hh"

hheavyhiggs::HChargedHadronicTagger::HChargedHadronicTagger(
  const hanalysis::HBottomTagger &NewBottomTagger,
  const hanalysis::HWTagger &NewWTagger,
  const hanalysis::HTopHadronicTagger &NewTopTagger,
  const hanalysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader.SetMva(BottomTagger);
    WTagger = NewWTagger;
    WReader.SetMva(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.SetMva(TopHadronicTagger);
    ChargedHiggsHadronicTagger = NewHeavyHiggsTagger;
    ChargedHiggsHadronicReader.SetMva(ChargedHiggsHadronicTagger);

    SetTaggerName("ChargedHadronic");

//     Branch = new hheavyhiggs::HChargedHadronicBranch();

    DefineVariables();

}

hheavyhiggs::HChargedHadronicTagger::~HChargedHadronicTagger()
{

    Print(HNotification , "Constructor");

    // delete Branch;
//     delete BottomReader;
//     delete TopHadronicReader;
//     delete ChargedHiggsHadronicReader;

}

void hheavyhiggs::HChargedHadronicTagger::FillBranch(hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch, const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

//     EventHadronicBranch->LeptonNumber = Octet.GetLeptonNumber();
//     EventHadronicBranch->JetNumber = Octet.GetJetNumber();
//     EventHadronicBranch->BottomNumber = Octet.GetBottomNumber();
//
//     EventHadronicBranch->ScalarHt = Octet.GetScalarHt();
//     EventHadronicBranch->HeavyParticleBdt = Octet.Bdt();
//
//     EventHadronicBranch->HeavyHiggsBdt = Octet.Quartet1().Bdt();
//     EventHadronicBranch->HeavyHiggsMass = Octet.GetQuartet1Jet().m();
//     EventHadronicBranch->HeavyHiggsPt = Octet.GetQuartet1Jet().pt();
//
//     EventHadronicBranch->BottomSumPt = Octet.GetQuartet2Jet().pt();
//     EventHadronicBranch->BottomDeltaPt = Octet.Quartet2().DeltaPt();
//
//     EventHadronicBranch->BottomDeltaRap = Octet.Quartet2().DeltaRap();
//     EventHadronicBranch->BottomDeltaPhi = Octet.Quartet2().DeltaPhi();
//     EventHadronicBranch->BottomDeltaR = Octet.Quartet2().DeltaR();
//
//     EventHadronicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
//     EventHadronicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
//     EventHadronicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();
//
//     EventHadronicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
//     EventHadronicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
//     EventHadronicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventHadronicBranch->EventTag = Octet.Tag();
}

void hheavyhiggs::HChargedHadronicTagger::FillBranch(const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

void hheavyhiggs::HChargedHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddObservable(Branch.LeptonNumber, "LeptonNumber");
    AddObservable(Branch.JetNumber, "JetNumber");
    AddObservable(Branch.BottomNumber, "BottomNumber");

    AddObservable(Branch.ScalarHt, "ScalarHt");
    AddObservable(Branch.HeavyParticleBdt, "HeavyParticleBdt");

    AddObservable(Branch.HeavyHiggsBdt, "HeavyHiggsBdt");
    AddObservable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddObservable(Branch.BottomSumPt, "BottomSumPt");
    AddObservable(Branch.BottomDeltaPt, "BottomDeltaPt");

    AddObservable(Branch.BottomDeltaRap, "BottomDeltaRap");
    AddObservable(Branch.BottomDeltaPhi, "BottomDeltaPhi");
    AddObservable(Branch.BottomDeltaR, "BottomDeltaR");

    AddObservable(Branch.HbSumDeltaRap, "HbSumDeltaRap");
    AddObservable(Branch.HbSumDeltaPhi, "HbSumDeltaPhi");
    AddObservable(Branch.HbSumDeltaR, "HbSumDeltaR");

    AddObservable(Branch.HbDeltaDeltaRap, "HbDeltaDeltaRap");
    AddObservable(Branch.HbDeltaDeltaPhi, "HbDeltaDeltaPhi");
    AddObservable(Branch.HbDeltaDeltaR, "HbDeltaDeltaR");

    AddSpectator(Branch.EventTag, "EventTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(HNotification, "Variables defined");

}

std::vector<hheavyhiggs::HChargedHadronicBranch * > hheavyhiggs::HChargedHadronicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::HTag Tag)
{
    std::vector<hheavyhiggs::HChargedHadronicBranch *> EventHadronicBranches;

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);
    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsHadronicTagger.GetBdt(Triplets, Jets, ChargedHiggsHadronicReader);

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
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & Octet : Octets) {
        hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch = new hheavyhiggs::HChargedHadronicBranch();
        Octet.SetLeptonNumber(Event.GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event.GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event.GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event.GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventHadronicBranch, Octet);
        EventHadronicBranches.push_back(EventHadronicBranch);
    }

    return EventHadronicBranches;

}
