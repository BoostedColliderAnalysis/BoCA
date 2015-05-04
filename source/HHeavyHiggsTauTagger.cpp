# include "HHeavyHiggsTauTagger.hh"

hanalysis::HHeavyHiggsTauTagger::HHeavyHiggsTauTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("HeavyHiggsTau");
}

hanalysis::HHeavyHiggsTauTagger::~HHeavyHiggsTauTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HHeavyHiggsTauTagger::SetTagger(const HTauTagger &NewTauTagger)
{
    Print(HNotification, "Set Tagger");
    TauTagger = NewTauTagger;
    SetTaggerName("HeavyHiggsTau");
    DefineVariables();
}

void hanalysis::HHeavyHiggsTauTagger::DefineVariables()
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

HHeavyHiggsTauBranch hanalysis::HHeavyHiggsTauTagger::GetBranch(const hanalysis::HDoublet &Doublet) const
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());

    HHeavyHiggsTauBranch HiggsBranch;

    HiggsBranch.Mass = Doublet.Jet().mt();
    HiggsBranch.Rap = Doublet.Jet().rap();
    HiggsBranch.Phi = Doublet.Jet().phi();
    HiggsBranch.Pt = Doublet.Jet().pt();
    HiggsBranch.Ht = Doublet.Ht();

    HiggsBranch.NeutrinoPt = Doublet.Singlet2().pt();
    HiggsBranch.LeptonPt = Doublet.Singlet1().pt();

    HiggsBranch.DeltaPt = Doublet.DeltaPt();
    HiggsBranch.DeltaR = Doublet.DeltaR();
    HiggsBranch.DeltaRap = Doublet.DeltaRap();
    HiggsBranch.DeltaPhi = Doublet.DeltaPhi();

    HiggsBranch.Bdt = Doublet.Bdt();
    HiggsBranch.Tag = Doublet.Tag();

    return HiggsBranch;

}

std::vector< HHeavyHiggsTauBranch> hanalysis::HHeavyHiggsTauTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag tag)
{

    Print(HInformation, "Get Top Tags");

    HJets Jets = GetJets(Event);
    Jets = TauTagger.GetJetBdt(Jets, TauReader);
    Print(HInformation, "Number Jet", Jets.size());

    const fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    HJets TauParticles = Event.GetParticles()->Generator();
    TauParticles.erase(std::remove_if(TauParticles.begin(), TauParticles.end(), WrongAbsId(TauId)), TauParticles.end());
    if (TauParticles.size() != 1) Print(HError, "Where is the Tau?", TauParticles.size());

    HJets HiggsParticles = Event.GetParticles()->Generator();
    HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?", HiggsParticles.size());

    for (const auto & Particle : TauParticles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        if (Jets.front().delta_R(Particle) < 0.4) static_cast<HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }
    HJets NewCleanJets;
    for (const auto & Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) continue;
        if (Jet.user_info<HJetInfo>().Tag() != tag) continue;
        NewCleanJets.push_back(Jet);
    }

    std::vector<HDoublet> Doublets;
    for (const auto & Jet : NewCleanJets) {
        HDoublet PreDoublet(Jet, MissingEt);
//         std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);

//         std::sort(PostDoublets.begin(), PostDoublets.end(), MinDeltaR(HiggsParticles.front()));
//         if (Tag == HSignal && PostDoublets.size() > 1) PostDoublets.erase(PostDoublets.begin() + 1, PostDoublets.end());
//         if (Tag == HBackground && PostDoublets.size() > 0) PostDoublets.erase(PostDoublets.begin());
//         for (auto & PostDoublet : PostDoublets) {
            PreDoublet.SetTag(tag);
            Doublets.push_back(PreDoublet);
//         }
    }


    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HHeavyHiggsTauBranch> HiggsBranches;
    for (const auto & Doublet : Doublets) HiggsBranches.push_back(GetBranch(Doublet));

    return HiggsBranches;
}

hanalysis::HObject::Tag hanalysis::HHeavyHiggsTauTagger::GetTag(const hanalysis::HDoublet &Doublet) const
{
    return kSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HHeavyHiggsTauTagger::GetBdt(const HJets &Jets, const fastjet::PseudoJet &MissingEt, const hanalysis::HReader &Reader)
{
    Print(HInformation, "Get Triple Bdt");
    std::vector<HDoublet> Doublets;
    for (const auto & Jet : Jets) {
        HDoublet PreDoublet(Jet, MissingEt);
//         std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
//         for (auto & PostDoublet : PostDoublets) {
//             if (PostDoublet.Jet().m() < 10) continue;
            Branch = GetBranch(PreDoublet);
            PreDoublet.SetBdt(Reader.Bdt());
            Doublets.push_back(PreDoublet);
//         }
    }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());

    return Doublets;
}


std::vector<hanalysis::HDoublet> hanalysis::HHeavyHiggsTauTagger::GetNeutrinos(const HDoublet &Doublet)const
{

    const fastjet::PseudoJet Jet = Doublet.Singlet1();
    const fastjet::PseudoJet MissingEt = Doublet.Singlet2();
    Print(HInformation, "Get Neutrinos", Jet.m(), (Jet - MissingEt).m());

    const float LinearTerm = (std::pow(WMass, 2) - Jet.m2()) / 2 + MissingEt.px() * Jet.px() + MissingEt.py() * Jet.py();

    const float LeptonSq = std::pow(Jet.e(), 2) - std::pow(Jet.pz(), 2);
    const float MetSq = std::pow(MissingEt.px(), 2) + std::pow(MissingEt.py(), 2);

    const double Radicand = std::pow(Jet.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);

    std::vector<HDoublet> Doublets;
    if (Radicand < 0) {
        Print(HInformation, "Imaginary root", "move missing et away from jet");
        HDoublet NewDoublet(Jet, MissingEt - 0.1 * (Jet - MissingEt));
        NewDoublet.SetFlag(true);
        NewDoublet.SetTag(Doublet.Tag());
        return GetNeutrinos(NewDoublet);
        return Doublets;
    }

    if (Radicand == 0) {
        Print(HError, "Radicant exactly zero", "implement this case!");
    }

    const float Sqrt = std::sqrt(Radicand);

    const float Neutrino1E = (Jet.e() * LinearTerm - Sqrt) / LeptonSq;
    const float Neutrino1Pz = (std::pow(Jet.pz(), 2) * LinearTerm - Jet.e() * Sqrt) / Jet.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), Neutrino1Pz, Neutrino1E);
    Print(HDebug, "Neutrnio 1", Neutrino1);
    HDoublet Doublet1(Jet, Neutrino1);
    Doublet1.SetTag(Doublet.Tag());
    Doublet1.SetFlag(Doublet.Flag());

    const float Neutrino2E = (Jet.e() * LinearTerm + Sqrt) / LeptonSq;
    const float Neutrino2Pz = (std::pow(Jet.pz(), 2) * LinearTerm + Jet.e() * Sqrt) / Jet.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), Neutrino2Pz, Neutrino2E);
    Print(HDebug, "Neutrino 2", Neutrino2);
    HDoublet Doublet2(Jet, Neutrino2);
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

std::vector<hanalysis::HDoublet> hanalysis::HHeavyHiggsTauTagger::GetDoublets(const HDoublet &Doublet, const HJets &Neutrinos, const Tag tag)
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
    switch (tag) {
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
