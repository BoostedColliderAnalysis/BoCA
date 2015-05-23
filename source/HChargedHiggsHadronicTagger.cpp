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

analysis::HChargedHiggsHadronicBranch analysis::HChargedHiggsHadronicTagger::GetBranch(const analysis::Quartet31 &quartet)
{
    Print(kInformation, "FillPairTagger", quartet.Bdt());

    HChargedHiggsHadronicBranch ChargedHiggsHadronicBranch;
    ChargedHiggsHadronicBranch.HeavyHiggsMass = quartet.Jet().m();
    ChargedHiggsHadronicBranch.HeavyHiggsPt = quartet.Jet().pt();

    ChargedHiggsHadronicBranch.TopDeltaR = quartet.DeltaR();
    ChargedHiggsHadronicBranch.TopDeltaRap = quartet.DeltaRap();
    ChargedHiggsHadronicBranch.TopDeltaPhi = quartet.DeltaPhi();

    ChargedHiggsHadronicBranch.TopBdt = quartet.Bdt();
    ChargedHiggsHadronicBranch.HeavyHiggsTag = quartet.Tag();
return ChargedHiggsHadronicBranch;
}


std::vector< analysis::HChargedHiggsHadronicBranch > analysis::HChargedHiggsHadronicTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");


    jet_tag.HeavyParticles = {WId, TopId, ChargedHiggsId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(jet_tag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);

    std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);



    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets)  {
            if (triplet.singlet() == Jet) continue;
            if (triplet.doublet().Singlet1() == Jet) continue;
            if (triplet.doublet().Singlet2() == Jet) continue;
            Quartet31 quartet(triplet, Jet);
            quartet.SetTag(GetTag(quartet));
            if (quartet.Tag() != Tag) continue;
            quartets.emplace_back(quartet);
        }

    std::vector<HChargedHiggsHadronicBranch> ChargedHiggsHadronicBranches;
        for (const auto & quartet : quartets) ChargedHiggsHadronicBranches.emplace_back(GetBranch(quartet));


    return ChargedHiggsHadronicBranches;

}

analysis::Object::Tag analysis::HChargedHiggsHadronicTagger::GetTag(const Quartet31 &quartet)
{
    Print(kInformation, "Get Triple Tag");

    if (quartet.triplet().Tag() == kBackground)return kBackground;
//     if (quartet.Gettriplet2().Tag() == HBackground)return HBackground;
    // TODO compare with semi leptonic case
    if (sgn(quartet.triplet().singlet().user_index()) == sgn(quartet.singlet().user_index())) return kBackground;
    return kSignal;
}


std::vector<analysis::Quartet31> analysis::HChargedHiggsHadronicTagger::GetBdt(std::vector<analysis::Triplet> &triplets, Jets &jets, const analysis::Reader &Reader)
{
    Print(kInformation, "Get Heavy Higgs Bdt");
    std::vector<analysis::Quartet31> quartets;
    for (const auto & triplet : triplets)
      for (const auto & Jet : jets)  {
        if (triplet.singlet() == Jet) continue;
        if (triplet.doublet().Singlet1() == Jet) continue;
        if (triplet.doublet().Singlet2() == Jet) continue;
            Quartet31 quartet(triplet, Jet);
            quartets.emplace_back(quartet);
            GetBranch(quartet);
            quartet.SetBdt(Reader.Bdt());
        }

    return quartets;
}
