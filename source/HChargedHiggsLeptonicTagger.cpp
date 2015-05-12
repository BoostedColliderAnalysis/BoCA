# include "HChargedHiggsLeptonicTagger.hh"

hanalysis::HChargedHiggsLeptonicTagger::HChargedHiggsLeptonicTagger(const BottomTagger &NewBottomTagger, const HTopLeptonicTagger &NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);

    set_tagger_name("ChargedHiggsLeptonic");

    DefineVariables();
}

hanalysis::HChargedHiggsLeptonicTagger::~HChargedHiggsLeptonicTagger()
{
    Print(kNotification, "Destructor");
}

HChargedHiggsLeptonicBranch hanalysis::HChargedHiggsLeptonicTagger::GetBranch(const Triplet &triplet)
{
    Print(kInformation, "FillPairTagger", triplet.Bdt());

    HChargedHiggsLeptonicBranch ChargedHiggsBranch;
    ChargedHiggsBranch.HeavyHiggsMass = triplet.Jet().m();
    ChargedHiggsBranch.HeavyHiggsPt = triplet.Jet().m();

    ChargedHiggsBranch.TopDeltaR = triplet.DeltaR();
    ChargedHiggsBranch.TopDeltaRap = triplet.DeltaRap();
    ChargedHiggsBranch.TopDeltaPhi = triplet.DeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = Quartet.GetLargertripletDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = Quartet.GetLargertripletDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = Quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = Quartet.GetSmallertripletDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = Quartet.GetSmallertripletDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = Quartet.GetSmallertripletDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = Quartet.GetLargertripletDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = Quartet.GetLargertripletDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = Quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = Quartet.GetSmallertripletDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = Quartet.GetSmallertripletDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = Quartet.GetSmallertripletDeltaPhi();

    ChargedHiggsBranch.TopBdt = triplet.Bdt();
    ChargedHiggsBranch.HeavyHiggsTag = triplet.Tag();
return ChargedHiggsBranch;
}

void hanalysis::HChargedHiggsLeptonicTagger::DefineVariables()
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


std::vector< HChargedHiggsLeptonicBranch> hanalysis::HChargedHiggsLeptonicTagger::GetBranches(HEvent &Event, const HObject::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");

    JetTag.HeavyParticles = {TopId, ChargedHiggsId};
    Jets jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     Jets Neutrinos = Event.GetParticles()->GetNeutrinos();

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & Jet : jets)  {
            if (doublet.Singlet1() == Jet) continue;
            Triplet triplet(doublet, Jet);
            triplet.SetTag(GetTag(triplet));
            if (triplet.Tag() != Tag) continue;
//             std::vector<HQuartet31> PreQuartets;
//             PreQuartets = GetQuartet(Quartet, MissingEt, Neutrinos, Tag);
//             for (auto & Quartet : PreQuartets) {
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

hanalysis::HObject::Tag hanalysis::HChargedHiggsLeptonicTagger::GetTag(const Triplet &triplet)
{
    Print(kInformation, "Get Triple Tag");

    if (triplet.doublet().Tag() == kBackground) return kBackground;
//     if (Quartet.Getdoublet2().Tag() == HBackground) return HBackground;
    // TODO check the following
    if (triplet.doublet().Singlet1().user_index() != -triplet.singlet().user_index()) return kBackground;
    return kSignal;
}

std::vector<hanalysis::Triplet>  hanalysis::HChargedHiggsLeptonicTagger::GetBdt(const std::vector<Doublet> &doublets,const Jets &jets, const Reader &Reader)
{
    Print(kInformation, "Get Bdt");

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & Jet : jets)  {
            if (doublet.Singlet1() == Jet) continue;
            Triplet triplet(doublet, Jet);
            triplet.SetTag(GetTag(triplet));
//             std::vector<HQuartet31> PreQuartets;
//             PreQuartets = GetQuartets(Quartet, MissingEt);
//             for (auto & Quartet : PreQuartets) {
                Branch = GetBranch(triplet);
                triplet.SetBdt(Reader.Bdt());
                triplets.emplace_back(triplet);
//             }
        }
    }
    return triplets;
}
