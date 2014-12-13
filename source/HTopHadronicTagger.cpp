# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger(HBottomTagger *NewBottomTagger, HWTagger *NewWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    WTagger = NewWTagger;
    WReader = new HReader(WTagger);

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
    delete WReader;
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

    Jets = BottomTagger->GetBottomBdt(Jets, BottomReader);

    std::vector<HDoublet> Doublets = WTagger->GetWBdt(Jets, WReader, State);

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



    std::vector<HTopHadronicBranch *> HadronicTopBranches;
    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *HadronicTopBranch = new HTopHadronicBranch();
        FillBranch(HadronicTopBranch, Triplet);
        HadronicTopBranches.push_back(HadronicTopBranch);
    }


    return HadronicTopBranches;

}

hanalysis::HObject::HState hanalysis::HTopHadronicTagger::GetTripletTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Triplet.GetJet().user_index()) != TopId) return HBackground;
    if (Triplet.GetDoublet().GetTag() == HBackground) return HBackground;
    if (sgn(Triplet.GetDoublet().GetJet1().user_index()) != sgn(Triplet.GetJet().user_index())) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetTopHadronicBdt(std::vector<HDoublet> &Doublets, HJets Jets, const HReader *const TopHadronicReader, const HState State)
{
    std::vector<HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.GetJet1()) continue;
            if (Jet == Doublet.GetJet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTripletTag(Triplet));
            if (State == HSignal && Triplet.GetTag() == HBackground) continue;
            FillBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader->GetBdt());
            Triplets.push_back(Triplet);
        }
    return Triplets;

}
