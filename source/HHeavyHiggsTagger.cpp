# include "HHeavyHiggsTagger.hh"

hanalysis::HHeavyHiggsTagger::HHeavyHiggsTagger(HBottomTagger *const NewBottomTagger, HLeptonicTopTagger *const NewTopTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopTagger = NewTopTagger;
    TopReader = new HReader(TopTagger);

    TaggerName = "HeavyHiggs";
    SignalNames = {"HeavyHiggs"};
    BackgroundNames = {"NotHeavyHiggs"};
    CandidateBranchName = "HeavyHiggs";

    Branch = new HHeavyHiggsBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsTagger::~HHeavyHiggsTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopReader;

}

void hanalysis::HHeavyHiggsTagger::FillBranch(HHeavyHiggsBranch *HeavyHiggsBranch, const HTriplePair &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = TriplePair.GetInvariantMass();
    HeavyHiggsBranch->HeavyHiggsPt = TriplePair.GetPtSum();

    HeavyHiggsBranch->BetterTopMass = TriplePair.GetBetterTripleMass(TopId);
    HeavyHiggsBranch->WorseTopMass = TriplePair.GetWorseTripleMass(TopId);

    HeavyHiggsBranch->BetterWMass = TriplePair.GetBetterPairMass(WId);
    HeavyHiggsBranch->WorseWMass = TriplePair.GetWorsePairMass(WId);

    HeavyHiggsBranch->BetterNeutrinoMass = TriplePair.GetBetterJetMass(ElectronNeutrinoId);
    HeavyHiggsBranch->WorseNeutrinoMass = TriplePair.GetWorseJetMass(ElectronNeutrinoId);

    HeavyHiggsBranch->TopDeltaR = TriplePair.GetDeltaR();
    HeavyHiggsBranch->TopDeltaRap = TriplePair.GetDeltaRap();
    HeavyHiggsBranch->TopDeltaPhi = TriplePair.GetDeltaPhi();

    HeavyHiggsBranch->LargerWDeltaR = TriplePair.GetLargerTripleDeltaR();
    HeavyHiggsBranch->LargerWDeltaRap = TriplePair.GetLargerTripleDeltaRap();
    HeavyHiggsBranch->LargerWDeltaPhi = TriplePair.GetLargerTripleDeltaR();

    HeavyHiggsBranch->SmallerWDeltaR = TriplePair.GetSmallerTripleDeltaR();
    HeavyHiggsBranch->SmallerWDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
    HeavyHiggsBranch->SmallerWDeltaPhi = TriplePair.GetSmallerTripleDeltaR();

    HeavyHiggsBranch->LargerNeutrinoDeltaR = TriplePair.GetLargerTripleDeltaR();
    HeavyHiggsBranch->LargerNeutrinoDeltaRap = TriplePair.GetLargerTripleDeltaRap();
    HeavyHiggsBranch->LargerNeutrinoDeltaPhi = TriplePair.GetLargerTripleDeltaR();

    HeavyHiggsBranch->SmallerNeutrinoDeltaR = TriplePair.GetSmallerTripleDeltaR();
    HeavyHiggsBranch->SmallerNeutrinoDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
    HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = TriplePair.GetSmallerTripleDeltaR();

    HeavyHiggsBranch->TopBdt = TriplePair.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = TriplePair.GetTag();
//     PairPair.GetMt2();
}

void hanalysis::HHeavyHiggsTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->BetterTopMass, "BetterTopMass"));
    Observables.push_back(NewObservable(&Branch->WorseTopMass, "WorseTopMass"));

    Observables.push_back(NewObservable(&Branch->BetterWMass, "BetterWMass"));
    Observables.push_back(NewObservable(&Branch->WorseWMass, "WorseWMass"));

    Observables.push_back(NewObservable(&Branch->BetterNeutrinoMass, "BetterNeutrinoMass"));
    Observables.push_back(NewObservable(&Branch->WorseNeutrinoMass, "WorseNeutrinoMass"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}

struct SortPairByMass {
    inline bool operator()(const hanalysis::HPairPair &Pair1, const hanalysis::HPairPair &Pair2) {
        return (Pair1.GetMassDifference(400) > Pair2.GetMassDifference(400));
    }
};



std::vector< HHeavyHiggsBranch * > hanalysis::HHeavyHiggsTagger::GetBranches(HEvent *const Event, const HObject::HState State)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsBranch *> HeavyHiggsBranches;

    JetTag->HeavyParticles = {HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    if (Jets.size() < 2) return HeavyHiggsBranches;

    HJets HeavyHiggsJets;
    HJets OtherJets;
    for (auto &Jet : Jets) {
        Print(HInformation, "Jet Id", GetParticleName(Jet.user_info<HJetInfo>().GetMaximalId()));

        if (std::abs(Jet.user_index()) != MixedJetId) {
            const int JetId = Jet.user_info<HJetInfo>().GetMaximalId();
            HJetInfo *JetInfo = new HJetInfo;
            BottomTagger->FillBranch(Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            Jet.set_user_info(JetInfo);
            if (JetId == HeavyHiggsId) HeavyHiggsJets.push_back(Jet);
            else OtherJets.push_back(Jet);
        }
    }
    Print(HError,"Jets",Jets.size(),HeavyHiggsJets.size(),OtherJets.size());
    if (State == HSignal && HeavyHiggsJets.size() < 2) return HeavyHiggsBranches;

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    if (Leptons.size() < 2) return HeavyHiggsBranches;

    HJets HeavyHiggsLeptons;
    HJets OtherLeptons;
    for (auto & Lepton : Leptons) {
        if (std::abs(Lepton.user_index()) == HeavyHiggsId) HeavyHiggsLeptons.push_back(Lepton);
        else OtherLeptons.push_back(Lepton);
    }
    if (State == HSignal && HeavyHiggsLeptons.size() < 2) return HeavyHiggsBranches;
    Print(HError,"Leptons",Leptons.size(),HeavyHiggsLeptons.size(),OtherLeptons.size());

    std::vector<HJetLeptonPair> JetLeptonPairs;
    if (State == HSignal) {
        Print(HInformation, "Higgs Jets", HeavyHiggsJets.size());
        for (const auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(1);
                JetLeptonPairs.push_back(JetPair);
            }
        }
    } else if (State == HBackground) {
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : HeavyHiggsLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(0);
                JetLeptonPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : HeavyHiggsJets) {
            for (const auto & Lepton : OtherLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(0);
                JetLeptonPairs.push_back(JetPair);
            }
        }
        for (const auto & Jet : OtherJets) {
            for (const auto & Lepton : OtherLeptons) {
                HJetLeptonPair JetPair(Jet, Lepton);
                JetPair.SetTag(0);
                JetLeptonPairs.push_back(JetPair);
            }
        }
    }
    Print(HError,"Pairs",JetLeptonPairs.size());
    if (JetLeptonPairs.size() < 2) return HeavyHiggsBranches;

    for (auto & JetPair : JetLeptonPairs) {
        TopTagger->FillBranch(JetPair);
        JetPair.SetBdt(TopReader->GetBdt());
    }

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Neutrinos = Event->GetParticles()->GetNeutrinos();


//     std::vector<HPairPair> PairPairs;
    std::vector<HTriplePair> TriplePairs;

    for (std::vector<HJetLeptonPair>::iterator Pair1 = JetLeptonPairs.begin(); Pair1 != JetLeptonPairs.end(); ++Pair1) {
        for (std::vector<HJetLeptonPair>::iterator Pair2 = std::next(Pair1); Pair2 != JetLeptonPairs.end(); ++Pair2) {
            Print(HInformation, "NextPair");
            if ((*Pair1).GetJet() == (*Pair2).GetJet()) continue;
            if ((*Pair1).GetLepton() == (*Pair2).GetLepton()) continue;
            HPairPair PairPair((*Pair1), (*Pair2), MissingEt);
            HTriplePair TriplePair /*= PairPair.GetTriplePair(Neutrinos)*/;
            TriplePairs.push_back(TriplePair);
        }
    }

    Print(HInformation, "Number of Heavy Higgses", TriplePairs.size());

    for (const auto & TriplePair : TriplePairs) {
        HHeavyHiggsBranch *HeavyHiggsBranch = new HHeavyHiggsBranch();
        FillBranch(HeavyHiggsBranch, TriplePair);
        HeavyHiggsBranches.push_back(HeavyHiggsBranch);
    }


    return HeavyHiggsBranches;

}

void hanalysis::HHeavyHiggsTagger::FillBranch(const hanalysis::HTriplePair &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    FillBranch(Branch, TriplePair);

}

