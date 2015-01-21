# include "HWSemiTagger.hh"

hanalysis::HWSemiTagger::HWSemiTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    SetTaggerName("WSemi");

    Branch = new HWSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();
    WMassWindow = 20;

}

hanalysis::HWSemiTagger::~HWSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
}

void hanalysis::HWSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch->NeutrinoPt, "NeutrinoPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HWSemiTagger::FillBranch(HWSemiBranch *const WSemiBranch, const hanalysis::HDoublet &Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());

    WSemiBranch->Mass = Doublet.Jet().m();
    WSemiBranch->Rap = Doublet.Jet().rap();
    WSemiBranch->Phi = Doublet.Jet().phi();
    WSemiBranch->Pt = Doublet.Jet().pt();
    WSemiBranch->Ht = Doublet.Ht();

    WSemiBranch->NeutrinoPt = Doublet.Singlet2().pt();
    WSemiBranch->LeptonPt = Doublet.Singlet1().pt();

    WSemiBranch->DeltaR = Doublet.DeltaR();
    WSemiBranch->DeltaRap = Doublet.DeltaRap();
    WSemiBranch->DeltaPhi = Doublet.DeltaPhi();

    WSemiBranch->Tag = Doublet.Tag();

}

void hanalysis::HWSemiTagger::FillBranch(const HDoublet &Doublet)
{
    Print(HInformation, "Fill W Tagger", Doublet.Bdt());
    FillBranch(Branch, Doublet);
}

std::vector< HWSemiBranch * > hanalysis::HWSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {WId};
    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Neutrinos = Event->GetParticles()->GetNeutrinos();

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        PreDoublet.SetTag(GetTag(PreDoublet));
        if (PreDoublet.Tag() != Tag) continue;
//         std::vector<HDoublet> PostDoublets = GetNeutrino(PreDoublet,Neutrinos);
//         std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        std::vector<HDoublet> PostDoublets = GetDoublets(PreDoublet, Neutrinos, Tag);
        for (const auto & PostDoublet : PostDoublets) {
            Print(HInformation, "W Mass ", PostDoublet.Jet().m());
            if (Tag == HSignal && std::abs(PostDoublet.Jet().m() - WMass) > WMassWindow) continue;
                Doublets.push_back(PostDoublet);
        }
    }

    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HWSemiBranch *> WSemiBranches;
    for (const auto & Doublet : Doublets) {
        HWSemiBranch *WSemiBranch = new HWSemiBranch();
        FillBranch(WSemiBranch, Doublet);
        WSemiBranches.push_back(WSemiBranch);
    }
    return WSemiBranches;
}

hanalysis::HObject::HTag hanalysis::HWSemiTagger::GetTag(const hanalysis::HDoublet &Doublet) const
{
    Print(HInformation, "Get Triple Tag");
    HJetInfo JetInfo = Doublet.Singlet1().user_info<HJetInfo>();
    JetInfo.ExtractFraction(WId);

    if (std::abs(JetInfo.GetMaximalId()) != WId) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HWSemiTagger::GetBdt(const HJets &Leptons, const fastjet::PseudoJet &MissingEt, const HReader *const Reader)
{
    Print(HInformation, "Get Triple Bdt");

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (auto & PostDoublet : PostDoublets) {
            FillBranch(PostDoublet);
            PostDoublet.SetBdt(Reader->Bdt());
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

    float Alpha = 1;
    float Beta = 1;
    float Correction = 0;
    float LinearTerm = (std::pow(WMass + Correction, 2) - Lepton.m2()) / 2 + Alpha * MissingEt.px() * Lepton.px() + Beta * MissingEt.py() * Lepton.py();

    float LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
    float MetSq = std::pow(Alpha * MissingEt.px(), 2) + std::pow(Beta * MissingEt.py(), 2);

    double Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);

//     Print(HError, "Randicand", Radicand,std::pow(LinearTerm, 2), MetSq, LeptonSq);
//     Print(HError, "Randicand", MissingEt.py(),MissingEt.px());
//     Print(HError, "Randicand", (std::pow(WMass + Correction, 2) - Lepton.m2()) / 2,LeptonSq);

//     int Counter = 0;
//     int Sign = 1;
//     while (Radicand < 0 && Correction < 50) {
//         LinearTerm = (std::pow(WMass + Correction, 2) - Lepton.m2()) / 2 + Alpha * MissingEt.px() * Lepton.px() + Beta * MissingEt.py() * Lepton.py();
//         LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
//         MetSq = std::pow(Alpha * MissingEt.px(), 2) + std::pow(Beta * MissingEt.py(), 2);
//         Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);
// //         Print(HError, "Correction", Correction, Sign, Counter);
// //         Print(HError, "W", LinearTerm, LeptonSq, MetSq, Radicand);
//         ++Counter;
//         Correction += float(Sign) * float(Counter);
//         Sign *= -1;
//     }

//     while (Radicand < 0 && Alpha > 0.1) {
//         while (Radicand < 0 && Beta > 0.1) {
//             Alpha *= 0.9;
//             Beta *= 0.9;
//             LinearTerm = (std::pow(WMass, 2) - Lepton.m2()) / 2 + Alpha * MissingEt.px() * Lepton.px() + Beta * MissingEt.py() * Lepton.py();
//             LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
//             MetSq = std::pow(Alpha * MissingEt.px(), 2) + std::pow(Beta * MissingEt.py(), 2);
//             Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);
//         }
//     }
//     while (Radicand < 0 && Alpha > 0.1) {
//         while (Radicand < 0 && Beta < 5) {
//             Alpha *= 0.9;
//             Beta *= 1.1;
//             LinearTerm = (std::pow(WMass, 2) - Lepton.m2()) / 2 + Alpha * MissingEt.px() * Lepton.px() + Beta * MissingEt.py() * Lepton.py();
//             LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
//             MetSq = std::pow(Alpha * MissingEt.px(), 2) + std::pow(Beta * MissingEt.py(), 2);
//             Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);
//         }
//     }
//
//     while (Radicand < 0 && Alpha > 0.1) {
//         while (Radicand < 0 && Beta < 5) {
//             Alpha *= 0.9;
//             Beta *= 1.1;
//             LinearTerm = (std::pow(WMass, 2) - Lepton.m2()) / 2 + Alpha * MissingEt.px() * Lepton.px() + Beta * MissingEt.py() * Lepton.py();
//             LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
//             MetSq = std::pow(Alpha * MissingEt.px(), 2) + std::pow(Beta * MissingEt.py(), 2);
//             Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);
//         }
//     }
//
//     while (Radicand < 0 && Alpha < 5) {
//         while (Radicand < 0 && Beta < 5) {
//             Alpha *= 1.1;
//             Beta *= 1.1;
//             LinearTerm = (std::pow(WMass, 2) - Lepton.m2()) / 2 + Alpha * MissingEt.px() * Lepton.px() + Beta * MissingEt.py() * Lepton.py();
//             LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
//             MetSq = std::pow(Alpha * MissingEt.px(), 2) + std::pow(Beta * MissingEt.py(), 2);
//             Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);
//         }
//     }

    std::vector<HDoublet> Doublets;
    if (Radicand < 0) {
        // TODO implemement a way to deal with these solutions
        HDoublet FakeDoublet(Lepton);
        Doublets.push_back(FakeDoublet);
//         Print(HError, "imaginary sqrt");
        return Doublets;
//         Radicand = 0;
    }
    const float Sqrt = std::sqrt(Radicand);

    const float Neutrino1E = (Lepton.e() * LinearTerm - Sqrt) / LeptonSq;
    const float Neutrino1Pz = (std::pow(Lepton.pz(), 2) * LinearTerm - Lepton.e() * Sqrt) / Lepton.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), Neutrino1Pz, Neutrino1E);
    HJetInfo *JetInfo1 = new HJetInfo();
//     JetInfo1->SetJetFamily(Lepton.user_info<HJetInfo>().GetJetFamily());
    Neutrino1.set_user_info(JetInfo1);
    Print(HDebug, "Neutrnio 1", Neutrino1);
    HDoublet Doublet1(Lepton, Neutrino1);
    Doublet1.SetTag(Doublet.Tag());

    const float Neutrino2E = (Lepton.e() * LinearTerm + Sqrt) / LeptonSq;
    const float Neutrino2Pz = (std::pow(Lepton.pz(), 2) * LinearTerm + Lepton.e() * Sqrt) / Lepton.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), Neutrino2Pz, Neutrino2E);
    HJetInfo *JetInfo2 = new HJetInfo();
//     JetInfo2->SetJetFamily(Lepton.user_info<HJetInfo>().GetJetFamily());
    Neutrino2.set_user_info(JetInfo2);
    Print(HDebug, "Neutrnio 2", Neutrino2);
    HDoublet Doublet2(Lepton, Neutrino2);
    Doublet2.SetTag(Doublet.Tag());


    Doublets.push_back(Doublet1);
    Doublets.push_back(Doublet2);

//     if (std::abs(Neutrino1Pz) < std::abs(Neutrino2Pz)) Doublets.push_back(Doublet1);
//     else Doublets.push_back(Doublet2);

    return Doublets;

}


struct SortByError {
    SortByError(fastjet::PseudoJet NewNeutrino) {
        this->Neutrino = NewNeutrino;
    }
    bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
        return ((Doublet1.Singlet2() + Neutrino).m() < (Doublet2.Singlet2() + Neutrino).m());
    }
    fastjet::PseudoJet Neutrino;
};


std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetDoublets(const HDoublet &Doublet, const HJets &Neutrinos, const HTag Tag)
{
    Print(HInformation, "Get Triple Pair");

    std::vector<HDoublet> Doublets = GetNeutrinos(Doublet);
    Print(HDebug, "Number Solutions", Doublets.size());

    if (Tag == HBackground) return Doublets;
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

    std::vector<HDoublet> FinalDoublet;
    FinalDoublet.push_back(BestDoublet);

    return FinalDoublet;
}
