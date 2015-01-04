# include "HChargedHiggsHadronicTagger.hh"

hanalysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger(HBottomTagger *const NewBottomTagger, HWTagger *const NewWTagger, HTopHadronicTagger *const NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    SetTaggerName("ChargedHiggsHadronic");

    Branch = new HChargedHiggsHadronicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HChargedHiggsHadronicTagger::~HChargedHiggsHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WReader;
    delete TopHadronicReader;

}

void hanalysis::HChargedHiggsHadronicTagger::FillBranch(HChargedHiggsHadronicBranch *ChargedHiggsHadronicBranch, const hanalysis::HQuartet31 &Quartet)
{
    Print(HInformation, "FillPairTagger", Quartet.GetBdt());

    ChargedHiggsHadronicBranch->HeavyHiggsMass = Quartet.GetQuartetJet().m();
    ChargedHiggsHadronicBranch->HeavyHiggsPt = Quartet.GetQuartetJet().pt();

    ChargedHiggsHadronicBranch->TopDeltaR = Quartet.GetDeltaR();
    ChargedHiggsHadronicBranch->TopDeltaRap = Quartet.GetDeltaRap();
    ChargedHiggsHadronicBranch->TopDeltaPhi = Quartet.GetDeltaPhi();

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

    ChargedHiggsHadronicBranch->TopBdt = Quartet.GetBdt();
    ChargedHiggsHadronicBranch->HeavyHiggsTag = Quartet.GetTag();

}

void hanalysis::HChargedHiggsHadronicTagger::DefineVariables()
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


std::vector< HChargedHiggsHadronicBranch * > hanalysis::HChargedHiggsHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HChargedHiggsHadronicBranch *> ChargedHiggsHadronicBranches;

    JetTag->HeavyParticles = {WId, TopId, ChargedHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetTruthBdt(Jets, BottomReader);

    std::vector<HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);

    std::vector<HTriplet> Triplets = TopHadronicTagger->GetBdt(Doublets, Jets, TopHadronicReader);


    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.GetJet() == Jet) continue;
            if (Triplet.GetDoublet().GetJet1() == Jet) continue;
            if (Triplet.GetDoublet().GetJet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.GetTag() != Tag) continue;
            Quartets.push_back(Quartet);
        }

    for (const auto & Quartet : Quartets) {
        HChargedHiggsHadronicBranch *ChargedHiggsHadronicBranch = new HChargedHiggsHadronicBranch();
        FillBranch(ChargedHiggsHadronicBranch, Quartet);
        ChargedHiggsHadronicBranches.push_back(ChargedHiggsHadronicBranch);
    }

    return ChargedHiggsHadronicBranches;

}

void hanalysis::HChargedHiggsHadronicTagger::FillBranch(const hanalysis::HQuartet31 &Quartet)
{
    Print(HInformation, "FillBranch", Quartet.GetBdt());

    FillBranch(Branch, Quartet);

}

hanalysis::HObject::HTag hanalysis::HChargedHiggsHadronicTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Triple Tag");

    if (Quartet.GetTriplet().GetTag() == HBackground)return HBackground;
//     if (Quartet.GetTriplet2().GetTag() == HBackground)return HBackground;
    // TODO compare with semi leptonic case
    if (sgn(Quartet.GetTriplet().GetJet().user_index()) == sgn(Quartet.GetSinglet().user_index())) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HQuartet31> hanalysis::HChargedHiggsHadronicTagger::GetBdt(std::vector<hanalysis::HTriplet> Triplets,std::vector<fastjet::PseudoJet> Jets, hanalysis::HReader *Reader)
{
    Print(HInformation, "Get Heavy Higgs Bdt");
    std::vector<hanalysis::HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
      for (const auto & Jet : Jets) {
        if (Triplet.GetJet() == Jet) continue;
        if (Triplet.GetDoublet().GetJet1() == Jet) continue;
        if (Triplet.GetDoublet().GetJet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartets.push_back(Quartet);
            FillBranch(Quartet);
            Quartet.SetBdt(Reader->GetBdt());
        }

    return Quartets;
}
