# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger(HBottomTagger *NewBottomTagger, HWTagger *NewWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    SetTaggerName("TopHadronic");
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
    TopHadronicBranch->Pt = Triplet.GetTripletJet().pt();
    TopHadronicBranch->Rap = Triplet.GetTripletJet().rap();
    TopHadronicBranch->Phi = Triplet.GetTripletJet().phi();

    TopHadronicBranch->BottomPt = Triplet.GetJet().pt();
    TopHadronicBranch->WPt = Triplet.GetDoubletJet().pt();

    TopHadronicBranch->DeltaR = Triplet.GetDeltaR();
    TopHadronicBranch->DeltaRap = Triplet.GetDeltaRap();
    TopHadronicBranch->DeltaPhi = Triplet.GetDeltaPhi();

    TopHadronicBranch->Bdt = Triplet.GetBdt();
    TopHadronicBranch->Tag = Triplet.GetTag();
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
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch->WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}


std::vector<HTopHadronicBranch *> hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());

    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    std::vector<HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);

    std::vector<hanalysis::HTriplet>  Triplets;
    for (const auto & Jet : Jets)
        for (const auto & Doublet : Doublets) {
            if (Jet == Doublet.GetJet1()) continue;
            if (Jet == Doublet.GetJet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.GetTag() != Tag) continue;
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

hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    HJetInfo BJetInfo = Triplet.GetJet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    HJetInfo W1JetInfo = Triplet.GetDoublet().GetJet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(WId);
    HJetInfo W2JetInfo = Triplet.GetDoublet().GetJet2().user_info<HJetInfo>();
    W2JetInfo.ExtractFraction(WId);

    if (std::abs(W1JetInfo.GetMaximalId()) != WId) return HBackground;
    if (W1JetInfo.GetMaximalId() != W2JetInfo.GetMaximalId()) return HBackground;
    if (std::abs(BJetInfo.GetMaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.GetMaximalId()) != sgn(W1JetInfo.GetMaximalId())) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader *const TopHadronicReader)
{
    std::vector<HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.GetJet1()) continue;
            if (Jet == Doublet.GetJet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            FillBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader->GetBdt());
            Triplets.push_back(Triplet);
        }
    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    return Triplets;
}
