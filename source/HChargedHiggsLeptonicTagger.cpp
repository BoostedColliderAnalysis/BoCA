# include "HChargedHiggsLeptonicTagger.hh"

hanalysis::HChargedHiggsLeptonicTagger::HChargedHiggsLeptonicTagger(HBottomTagger *const NewBottomTagger, HTopLeptonicTagger *const NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader = new HReader(TopLeptonicTagger);

    SetTaggerName("ChargedHiggsLeptonic");

    Branch = new HChargedHiggsLeptonicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HChargedHiggsLeptonicTagger::~HChargedHiggsLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;

}

void hanalysis::HChargedHiggsLeptonicTagger::FillBranch(const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "FillPairTagger", Triplet.Bdt());
    FillBranch(Branch, Triplet);
}

void hanalysis::HChargedHiggsLeptonicTagger::FillBranch(HChargedHiggsLeptonicBranch *ChargedHiggsBranch, const HTriplet &Triplet)
{
    Print(HInformation, "FillPairTagger", Triplet.Bdt());

    ChargedHiggsBranch->HeavyHiggsMass = Triplet.Jet().m();
    ChargedHiggsBranch->HeavyHiggsPt = Triplet.Jet().m();

    ChargedHiggsBranch->TopDeltaR = Triplet.DeltaR();
    ChargedHiggsBranch->TopDeltaRap = Triplet.DeltaRap();
    ChargedHiggsBranch->TopDeltaPhi = Triplet.DeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = Quartet.GetLargerTripletDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = Quartet.GetLargerTripletDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = Quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = Quartet.GetSmallerTripletDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = Quartet.GetSmallerTripletDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = Quartet.GetSmallerTripletDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = Quartet.GetLargerTripletDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = Quartet.GetLargerTripletDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = Quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = Quartet.GetSmallerTripletDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = Quartet.GetSmallerTripletDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = Quartet.GetSmallerTripletDeltaPhi();

    ChargedHiggsBranch->TopBdt = Triplet.Bdt();
    ChargedHiggsBranch->HeavyHiggsTag = Triplet.Tag();

}

void hanalysis::HChargedHiggsLeptonicTagger::DefineVariables()
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


std::vector< HChargedHiggsLeptonicBranch * > hanalysis::HChargedHiggsLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {TopId, ChargedHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<HDoublet> Doublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
//     HJets Neutrinos = Event->GetParticles()->GetNeutrinos();

    Print(HInformation, "Number of Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Jet : Jets) {
            if (Doublet.Singlet1() == Jet) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.Tag() != Tag) continue;
//             std::vector<HQuartet31> PreQuartets;
//             PreQuartets = GetQuartet(Quartet, MissingEt, Neutrinos, Tag);
//             for (auto & Quartet : PreQuartets) {
                Triplets.push_back(Triplet);
//             }
        }
    }
    Print(HInformation, "Numeber of Triplets", Triplets.size());


    if (Tag == HSignal && Triplets.size() > 1) {
        Print(HError, "Higgs Candidates", Triplets.size());
        std::sort(Triplets.begin(), Triplets.end(), SortByBdt());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    std::vector<HChargedHiggsLeptonicBranch *> ChargedHiggsBranches;
    for (const auto & Triplet : Triplets) {
        HChargedHiggsLeptonicBranch *ChargedHiggsLeptonicBranch = new HChargedHiggsLeptonicBranch();
        FillBranch(ChargedHiggsLeptonicBranch, Triplet);
        ChargedHiggsBranches.push_back(ChargedHiggsLeptonicBranch);
    }

    return ChargedHiggsBranches;

}

hanalysis::HObject::HTag hanalysis::HChargedHiggsLeptonicTagger::GetTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    if (Triplet.Doublet().Tag() == HBackground) return HBackground;
//     if (Quartet.GetDoublet2().Tag() == HBackground) return HBackground;
    // TODO check the following
    if (Triplet.Doublet().Singlet1().user_index() != -Triplet.Singlet().user_index()) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HChargedHiggsLeptonicTagger::GetBdt(const std::vector<HDoublet> &Doublets,const std::vector<fastjet::PseudoJet> Jets, const HReader *const Reader)
{
    Print(HInformation, "Get Bdt");

    std::vector<HTriplet> Triplets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Jet : Jets) {
            if (Doublet.Singlet1() == Jet) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
//             std::vector<HQuartet31> PreQuartets;
//             PreQuartets = GetQuartets(Quartet, MissingEt);
//             for (auto & Quartet : PreQuartets) {
                FillBranch(Triplet);
                Triplet.SetBdt(Reader->Bdt());
                Triplets.push_back(Triplet);
//             }
        }
    }
    return Triplets;
}
