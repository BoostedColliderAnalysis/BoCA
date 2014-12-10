# include "HTopLeptonicTagger.hh"

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger(HBottomTagger *const NewBottomTagger)
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

hanalysis::HTopLeptonicTagger::~HTopLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
}

void hanalysis::HTopLeptonicTagger::DefineVariables()
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

void hanalysis::HTopLeptonicTagger::FillBranch(HLeptonicTopBranch *const LeptonicTopBranch, const HTriple &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    LeptonicTopBranch->Mass = JetLeptonPair.GetInvariantMass();
    LeptonicTopBranch->JetPt = JetLeptonPair.GetJetPt();
    LeptonicTopBranch->LeptonPt = JetLeptonPair.GetLeptonPt();
    LeptonicTopBranch->DeltaR = JetLeptonPair.GetDeltaR();
    LeptonicTopBranch->DeltaRap = JetLeptonPair.GetDeltaRap();
    LeptonicTopBranch->DeltaPhi = JetLeptonPair.GetPhiDelta();
    LeptonicTopBranch->BottomBdt = JetLeptonPair.GetBdt();
    LeptonicTopBranch->TopTag = JetLeptonPair.GetTag();

}

void hanalysis::HTopLeptonicTagger::FillBranch(const HTriple &JetLeptonPair)
{
    Print(HInformation, "Fill Top Tagger", JetLeptonPair.GetBdt());

    FillBranch(Branch, JetLeptonPair);

}


std::vector<HLeptonicTopBranch *> hanalysis::HTopLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HState State)
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

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<HTriple> Triples;
    for (const auto & Lepton : Leptons) {
        if (State == HSignal && std::abs(Lepton.user_index() != TopId)) continue;

        for (const auto & Jet : Jets) {
            Print(HDebug, "Lepton Tagging", GetParticleName(Lepton.user_index()), GetParticleName(Jet.user_index()));

            if (State == HSignal && std::abs(Jet.user_index() != TopId)) continue;
            if (State == HSignal && Lepton.user_index() != Jet.user_index()) continue;

            if (State == HBackground && (Lepton.user_index() == Jet.user_index() && std::abs(Jet.user_index()) == TopId)) continue;
            HJets Neutrinos = GetNeutrinos(Lepton, Jet, MissingEt);
            for (const auto & Neutrino : Neutrinos) {
                HTriple Triple(Neutrino, Lepton, Jet);
                if (std::abs(Jet.user_index()) == TopId && Jet.user_index() == Lepton.user_index()) Triple.SetTag(1);
                else Triple.SetTag(0);
                Triples.push_back(Triple);
            }
        }
    }

    Print(HInformation, "Number JetPairs", Triples.size());

    std::vector<HLeptonicTopBranch *> LeptonicTopBranches;
    for (const auto & Triple : Triples) {
        HLeptonicTopBranch *LeptonicTopBranch = new HLeptonicTopBranch();
        FillBranch(LeptonicTopBranch, Triple);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }

    return LeptonicTopBranches;

}

HJets hanalysis::HTopLeptonicTagger::GetNeutrinos(const fastjet::PseudoJet &Lepton, const fastjet::PseudoJet &Bottom, const fastjet::PseudoJet &MissingEt)const
{

    HJets Neutrinos;

    const float Sqrt = sqrt(pow(Bottom.pz(), 2) * (
                                4 * pow(Bottom.py(), 2) * pow(Lepton.py(), 2)
                                + 8 * Bottom.py() * Bottom.pz() * Lepton.py() * Lepton.pz()
                                + 4 * pow(Bottom.pz(), 2) * pow(Lepton.pz(), 2)
                                - 4 * Bottom.py() * Lepton.py() * pow(TopMass, 2)
                                - 4 * Bottom.pz() * Lepton.pz() * pow(TopMass, 2)
                                + pow(TopMass, 4)
                                + 4 * Bottom.py() * Lepton.py() * pow(WMass, 2)
                                + 4 * Bottom.pz() * Lepton.pz() * pow(WMass, 2)
                                - 2 * pow(TopMass, 2) * pow(WMass, 2)
                                + pow(WMass, 4)
                                + 4 * pow(Bottom.pz(), 2) * pow(MissingEt.px(), 2)
                                + 4 * pow(Bottom.px(), 2) * pow(Lepton.px() + MissingEt.px(), 2)
                                + 4 * Bottom.py() * (2 * Bottom.py() * Lepton.py() + 2 * Bottom.pz() * Lepton.pz() - pow(TopMass, 2) + pow(WMass, 2)) * MissingEt.py()
                                + 4 * (pow(Bottom.py(), 2) + pow(Bottom.pz(), 2)) * pow(MissingEt.py(), 2)
                                + 4 * pow(Bottom.E(), 2) * (pow(Lepton.E(), 2) - pow(MissingEt.px(), 2) - pow(MissingEt.py(), 2))
                                + 4 * Bottom.px() * (Lepton.px() + MissingEt.px()) * (2 * Bottom.pz() * Lepton.pz() - pow(TopMass, 2) + pow(WMass, 2) + 2 * Bottom.py()(Lepton.py() + MissingEt.py()))
                                - 4 * Bottom.E() * Lepton.E() * (2 * Bottom.pz() * Lepton.pz() - pow(TopMass, 2) + pow(WMass, 2) + 2 * Bottom.px() * (Lepton.px() + MissingEt.px()) + 2 * Bottom.py() * (Lepton.py() + MissingEt.py()))));


    float NeutrinoE = (1 / (2 * (Bottom.E() - Bottom.pz()) * (Bottom.E() + Bottom.pz()))) * (Bottom.E() * (-2 * Bottom.E() * Lepton.E() + 2 * Bottom.pz() * Lepton.pz() - pow(TopMass, 2) + pow(WMass, 2) + 2 * Bottom.px() * (Lepton.px() + MissingEt.px()) + 2 * Bottom.py() * (Lepton.py() + MissingEt.py())) - Sqrt);

    float NeutrinoPz = (1 / (2 * (Bottom.E() - Bottom.pz()) * Bottom.pz() * (Bottom.E() + Bottom.pz()))) * (2 * pow(Bottom.pz(), 3) * Lepton.pz() + pow(Bottom.pz(), 2)(-2 * Bottom.E() * Lepton.E() - pow(TopMass, 2) + pow(WMass, 2) + 2 * Bottom.px()(Lepton.px() + MissingEt.px()) + 2 * Bottom.py() * (Lepton.py() + MissingEt.py())) - Bottom.E() * Sqrt);
    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), NeutrinoPz, NeutrinoE);
    Neutrinos.push_back(Neutrino1);

    NeutrinoE = (1 / (2 * (Bottom.E() - Bottom.pz()) * (Bottom.E() + Bottom.pz()))) * (Bottom.E() * (-2 * Bottom.E() * Lepton.E() + 2 * Bottom.pz() * Lepton.pz() - pow(TopMass, 2) + pow(WMass, 2) + 2 * Bottom.px() * (Lepton.px() + MissingEt.px()) + 2 * Bottom.py()(Lepton.py() + MissingEt.py())) + Sqrt);

    NeutrinoPz = (1 / (2 * (-pow(Bottom.E(), 2) * Bottom.pz() + pow(Bottom.pz(), 3)))) * (-2 * pow(Bottom.pz(), 3) * Lepton.pz() + pow(Bottom.pz(), 2) * (2 * Bottom.E() * Lepton.E() + pow(TopMass, 2) - pow(WMass, 2) - 2 * Bottom.px() * (Lepton.px() + MissingEt.px()) - 2 * Bottom.py() * (Lepton.py() + MissingEt.py())) - Bottom.E() * Sqrt);
    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), NeutrinoPz, NeutrinoE);
    Neutrinos.push_back(Neutrino2);

    return Neutrinos;

}













































































