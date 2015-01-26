# include "HChargedHiggsHadronicTagger.hh"

hanalysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger(const HBottomTagger &NewBottomTagger, const HWTagger &NewWTagger, const HTopHadronicTagger &NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader.SetMva(BottomTagger);
    WTagger = NewWTagger;
    WReader.SetMva(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.SetMva(TopHadronicTagger);

    SetTaggerName("ChargedHiggsHadronic");

//     Branch = new HChargedHiggsHadronicBranch();
    //JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
  SetTaggerName("ChargedHiggsHadronic");
}

hanalysis::HChargedHiggsHadronicTagger::~HChargedHiggsHadronicTagger()
{
    Print(HNotification, "Destructor");
    // delete Branch;
    //delete JetTag;
//     delete BottomReader;
//     delete WReader;
//     delete TopHadronicReader;

}

void hanalysis::HChargedHiggsHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch.HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch.TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch.TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch.TopDeltaPhi, "TopDeltaPhi"));

    Observables.push_back(NewObservable(&Branch.TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch.HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch.HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HChargedHiggsHadronicTagger::FillBranch(HChargedHiggsHadronicBranch *ChargedHiggsHadronicBranch, const hanalysis::HQuartet31 &Quartet)
{
    Print(HInformation, "FillPairTagger", Quartet.Bdt());

    ChargedHiggsHadronicBranch->HeavyHiggsMass = Quartet.Jet().m();
    ChargedHiggsHadronicBranch->HeavyHiggsPt = Quartet.Jet().pt();

    ChargedHiggsHadronicBranch->TopDeltaR = Quartet.DeltaR();
    ChargedHiggsHadronicBranch->TopDeltaRap = Quartet.DeltaRap();
    ChargedHiggsHadronicBranch->TopDeltaPhi = Quartet.DeltaPhi();

    ChargedHiggsHadronicBranch->TopBdt = Quartet.Bdt();
    ChargedHiggsHadronicBranch->HeavyHiggsTag = Quartet.Tag();

}

void hanalysis::HChargedHiggsHadronicTagger::FillBranch(const hanalysis::HQuartet31 &Quartet)
{
    Print(HInformation, "FillBranch", Quartet.Bdt());

    FillBranch(&Branch, Quartet);

}


std::vector< HChargedHiggsHadronicBranch * > hanalysis::HChargedHiggsHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HChargedHiggsHadronicBranch *> ChargedHiggsHadronicBranches;

    JetTag.HeavyParticles = {WId, TopId, ChargedHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    std::vector<HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);

    std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);


    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.Tag() != Tag) continue;
            Quartets.push_back(Quartet);
        }

    for (const auto & Quartet : Quartets) {
        HChargedHiggsHadronicBranch *ChargedHiggsHadronicBranch = new HChargedHiggsHadronicBranch();
        FillBranch(ChargedHiggsHadronicBranch, Quartet);
        ChargedHiggsHadronicBranches.push_back(ChargedHiggsHadronicBranch);
    }

    return ChargedHiggsHadronicBranches;

}

hanalysis::HObject::HTag hanalysis::HChargedHiggsHadronicTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Triple Tag");

    if (Quartet.Triplet().Tag() == HBackground)return HBackground;
//     if (Quartet.GetTriplet2().Tag() == HBackground)return HBackground;
    // TODO compare with semi leptonic case
    if (sgn(Quartet.Triplet().Singlet().user_index()) == sgn(Quartet.Singlet().user_index())) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HQuartet31> hanalysis::HChargedHiggsHadronicTagger::GetBdt(std::vector<hanalysis::HTriplet> Triplets,std::vector<fastjet::PseudoJet> Jets, const hanalysis::HReader &Reader)
{
    Print(HInformation, "Get Heavy Higgs Bdt");
    std::vector<hanalysis::HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
      for (const auto & Jet : Jets) {
        if (Triplet.Singlet() == Jet) continue;
        if (Triplet.Doublet().Singlet1() == Jet) continue;
        if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartets.push_back(Quartet);
            FillBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
        }

    return Quartets;
}
