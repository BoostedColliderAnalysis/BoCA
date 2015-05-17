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

void hheavyhiggs::HChargedHadronicTagger::FillBranch(hheavyhiggs::HChargedHadronicBranch *eventHadronicBranch, const HOctet44 &Octet)
{
    Print(kInformation, "FillPairTagger", Octet.Bdt());

//     eventHadronicBranch->LeptonNumber = Octet.GetLeptonNumber();
//     eventHadronicBranch->JetNumber = Octet.GetJetNumber();
//     eventHadronicBranch->BottomNumber = Octet.GetBottomNumber();
//
//     eventHadronicBranch->ScalarHt = Octet.GetScalarHt();
//     eventHadronicBranch->HeavyParticleBdt = Octet.Bdt();
//
//     eventHadronicBranch->HeavyHiggsBdt = Octet.Quartet1().Bdt();
//     eventHadronicBranch->HeavyHiggsMass = Octet.GetQuartet1Jet().m();
//     eventHadronicBranch->HeavyHiggsPt = Octet.GetQuartet1Jet().pt();
//
//     eventHadronicBranch->BottomSumPt = Octet.GetQuartet2Jet().pt();
//     eventHadronicBranch->BottomDeltaPt = Octet.Quartet2().DeltaPt();
//
//     eventHadronicBranch->BottomDeltaRap = Octet.Quartet2().DeltaRap();
//     eventHadronicBranch->BottomDeltaPhi = Octet.Quartet2().DeltaPhi();
//     eventHadronicBranch->BottomDeltaR = Octet.Quartet2().DeltaR();
//
//     eventHadronicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
//     eventHadronicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
//     eventHadronicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();
//
//     eventHadronicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
//     eventHadronicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
//     eventHadronicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    eventHadronicBranch->eventTag = Octet.Tag();
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
    std::vector<analysis::HQuartet31> Quartets = ChargedHiggsHadronicTagger.GetBdt(triplets, jets, ChargedHiggsHadronicReader);

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
        hheavyhiggs::HChargedHadronicBranch *eventHadronicBranch = new hheavyhiggs::HChargedHadronicBranch();
        Octet.SetLeptonNumber(event.Leptons().GetLeptonJets().size());
        Octet.SetJetNumber(event.hadrons().GetJets().size());
        Octet.SetBottomNumber(event.hadrons().GetBottomJets().size());
        Octet.SetScalarHt(event.hadrons().GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(eventHadronicBranch, Octet);
        eventHadronicBranches.emplace_back(eventHadronicBranch);
    }

    return eventHadronicBranches;

}
