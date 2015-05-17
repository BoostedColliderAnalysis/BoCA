# include "HChargedHiggsHadronicTagger.hh"

analysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger(const BottomTagger &NewBottomTagger, const WHadronicTagger &NewWTagger, const TopHadronicTagger &NewTopTagger)
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    top_hadronic_tagger = NewTopTagger;
    TopHadronicReader.set_tagger(top_hadronic_tagger);

    set_tagger_name("ChargedHiggsHadronic");
    DefineVariables();
}

analysis::HChargedHiggsHadronicTagger::HChargedHiggsHadronicTagger()
{
  //     DebugLevel = analysis::Object::kDebug;

  Print(kNotification, "Constructor");
  set_tagger_name("ChargedHiggsHadronic");
}

analysis::HChargedHiggsHadronicTagger::~HChargedHiggsHadronicTagger()
{
    Print(kNotification, "Destructor");
}

void analysis::HChargedHiggsHadronicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(Branch.TopDeltaR, "TopDeltaR");
    AddVariable(Branch.TopDeltaRap, "TopDeltaRap");
    AddVariable(Branch.TopDeltaPhi, "TopDeltaPhi");

    AddVariable(Branch.TopBdt, "TopBdt");

    AddSpectator(Branch.HeavyHiggsTag, "HeavyHiggsTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(kNotification, "Variables defined");

}

HChargedHiggsHadronicBranch analysis::HChargedHiggsHadronicTagger::GetBranch(const analysis::HQuartet31 &Quartet)
{
    Print(kInformation, "FillPairTagger", Quartet.Bdt());

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


std::vector< HChargedHiggsHadronicBranch > analysis::HChargedHiggsHadronicTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");


    JetTag.HeavyParticles = {WId, TopId, ChargedHiggsId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(JetTag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);

    std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);



    std::vector<HQuartet31> Quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets)  {
            if (triplet.singlet() == Jet) continue;
            if (triplet.doublet().Singlet1() == Jet) continue;
            if (triplet.doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(triplet, Jet);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.Tag() != Tag) continue;
            Quartets.emplace_back(Quartet);
        }

    std::vector<HChargedHiggsHadronicBranch> ChargedHiggsHadronicBranches;
        for (const auto & Quartet : Quartets) ChargedHiggsHadronicBranches.emplace_back(GetBranch(Quartet));


    return ChargedHiggsHadronicBranches;

}

analysis::Object::Tag analysis::HChargedHiggsHadronicTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(kInformation, "Get Triple Tag");

    if (Quartet.triplet().Tag() == kBackground)return kBackground;
//     if (Quartet.Gettriplet2().Tag() == HBackground)return HBackground;
    // TODO compare with semi leptonic case
    if (sgn(Quartet.triplet().singlet().user_index()) == sgn(Quartet.singlet().user_index())) return kBackground;
    return kSignal;
}


std::vector<analysis::HQuartet31> analysis::HChargedHiggsHadronicTagger::GetBdt(std::vector<analysis::Triplet> &triplets, Jets &jets, const analysis::Reader &Reader)
{
    Print(kInformation, "Get Heavy Higgs Bdt");
    std::vector<analysis::HQuartet31> Quartets;
    for (const auto & triplet : triplets)
      for (const auto & Jet : jets)  {
        if (triplet.singlet() == Jet) continue;
        if (triplet.doublet().Singlet1() == Jet) continue;
        if (triplet.doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(triplet, Jet);
            Quartets.emplace_back(Quartet);
            GetBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
        }

    return Quartets;
}
