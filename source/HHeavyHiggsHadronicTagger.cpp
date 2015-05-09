# include "HHeavyHiggsHadronicTagger.hh"

hanalysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
  set_tagger_name("HeavyHiggsHadronic");
}

hanalysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger(const BottomTagger &NewBottomTagger, const HWHadronicTagger &NewWTagger, const HTopHadronicTagger &NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.set_tagger(TopHadronicTagger);

    set_tagger_name("HeavyHiggsHadronic");
    DefineVariables();
}

hanalysis::HHeavyHiggsHadronicTagger::~HHeavyHiggsHadronicTagger()
{
    Print(HNotification, "Destructor");
}

HHeavyHiggsHadronicBranch hanalysis::HHeavyHiggsHadronicTagger::GetBranch(const hanalysis::HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());

    HHeavyHiggsHadronicBranch HeavyHiggsHadronicBranch;
    HeavyHiggsHadronicBranch.HeavyHiggsMass = Sextet.Jet().m();
    HeavyHiggsHadronicBranch.HeavyHiggsPt = Sextet.Jet().pt();

    HeavyHiggsHadronicBranch.TopDeltaR = Sextet.DeltaR();
    HeavyHiggsHadronicBranch.TopDeltaRap = Sextet.DeltaRap();
    HeavyHiggsHadronicBranch.TopDeltaPhi = Sextet.DeltaPhi();

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

    HeavyHiggsHadronicBranch.TopBdt = Sextet.Bdt();
    HeavyHiggsHadronicBranch.HeavyHiggsTag = Sextet.Tag();

    return HeavyHiggsHadronicBranch;
}

void hanalysis::HHeavyHiggsHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddVariable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(Branch.TopDeltaR, "TopDeltaR");
    AddVariable(Branch.TopDeltaRap, "TopDeltaRap");
    AddVariable(Branch.TopDeltaPhi, "TopDeltaPhi");

//     AddObservable(Branch.LargerWDeltaR, "LargerWDeltaR");
//     AddObservable(Branch.LargerWDeltaRap, "LargerWDeltaRap");
//     AddObservable(Branch.LargerWDeltaPhi, "LargerWDeltaPhi");
//
//     AddObservable(Branch.SmallerWDeltaR, "SmallerWDeltaR");
//     AddObservable(Branch.SmallerWDeltaRap, "SmallerWDeltaRap");
//     AddObservable(Branch.SmallerWDeltaPhi, "SmallerWDeltaPhi");
//
//     AddObservable(Branch.LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
//     AddObservable(Branch.LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
//     AddObservable(Branch.LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");
//
//     AddObservable(Branch.SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
//     AddObservable(Branch.SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
//     AddObservable(Branch.SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

    AddVariable(Branch.TopBdt, "TopBdt");

    AddSpectator(Branch.HeavyHiggsTag, "HeavyHiggsTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(HNotification, "Variables defined");

}


std::vector< HHeavyHiggsHadronicBranch> hanalysis::HHeavyHiggsHadronicTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsHadronicBranch> HeavyHiggsHadronicBranches;

    JetTag.HeavyParticles = {WId, TopId, HeavyHiggsId};
    Jets jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    std::vector<HDoublet> Doublets = WTagger.GetBdt(jets, WReader);

    std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, jets, TopHadronicReader);


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
            Sextets.emplace_back(Sextet);
        }

        for (const auto & Sextet : Sextets) HeavyHiggsHadronicBranches.emplace_back(GetBranch(Sextet));

    return HeavyHiggsHadronicBranches;

}

hanalysis::HObject::Tag hanalysis::HHeavyHiggsHadronicTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get Triple Tag");

    if (Sextet.Triplet1().Tag() == kBackground)return kBackground;
    if (Sextet.Triplet2().Tag() == kBackground)return kBackground;
    if (sgn(Sextet.Triplet1().Singlet().user_index()) == sgn(Sextet.Triplet2().Singlet().user_index())) return kBackground;
    return kSignal;
}


std::vector<hanalysis::HSextet> hanalysis::HHeavyHiggsHadronicTagger::GetBdt(std::vector< hanalysis::HTriplet > Triplets, const hanalysis::Reader &Reader)
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
            Sextets.emplace_back(Sextet);
            Branch = GetBranch(Sextet);
            Sextet.SetBdt(Reader.Bdt());
        }

    return Sextets;
}
