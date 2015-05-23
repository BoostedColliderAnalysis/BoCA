# include "HChargedHiggsLeptonicTagger.hh"

analysis::HChargedHiggsLeptonicTagger::HChargedHiggsLeptonicTagger(const BottomTagger &NewBottomTagger, const HTopLeptonicTagger &NewTopLeptonicTagger)
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);

    set_tagger_name("ChargedHiggsLeptonic");

    DefineVariables();
}

analysis::HChargedHiggsLeptonicTagger::~HChargedHiggsLeptonicTagger()
{
    Print(kNotification, "Destructor");
}

analysis::HChargedHiggsLeptonicBranch analysis::HChargedHiggsLeptonicTagger::GetBranch(const Triplet &triplet)
{
    Print(kInformation, "FillPairTagger", triplet.Bdt());

    HChargedHiggsLeptonicBranch ChargedHiggsBranch;
    ChargedHiggsBranch.HeavyHiggsMass = triplet.Jet().m();
    ChargedHiggsBranch.HeavyHiggsPt = triplet.Jet().m();

    ChargedHiggsBranch.TopDeltaR = triplet.DeltaR();
    ChargedHiggsBranch.TopDeltaRap = triplet.DeltaRap();
    ChargedHiggsBranch.TopDeltaPhi = triplet.DeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = quartet.GetLargertripletDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = quartet.GetLargertripletDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = quartet.GetSmallertripletDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = quartet.GetSmallertripletDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = quartet.GetSmallertripletDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = quartet.GetLargertripletDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = quartet.GetLargertripletDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = quartet.GetSmallertripletDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = quartet.GetSmallertripletDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = quartet.GetSmallertripletDeltaPhi();

    ChargedHiggsBranch.TopBdt = triplet.Bdt();
    ChargedHiggsBranch.HeavyHiggsTag = triplet.Tag();
return ChargedHiggsBranch;
}

void analysis::HChargedHiggsLeptonicTagger::DefineVariables()
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


std::vector< analysis::HChargedHiggsLeptonicBranch> analysis::HChargedHiggsLeptonicTagger::GetBranches(Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");

    jet_tag.HeavyParticles = {TopId, ChargedHiggsId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(jet_tag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = event.leptons().GetTaggedJets(jet_tag);
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     Jets Neutrinos = event.partons().GetNeutrinos();

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & Jet : jets)  {
            if (doublet.Singlet1() == Jet) continue;
            Triplet triplet(doublet, Jet);
            triplet.SetTag(GetTag(triplet));
            if (triplet.Tag() != Tag) continue;
//             std::vector<Quartet31> Prequartets;
//             Prequartets = Getquartet(quartet, MissingEt, Neutrinos, Tag);
//             for (auto & quartet : Prequartets) {
                triplets.emplace_back(triplet);
//             }
        }
    }
    Print(kInformation, "Numeber of triplets", triplets.size());


    if (Tag == kSignal && triplets.size() > 1) {
        Print(kError, "Higgs Candidates", triplets.size());
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    std::vector<HChargedHiggsLeptonicBranch> ChargedHiggsBranches;
    for (const auto & triplet : triplets) ChargedHiggsBranches.emplace_back(GetBranch(triplet));

    return ChargedHiggsBranches;

}

analysis::Object::Tag analysis::HChargedHiggsLeptonicTagger::GetTag(const Triplet &triplet)
{
    Print(kInformation, "Get Triple Tag");

    if (triplet.doublet().Tag() == kBackground) return kBackground;
//     if (quartet.Getdoublet2().Tag() == HBackground) return HBackground;
    // TODO check the following
    if (triplet.doublet().Singlet1().user_index() != -triplet.singlet().user_index()) return kBackground;
    return kSignal;
}

std::vector<analysis::Triplet>  analysis::HChargedHiggsLeptonicTagger::GetBdt(const std::vector<Doublet> &doublets,const Jets &jets, const Reader &Reader)
{
    Print(kInformation, "Get Bdt");

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & Jet : jets)  {
            if (doublet.Singlet1() == Jet) continue;
            Triplet triplet(doublet, Jet);
            triplet.SetTag(GetTag(triplet));
//             std::vector<Quartet31> Prequartets;
//             Prequartets = Getquartets(quartet, MissingEt);
//             for (auto & quartet : Prequartets) {
                Branch = GetBranch(triplet);
                triplet.SetBdt(Reader.Bdt());
                triplets.emplace_back(triplet);
//             }
        }
    }
    return triplets;
}
