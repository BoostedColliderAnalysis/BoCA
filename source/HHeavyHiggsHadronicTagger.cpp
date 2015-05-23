# include "HHeavyHiggsHadronicTagger.hh"

analysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger()
{
  //     DebugLevel = analysis::Object::kDebug;

  Print(kNotification, "Constructor");
  set_tagger_name("HeavyHiggsHadronic");
}

analysis::HHeavyHiggsHadronicTagger::HHeavyHiggsHadronicTagger(const BottomTagger &NewBottomTagger, const WHadronicTagger &NewWTagger, const TopHadronicTagger &NewTopTagger)
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    top_hadronic_tagger = NewTopTagger;
    TopHadronicReader.set_tagger(top_hadronic_tagger);

    set_tagger_name("HeavyHiggsHadronic");
    DefineVariables();
}

analysis::HHeavyHiggsHadronicTagger::~HHeavyHiggsHadronicTagger()
{
    Print(kNotification, "Destructor");
}

analysis::HHeavyHiggsHadronicBranch analysis::HHeavyHiggsHadronicTagger::GetBranch(const analysis::Sextet &sextet)
{
    Print(kInformation, "FillPairTagger", sextet.Bdt());

    HHeavyHiggsHadronicBranch HeavyHiggsHadronicBranch;
    HeavyHiggsHadronicBranch.HeavyHiggsMass = sextet.Jet().m();
    HeavyHiggsHadronicBranch.HeavyHiggsPt = sextet.Jet().pt();

    HeavyHiggsHadronicBranch.TopDeltaR = sextet.DeltaR();
    HeavyHiggsHadronicBranch.TopDeltaRap = sextet.DeltaRap();
    HeavyHiggsHadronicBranch.TopDeltaPhi = sextet.DeltaPhi();

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

    HeavyHiggsHadronicBranch.TopBdt = sextet.Bdt();
    HeavyHiggsHadronicBranch.HeavyHiggsTag = sextet.Tag();

    return HeavyHiggsHadronicBranch;
}

void analysis::HHeavyHiggsHadronicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

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

    Print(kNotification, "Variables defined");

}


std::vector< analysis::HHeavyHiggsHadronicBranch> analysis::HHeavyHiggsHadronicTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsHadronicBranch> HeavyHiggsHadronicBranches;

    jet_tag.HeavyParticles = {WId, TopId, HeavyHiggsId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(jet_tag);

//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);

    std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);


    std::vector<Sextet> sextets;
    for (const auto & triplet1 : triplets)
        for (const auto & triplet2 : triplets) {
            if (triplet1.singlet() == triplet2.singlet()) continue;
            if (triplet1.singlet() == triplet2.doublet().Singlet1()) continue;
            if (triplet1.singlet() == triplet2.doublet().Singlet2()) continue;
            if (triplet1.doublet().Singlet1() == triplet2.singlet()) continue;
            if (triplet1.doublet().Singlet1() == triplet2.doublet().Singlet1()) continue;
            if (triplet1.doublet().Singlet1() == triplet2.doublet().Singlet2()) continue;
            if (triplet1.doublet().Singlet2() == triplet2.singlet()) continue;
            if (triplet1.doublet().Singlet2() == triplet2.doublet().Singlet1()) continue;
            if (triplet1.doublet().Singlet2() == triplet2.doublet().Singlet2()) continue;
            Sextet sextet(triplet1, triplet2);
            sextet.SetTag(GetTag(sextet));
            if (sextet.Tag() != Tag) continue;
            sextets.emplace_back(sextet);
        }

        for (const auto & sextet : sextets) HeavyHiggsHadronicBranches.emplace_back(GetBranch(sextet));

    return HeavyHiggsHadronicBranches;

}

analysis::Object::Tag analysis::HHeavyHiggsHadronicTagger::GetTag(const Sextet &sextet)
{
    Print(kInformation, "Get Triple Tag");

    if (sextet.triplet1().Tag() == kBackground)return kBackground;
    if (sextet.triplet2().Tag() == kBackground)return kBackground;
    if (sgn(sextet.triplet1().singlet().user_index()) == sgn(sextet.triplet2().singlet().user_index())) return kBackground;
    return kSignal;
}


std::vector<analysis::Sextet> analysis::HHeavyHiggsHadronicTagger::GetBdt(std::vector< analysis::Triplet > triplets, const analysis::Reader &Reader)
{
    Print(kInformation, "Get Heavy Higgs Bdt");
    std::vector<analysis::Sextet> sextets;
    for (const auto & triplet1 : triplets)
      for (const auto & triplet2 : triplets) {
        if (triplet1.singlet() == triplet2.singlet()) continue;
        if (triplet1.singlet() == triplet2.doublet().Singlet1()) continue;
        if (triplet1.singlet() == triplet2.doublet().Singlet2()) continue;
        if (triplet1.doublet().Singlet1() == triplet2.singlet()) continue;
        if (triplet1.doublet().Singlet1() == triplet2.doublet().Singlet1()) continue;
        if (triplet1.doublet().Singlet1() == triplet2.doublet().Singlet2()) continue;
        if (triplet1.doublet().Singlet2() == triplet2.singlet()) continue;
        if (triplet1.doublet().Singlet2() == triplet2.doublet().Singlet1()) continue;
        if (triplet1.doublet().Singlet2() == triplet2.doublet().Singlet2()) continue;
            Sextet sextet(triplet1, triplet2);
            sextets.emplace_back(sextet);
            Branch = GetBranch(sextet);
            sextet.SetBdt(Reader.Bdt());
        }

    return sextets;
}
