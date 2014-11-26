# include "HBottomTagger.hh"

hdelphes::HBottomTagger::HBottomTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    AnalysisName = "HiggsCpv";
    TaggerName = "Bottom";
    SignalNames = {"Bottom"};
    BackgroundNames = {"NotBottom"};
    TestName = "Test";
    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even"};
    SignalTreeNames = TestTreeNames;
    BackgroundTreeNames = TestTreeNames;
    CandidateBranchName = "Bottom";
    BTagger = new HBottomBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hdelphes::HBottomTagger::~HBottomTagger()
{
    Print(HNotification, "Destructor");
    delete BTagger;
}

std::vector<HBottomBranch *> hdelphes::HBottomTagger::GetBottomTag(hanalysis::HEvent *const Event, const HState State)
{

    Print(HInformation, "Get Bottom Tag", State);

    JetTag->SetHeavyParticles( {BottomId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    if (State == HSignal) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != BottomId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    } else if (State == HBackground) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    }

    Print(HInformation, "Number Jets", Jets.size());
//     if (Jets.size() < 1) return 0;

    std::vector<HBottomBranch *> BottomTaggers;

    for (const auto & Jet : Jets) {
        HBottomBranch *BottomTagger = new HBottomBranch;
        FillBottomBranch(Jet, BottomTagger);
        BottomTaggers.push_back(BottomTagger);
    }

    return BottomTaggers;

}

void hdelphes::HBottomTagger::FillBottomBranch(const fastjet::PseudoJet &Jet, HBottomBranch *BTagger)
{

    Print(HInformation, "Fill Bottom Tagger");

    if (Jet.has_user_info<hanalysis::HJetInfo>()) {
        Print(HInformation, "Has Info", Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement());
        BTagger->VertexMass = Jet.user_info<hanalysis::HJetInfo>().GetVertexMass();
        BTagger->Mass = Jet.m();
        BTagger->Pt = Jet.pt();
        BTagger->Displacement = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        BTagger->Multipliticity = Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber();
        Print(HDebug, "Multiplicity", Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber(), BTagger->Multipliticity);
        BTagger->DeltaR = GetDeltaR(Jet);
        if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
            BTagger->BottomTag = 1;
        } else {
            BTagger->BottomTag = 0;
        }

    } else {
        Print(HError, "BJet without user info");
    }

}

float hdelphes::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet)
{

    Print(HInformation, "Get Delta R");

    float DeltaR;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;

}

float hdelphes::HBottomTagger::GetBottomBdt(const fastjet::PseudoJet &Bottom)
{
    Print(HInformation, "Get Bottom Bdt");

    HBottomBranch *BottomTagger = new HBottomBranch();
    FillBottomBranch(Bottom, BottomTagger);
    const float Bdt = GetBdt(BottomTagger, Reader->Reader);
    delete BottomTagger;

    return Bdt;

}

void hdelphes::HBottomTagger::DefineVariables()
{

    Print(HNotification , "Define Variables", BTagger->Mass);

    Observables.push_back(NewObservable(&BTagger->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&BTagger->Pt, "Pt"));
    Observables.push_back(NewObservable(&BTagger->Displacement, "Displacement"));
    Observables.push_back(NewObservable(&BTagger->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&BTagger->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&BTagger->Mass, "Mass"));
    Spectators.push_back(NewObservable(&BTagger->BottomTag, "BottomTag"));

    Print(HNotification, "Variables defined");

}

float hdelphes::HBottomTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader)
{

    Print(HInformation, "Get Bdt", BdtMethodName);

    *BTagger = *static_cast<HBottomBranch *>(Branch);
    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);
    Print(HInformation, "BTagger Bdt", BdtEvaluation);

    return ((BdtEvaluation + 1.) / 2.);

}
