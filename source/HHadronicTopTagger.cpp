# include "HHadronicTopTagger.hh"

hanalysis::HHadronicTopTagger::HHadronicTopTagger(HBottomTagger *NewBottomTagger, HHadronicWTagger *NewHadronicWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader (BottomTagger);

    HadronicWTagger = NewHadronicWTagger;
    HadronicWReader = new HReader (HadronicWTagger);

    TaggerName = "HadronicTop";
    SignalNames = {"HadronicTop"};
    BackgroundNames = {"NotHadronicTop"};
    CandidateBranchName = "HadronicTop";

    Branch = new HHadronicTopBranch();
    JetTag = new HJetTag();

    DefineVariables();

}

hanalysis::HHadronicTopTagger::~HHadronicTopTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete HadronicWReader;
}

void hanalysis::HHadronicTopTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->WPt, "WPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->WBottomBdt, "WBottomTag"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}


std::vector<HHadronicTopBranch *> hanalysis::HHadronicTopTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId,HiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());


    if (State == HSignal) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;

                hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                BottomTagger->FillBranch(*Jet);
                JetInfo->SetBdt(BottomReader->GetBdt());
                (*Jet).set_user_info(JetInfo);
            }
        }
    } else if (State == HBackground) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId || std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == MixedJetId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;

                hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                BottomTagger->FillBranch(*Jet);
                JetInfo->SetBdt(BottomReader->GetBdt());
                (*Jet).set_user_info(JetInfo);
            }
        }
    }

    std::vector<hanalysis::HPairJetPair>  TopTriples;
    for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            for (HJets::iterator Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                HSuperStructure JetPair((*Jet1), (*Jet2));
                std::vector<hanalysis::HPairJetPair> Triple = FillTriple(*Jet1, *Jet2, *Jet3);
                TopTriples.insert(TopTriples.end(),Triple.begin(),Triple.end());
            }
        }
    }


    std::vector<HHadronicTopBranch *> LeptonicTopBranches;
    for (const auto & TopTriple : TopTriples) {
        HHadronicTopBranch *LeptonicTopBranch = new HHadronicTopBranch();
        FillBranch(LeptonicTopBranch, TopTriple);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }


    return LeptonicTopBranches;

}

std::vector<hanalysis::HPairJetPair> hanalysis::HHadronicTopTagger::FillTriple(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2, const fastjet::PseudoJet &Jet3)
{
    Print(HInformation, "Fill Triples");
    float Tag;
    if (Jet1.user_index() == Jet2.user_index() && Jet2.user_index() == Jet3.user_index() && Jet3.user_index() == TopId) Tag = 1;
    else if (Jet1.user_index() == Jet2.user_index() && Jet2.user_index() == Jet3.user_index() && Jet3.user_index() == MixedJetId) Tag = .5;
    else Tag = 0;

    std::vector<hanalysis::HPairJetPair>  TopTriples;

    HSuperStructure JetPair12(Jet1, Jet2);
    HadronicWTagger->FillBranch(JetPair12);
    JetPair12.SetBdt(HadronicWReader->GetBdt());
    hanalysis::HPairJetPair TopTriple1(JetPair12, Jet3);
    TopTriple1.SetTag(Tag);
    TopTriples.push_back(TopTriple1);

    HSuperStructure JetPair23(Jet2, Jet3);
    HadronicWTagger->FillBranch(JetPair23);
    JetPair23.SetBdt(HadronicWReader->GetBdt());
    hanalysis::HPairJetPair TopTriple2(JetPair23, Jet1);
    TopTriple2.SetTag(Tag);
    TopTriples.push_back(TopTriple2);

    HSuperStructure JetPair13(Jet1, Jet3);
    HadronicWTagger->FillBranch(JetPair13);
    JetPair13.SetBdt(HadronicWReader->GetBdt());
    hanalysis::HPairJetPair TopTriple3(JetPair13, Jet2);
    TopTriple3.SetTag(Tag);
    TopTriples.push_back(TopTriple3);

    return TopTriples;

}


void hanalysis::HHadronicTopTagger::FillBranch(const hanalysis::HPairJetPair &PairJetPair)
{
    Print(HInformation, "Fill Top Tagger", PairJetPair.GetBdt());

    FillBranch(Branch, PairJetPair);

}


void hanalysis::HHadronicTopTagger::FillBranch(HHadronicTopBranch *LeptonicTopBranch, const hanalysis::HPairJetPair &PairJetPair)
{
    Print(HInformation, "Fill Top Tagger", PairJetPair.GetBdt());

    LeptonicTopBranch->Mass = PairJetPair.GetInvariantMass();
    LeptonicTopBranch->JetPt = PairJetPair.GetJetPt();
    LeptonicTopBranch->WPt = PairJetPair.GetPairPt();
    LeptonicTopBranch->DeltaR = PairJetPair.GetDeltaR();
    LeptonicTopBranch->DeltaRap = PairJetPair.GetDeltaRap();
    LeptonicTopBranch->DeltaPhi = PairJetPair.GetDeltaPhi();
    LeptonicTopBranch->WBottomBdt = PairJetPair.GetBdt();
    LeptonicTopBranch->TopTag = PairJetPair.GetTag();

}
