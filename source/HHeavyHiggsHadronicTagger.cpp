# include "HHeavyHiggsHadronicTagger.hh"

hanalysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger, HTopHadronicTagger *const NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    SetTaggerName("HeavyHiggsHadronic");

    Branch = new HHeavyHiggsHadronicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsHadronicTagger::~HHeavyHiggsHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WReader;
    delete TopHadronicReader;

}

void hanalysis::HHeavyHiggsHadronicTagger::FillBranch(HHeavyHiggsHadronicBranch *HeavyHiggsHadronicBranch, const hanalysis::HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());

    HeavyHiggsHadronicBranch->HeavyHiggsMass = Sextet.Jet().m();
    HeavyHiggsHadronicBranch->HeavyHiggsPt = Sextet.Jet().pt();

    HeavyHiggsHadronicBranch->TopDeltaR = Sextet.DeltaR();
    HeavyHiggsHadronicBranch->TopDeltaRap = Sextet.DeltaRap();
    HeavyHiggsHadronicBranch->TopDeltaPhi = Sextet.DeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();

    HeavyHiggsHadronicBranch->TopBdt = Sextet.Bdt();
    HeavyHiggsHadronicBranch->HeavyHiggsTag = Sextet.Tag();

}

void hanalysis::HHeavyHiggsHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

//     Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}


std::vector< HHeavyHiggsHadronicBranch * > hanalysis::HHeavyHiggsHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsHadronicBranch *> HeavyHiggsHadronicBranches;

    JetTag->HeavyParticles = {WId, TopId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    std::vector<HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);

    std::vector<HTriplet> Triplets = TopHadronicTagger->GetBdt(Doublets, Jets, TopHadronicReader);


    std::vector<HSextet> Sextets;
    for (const auto & Triplet1 : Triplets)
        for (const auto & Triplet2 : Triplets) {
            if (Triplet1.Singlet() == Triplet2.Singlet()) continue;
            if (Triplet1.Singlet() == Triplet2.Doublet().Singlet1()) continue;
            if (Triplet1.Singlet() == Triplet2.Doublet().Singlet2()) continue;
            if (Triplet1.Doublet().Singlet1() == Triplet2.Singlet()) continue;
            if (Triplet1.Doublet().Singlet1() == Triplet2.Doublet().Singlet1()) continue;
            if (Triplet1.Doublet().Singlet1() == Triplet2.Doublet().Singlet2()) continue;
            if (Triplet1.Doublet().Singlet2() == Triplet2.Singlet()) continue;
            if (Triplet1.Doublet().Singlet2() == Triplet2.Doublet().Singlet1()) continue;
            if (Triplet1.Doublet().Singlet2() == Triplet2.Doublet().Singlet2()) continue;
            HSextet Sextet(Triplet1, Triplet2);
            Sextet.SetTag(GetTag(Sextet));
            if (Sextet.Tag() != Tag) continue;
            Sextets.push_back(Sextet);
        }

    for (const auto & Sextet : Sextets) {
        HHeavyHiggsHadronicBranch *HeavyHiggsHadronicBranch = new HHeavyHiggsHadronicBranch();
        FillBranch(HeavyHiggsHadronicBranch, Sextet);
        HeavyHiggsHadronicBranches.push_back(HeavyHiggsHadronicBranch);
    }

    return HeavyHiggsHadronicBranches;

}

void hanalysis::HHeavyHiggsHadronicTagger::FillBranch(const hanalysis::HSextet &Sextet)
{
    Print(HInformation, "FillBranch", Sextet.Bdt());

    FillBranch(Branch, Sextet);

}

hanalysis::HObject::HTag hanalysis::HHeavyHiggsHadronicTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get Triple Tag");

    if (Sextet.Triplet1().Tag() == HBackground)return HBackground;
    if (Sextet.Triplet2().Tag() == HBackground)return HBackground;
    if (sgn(Sextet.Triplet1().Singlet().user_index()) == sgn(Sextet.Triplet2().Singlet().user_index())) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HSextet> hanalysis::HHeavyHiggsHadronicTagger::GetBdt(std::vector<hanalysis::HTriplet> Triplets, hanalysis::HReader *Reader)
{
    Print(HInformation, "Get Heavy Higgs Bdt");
    std::vector<hanalysis::HSextet> Sextets;
    for (const auto & Triplet1 : Triplets)
      for (const auto & Triplet2 : Triplets) {
        if (Triplet1.Singlet() == Triplet2.Singlet()) continue;
        if (Triplet1.Singlet() == Triplet2.Doublet().Singlet1()) continue;
        if (Triplet1.Singlet() == Triplet2.Doublet().Singlet2()) continue;
        if (Triplet1.Doublet().Singlet1() == Triplet2.Singlet()) continue;
        if (Triplet1.Doublet().Singlet1() == Triplet2.Doublet().Singlet1()) continue;
        if (Triplet1.Doublet().Singlet1() == Triplet2.Doublet().Singlet2()) continue;
        if (Triplet1.Doublet().Singlet2() == Triplet2.Singlet()) continue;
        if (Triplet1.Doublet().Singlet2() == Triplet2.Doublet().Singlet1()) continue;
        if (Triplet1.Doublet().Singlet2() == Triplet2.Doublet().Singlet2()) continue;
            HSextet Sextet(Triplet1, Triplet2);
            Sextets.push_back(Sextet);
            FillBranch(Sextet);
            Sextet.SetBdt(Reader->Bdt());
        }

    return Sextets;
}
