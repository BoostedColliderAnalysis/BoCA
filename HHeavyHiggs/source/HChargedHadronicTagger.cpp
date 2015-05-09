# include "HChargedHadronicTagger.hh"

hheavyhiggs::HChargedHadronicTagger::HChargedHadronicTagger(
  const hanalysis::BottomTagger &NewBottomTagger,
  const hanalysis::HWHadronicTagger &NewWTagger,
  const hanalysis::HTopHadronicTagger &NewTopTagger,
  const hanalysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.set_tagger(TopHadronicTagger);
    ChargedHiggsHadronicTagger = NewHeavyHiggsTagger;
    ChargedHiggsHadronicReader.set_tagger(ChargedHiggsHadronicTagger);

    set_tagger_name("ChargedHadronic");

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

    AddVariable(Branch.LeptonNumber, "LeptonNumber");
    AddVariable(Branch.JetNumber, "JetNumber");
    AddVariable(Branch.BottomNumber, "BottomNumber");

    AddVariable(Branch.ScalarHt, "ScalarHt");
    AddVariable(Branch.HeavyParticleBdt, "HeavyParticleBdt");

    AddVariable(Branch.HeavyHiggsBdt, "HeavyHiggsBdt");
    AddVariable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(Branch.BottomSumPt, "BottomSumPt");
    AddVariable(Branch.BottomDeltaPt, "BottomDeltaPt");

    AddVariable(Branch.BottomDeltaRap, "BottomDeltaRap");
    AddVariable(Branch.BottomDeltaPhi, "BottomDeltaPhi");
    AddVariable(Branch.BottomDeltaR, "BottomDeltaR");

    AddVariable(Branch.HbSumDeltaRap, "HbSumDeltaRap");
    AddVariable(Branch.HbSumDeltaPhi, "HbSumDeltaPhi");
    AddVariable(Branch.HbSumDeltaR, "HbSumDeltaR");

    AddVariable(Branch.HbDeltaDeltaRap, "HbDeltaDeltaRap");
    AddVariable(Branch.HbDeltaDeltaPhi, "HbDeltaDeltaPhi");
    AddVariable(Branch.HbDeltaDeltaR, "HbDeltaDeltaR");

    AddSpectator(Branch.EventTag, "EventTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(HNotification, "Variables defined");

}

std::vector<hheavyhiggs::HChargedHadronicBranch * > hheavyhiggs::HChargedHadronicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    std::vector<hheavyhiggs::HChargedHadronicBranch *> EventHadronicBranches;

    Jets jets = Event.GetJets()->GetStructuredJets();
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
    if (jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::HDoublet> Doublets = WTagger.GetBdt(jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, jets, TopHadronicReader);
    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsHadronicTagger.GetBdt(Triplets, jets, ChargedHiggsHadronicReader);

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
            Octets.emplace_back(HOctet44(Quartet1, Quartet2));
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
        EventHadronicBranches.emplace_back(EventHadronicBranch);
    }

    return EventHadronicBranches;

}
