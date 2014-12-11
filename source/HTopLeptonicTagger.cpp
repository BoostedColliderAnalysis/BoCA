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

    Branch = new HTopLeptonicBranch();
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

    Observables.push_back(NewObservable(&Branch->TriplePt, "TriplePt"));
    Observables.push_back(NewObservable(&Branch->PairPt, "PairPt"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
    Observables.push_back(NewObservable(&Branch->MissingEt, "MissingEt"));

    Observables.push_back(NewObservable(&Branch->PairDeltaPhi, "PairDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->PairDeltaRap, "PairDeltaRap"));
    Observables.push_back(NewObservable(&Branch->PairDeltaR, "PairDeltaR"));

    Observables.push_back(NewObservable(&Branch->TripleDeltaPhi, "TripleDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->TripleDeltaRap, "TripleDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TripleDeltaR, "TripleDeltaR"));

    Observables.push_back(NewObservable(&Branch->BottomBdt, "BottomBdt"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HTopLeptonicTagger::FillBranch(HTopLeptonicBranch *const LeptonicTopBranch, const HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.GetBdt());

    LeptonicTopBranch->Mass = Triplet.GetTripletJet().m();

    LeptonicTopBranch->PairPt = Triplet.GetTripletJet().pt();
    LeptonicTopBranch->PairPt = Triplet.GetDoubletJet().pt();
    LeptonicTopBranch->JetPt = Triplet.GetJet().pt();
    LeptonicTopBranch->LeptonPt = Triplet.GetDoublet().GetJet1().pt();
    LeptonicTopBranch->MissingEt = Triplet.GetDoublet().GetJet2().pt();

    LeptonicTopBranch->TripleDeltaR = Triplet.GetDeltaR();
    LeptonicTopBranch->TripleDeltaRap = Triplet.GetDeltaRap();
    LeptonicTopBranch->TripleDeltaPhi = Triplet.GetDeltaPhi();

    LeptonicTopBranch->PairDeltaR = Triplet.GetDoublet().GetDeltaR();
    LeptonicTopBranch->PairDeltaRap = Triplet.GetDoublet().GetDeltaRap();
    LeptonicTopBranch->PairDeltaPhi = Triplet.GetDoublet().GetPhiDelta();

    LeptonicTopBranch->BottomBdt = Triplet.GetBdt();
    LeptonicTopBranch->TopTag = Triplet.GetTag();

}

void hanalysis::HTopLeptonicTagger::FillBranch(const HTriplet &Triple)
{
    Print(HInformation, "Fill Top Tagger", Triple.GetBdt());

    FillBranch(Branch, Triple);

}


std::vector<HTopLeptonicBranch *> hanalysis::HTopLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HState State)
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

    std::vector<HTriplet> Triples;
    for (const auto & Lepton : Leptons) {
        if (State == HSignal && std::abs(Lepton.user_index() != TopId)) continue;

        for (const auto & Jet : Jets) {
            Print(HDebug, "Lepton Tagging", GetParticleName(Lepton.user_index()), GetParticleName(Jet.user_index()));

            if (State == HSignal && std::abs(Jet.user_index() != TopId)) continue;
            if (State == HSignal && Lepton.user_index() != Jet.user_index()) continue;

            if (State == HBackground && (Lepton.user_index() == Jet.user_index() && std::abs(Jet.user_index()) == TopId)) continue;
            HJets Neutrinos = GetNeutrinos(Lepton, Jet, MissingEt);
            for (const auto & Neutrino : Neutrinos) {
              HDoublet Doublet(Lepton,Neutrino);
                HTriplet Triple(Doublet, Jet);
                if (std::abs(Jet.user_index()) == TopId && Jet.user_index() == Lepton.user_index()) Triple.SetTag(1);
                else Triple.SetTag(0);
                Triples.push_back(Triple);
            }
        }
    }

    Print(HInformation, "Number JetPairs", Triples.size());

    std::vector<HTopLeptonicBranch *> LeptonicTopBranches;
    for (const auto & Triple : Triples) {
        HTopLeptonicBranch *LeptonicTopBranch = new HTopLeptonicBranch();
        FillBranch(LeptonicTopBranch, Triple);
        LeptonicTopBranches.push_back(LeptonicTopBranch);
    }

    return LeptonicTopBranches;

}

HJets hanalysis::HTopLeptonicTagger::GetNeutrinos(const fastjet::PseudoJet &Lepton, const fastjet::PseudoJet &Bottom, const fastjet::PseudoJet &MissingEt)const
{

    HJets Neutrinos;

    const float TopMass2 = std::pow(TopMass, 2);
    const float WMass2 = std::pow(WMass, 2);

    const float LeptonicPx = Lepton.px() + MissingEt.px();
    const float LeptonicPy = Lepton.py() + MissingEt.py();

    const float BPxLPx = 2 * Bottom.px() * LeptonicPx;
    const float BPyLPy = 2 * Bottom.py() * LeptonicPy;


    const float bElE = 2 * Bottom.e() * Lepton.e();
    const float bPylPy = 2 * Bottom.py() * Lepton.py();
    const float bPzlPz = 2 * Bottom.pz() * Lepton.pz();

    const float Sum =  4 * std::pow(Bottom.py(), 2) * std::pow(Lepton.py(), 2)
                       + 2 * bPylPy * bPzlPz
                       + 4 * std::pow(Bottom.pz(), 2) * std::pow(Lepton.pz(), 2)
                       - 2 * bPylPy * TopMass2
                       - 2 * bPzlPz * TopMass2
                       + std::pow(TopMass2, 2)
                       + 2 * bPylPy * WMass2
                       + 2 * bPzlPz * WMass2
                       - 2 * TopMass2 * WMass2
                       + std::pow(WMass, 4)
                       + 4 * std::pow(Bottom.pz(), 2) * std::pow(MissingEt.px(), 2)
                       + 4 * std::pow(Bottom.px(), 2) * std::pow(LeptonicPx, 2)
                       + 4 * Bottom.py() * (bPylPy + bPzlPz - TopMass2 + WMass2) * MissingEt.py()
                       + 4 * (std::pow(Bottom.py(), 2) + std::pow(Bottom.pz(), 2)) * std::pow(MissingEt.py(), 2)
                       + 4 * std::pow(Bottom.E(), 2) * (std::pow(Lepton.E(), 2) - std::pow(MissingEt.px(), 2) - std::pow(MissingEt.py(), 2))
                       + 2 * BPxLPx * (bPzlPz - TopMass2 + WMass2 + BPyLPy)
                       - 2 * bElE * (bPzlPz - TopMass2 + WMass2 + BPxLPx + BPyLPy);

    if (Sum < 0) {
        Print(HError, "Imaginiary sqrt");
        return Neutrinos;
    }

    const float Sqrt = std::sqrt(std::pow(Bottom.pz(), 2) * Sum);


    float NeutrinoE = (1 / (2 * (Bottom.E() - Bottom.pz()) * (Bottom.E() + Bottom.pz()))) * (Bottom.E() * (-bElE + bPzlPz - TopMass2 + WMass2 + BPxLPx + BPyLPy) - Sqrt);

    float NeutrinoPz = (1 / (2 * (Bottom.E() - Bottom.pz()) * Bottom.pz() * (Bottom.E() + Bottom.pz()))) * (2 * std::pow(Bottom.pz(), 3) * Lepton.pz() + std::pow(Bottom.pz(), 2) * (-bElE - TopMass2 + WMass2 + BPxLPx + BPyLPy) - Bottom.E() * Sqrt);

    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), NeutrinoPz, NeutrinoE);
    Neutrinos.push_back(Neutrino1);

    NeutrinoE = (1 / (2 * (Bottom.E() - Bottom.pz()) * (Bottom.E() + Bottom.pz()))) * (Bottom.E() * (-bElE + bPzlPz - TopMass2 + WMass2 + BPxLPx + BPyLPy) + Sqrt);

    NeutrinoPz = (1 / (2 * (-std::pow(Bottom.E(), 2) * Bottom.pz() + std::pow(Bottom.pz(), 3)))) * (-2 * std::pow(Bottom.pz(), 3) * Lepton.pz() + std::pow(Bottom.pz(), 2) * (bElE + TopMass2 - WMass2 - BPxLPx - BPyLPy) - Bottom.E() * Sqrt);

    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), NeutrinoPz, NeutrinoE);
    Neutrinos.push_back(Neutrino2);

    return Neutrinos;

}
