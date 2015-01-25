# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger)
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
    TopWindow = 50;
    JetRadiusParameter = 1;
}

hanalysis::HTopHadronicTagger::~HTopHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WReader;
}

void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch->BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch->WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HTopHadronicTagger::FillBranch(HTopHadronicBranch *const TopHadronicBranch, const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    TopHadronicBranch->Mass = Triplet.Jet().m();
    TopHadronicBranch->Rap = Triplet.Jet().rap();
    TopHadronicBranch->Phi = Triplet.Jet().phi();
    TopHadronicBranch->Pt = Triplet.Jet().pt();
    TopHadronicBranch->Ht = Triplet.Ht();

    TopHadronicBranch->BottomPt = Triplet.Singlet().pt();
    TopHadronicBranch->WPt = Triplet.DoubletJet().pt();

    TopHadronicBranch->DeltaPt = Triplet.DeltaPt();
    TopHadronicBranch->DeltaR = Triplet.DeltaR();
    TopHadronicBranch->DeltaRap = Triplet.DeltaRap();
    TopHadronicBranch->DeltaPhi = Triplet.DeltaPhi();

    TopHadronicBranch->Bdt = Triplet.Bdt();
    TopHadronicBranch->Tag = Triplet.Tag();
}

void hanalysis::HTopHadronicTagger::FillBranch(const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());
    FillBranch(Branch, Triplet);
}

std::vector<HTopHadronicBranch *> hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

//     Jets = WTagger->BottomTagger->GetBdt(Jets, WTagger->BottomReader);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    std::vector<HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets;

    // combine jets with pairs
    for (const auto & Jet : Jets)
        for (const auto & Doublet : Doublets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.Tag() != Tag) continue;
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            Triplets.push_back(Triplet);
        }

    // choose single jets
    for (const auto & Jet : Jets) {
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        if (Jet.user_info<HJetInfo>().Tag() != Tag) continue;
        if (Tag == HSignal && std::abs(Jet.m() - TopMass) > TopWindow) continue;
        HTriplet Triplet(Jet);
        if(Jet.m() != Triplet.Jet().m()) Print(HError,"Triplet Mass Error",Jet.m(),Triplet.Jet().m());
        if(Jet.pt() != Triplet.Jet().pt()) Print(HError,"Triplet Pt Error",Jet.pt(),Triplet.Jet().pt());
        if(Jet != Triplet.Jet()) Print(HError,"Triplet Jet Error 1",Jet);
        if(Jet != Triplet.Jet()) Print(HError,"Triplet Jet Error 3",Triplet.Jet());
        Triplets.push_back(Triplet);
    }

    if (Tag == HSignal && Triplets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        std::sort(Triplets.begin(), Triplets.end(), SortByMass<HTriplet>(TopMass));
        Triplets.erase(Triplets.begin() + 1, Triplets.end()); // FIXME assuming maximal one hadronic top
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

    HJetInfo BJetInfo = Triplet.Singlet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    HJetInfo W1JetInfo = Triplet.Doublet().Singlet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(WId);
    HJetInfo W2JetInfo = Triplet.Doublet().Singlet2().user_info<HJetInfo>();
    W2JetInfo.ExtractFraction(WId);

    if (std::abs(W1JetInfo.MaximalId()) != WId) return HBackground;
    if (W1JetInfo.MaximalId() != W2JetInfo.MaximalId()) return HBackground;
    if (std::abs(BJetInfo.MaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.MaximalId()) != sgn(W1JetInfo.MaximalId())) return HBackground;
    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Get Jet Tag");

    HJetInfo JetInfo = Jet.user_info<HJetInfo>();
    JetInfo.ExtractFraction(TopId);

    if (JetInfo.MaximalId() != TopId) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader *const TopHadronicReader)
{

    std::vector<HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.Singlet1()) continue;
            if (Jet == Doublet.Singlet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            if (Triplet.DeltaR() < MinCellResolution) continue;
            if (std::abs(Triplet.Jet().rap()) > 100) continue;
            if (std::abs(Triplet.Jet().m()) < 10) continue;
            FillBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader->Bdt());
            Triplets.push_back(Triplet);
        }

    for (const auto & Jet : Jets) {
        HTriplet Triplet(Jet);
        if (std::abs(Triplet.Jet().rap()) > 100) continue;
        if (std::abs(Triplet.Jet().m()) < 10) continue;
        FillBranch(Triplet);
        Triplet.SetBdt(TopHadronicReader->Bdt());
        Triplets.push_back(Triplet);
    }


    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    return Triplets;
}
