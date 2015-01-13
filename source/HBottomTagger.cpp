# include "HBottomTagger.hh"

hanalysis::HBottomTagger::HBottomTagger()
{
    Print(HNotification, "Constructor");
    SetTaggerName("Bottom");
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

void hanalysis::HBottomTagger::FillBranch(const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Fill Branch");
    FillBranch(Branch, Jet);
}


void hanalysis::HBottomTagger::FillBranch(HBottomBranch *const BottomBranch, const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Fill Branch");

    if (Jet.has_user_info<HJetInfo>()) {
        BottomBranch->VertexMass = Jet.user_info<HJetInfo>().GetVertexMass();
        BottomBranch->Mass = Jet.m();
        BottomBranch->Pt = Jet.pt();
        BottomBranch->Rap = Jet.rap();
        BottomBranch->Phi = Jet.phi();
        BottomBranch->Displacement = Jet.user_info<HJetInfo>().GetJetDisplacement();
        BottomBranch->Multipliticity = Jet.user_info<HJetInfo>().GetVertexNumber();
        BottomBranch->DeltaR = GetDeltaR(Jet);
        BottomBranch->Spread = GetSpread(Jet);
        BottomBranch->EnergyFraction = Jet.user_info<HJetInfo>().GetVertexEnergy() / Jet.e();
        BottomBranch->BTag = Jet.user_info<HJetInfo>().GetBTag();
        if (std::abs(Jet.user_index()) == BottomId) BottomBranch->Tag = 1;
        else BottomBranch->Tag = 0;
    } else Print(HError, "BJet without user info");
}

void hanalysis::HBottomTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Displacement, "Displacement"));
    Observables.push_back(NewObservable(&Branch->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Spread, "Spread"));
    Observables.push_back(NewObservable(&Branch->EnergyFraction, "EnergyFraction"));
    Observables.push_back(NewObservable(&Branch->BTag, "BTag"));

    Spectators.push_back(NewObservable(&Branch->Mass, "Mass"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));
}

std::vector<HBottomBranch *> hanalysis::HBottomTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Bottom Tag", Tag);

    JetTag->HeavyParticles = {BottomId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
        (*Jet).user_info<HJetInfo>().PrintAllFamilyInfos(HDebug);
        HJetInfo JetInfo = (*Jet).user_info<HJetInfo>();
        JetInfo.ExtractFraction(BottomId);
        JetInfo.PrintAllInfos(HDebug);
        if (JetInfo.GetMaximalFraction() < .8 || GetTag(JetInfo) != Tag) Jet = Jets.erase(Jet);
        else {
          (*Jet).set_user_index(JetInfo.GetMaximalId());
          ++Jet;
        }
    }

    Print(HDebug, "Number Jets", Jets.size());

    std::vector<HBottomBranch *> BottomBranches;
    for (const auto & Jet : Jets) {
        HBottomBranch *BottomBranch = new HBottomBranch;
        FillBranch(BottomBranch, Jet);
        BottomBranches.push_back(BottomBranch);
    }

    return BottomBranches;
}

hanalysis::HObject::HTag hanalysis::HBottomTagger::GetTag(const fastjet::PseudoJet &Jet) const
{
    Print(HDebug, "Get Bottom Tag", Jet.user_info<HJetInfo>().GetMaximalFraction());

    if (std::abs(Jet.user_info<HJetInfo>().GetMaximalFraction()) != BottomId) return HBackground;
    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HBottomTagger::GetTag(const HJetInfo &JetInfo) const
{
  Print(HDebug, "Get Bottom Tag", JetInfo.GetMaximalId(), JetInfo.GetMaximalFraction());

    if (std::abs(JetInfo.GetMaximalId()) != BottomId) return HBackground;
    return HSignal;
}


HJets hanalysis::HBottomTagger::GetBdt(HJets &Jets, const HReader *const BottomReader)
{
    for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        HJetInfo *JetInfo = new HJetInfo();
        if((*Jet).has_user_info<HJetInfo>()) *JetInfo = (*Jet).user_info<HJetInfo>();
        FillBranch(*Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        (*Jet).set_user_info(JetInfo);
    }
    return Jets;
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
