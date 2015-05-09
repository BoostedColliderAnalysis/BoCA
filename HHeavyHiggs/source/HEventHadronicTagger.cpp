# include "HEventHadronicTagger.hh"

hheavyhiggs::HEventHadronicTagger::HEventHadronicTagger()
{
  Print(HNotification , "Constructor");
  set_tagger_name("HadronicEvent");
}

hheavyhiggs::HEventHadronicTagger::HEventHadronicTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HWHadronicTagger &NewWTagger, const hanalysis::HTopHadronicTagger &NewTopTagger,const  hanalysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.set_tagger(TopHadronicTagger);
    HeavyHiggsHadronicTagger = NewHeavyHiggsTagger;
    HeavyHiggsHadronicReader.set_tagger(HeavyHiggsHadronicTagger);

    set_tagger_name("HadronicEvent");

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

std::vector<hheavyhiggs::HEventHadronicBranch * > hheavyhiggs::HEventHadronicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    std::vector<hheavyhiggs::HEventHadronicBranch *> EventHadronicBranches;

    Jets jets = Event.GetJets()->GetStructuredJets();
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    if (jets.size() < 8) return EventHadronicBranches;

    std::vector<hanalysis::HDoublet> Doublets = WTagger.GetBdt(jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, jets, TopHadronicReader);
    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsHadronicTagger.GetBdt(Triplets, HeavyHiggsHadronicReader);

    std::vector<HOctet> Octets;

    for (const auto & Jet1 : jets) 
        for (const auto & Jet2 : jets)  {
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
                Octets.emplace_back(HOctet(Sextet, Doublet));
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
        EventHadronicBranches.emplace_back(EventHadronicBranch);
    }

    return EventHadronicBranches;

}
