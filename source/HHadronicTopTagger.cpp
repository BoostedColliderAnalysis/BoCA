# include "HHadronicTopTagger.hh"

hanalysis::HHadronicTopTagger::HHadronicTopTagger(HBottomTagger *NewBottomTagger, HWTagger *NewWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    WTagger = NewWTagger;
    HadronicWReader = new HReader(WTagger);

    TaggerName = "TopHadronic";
    SignalNames = {"TopHadronic"};
    BackgroundNames = {"NotTopHadronic"};
    CandidateBranchName = "TopHadronic";

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


void hanalysis::HHadronicTopTagger::FillBranch(HHadronicTopBranch *TopHadronicBranch, const hanalysis::HPairJetPair &PairJetPair)
{
    Print(HInformation, "Fill Top Tagger", PairJetPair.GetBdt());

    TopHadronicBranch->Mass = PairJetPair.GetInvariantMass();
    TopHadronicBranch->JetPt = PairJetPair.GetJetPt();
    TopHadronicBranch->WPt = PairJetPair.GetPairPt();
    TopHadronicBranch->DeltaR = PairJetPair.GetDeltaR();
    TopHadronicBranch->DeltaRap = PairJetPair.GetDeltaRap();
    TopHadronicBranch->DeltaPhi = PairJetPair.GetDeltaPhi();
    TopHadronicBranch->WBottomBdt = PairJetPair.GetBdt();
    TopHadronicBranch->TopTag = PairJetPair.GetTag();
}

void hanalysis::HHadronicTopTagger::FillBranch(const hanalysis::HPairJetPair &PairJetPair)
{
    Print(HInformation, "Fill Top Tagger", PairJetPair.GetBdt());
    FillBranch(Branch, PairJetPair);
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

    JetTag->HeavyParticles = {WId, TopId, HiggsId, HeavyHiggsId, CpvHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());

    HJets TopJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {
        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == MixedJetId) continue;

        Jet.set_user_index(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId());
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId) JetInfo->SetTag(1);
        else if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == WId) JetInfo->SetTag(1);
        else JetInfo->SetTag(0);

        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);

        if (JetInfo->GetTag() == 1) {
            TopJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }

    std::vector<hanalysis::HPairJetPair>  TopTriples;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            for (auto Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                std::vector<hanalysis::HPairJetPair> Triples = FillTriple(*Jet1, *Jet2, *Jet3);
                TopTriples.insert(TopTriples.end(), Triples.begin(), Triples.end());
            }
        }
    }

    std::vector<HHadronicTopBranch *> HadronicTopBranches;
    for (const auto & TopTriple : TopTriples) {
        HHadronicTopBranch *HadronicTopBranch = new HHadronicTopBranch();
        FillBranch(HadronicTopBranch, TopTriple);
        HadronicTopBranches.push_back(HadronicTopBranch);
    }


    return HadronicTopBranches;

}

std::vector<hanalysis::HPairJetPair> hanalysis::HHadronicTopTagger::FillTriple(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2, const fastjet::PseudoJet &Jet3)
{
    Print(HInformation, "Fill Triples");
    float Tag;
    if (Jet1.user_index() == Jet2.user_index() && Jet2.user_index() == Jet3.user_index() && (std::abs(Jet3.user_index()) == TopId || std::abs(Jet3.user_index()) == WId)) Tag = 1;
    else Tag = 0;

    std::vector<hanalysis::HPairJetPair>  TopTriples;

    HSuperStructure JetPair12(Jet1, Jet2);
    WTagger->FillBranch(JetPair12);
    JetPair12.SetBdt(HadronicWReader->GetBdt());
    hanalysis::HPairJetPair TopTriple1(JetPair12, Jet3);
    TopTriple1.SetTag(GetTripleTag(JetPair12, Jet3));
    TopTriples.push_back(TopTriple1);

    HSuperStructure JetPair23(Jet2, Jet3);
    WTagger->FillBranch(JetPair23);
    JetPair23.SetBdt(HadronicWReader->GetBdt());
    hanalysis::HPairJetPair TopTriple2(JetPair23, Jet1);
    TopTriple2.SetTag(GetTripleTag(JetPair23, Jet1));
    TopTriples.push_back(TopTriple2);

    HSuperStructure JetPair13(Jet1, Jet3);
    WTagger->FillBranch(JetPair13);
    JetPair13.SetBdt(HadronicWReader->GetBdt());
    hanalysis::HPairJetPair TopTriple3(JetPair13, Jet2);
    TopTriple3.SetTag(GetTripleTag(JetPair13, Jet2));
    TopTriples.push_back(TopTriple3);

    return TopTriples;

}

bool hanalysis::HHadronicTopTagger::GetTripleTag(const HSuperStructure &JetPair,const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Jet.user_index() != TopId)) return 0;
    if (JetPair.GetJet1().user_index() != JetPair.GetJet2().user_index()) return 0;
    if (std::abs(JetPair.GetJet1().user_index()) != WId) return 0;
    return 1;
}
