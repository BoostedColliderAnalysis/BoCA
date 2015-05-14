# include "HHeavyHiggsTauTagger.hh"

hanalysis::HHeavyHiggsTauTagger::HHeavyHiggsTauTagger()
{
//     DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsTau");
}

hanalysis::HHeavyHiggsTauTagger::~HHeavyHiggsTauTagger()
{
    Print(kNotification, "Destructor");
}

void hanalysis::HHeavyHiggsTauTagger::SetTagger(const HTauTagger &NewTauTagger)
{
    Print(kNotification, "Set Tagger");
    TauTagger = NewTauTagger;
    set_tagger_name("HeavyHiggsTau");
    DefineVariables();
}

void hanalysis::HHeavyHiggsTauTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.NeutrinoPt, "NeutrinoPt");
    AddVariable(Branch.LeptonPt, "LeptonPt");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddSpectator(Branch.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

HHeavyHiggsTauBranch hanalysis::HHeavyHiggsTauTagger::GetBranch(const hanalysis::Doublet &doublet) const
{
    Print(kInformation, "Fill Top Tagger", doublet.Bdt());

    HHeavyHiggsTauBranch HiggsBranch;

    HiggsBranch.Mass = doublet.Jet().mt();
    HiggsBranch.Rap = doublet.Jet().rap();
    HiggsBranch.Phi = doublet.Jet().phi();
    HiggsBranch.Pt = doublet.Jet().pt();
    HiggsBranch.Ht = doublet.Ht();

    HiggsBranch.NeutrinoPt = doublet.Singlet2().pt();
    HiggsBranch.LeptonPt = doublet.Singlet1().pt();

    HiggsBranch.DeltaPt = doublet.DeltaPt();
    HiggsBranch.DeltaR = doublet.DeltaR();
    HiggsBranch.DeltaRap = doublet.DeltaRap();
    HiggsBranch.DeltaPhi = doublet.DeltaPhi();

    HiggsBranch.Bdt = doublet.Bdt();
    HiggsBranch.Tag = doublet.Tag();

    return HiggsBranch;

}

std::vector< HHeavyHiggsTauBranch> hanalysis::HHeavyHiggsTauTagger::GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag tag)
{

    Print(kInformation, "Get Top Tags");

    Jets jets = GetJets(event);
    jets = TauTagger.GetJetBdt(jets, TauReader);
    Print(kInformation, "Number Jet", jets.size());

    const fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();

    Jets TauParticles = event.Partons().Generator();
    TauParticles.erase(std::remove_if(TauParticles.begin(), TauParticles.end(), WrongAbsId(TauId)), TauParticles.end());
    if (TauParticles.size() != 1) Print(kError, "Where is the Tau?", TauParticles.size());

    Jets HiggsParticles = event.Partons().Generator();
    HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?", HiggsParticles.size());

    for (const auto & Particle : TauParticles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }
    Jets NewCleanJets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) continue;
        if (Jet.user_info<JetInfo>().Tag() != tag) continue;
        NewCleanJets.emplace_back(Jet);
    }

    std::vector<Doublet> doublets;
    for (const auto & Jet : NewCleanJets) {
        Doublet Predoublet(Jet, MissingEt);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);

//         std::sort(Postdoublets.begin(), Postdoublets.end(), MinDeltaR(HiggsParticles.front()));
//         if (Tag == kSignal && Postdoublets.size() > 1) Postdoublets.erase(Postdoublets.begin() + 1, Postdoublets.end());
//         if (Tag == HBackground && Postdoublets.size() > 0) Postdoublets.erase(Postdoublets.begin());
//         for (auto & Postdoublet : Postdoublets) {
            Predoublet.SetTag(tag);
            doublets.emplace_back(Predoublet);
//         }
    }


    Print(kInformation, "Number doublets", doublets.size());

    std::vector<HHeavyHiggsTauBranch> HiggsBranches;
    for (const auto & doublet : doublets) HiggsBranches.emplace_back(GetBranch(doublet));

    return HiggsBranches;
}

hanalysis::HObject::Tag hanalysis::HHeavyHiggsTauTagger::GetTag(const hanalysis::Doublet &doublet) const
{
    return kSignal;
}

std::vector<hanalysis::Doublet>  hanalysis::HHeavyHiggsTauTagger::GetBdt(const Jets &jets, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader &Reader)
{
    Print(kInformation, "Get Triple Bdt");
    std::vector<Doublet> doublets;
    for (const auto & Jet : jets)  {
        Doublet Predoublet(Jet, MissingEt);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
//         for (auto & Postdoublet : Postdoublets) {
//             if (Postdoublet.Jet().m() < 10) continue;
            Branch = GetBranch(Predoublet);
            Predoublet.SetBdt(Reader.Bdt());
            doublets.emplace_back(Predoublet);
//         }
    }
    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());

    return doublets;
}


std::vector<hanalysis::Doublet> hanalysis::HHeavyHiggsTauTagger::GetNeutrinos(const Doublet &doublet)const
{

    const fastjet::PseudoJet Jet = doublet.Singlet1();
    const fastjet::PseudoJet MissingEt = doublet.Singlet2();
    Print(kInformation, "Get Neutrinos", Jet.m(), (Jet - MissingEt).m());

    const float LinearTerm = (std::pow(WMass, 2) - Jet.m2()) / 2 + MissingEt.px() * Jet.px() + MissingEt.py() * Jet.py();

    const float LeptonSq = std::pow(Jet.e(), 2) - std::pow(Jet.pz(), 2);
    const float MetSq = std::pow(MissingEt.px(), 2) + std::pow(MissingEt.py(), 2);

    const double Radicand = std::pow(Jet.pz(), 2) * (std::pow(LinearTerm, 2) -  LeptonSq * MetSq);

    std::vector<Doublet> doublets;
    if (Radicand < 0) {
        Print(kInformation, "Imaginary root", "move missing et away from jet");
        Doublet Newdoublet(Jet, MissingEt - 0.1 * (Jet - MissingEt));
        Newdoublet.SetFlag(true);
        Newdoublet.SetTag(doublet.Tag());
        return GetNeutrinos(Newdoublet);
        return doublets;
    }

    if (Radicand == 0) {
        Print(kError, "Radicant exactly zero", "implement this case!");
    }

    const float Sqrt = std::sqrt(Radicand);

    const float Neutrino1E = (Jet.e() * LinearTerm - Sqrt) / LeptonSq;
    const float Neutrino1Pz = (std::pow(Jet.pz(), 2) * LinearTerm - Jet.e() * Sqrt) / Jet.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), Neutrino1Pz, Neutrino1E);
    Print(kDebug, "Neutrnio 1", Neutrino1);
    Doublet doublet1(Jet, Neutrino1);
    doublet1.SetTag(doublet.Tag());
    doublet1.SetFlag(doublet.Flag());

    const float Neutrino2E = (Jet.e() * LinearTerm + Sqrt) / LeptonSq;
    const float Neutrino2Pz = (std::pow(Jet.pz(), 2) * LinearTerm + Jet.e() * Sqrt) / Jet.pz() / LeptonSq;
    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), Neutrino2Pz, Neutrino2E);
    Print(kDebug, "Neutrino 2", Neutrino2);
    Doublet doublet2(Jet, Neutrino2);
    doublet2.SetTag(doublet.Tag());
    doublet2.SetFlag(doublet.Flag());

    doublets.emplace_back(doublet1);
    doublets.emplace_back(doublet2);

//     if (std::abs(Neutrino1Pz) < std::abs(Neutrino2Pz)) doublets.emplace_back(doublet1);
//     else doublets.emplace_back(doublet2);

    return doublets;

}


struct SortByError {
    SortByError(const fastjet::PseudoJet &NewNeutrino) {
        this->Neutrino = NewNeutrino;
    }
    bool operator()(const hanalysis::Doublet &doublet1, const hanalysis::Doublet &doublet2) {
        return ((doublet1.Singlet2() + Neutrino).m() < (doublet2.Singlet2() + Neutrino).m());
    }
    fastjet::PseudoJet Neutrino;
};

struct FindError {
    FindError(const fastjet::PseudoJet &NewNeutrino, const float NewError) {
        this->Neutrino = NewNeutrino;
        this->Error = NewError;
    }
    bool operator()(const hanalysis::Doublet &doublet) {
        return ((doublet.Singlet2() + Neutrino).m() == Error);
    }
    fastjet::PseudoJet Neutrino;
    float Error;
};

std::vector<hanalysis::Doublet> hanalysis::HHeavyHiggsTauTagger::GetDoublets(const Doublet &doublet, const Jets &Neutrinos, const Tag tag)
{
    Print(kInformation, "Get Triple Pair");

    std::vector<Doublet> doublets = GetNeutrinos(doublet);
    Print(kDebug, "Number Solutions", doublets.size());
    if (doublets.empty()) return doublets;

    float BestError = LargeNumber;
    Doublet Bestdoublet;
    for (const auto Neutrino : Neutrinos) {
        std::sort(doublets.begin(), doublets.end(), SortByError(Neutrino));
        float Error = (doublets.front().Singlet2() + Neutrino).m();
        if (Error < BestError) {
            Bestdoublet = doublets.front();
            BestError = Error;
        }
    }

    std::vector<Doublet> Finaldoublets;
    switch (tag) {
    case kSignal:
        Finaldoublets.emplace_back(Bestdoublet);
        return Finaldoublets;
    case kBackground:
        for (const auto Neutrino : Neutrinos) doublets.erase(std::remove_if(doublets.begin(), doublets.end(), FindError(Neutrino, BestError)), doublets.end());
        return doublets;
    default:
        Print(kError, "we should never end up here");
        return doublets;
    }


}
