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


void hanalysis::HBottomTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->VertexMass, "VertexMass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
//     Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
//     Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->MaxDisplacement, "MaxDisplacement"));
    Observables.push_back(NewObservable(&Branch->MeanDisplacement, "MeanDisplacement"));
    Observables.push_back(NewObservable(&Branch->SumDisplacement, "SumDisplacement"));
    Observables.push_back(NewObservable(&Branch->Multipliticity, "Multipliticity"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Spread, "Spread"));
    Observables.push_back(NewObservable(&Branch->VertexDeltaR, "VertexDeltaR"));
    Observables.push_back(NewObservable(&Branch->VertexSpread, "VertexSpread"));
    Observables.push_back(NewObservable(&Branch->EnergyFraction, "EnergyFraction"));
    Observables.push_back(NewObservable(&Branch->BTag, "BTag"));

//     Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));
    Spectators.push_back(NewObservable(&Branch->Bdt, "Bdt"));
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
        float MaxDisp = Jet.user_info<HJetInfo>().GetJetMaxDisplacement();
        if (MaxDisp > 0)BottomBranch->MaxDisplacement = std::log(MaxDisp);
        else BottomBranch->MaxDisplacement = -3;
        float MeanDisp = Jet.user_info<HJetInfo>().GetJetMeanDisplacement();
        if (MeanDisp > 0)BottomBranch->MeanDisplacement = std::log(MeanDisp);
        else BottomBranch->MeanDisplacement = -3;
        float SumDisp = Jet.user_info<HJetInfo>().GetJetSumDisplacement();
        if (SumDisp > 0)BottomBranch->SumDisplacement = std::log(SumDisp);
        else BottomBranch->SumDisplacement = -3;
        BottomBranch->Multipliticity = Jet.user_info<HJetInfo>().GetVertexNumber();
        BottomBranch->DeltaR = GetDeltaR(Jet);
        BottomBranch->Spread = GetSpread(Jet);
        BottomBranch->VertexDeltaR = GetDeltaR(Jet.user_info<HJetInfo>().GetVertexJet());
        BottomBranch->VertexSpread = GetSpread(Jet.user_info<HJetInfo>().GetVertexJet());
        BottomBranch->EnergyFraction = Jet.user_info<HJetInfo>().GetVertexEnergy() / Jet.e();
        BottomBranch->BTag = Jet.user_info<HJetInfo>().GetBTag();
        BottomBranch->Tag = Jet.user_info<HJetInfo>().GetTag();
        BottomBranch->Bdt = Jet.user_info<HJetInfo>().GetBdt();
    } else Print(HError, "BJet without user info");

    if (BottomBranch->Bdt < -10) {
        Print(HError, "VertexMass", BottomBranch->VertexMass);
        Print(HError, "Mass", BottomBranch->Mass);
        Print(HError, "Pt", BottomBranch->Pt);
        Print(HError, "Rap", BottomBranch->Rap);
        Print(HError, "Phi", BottomBranch->Phi);
        Print(HError, "Max", BottomBranch->MaxDisplacement);
        Print(HError, "Mmmean", BottomBranch->MeanDisplacement);
        Print(HError, "SumDisp", BottomBranch->SumDisplacement);
        Print(HError, "Multi", BottomBranch->Multipliticity);
        Print(HError, "DeltaR", BottomBranch->DeltaR);
        Print(HError, "Spread", BottomBranch->Spread);
        Print(HError, "DeltaR", BottomBranch->VertexDeltaR);
        Print(HError, "Spread", BottomBranch->VertexSpread);
        Print(HError, "Energy", BottomBranch->EnergyFraction);
    }
}

void hanalysis::HBottomTagger::FillBranch(const fastjet::PseudoJet &Jet)
{
    Print(HInformation, "Fill Branch");
    FillBranch(Branch, Jet);
}

std::vector<HBottomBranch *> hanalysis::HBottomTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Bottom Tag", Tag);

    JetTag->HeavyParticles = {BottomId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
        HJetInfo *JetInfo = new HJetInfo();
        JetInfo->SetVertices((*Jet).user_info<HJetInfo>().GetVertices());
        JetInfo->SetJetFamily((*Jet).user_info<HJetInfo>().GetJetFamily());
        JetInfo->SetBTag((*Jet).user_info<HJetInfo>().GetBTag());
        JetInfo->ExtractFraction(BottomId);
        JetInfo->PrintAllInfos(HDebug);
        JetInfo->SetTag(GetTag(*Jet));
        if (
            JetInfo->GetTag() != Tag ||
            (Tag == HSignal && JetInfo->GetMaximalFraction() < .8) ||
            (Tag == HSignal && JetInfo->GetJetMeanDisplacement() < .1) ||
            (Tag == HBackground && JetInfo->GetFraction(BottomId) > .2) ||
            std::abs((*Jet).rap()) > 2.5
        ) Jet = Jets.erase(Jet);
        else {
            (*Jet).set_user_info(JetInfo);
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
    HJetInfo JetInfo = Jet.user_info<HJetInfo>();
    JetInfo.ExtractFraction(BottomId);
    JetInfo.PrintAllInfos(HDebug);

    Print(HDebug, "B Tag Info", Jet.rap(), JetInfo.GetMaximalId());
    if (std::abs(JetInfo.GetMaximalId()) != BottomId) return HBackground;
    return HSignal;
}

// hanalysis::HObject::HTag hanalysis::HBottomTagger::GetTag(const HJetInfo &JetInfo) const
// {
//   Print(HDebug, "Get Bottom Tag", JetInfo.GetMaximalId(), JetInfo.GetMaximalFraction());
//
//     if (std::abs(JetInfo.GetMaximalId()) != BottomId) return HBackground;
//     return HSignal;
// }


HJets hanalysis::HBottomTagger::GetBdt(HJets &Jets, const HReader *const BottomReader)
{
    for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        HJetInfo *JetInfo = new HJetInfo();
        if ((*Jet).has_user_info<HJetInfo>()) *JetInfo = (*Jet).user_info<HJetInfo>();
        FillBranch(*Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Print(HInformation, "Bdt", JetInfo->GetBdt());
        (*Jet).set_user_info(JetInfo);
    }
    return Jets;
}


HJets hanalysis::HBottomTagger::GetBdt2(HJets &Jets, const HReader *const BottomReader)
{
    for (auto Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        HJetInfo *JetInfo = new HJetInfo();
        if ((*Jet).has_user_info<HJetInfo>()) *JetInfo = (*Jet).user_info<HJetInfo>();
        FillBranch(*Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        JetInfo->SetTag(GetTag(*Jet));
        Print(HInformation, "Bdt", JetInfo->GetBdt(), JetInfo->GetTag());
        (*Jet).set_user_info(JetInfo);
    }
    return Jets;
}



float hanalysis::HBottomTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    if (!Jet.has_constituents()) return 0;

    float DeltaR = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) continue;
        Print(HDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;
}

float hanalysis::HBottomTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");
    if (!Jet.has_constituents()) return 0;

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) return 0;
    float Spread = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) continue;
        Spread += TempDeltaR * Constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}
