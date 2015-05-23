# include "HChargedHadronicTagger.hh"

hheavyhiggs::HChargedHadronicTagger::HChargedHadronicTagger(
  const analysis::BottomTagger &NewBottomTagger,
  const analysis::WHadronicTagger &NewWTagger,
  const analysis::TopHadronicTagger &NewTopTagger,
  const analysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    top_hadronic_tagger = NewTopTagger;
    TopHadronicReader.set_tagger(top_hadronic_tagger);
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

void hheavyhiggs::HChargedHadronicTagger::FillBranch(hheavyhiggs::HChargedHadronicBranch *eventHadronicBranch, const Octet44 &octet)
{
    Print(kInformation, "FillPairTagger", octet.Bdt());

//     eventHadronicBranch->LeptonNumber = octet.GetLeptonNumber();
//     eventHadronicBranch->JetNumber = octet.GetJetNumber();
//     eventHadronicBranch->BottomNumber = octet.GetBottomNumber();
//
//     eventHadronicBranch->ScalarHt = octet.GetScalarHt();
//     eventHadronicBranch->HeavyParticleBdt = octet.Bdt();
//
//     eventHadronicBranch->HeavyHiggsBdt = octet.quartet1().Bdt();
//     eventHadronicBranch->HeavyHiggsMass = octet.Getquartet1Jet().m();
//     eventHadronicBranch->HeavyHiggsPt = octet.Getquartet1Jet().pt();
//
//     eventHadronicBranch->BottomSumPt = octet.Getquartet2Jet().pt();
//     eventHadronicBranch->BottomDeltaPt = octet.quartet2().DeltaPt();
//
//     eventHadronicBranch->BottomDeltaRap = octet.quartet2().DeltaRap();
//     eventHadronicBranch->BottomDeltaPhi = octet.quartet2().DeltaPhi();
//     eventHadronicBranch->BottomDeltaR = octet.quartet2().DeltaR();
//
//     eventHadronicBranch->HbSumDeltaRap = octet.GetHbSumDeltaRap();
//     eventHadronicBranch->HbSumDeltaPhi = octet.GetHbSumDeltaPhi();
//     eventHadronicBranch->HbSumDeltaR = octet.GetHbSumDeltaR();
//
//     eventHadronicBranch->HbDeltaDeltaRap = octet.GetHbDeltaDeltaRap();
//     eventHadronicBranch->HbDeltaDeltaPhi = octet.GetHbDeltaDeltaPhi();
//     eventHadronicBranch->HbDeltaDeltaR = octet.GetHbDeltaDeltaR();

    eventHadronicBranch->eventTag = octet.Tag();
}

void hheavyhiggs::HChargedHadronicTagger::FillBranch(const Octet44 &octet)
{
    Print(kInformation, "FillPairTagger");
    FillBranch(&Branch, octet);
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

    AddSpectator(Branch.eventTag, "eventTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(kNotification, "Variables defined");

}

std::vector<hheavyhiggs::HChargedHadronicBranch * > hheavyhiggs::HChargedHadronicTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    std::vector<hheavyhiggs::HChargedHadronicBranch *> eventHadronicBranches;

    Jets jets = event.hadrons().GetStructuredJets();
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
    if (jets.size() < 8) return eventHadronicBranches;

    std::vector<analysis::Doublet> doublets = WTagger.GetBdt(jets, WReader);
    std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
    std::vector<analysis::Quartet31> quartets = ChargedHiggsHadronicTagger.GetBdt(triplets, jets, ChargedHiggsHadronicReader);

    std::vector<Octet44> octets;

    for (const auto quartet1 : quartets) {
        for (const auto quartet2 :  quartets) {
            if (quartet1.singlet() == quartet2.singlet()) continue;
            if (quartet1.singlet() == quartet2.triplet().singlet()) continue;
            if (quartet1.singlet() == quartet2.triplet().doublet().Singlet1()) continue;
            if (quartet1.singlet() == quartet2.triplet().doublet().Singlet2()) continue;
            if (quartet1.triplet().singlet() == quartet2.singlet()) continue;
            if (quartet1.triplet().singlet() == quartet2.triplet().singlet()) continue;
            if (quartet1.triplet().singlet() == quartet2.triplet().doublet().Singlet1()) continue;
            if (quartet1.triplet().singlet() == quartet2.triplet().doublet().Singlet2()) continue;
            if (quartet1.triplet().doublet().Singlet1() == quartet2.singlet()) continue;
            if (quartet1.triplet().doublet().Singlet1() == quartet2.triplet().singlet()) continue;
            if (quartet1.triplet().doublet().Singlet1() == quartet2.triplet().doublet().Singlet1()) continue;
            if (quartet1.triplet().doublet().Singlet1() == quartet2.triplet().doublet().Singlet2()) continue;
            if (quartet1.triplet().doublet().Singlet2() == quartet2.singlet()) continue;
            if (quartet1.triplet().doublet().Singlet2() == quartet2.triplet().singlet()) continue;
            if (quartet1.triplet().doublet().Singlet2() == quartet2.triplet().doublet().Singlet1()) continue;
            if (quartet1.triplet().doublet().Singlet2() == quartet2.triplet().doublet().Singlet2()) continue;
            octets.emplace_back(Octet44(quartet1, quartet2));
        }
    }

    if (octets.size() > 1) {
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    for (auto & octet : octets) {
        hheavyhiggs::HChargedHadronicBranch *eventHadronicBranch = new hheavyhiggs::HChargedHadronicBranch();
        octet.SetLeptonNumber(event.leptons().GetLeptonJets().size());
        octet.SetJetNumber(event.hadrons().GetJets().size());
        octet.SetBottomNumber(event.hadrons().GetBottomJets().size());
        octet.SetScalarHt(event.hadrons().GetScalarHt());
        octet.SetTag(Tag);
        FillBranch(eventHadronicBranch, octet);
        eventHadronicBranches.emplace_back(eventHadronicBranch);
    }

    return eventHadronicBranches;

}
