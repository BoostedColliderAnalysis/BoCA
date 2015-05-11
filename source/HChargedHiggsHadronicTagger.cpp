# include "HChargedHiggsHadronicTagger.hh"

hanalysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger(const BottomTagger &NewBottomTagger, const HWHadronicTagger &NewWTagger, const HTopHadronicTagger &NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    TopHadronicTagger = NewTopTagger;
    TopHadronicReader.set_tagger(TopHadronicTagger);

    set_tagger_name("ChargedHiggsHadronic");
    DefineVariables();
}

hanalysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
  set_tagger_name("ChargedHiggsHadronic");
}

hanalysis::HChargedHiggsHadronicTagger::~HChargedHiggsHadronicTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HChargedHiggsHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddVariable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(Branch.TopDeltaR, "TopDeltaR");
    AddVariable(Branch.TopDeltaRap, "TopDeltaRap");
    AddVariable(Branch.TopDeltaPhi, "TopDeltaPhi");

    AddVariable(Branch.TopBdt, "TopBdt");

    AddSpectator(Branch.HeavyHiggsTag, "HeavyHiggsTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(HNotification, "Variables defined");

}

HChargedHiggsHadronicBranch hanalysis::HChargedHiggsHadronicTagger::GetBranch(const hanalysis::HQuartet31 &Quartet)
{
    Print(HInformation, "FillPairTagger", Quartet.Bdt());

    HChargedHiggsHadronicBranch ChargedHiggsHadronicBranch;
    ChargedHiggsHadronicBranch.HeavyHiggsMass = Quartet.Jet().m();
    ChargedHiggsHadronicBranch.HeavyHiggsPt = Quartet.Jet().pt();

    ChargedHiggsHadronicBranch.TopDeltaR = Quartet.DeltaR();
    ChargedHiggsHadronicBranch.TopDeltaRap = Quartet.DeltaRap();
    ChargedHiggsHadronicBranch.TopDeltaPhi = Quartet.DeltaPhi();

    ChargedHiggsHadronicBranch.TopBdt = Quartet.Bdt();
    ChargedHiggsHadronicBranch.HeavyHiggsTag = Quartet.Tag();
return ChargedHiggsHadronicBranch;
}


std::vector< HChargedHiggsHadronicBranch > hanalysis::HChargedHiggsHadronicTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get Higgs Tags");


    JetTag.HeavyParticles = {WId, TopId, ChargedHiggsId};
    Jets jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    std::vector<HDoublet> Doublets = WTagger.GetBdt(jets, WReader);

    std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, jets, TopHadronicReader);



    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : jets)  {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.Tag() != Tag) continue;
            Quartets.emplace_back(Quartet);
        }

    std::vector<HChargedHiggsHadronicBranch> ChargedHiggsHadronicBranches;
        for (const auto & Quartet : Quartets) ChargedHiggsHadronicBranches.emplace_back(GetBranch(Quartet));


    return ChargedHiggsHadronicBranches;

}

hanalysis::HObject::Tag hanalysis::HChargedHiggsHadronicTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Triple Tag");

    if (Quartet.Triplet().Tag() == kBackground)return kBackground;
//     if (Quartet.GetTriplet2().Tag() == HBackground)return HBackground;
    // TODO compare with semi leptonic case
    if (sgn(Quartet.Triplet().Singlet().user_index()) == sgn(Quartet.Singlet().user_index())) return kBackground;
    return kSignal;
}


std::vector<hanalysis::HQuartet31> hanalysis::HChargedHiggsHadronicTagger::GetBdt(std::vector<hanalysis::HTriplet> &Triplets, Jets &jets, const hanalysis::Reader &Reader)
{
    Print(HInformation, "Get Heavy Higgs Bdt");
    std::vector<hanalysis::HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
      for (const auto & Jet : jets)  {
        if (Triplet.Singlet() == Jet) continue;
        if (Triplet.Doublet().Singlet1() == Jet) continue;
        if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartets.emplace_back(Quartet);
            GetBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
        }

    return Quartets;
}
