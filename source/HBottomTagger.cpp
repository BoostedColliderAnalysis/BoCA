# include "HBottomTagger.hh"

hdelphes::HBottomTagger::HBottomTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    AnalysisName = "HiggsCpv";
    TaggerName = "Bottom";
    SignalNames = {"Bottom"};
    BackgroundNames = {"NotBottom"};
    CandidateBranchName = "Bottom";
    Branch = new HBottomBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hdelphes::HBottomTagger::~HBottomTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
}

void hdelphes::HBottomTagger::DefineVariables()
{

    Print(HNotification , "Define Variables", Branch->Mass);

    Observables.push_back(NewObservable(&Branch->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Displacement, "Displacement"));
    Observables.push_back(NewObservable(&Branch->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&Branch->Mass, "Mass"));
    Spectators.push_back(NewObservable(&Branch->BottomTag, "BottomTag"));

    Print(HNotification, "Variables defined");

}

std::vector<HBottomBranch *> hdelphes::HBottomTagger::GetBranches(hanalysis::HEvent *const Event, const HState State)
{

    Print(HInformation, "Get Bottom Tag", State);

    JetTag->SetHeavyParticles( {BottomId, TopId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    if (State == HSignal) {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != BottomId) {
                Jet = Jets.erase(Jet);
            } else {
                Print(HError,"we have a bootom",(*Jet).m()); // FIXME where are the bottoms; check truth level tagger
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

    std::vector<HBottomBranch *> BottomBranches;
    for (const auto & Jet : Jets) {
        HBottomBranch *BottomBranch = new HBottomBranch;
        FillBranch(BottomBranch, Jet);
        BottomBranches.push_back(BottomBranch);
    }

    return BottomBranches;

}

void hdelphes::HBottomTagger::FillBranch(const fastjet::PseudoJet &Jet)
{

    Print(HInformation, "Fill Bottom Branch");
    FillBranch(Branch, Jet);

}


void hdelphes::HBottomTagger::FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet)
{

    Print(HInformation, "Fill Bottom Branch");

    if (Jet.has_user_info<hanalysis::HJetInfo>()) {
        Print(HDebug, "Has Info", Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement());
        Print(HDebug, "Multiplicity", Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber(), BottomBranch->Multipliticity);

        BottomBranch->VertexMass = Jet.user_info<hanalysis::HJetInfo>().GetVertexMass();
        BottomBranch->Mass = Jet.m();
        BottomBranch->Pt = Jet.pt();
        BottomBranch->Displacement = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        BottomBranch->Multipliticity = Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber();
        BottomBranch->DeltaR = GetDeltaR(Jet);
        BottomBranch->Centrality = GetCentrality(Jet);
        if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
            BottomBranch->BottomTag = 1;
        } else {
            BottomBranch->BottomTag = 0;
        }

    } else {
        Print(HError, "BJet without user info");
    }

}

float hdelphes::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{

    Print(HInformation, "Get Delta R");

    float DeltaR;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;

}



float hdelphes::HBottomTagger::GetCentrality(const fastjet::PseudoJet &Jet) const
{

    Print(HInformation, "Get Centrality");

    float Centrality;
    for (const auto & Constituent : Jet.constituents()) {
        Centrality += Jet.delta_R(Constituent) * Constituent.pt();
    }
    return (Centrality / Jet.pt());

}
