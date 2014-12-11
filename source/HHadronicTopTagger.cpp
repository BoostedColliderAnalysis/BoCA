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


void hanalysis::HHadronicTopTagger::FillBranch(HHadronicTopBranch *TopHadronicBranch, const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.GetBdt());

    TopHadronicBranch->Mass = Triplet.GetTripletJet().m();
    TopHadronicBranch->JetPt = Triplet.GetJet().pt();
    TopHadronicBranch->WPt = Triplet.GetDoubletJet().pt();
    TopHadronicBranch->DeltaR = Triplet.GetDeltaR();
    TopHadronicBranch->DeltaRap = Triplet.GetDeltaRap();
    TopHadronicBranch->DeltaPhi = Triplet.GetDeltaPhi();
    TopHadronicBranch->WBottomBdt = Triplet.GetBdt();
    TopHadronicBranch->TopTag = Triplet.GetTag();
}

void hanalysis::HHadronicTopTagger::FillBranch(const hanalysis::HTriplet &PairJetPair)
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
    Observables.push_back(NewObservable(&Branch->WBottomBdt, "WBottomBdt"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}


std::vector<HHadronicTopBranch *> hanalysis::HHadronicTopTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {WId, TopId, HiggsId, HeavyHiggsId, CpvHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());


    for (auto Jet = Jets.begin(); Jet != Jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = Jets.erase(Jet);
        } else {
            HJetInfo *JetInfo = new HJetInfo;
            BottomTagger->FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Jet).set_user_info(JetInfo);
            ++Jet;
        }
    }

    std::vector<hanalysis::HTriplet>  TopTriples;
    for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2) {
            for (auto Jet3 = Jet2 + 1; Jet3 != JetsEnd; ++Jet3) {
                std::vector<hanalysis::HTriplet> Triples = FillTriple(*Jet1, *Jet2, *Jet3, State);
                if (Triples.size() > 0)TopTriples.insert(TopTriples.end(), Triples.begin(), Triples.end());
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

std::vector<hanalysis::HTriplet> hanalysis::HHadronicTopTagger::FillTriple(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2, const fastjet::PseudoJet &Jet3, const hanalysis::HObject::HState State)
{

    std::vector<hanalysis::HTriplet>  TopTriples;

    HDoublet JetPair12(Jet1, Jet2);
    if (GetTripleTag(JetPair12, Jet3) == State) {
        WTagger->FillBranch(JetPair12);
        JetPair12.SetBdt(HadronicWReader->GetBdt());
        hanalysis::HTriplet TopTriple1(JetPair12, Jet3);
        TopTriple1.SetTag(State);
        TopTriples.push_back(TopTriple1);
    }

    HDoublet JetPair23(Jet2, Jet3);
    if (GetTripleTag(JetPair23, Jet1) == State) {
        WTagger->FillBranch(JetPair23);
        JetPair23.SetBdt(HadronicWReader->GetBdt());
        hanalysis::HTriplet TopTriple2(JetPair23, Jet1);
        TopTriple2.SetTag(State);
        TopTriples.push_back(TopTriple2);
    }

    HDoublet JetPair13(Jet1, Jet3);
    if (GetTripleTag(JetPair13, Jet2) == State) {
        WTagger->FillBranch(JetPair13);
        JetPair13.SetBdt(HadronicWReader->GetBdt());
        hanalysis::HTriplet TopTriple3(JetPair13, Jet2);
        TopTriple3.SetTag(State);
        TopTriples.push_back(TopTriple3);
    }

    return TopTriples;

}

hanalysis::HObject::HState hanalysis::HHadronicTopTagger::GetTripleTag(const HDoublet &JetPair, const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Jet.user_index() != TopId)) return HBackground;
    if (JetPair.GetJet1().user_index() != JetPair.GetJet2().user_index()) return HBackground;
    if (std::abs(JetPair.GetJet1().user_index()) != WId) return HBackground;
    if (sgn(JetPair.GetJet1().user_index()) != sgn(Jet.user_index())) return HBackground;
    return HSignal;
}
