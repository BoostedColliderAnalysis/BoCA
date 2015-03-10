# include "HWSemiTagger.hh"

hanalysis::HWSemiTagger::HWSemiTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTagger();
}

hanalysis::HWSemiTagger::~HWSemiTagger()
{
    Print(HNotification, "Destructor");
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

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.NeutrinoPt, "NeutrinoPt"));
    Observables.push_back(NewObservable(&Branch.LeptonPt, "LeptonPt"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

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

std::vector< HWSemiBranch> hanalysis::HWSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag.HeavyParticles = {WId};
    HJets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetTaggedJets(JetTag));
    if (Leptons.size() > 1) Leptons.erase(Leptons.begin() + 1, Leptons.end());

    const fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     HJets Neutrinos = Event.GetParticles()->GetNeutrinos();
//     if (Neutrinos.size() != 1)Print(HError, "wrong number of neutrinos", Neutrinos.size());

//     Print(HError, "MissingEt check", MissingEt.px(), MissingEt.py(), Neutrinos.front().px(), Neutrinos.front().py());
//     MissingEt = Neutrinos.front();

    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongFamily(WId, TopId)), Particles.end());
    if (Particles.size() != 1) Print(HError, "Where is the W?", Particles.size());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
//         PreDoublet.SetTag(GetTag(PreDoublet));
//         if (PreDoublet.Tag() != Tag) continue;
//         std::vector<HDoublet> PostDoublets = GetDoublets(PreDoublet, Neutrinos, Tag);
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);


        
//         for (const auto & Particle : Particles) {
//           PostDoublets = SortByDeltaRTo(PostDoublets, Particle);
//           if (PostDoublets.front().delta_R(Particle) > DetectorGeometry.JetConeSize) continue;
//           if (Tag == HSignal) BottomJets.push_back(PostDoublets.front());
//           if (PostDoublets.size() > 1) PostDoublets.erase(PostDoublets.begin());
//         }






        std::sort(PostDoublets.begin(), PostDoublets.end(), MinDeltaR(Particles.front()));

        if (Tag == HSignal && PostDoublets.size() > 1) PostDoublets.erase(PostDoublets.begin() + 1, PostDoublets.end());
        if (Tag == HBackground && PostDoublets.size() > 0) PostDoublets.erase(PostDoublets.begin());


        for (auto & PostDoublet : PostDoublets) {
//             Print(HInformation, "W Mass ", PostDoublet.Jet().m());
//             if (Tag == HSignal && std::abs(PostDoublet.Jet().m() - WMass) > WMassWindow) continue;
//             if (Tag == HSignal && PostDoublet.DeltaR() > 0.5) continue;
//             if (Tag == HBackground && PostDoublet.DeltaR() < 0.2) continue;
              PostDoublet.SetTag(Tag);

//             for (const auto Particle : Particles) if (Tag == HBackground && PostDoublet.Jet().delta_R(Particle) < std::min(PostDoublet.DeltaR(),float(0.4))) continue;
            Doublets.push_back(PostDoublet);
        }
    }

    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HWSemiBranch> WSemiBranches;
    for (const auto & Doublet : Doublets) WSemiBranches.push_back(GetBranch(Doublet));

    return WSemiBranches;
}

hanalysis::HObject::HTag hanalysis::HWSemiTagger::GetTag(const hanalysis::HDoublet &Doublet) const
{
    Print(HInformation, "Get Triple Tag");
    static_cast<HJetInfo *>(Doublet.Singlet1().user_info_shared_ptr().get())->ExtractFraction(WId);

    if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
    return HSignal;
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
            if (PostDoublet.Jet().m() < 10) continue;
            Branch = GetBranch(PostDoublet);
            PostDoublet.SetBdt(Reader.Bdt());
            Doublets.push_back(PostDoublet);
        }
    }
    std::sort(Doublets.begin(), Doublets.end());
//     Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());

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

std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetDoublets(const HDoublet &Doublet, const HJets &Neutrinos, const HTag Tag)
{
    Print(HInformation, "Get Triple Pair");

    std::vector<HDoublet> Doublets = GetNeutrinos(Doublet);
    Print(HDebug, "Number Solutions", Doublets.size());
    if (Doublets.size() < 1) return Doublets;

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
    case HSignal:
        FinalDoublets.push_back(BestDoublet);
        return FinalDoublets;
    case HBackground:
        for (const auto Neutrino : Neutrinos) Doublets.erase(std::remove_if(Doublets.begin(), Doublets.end(), FindError(Neutrino, BestError)), Doublets.end());
        return Doublets;
    default:
        Print(HError, "we should never end up here");
        return Doublets;
    }


}
