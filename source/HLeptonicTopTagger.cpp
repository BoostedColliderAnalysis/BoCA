# include "HLeptonicTopTagger.hh"

hanalysis::HLeptonicTopTagger::HLeptonicTopTagger(HBottomTagger *const NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    TaggerName = "TopLeptonic";
    SignalNames = {"TopLeptonic"};
    BackgroundNames = {"NotTopLeptonic"};
    CandidateBranchName = "TopLeptonic";

    Branch = new HLeptonicTopBranch();
    JetTag = new HJetTag();

    DefineVariables();

}

hanalysis::HLeptonicTopTagger::~HLeptonicTopTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
}

void hanalysis::HLeptonicTopTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->BottomBdt, "BottomBdt"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HLeptonicTopTagger::FillBranch(HLeptonicTopBranch * const LeptonicTopBranch, const HDoublet &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    LeptonicTopBranch->Mass = JetLeptonPair.GetDoubletJet().m();
    LeptonicTopBranch->JetPt = JetLeptonPair.GetJet1().pt();
    LeptonicTopBranch->LeptonPt = JetLeptonPair.GetJet2().pt();
    LeptonicTopBranch->DeltaR = JetLeptonPair.GetDeltaR();
    LeptonicTopBranch->DeltaRap = JetLeptonPair.GetDeltaRap();
    LeptonicTopBranch->DeltaPhi = JetLeptonPair.GetPhiDelta();
    LeptonicTopBranch->BottomBdt = JetLeptonPair.GetBdt();
    LeptonicTopBranch->TopTag = JetLeptonPair.GetTag();

}

void hanalysis::HLeptonicTopTagger::FillBranch(const HDoublet &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    FillBranch(Branch, JetLeptonPair);

}


std::vector<HLeptonicTopBranch *> hanalysis::HLeptonicTopTagger::GetBranches(HEvent *const Event, const HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId, HiggsId, CpvHiggsId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());

    for (auto Jet = Jets.begin(); Jet != Jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = Jets.erase(Jet);
        } else {
            HJetInfo *JetInfo = new HJetInfo;
            BottomTagger->FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Jet).set_user_info(JetInfo);
            ++Jet;
        }
    }

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) {
            Lepton = Leptons.erase(Lepton);
        } else {
            ++Lepton;
        }
    }

    std::vector<HDoublet> JetLeptonPairs;
    for (const auto & Lepton : Leptons) {
        if (State == HSignal && std::abs(Lepton.user_index() != TopId)) continue;

        for (const auto & Jet : Jets) {
            Print(HDebug, "Lepton Tagging", GetParticleName(Lepton.user_index()), GetParticleName(Jet.user_index()));

            if (State == HSignal && std::abs(Jet.user_index() != TopId)) continue;
            if (State == HSignal && Lepton.user_index() != Jet.user_index()) continue;

            if (State == HBackground && (Lepton.user_index() == Jet.user_index() && std::abs(Jet.user_index()) == TopId)) continue;

            HDoublet JetLeptonPair(Jet, Lepton);
            if (std::abs(Jet.user_index()) == TopId && Jet.user_index() == Lepton.user_index()) JetLeptonPair.SetTag(1);
            else JetLeptonPair.SetTag(0);
            JetLeptonPairs.push_back(JetLeptonPair);
        }
    }

    Print(HInformation, "Number JetPairs", JetLeptonPairs.size());

    std::vector<HLeptonicTopBranch *> LeptonicTopBranches;
    for (const auto & JetLeptonPair : JetLeptonPairs) {
        HLeptonicTopBranch *LeptonicTopBranch = new HLeptonicTopBranch();
        FillBranch(LeptonicTopBranch, JetLeptonPair);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }

    return LeptonicTopBranches;

}

