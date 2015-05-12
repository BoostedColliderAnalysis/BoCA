# include "HChargedHadronicTagger.hh"

hheavyhiggs::HChargedHadronicTagger::HChargedHadronicTagger(
  const hanalysis::BottomTagger &NewBottomTagger,
  const hanalysis::HWHadronicTagger &NewWTagger,
  const hanalysis::HTopHadronicTagger &NewTopTagger,
  const hanalysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(kNotification , "Constructor");

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

    Print(kNotification , "Constructor");

    // delete Branch;
//     delete BottomReader;
//     delete TopHadronicReader;
//     delete ChargedHiggsHadronicReader;

}

void hheavyhiggs::HChargedHadronicTagger::FillBranch(hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch, const HOctet44 &Octet)
{
    Print(kInformation, "FillPairTagger", Octet.Bdt());

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
    Print(kInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

void hheavyhiggs::HChargedHadronicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

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

    Print(kNotification, "Variables defined");

}

std::vector<hheavyhiggs::HChargedHadronicBranch * > hheavyhiggs::HChargedHadronicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    std::vector<hheavyhiggs::HChargedHadronicBranch *> EventHadronicBranches;

    Jets jets = Event.GetJets()->GetStructuredJets();
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
    if (jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::Doublet> doublets = WTagger.GetBdt(jets, WReader);
    std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(doublets, jets, TopHadronicReader);
    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsHadronicTagger.GetBdt(triplets, jets, ChargedHiggsHadronicReader);

    std::vector<HOctet44> Octets;

    for (const auto Quartet1 : Quartets) {
        for (const auto Quartet2 :  Quartets) {
            if (Quartet1.singlet() == Quartet2.singlet()) continue;
            if (Quartet1.singlet() == Quartet2.triplet().singlet()) continue;
            if (Quartet1.singlet() == Quartet2.triplet().doublet().Singlet1()) continue;
            if (Quartet1.singlet() == Quartet2.triplet().doublet().Singlet2()) continue;
            if (Quartet1.triplet().singlet() == Quartet2.singlet()) continue;
            if (Quartet1.triplet().singlet() == Quartet2.triplet().singlet()) continue;
            if (Quartet1.triplet().singlet() == Quartet2.triplet().doublet().Singlet1()) continue;
            if (Quartet1.triplet().singlet() == Quartet2.triplet().doublet().Singlet2()) continue;
            if (Quartet1.triplet().doublet().Singlet1() == Quartet2.singlet()) continue;
            if (Quartet1.triplet().doublet().Singlet1() == Quartet2.triplet().singlet()) continue;
            if (Quartet1.triplet().doublet().Singlet1() == Quartet2.triplet().doublet().Singlet1()) continue;
            if (Quartet1.triplet().doublet().Singlet1() == Quartet2.triplet().doublet().Singlet2()) continue;
            if (Quartet1.triplet().doublet().Singlet2() == Quartet2.singlet()) continue;
            if (Quartet1.triplet().doublet().Singlet2() == Quartet2.triplet().singlet()) continue;
            if (Quartet1.triplet().doublet().Singlet2() == Quartet2.triplet().doublet().Singlet1()) continue;
            if (Quartet1.triplet().doublet().Singlet2() == Quartet2.triplet().doublet().Singlet2()) continue;
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
