# include "HWSemiTagger.hh"

hanalysis::HWSemiTagger::HWSemiTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTagger();
}

void hanalysis::HWSemiTagger::SetTagger()
{
    Print(HNotification, "Set Tagger");
    WMassWindow = 20;
    SetTaggerName("WSemi");
    DefineVariables();
}

void hanalysis::HWSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.NeutrinoPt, "NeutrinoPt");
    AddObservable(Branch.LeptonPt, "LeptonPt");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddSpectator(Branch.Tag, "Tag");

    Print(HNotification, "Variables defined");

}

HWSemiBranch hanalysis::HWSemiTagger::GetBranch(const hanalysis::HDoublet &Doublet) const
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());

    HWSemiBranch WSemiBranch;

    WSemiBranch.Mass = Doublet.Jet().m();
    WSemiBranch.Rap = Doublet.Jet().rap();
    WSemiBranch.Phi = Doublet.Jet().phi();
    WSemiBranch.Pt = Doublet.Jet().pt();
    WSemiBranch.Ht = Doublet.Ht();

    WSemiBranch.NeutrinoPt = Doublet.Singlet2().pt();
    WSemiBranch.LeptonPt = Doublet.Singlet1().pt();

    WSemiBranch.DeltaPt = Doublet.DeltaPt();
    WSemiBranch.DeltaR = Doublet.DeltaR();
    WSemiBranch.DeltaRap = Doublet.DeltaRap();
    WSemiBranch.DeltaPhi = Doublet.DeltaPhi();

    WSemiBranch.Bdt = Doublet.Bdt();
    WSemiBranch.Tag = Doublet.Tag();

    return WSemiBranch;

}

std::vector< HWSemiBranch> hanalysis::HWSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag.HeavyParticles = {WId};
    HJets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetTaggedJets(JetTag));
    if (Leptons.size() > 1) Leptons.erase(Leptons.begin() + 1, Leptons.end());

    const fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    HJets Particles = Event.GetParticles()->Generator();
    int WSemiId = GetWSemiId(Event);
    fastjet::PseudoJet WBoson;
    Particles = RemoveIfWrongParticle(Particles, WSemiId);
    if (Particles.size() == 1) {
        WBoson = Particles.front();
    } else Print(HError, "Where is the W?", Particles.size());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        std::sort(PostDoublets.begin(), PostDoublets.end(), MinDeltaR(WBoson));
        for (auto & PostDoublet : PostDoublets) {
            if (Tag == kSignal && std::abs(PostDoublet.Jet().m() - WMass) > WMassWindow) continue;
            if (Tag == kSignal && PostDoublet.Jet().delta_R(WBoson) > DetectorGeometry.JetConeSize) continue;
            if (Tag == kBackground && PostDoublet.Jet().delta_R(WBoson) > DetectorGeometry.JetConeSize) continue;
            PostDoublet.SetTag(Tag);
            Doublets.push_back(PostDoublet);
        }
    }
    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HWSemiBranch> WSemiBranches;
    for (const auto & Doublet : Doublets) WSemiBranches.push_back(GetBranch(Doublet));

    return WSemiBranches;
}

hanalysis::HObject::Tag hanalysis::HWSemiTagger::GetTag(const hanalysis::HDoublet &Doublet) const
{
    Print(HInformation, "Get Triple Tag");
    static_cast<HJetInfo *>(Doublet.Singlet1().user_info_shared_ptr().get())->ExtractFraction(WId);

    if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != WId) return kBackground;
    return kSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HWSemiTagger::GetBdt(const HJets &Leptons, const fastjet::PseudoJet &MissingEt, const HReader &Reader)
{
    Print(HInformation, "Get Triple Bdt");
    HJets NewLeptons = fastjet::sorted_by_pt(Leptons);
    if (NewLeptons.size() > 1) NewLeptons.erase(NewLeptons.begin() + 1, NewLeptons.end());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : NewLeptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (auto & PostDoublet : PostDoublets) {
            if (std::abs(PostDoublet.Jet().m() - WMass) > WMassWindow) continue;
            Branch = GetBranch(PostDoublet);
            PostDoublet.SetBdt(Reader.Bdt());
            Doublets.push_back(PostDoublet);
        }
    }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());

    return Doublets;
}


std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetNeutrinos(const HDoublet &Doublet)const
{

    Print(HInformation, "Get Neutrinos");
    const fastjet::PseudoJet Lepton = Doublet.Singlet1();
    const fastjet::PseudoJet MissingEt = Doublet.Singlet2();

    const float LinearTerm = (std::pow(WMass, 2) - Lepton.m2()) / 2 + MissingEt.px() * Lepton.px() + MissingEt.py() * Lepton.py();

    const float LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
    const float MetSq = std::pow(MissingEt.px(), 2) + std::pow(MissingEt.py(), 2);

    const double Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);

    std::vector<HDoublet> Doublets;
    if (Radicand < 0) {
        Print(HInformation, "Imaginary root", "move missing et towards lepton");
        HDoublet NewDoublet(Lepton, MissingEt + 0.1 * (Lepton - MissingEt));
        NewDoublet.SetFlag(true);
        NewDoublet.SetTag(Doublet.Tag());
        return GetNeutrinos(NewDoublet);
        return Doublets;
    }

    if (Radicand == 0) {
        Print(HError, "Radicant exactly zero", "implement this case!");
    }

    const float Sqrt = std::sqrt(Radicand);

    const float Neutrino1E = (Lepton.e() * LinearTerm - Sqrt) / LeptonSq;
    const float Neutrino1Pz = (std::pow(Lepton.pz(), 2) * LinearTerm - Lepton.e() * Sqrt) / Lepton.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), Neutrino1Pz, Neutrino1E);
    Print(HDebug, "Neutrnio 1", Neutrino1);
    HDoublet Doublet1(Lepton, Neutrino1);
    Doublet1.SetTag(Doublet.Tag());
    Doublet1.SetFlag(Doublet.Flag());

    const float Neutrino2E = (Lepton.e() * LinearTerm + Sqrt) / LeptonSq;
    const float Neutrino2Pz = (std::pow(Lepton.pz(), 2) * LinearTerm + Lepton.e() * Sqrt) / Lepton.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), Neutrino2Pz, Neutrino2E);
    Print(HDebug, "Neutrino 2", Neutrino2);
    HDoublet Doublet2(Lepton, Neutrino2);
    Doublet2.SetTag(Doublet.Tag());
    Doublet2.SetFlag(Doublet.Flag());

    Doublets.push_back(Doublet1);
    Doublets.push_back(Doublet2);

//     if (std::abs(Neutrino1Pz) < std::abs(Neutrino2Pz)) Doublets.push_back(Doublet1);
//     else Doublets.push_back(Doublet2);

    return Doublets;

}


struct SortByError {
    SortByError(const fastjet::PseudoJet &NewNeutrino) {
        this->Neutrino = NewNeutrino;
    }
    bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
        return ((Doublet1.Singlet2() + Neutrino).m() < (Doublet2.Singlet2() + Neutrino).m());
    }
    fastjet::PseudoJet Neutrino;
};

struct FindError {
    FindError(const fastjet::PseudoJet &NewNeutrino, const float NewError) {
        this->Neutrino = NewNeutrino;
        this->Error = NewError;
    }
    bool operator()(const hanalysis::HDoublet &Doublet) {
        return ((Doublet.Singlet2() + Neutrino).m() == Error);
    }
    fastjet::PseudoJet Neutrino;
    float Error;
};

std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetDoublets(const HDoublet &Doublet, const HJets &Neutrinos, const Tag Tag)
{
    Print(HInformation, "Get Triple Pair");

    std::vector<HDoublet> Doublets = GetNeutrinos(Doublet);
    Print(HDebug, "Number Solutions", Doublets.size());
    if (Doublets.empty()) return Doublets;

    float BestError = LargeNumber;
    HDoublet BestDoublet;
    for (const auto Neutrino : Neutrinos) {
        std::sort(Doublets.begin(), Doublets.end(), SortByError(Neutrino));
        float Error = (Doublets.front().Singlet2() + Neutrino).m();
        if (Error < BestError) {
            BestDoublet = Doublets.front();
            BestError = Error;
        }
    }

    std::vector<HDoublet> FinalDoublets;
    switch (Tag) {
    case kSignal:
        FinalDoublets.push_back(BestDoublet);
        return FinalDoublets;
    case kBackground:
        for (const auto Neutrino : Neutrinos) Doublets.erase(std::remove_if(Doublets.begin(), Doublets.end(), FindError(Neutrino, BestError)), Doublets.end());
        return Doublets;
    default:
        Print(HError, "we should never end up here");
        return Doublets;
    }


}




HJets hanalysis::HWSemiTagger::GetWDaughters(HEvent &Event)
{
    HJets WKids = Event.GetParticles()->Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(HError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfQuark(WKids);
    if (WKids.size() != 2) Print(HError, "Where is the W 2?", WKids.size());
    else Print(HInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id));
    return WKids;
}

int hanalysis::HWSemiTagger::GetWSemiId(const HJets &Jets)
{
    if (Jets.empty()) return WId;
    else return Jets.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id;
}

