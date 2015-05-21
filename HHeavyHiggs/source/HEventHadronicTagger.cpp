# include "HEventHadronicTagger.hh"

hheavyhiggs::EventHadronicTagger::EventHadronicTagger()
{
  Print(kNotification , "Constructor");
  set_tagger_name("Hadronicevent");
}

hheavyhiggs::EventHadronicTagger::EventHadronicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopHadronicTagger &NewTopTagger,const  analysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    top_hadronic_tagger = NewTopTagger;
    TopHadronicReader.set_tagger(top_hadronic_tagger);
    HeavyHiggsHadronicTagger = NewHeavyHiggsTagger;
    HeavyHiggsHadronicReader.set_tagger(HeavyHiggsHadronicTagger);

    set_tagger_name("Hadronicevent");

//     Branch = new hheavyhiggs::EventHadronicBranch();

    DefineVariables();

}

hheavyhiggs::EventHadronicTagger::~EventHadronicTagger()
{

    Print(kNotification , "Constructor");

    // delete Branch;
//     delete BottomReader;
//     delete TopHadronicReader;
//     delete HeavyHiggsHadronicReader;

}

void hheavyhiggs::EventHadronicTagger::FillBranch(hheavyhiggs::EventHadronicBranch *eventHadronicBranch, const Octet62 &octet)
{
    Print(kInformation, "FillPairTagger", octet.Bdt());

//     eventHadronicBranch->LeptonNumber = octet.LeptonNumber();
//     eventHadronicBranch->JetNumber = octet.JetNumber();
//     eventHadronicBranch->BottomNumber = octet.BottomNumber();

//     eventHadronicBranch->ScalarHt = octet.ScalarHt();
    eventHadronicBranch->HeavyParticleBdt = octet.Bdt();

    eventHadronicBranch->HeavyHiggsBdt = octet.sextet().Bdt();
    eventHadronicBranch->HeavyHiggsMass = octet.sextet().Jet().m();
    eventHadronicBranch->HeavyHiggsPt = octet.sextet().Jet().pt();

    eventHadronicBranch->BottomSumPt = octet.doublet_jet().pt();
    eventHadronicBranch->BottomDeltaPt = octet.doublet().DeltaPt();

    eventHadronicBranch->BottomDeltaRap = octet.doublet().DeltaRap();
    eventHadronicBranch->BottomDeltaPhi = octet.doublet().DeltaPhi();
    eventHadronicBranch->BottomDeltaR = octet.doublet().DeltaR();

    eventHadronicBranch->HbSumDeltaRap = octet.DeltaRap();
    eventHadronicBranch->HbSumDeltaPhi = octet.DeltaPhi();
    eventHadronicBranch->HbSumDeltaR = octet.DeltaR();

    eventHadronicBranch->HbDeltaDeltaRap = octet.HbDeltaDeltaRap();
    eventHadronicBranch->HbDeltaDeltaPhi = octet.HbDeltaDeltaPhi();
    eventHadronicBranch->HbDeltaDeltaR = octet.HbDeltaDeltaR();

    eventHadronicBranch->eventTag = octet.Tag();
}

void hheavyhiggs::EventHadronicTagger::FillBranch(const Octet62 &octet)
{
    Print(kInformation, "FillPairTagger");
    FillBranch(&Branch, octet);
}

void hheavyhiggs::EventHadronicTagger::DefineVariables()
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

std::vector<hheavyhiggs::EventHadronicBranch * > hheavyhiggs::EventHadronicTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    std::vector<hheavyhiggs::EventHadronicBranch *> eventHadronicBranches;

    Jets jets = event.hadrons().GetStructuredJets();
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    if (jets.size() < 8) return eventHadronicBranches;

    std::vector<analysis::Doublet> doublets = WTagger.GetBdt(jets, WReader);
    std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
    std::vector<analysis::Sextet> sextets = HeavyHiggsHadronicTagger.GetBdt(triplets, HeavyHiggsHadronicReader);

    std::vector<Octet62> octets;

    for (const auto & Jet1 : jets)
        for (const auto & Jet2 : jets)  {
            if (Jet1 == Jet2) continue;
            analysis::Doublet doublet(Jet1,Jet2);
            for (const auto & sextet : sextets) {
                if (Jet1 == sextet.triplet1().singlet()) continue;
                if (Jet1 == sextet.triplet1().doublet().Singlet1()) continue;
                if (Jet1 == sextet.triplet1().doublet().Singlet2()) continue;
                if (Jet1 == sextet.triplet2().singlet()) continue;
                if (Jet1 == sextet.triplet2().doublet().Singlet1()) continue;
                if (Jet1 == sextet.triplet2().doublet().Singlet2()) continue;
                if (Jet2 == sextet.triplet1().singlet()) continue;
                if (Jet2 == sextet.triplet1().doublet().Singlet1()) continue;
                if (Jet2 == sextet.triplet1().doublet().Singlet2()) continue;
                if (Jet2 == sextet.triplet2().singlet()) continue;
                if (Jet2 == sextet.triplet2().doublet().Singlet1()) continue;
                if (Jet2 == sextet.triplet2().doublet().Singlet2()) continue;
                octets.emplace_back(Octet62(sextet, doublet));
            }
        }

    if (octets.size() > 1) {
      std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    for (auto & octet : octets) {
        hheavyhiggs::EventHadronicBranch *eventHadronicBranch = new hheavyhiggs::EventHadronicBranch();
//         octet.SetLeptonNumber(event.leptons().GetLeptonJets().size());
//         octet.SetJetNumber(event.hadrons().GetJets().size());
//         octet.SetBottomNumber(event.hadrons().GetBottomJets().size());
//         octet.SetScalarHt(event.hadrons().GetScalarHt());
        octet.SetTag(Tag);
        FillBranch(eventHadronicBranch, octet);
        eventHadronicBranches.emplace_back(eventHadronicBranch);
    }

    return eventHadronicBranches;

}
