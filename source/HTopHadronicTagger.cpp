# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger(HBottomTagger *NewBottomTagger, HWTagger *NewWTagger)
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

    Branch = new HTopHadronicBranch();
    JetTag = new HJetTag();

    DefineVariables();

}

hanalysis::HTopHadronicTagger::~HTopHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete HadronicWReader;
}


void hanalysis::HTopHadronicTagger::FillBranch(HTopHadronicBranch *TopHadronicBranch, const hanalysis::HTriplet &Triplet)
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

void hanalysis::HTopHadronicTagger::FillBranch(const hanalysis::HTriplet &PairJetPair)
{
    Print(HInformation, "Fill Top Tagger", PairJetPair.GetBdt());
    FillBranch(Branch, PairJetPair);
}

void hanalysis::HTopHadronicTagger::DefineVariables()
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


std::vector<HTopHadronicBranch *> hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State)
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


    std::vector<hanalysis::HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2) {
            if (Jet1 == Jet2) continue;
            HDoublet Doublet(*Jet1, *Jet2);
            Doublet.SetTag(GetDoubletTag(Doublet));
            if (Doublet.GetTag() != State) continue;
            WTagger->FillBranch(Doublet);
            Doublet.SetBdt(HadronicWReader->GetBdt());
            Doublets.push_back(Doublet);
        }


    std::vector<hanalysis::HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.GetJet1()) continue;
            if (Jet == Doublet.GetJet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTripletTag(Triplet));
            if (Triplet.GetTag() != State) continue;
            Triplets.push_back(Triplet);
        }






    /*
        std::vector<hanalysis::HTriplet>  TopTriplets;
        for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1) {
            for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2) {
                for (auto Jet3 = Jet2 + 1; Jet3 != JetsEnd; ++Jet3) {
                    std::vector<hanalysis::HTriplet> Triplets = FillTriple(*Jet1, *Jet2, *Jet3, State);
                    if (Triplets.size() > 0)TopTriplets.insert(TopTriplets.end(), Triplets.begin(), Triplets.end());
                }
            }
        }*/

    std::vector<HTopHadronicBranch *> HadronicTopBranches;
    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *HadronicTopBranch = new HTopHadronicBranch();
        FillBranch(HadronicTopBranch, Triplet);
        HadronicTopBranches.push_back(HadronicTopBranch);
    }


    return HadronicTopBranches;

}

// std::vector<hanalysis::HTriplet> hanalysis::HTopHadronicTagger::FillTriple(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2, const fastjet::PseudoJet &Jet3, const hanalysis::HObject::HState State)
// {
//
//     std::vector<hanalysis::HTriplet>  TopTriplets;
//
//     HDoublet Doublet12(Jet1, Jet2);
//     if (GetTripletTag(Doublet12, Jet3) == State) {
//         WTagger->FillBranch(Doublet12);
//         Doublet12.SetBdt(HadronicWReader->GetBdt());
//         hanalysis::HTriplet TopTriple1(Doublet12, Jet3);
//         TopTriple1.SetTag(State);
//         TopTriplets.push_back(TopTriple1);
//     }
//
//     HDoublet JetPair23(Jet2, Jet3);
//     if (GetTripletTag(JetPair23, Jet1) == State) {
//         WTagger->FillBranch(JetPair23);
//         JetPair23.SetBdt(HadronicWReader->GetBdt());
//         hanalysis::HTriplet TopTriple2(JetPair23, Jet1);
//         TopTriple2.SetTag(State);
//         TopTriplets.push_back(TopTriple2);
//     }
//
//     HDoublet JetPair13(Jet1, Jet3);
//     if (GetTripletTag(JetPair13, Jet2) == State) {
//         WTagger->FillBranch(JetPair13);
//         JetPair13.SetBdt(HadronicWReader->GetBdt());
//         hanalysis::HTriplet TopTriple3(JetPair13, Jet2);
//         TopTriple3.SetTag(State);
//         TopTriplets.push_back(TopTriple3);
//     }
//
//     return TopTriplets;
//
// }

hanalysis::HObject::HState hanalysis::HTopHadronicTagger::GetDoubletTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Triple Tag");

    if (Doublet.GetJet1().user_index() != Doublet.GetJet2().user_index()) return HBackground;
    if (std::abs(Doublet.GetJet1().user_index()) != WId) return HBackground;
    return HSignal;
}

hanalysis::HObject::HState hanalysis::HTopHadronicTagger::GetTripletTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Triplet.GetJet().user_index() != TopId)) return HBackground;
    if (Triplet.GetTag() == HBackground) return HBackground;
    if (sgn(Triplet.GetDoublet().GetJet1().user_index()) != sgn(Triplet.GetJet().user_index())) return HBackground;
    return HSignal;
}
