# include "HBottomTagger.hh"

hanalysis::HBottomTagger::HBottomTagger()
{
    Print(HNotification, "Constructor");
    TaggerName = "Bottom";
    SignalNames = {"Bottom"};
    BackgroundNames = {"NotBottom"};
    CandidateBranchName = "Bottom";
    Branch = new HBottomBranch();
    JetTag = new HJetTag();

    DefineVariables();

}

hanalysis::HBottomTagger::~HBottomTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
}

void hanalysis::HBottomTagger::DefineVariables()
{
    Print(HNotification , "Define Variables", Branch->Mass);

    Observables.push_back(NewObservable(&Branch->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Displacement, "Displacement"));
    Observables.push_back(NewObservable(&Branch->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Spread, "Spread"));
    Observables.push_back(NewObservable(&Branch->EnergyFraction, "EnergyFraction"));

    Spectators.push_back(NewObservable(&Branch->Mass, "Mass"));
    Spectators.push_back(NewObservable(&Branch->BottomTag, "BottomTag"));
}


void hanalysis::HBottomTagger::FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Fill Bottom Branch");

    if (Jet.has_user_info<HJetInfo>()) {
        BottomBranch->VertexMass = Jet.user_info<HJetInfo>().GetVertexMass();
        BottomBranch->Mass = Jet.m();
        BottomBranch->Pt = Jet.pt();
        BottomBranch->Displacement = Jet.user_info<HJetInfo>().GetJetDisplacement();
        BottomBranch->Multipliticity = Jet.user_info<HJetInfo>().GetVertexNumber();
        BottomBranch->DeltaR = GetDeltaR(Jet);
        BottomBranch->Spread = GetSpread(Jet);
        BottomBranch->EnergyFraction = Jet.user_info<HJetInfo>().GetVertexEnergy() / Jet.e();
        if (std::abs(Jet.user_info<HJetInfo>().GetMaximalId()) == BottomId) BottomBranch->BottomTag = 1;
        else BottomBranch->BottomTag = 0;
    } else Print(HError, "BJet without user info");
}

void hanalysis::HBottomTagger::FillBranch(const fastjet::PseudoJet &Jet)
{

    Print(HInformation, "Fill Bottom Branch");
    FillBranch(Branch, Jet);

}

std::vector<HBottomBranch *> hanalysis::HBottomTagger::GetBranches(HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Bottom Tag", State);

    JetTag->HeavyParticles = {TopId, BottomId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
      if (GetSingletTag(*Jet)!=State || std::abs((*Jet).user_index()) == MixedJetId) Jet = Jets.erase(Jet);
      else ++Jet;
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

hanalysis::HObject::HState hanalysis::HBottomTagger::GetSingletTag(const fastjet::PseudoJet& Jet) const
{
  Print(HInformation, "Get Doublet Tag");

  if (std::abs(Jet.user_index()) != BottomId) return HBackground;
  return HSignal;
}

float hanalysis::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    float DeltaR;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;
}


float hanalysis::HBottomTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");

    float Spread;
    for (const auto & Constituent : Jet.constituents()) Spread += Jet.delta_R(Constituent) * Constituent.pt();
    return (Spread / Jet.pt() / GetDeltaR(Jet));
}


HJets hanalysis::HBottomTagger::GetBottomBdt(HJets &Jets, const HReader * const BottomReader) {
    for (auto Jet = Jets.begin(); Jet != Jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) Jet = Jets.erase(Jet);
        else {
            HJetInfo *JetInfo = new HJetInfo;
            FillBranch(*Jet);
            JetInfo->SetBdt(BottomReader->GetBdt());
            (*Jet).set_user_info(JetInfo);
            ++Jet;
        }
    }
    return Jets;
}


