# include "HWSemiTagger.hh"

hanalysis::HWSemiTagger::HWSemiTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    SetTaggerName("WSemi");

    Branch = new HWSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();

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

    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->NeutrinoPt, "NeutrinoPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
//     Observables.push_back(NewObservable(&Branch->MissingEt, "MissingEt"));

    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Spectators.push_back(NewObservable(&Branch->WTag, "WTag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HWSemiTagger::FillBranch(HWSemiBranch*const WSemiBranch, const hanalysis::HDoublet& Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.GetBdt());

    WSemiBranch->Mass = Doublet.GetDoubletJet().m();

    WSemiBranch->Pt = Doublet.GetDoubletJet().pt();

    WSemiBranch->NeutrinoPt = Doublet.GetJet2().pt();
    WSemiBranch->LeptonPt = Doublet.GetJet1().pt();
//     WSemiBranch->MissingEt = Doublet.GetDoublet().GetJet2().pt();

    WSemiBranch->DeltaR = Doublet.GetDeltaR();
    WSemiBranch->DeltaRap = Doublet.GetDeltaRap();
    WSemiBranch->DeltaPhi = Doublet.GetPhiDelta();

    WSemiBranch->WTag = Doublet.GetTag();

}

void hanalysis::HWSemiTagger::FillBranch(const HDoublet &Doublet)
{
    Print(HInformation, "Fill W Tagger", Doublet.GetBdt());

    FillBranch(Branch, Doublet);

}


// class SortJetByWMass
// {
// public:
//     inline bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
//         const hanalysis::HObject Object;
//         return (std::abs(Doublet1.GetDoubletJet().m() - Object.WMass) < std::abs(Doublet2.GetDoubletJet().m() - Object.WMass));
//     }
// };


std::vector< HWSemiBranch* > hanalysis::HWSemiTagger::GetBranches(hanalysis::HEvent*const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {WId, TopId};
//     JetTag->HeavyFamily = {
//       HFamily(WId, TopId, EmptyId),
//     };

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Leptons.erase(Lepton);
        else ++Lepton;
    }

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        PreDoublet.SetTag(GetTag(PreDoublet));
//         if (PreDoublet.GetTag() != Tag) continue;
        if (PreDoublet.GetTag() == HBackground && Tag == HSignal) continue;
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (const auto & PostDoublet : PostDoublets)
        {
          Doublets.push_back(PostDoublet);
          Print(HInformation,"W Mass ",PostDoublet.GetDoubletJet().m());
        }

    }
    Print(HInformation, "Number Doublets", Doublets.size());

//     if (Tag == HSignal && Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end(), SortJetByWMass());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }

//     if (Tag == HBackground) { // TODO clena this up
//         if (Doublets.size() > 1) std::sort(Doublets.begin(), Doublets.end(), SortJetByWMass());
//         if (Doublets.size() > 0) if(Doublets.front().GetTag() == HSignal) Doublets.erase(Doublets.begin());
//     }

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

    if (std::abs(Doublet.GetJet1().user_index()) != WId) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HWSemiTagger::GetTruthDoublets(const HReader * Reader, HEvent * const Event)
{


  JetTag->HeavyParticles = {WId, TopId};
//   JetTag->HeavyFamily = {
//     HFamily(WId, TopId, EmptyId),
//   };

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Leptons.erase(Lepton);
        else ++Lepton;
    }

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        PreDoublet.SetTag(GetTag(PreDoublet));
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (auto & PostDoublet : PostDoublets) {
            FillBranch(PostDoublet);
            PostDoublet.SetBdt(Reader->GetBdt());
            Doublets.push_back(PostDoublet);
        }
    }

    return Doublets;
}

std::vector<hanalysis::HDoublet>  hanalysis::HWSemiTagger::GetTruthBdt(HJets &Leptons, const fastjet::PseudoJet &MissingEt, const HReader *const Reader)
{

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Leptons.erase(Lepton);
        else  ++Lepton;
    }

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        PreDoublet.SetTag(GetTag(PreDoublet));
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (auto & PostDoublet : PostDoublets) {
            FillBranch(PostDoublet);
            PostDoublet.SetBdt(Reader->GetBdt());
            Doublets.push_back(PostDoublet);
        }
    }

    return Doublets;
}

std::vector<hanalysis::HDoublet>  hanalysis::HWSemiTagger::GetBdt(HJets &Leptons, const fastjet::PseudoJet &MissingEt, const HReader *const Reader)
{

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        PreDoublet.SetTag(GetTag(PreDoublet));
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (auto & PostDoublet : PostDoublets) {
            FillBranch(PostDoublet);
            PostDoublet.SetBdt(Reader->GetBdt());
            Doublets.push_back(PostDoublet);
        }
    }

    return Doublets;
}


std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetNeutrinos(const HDoublet &Doublet)const
{
    const fastjet::PseudoJet Lepton = Doublet.GetJet1();
    const fastjet::PseudoJet MissingEt = Doublet.GetJet2();
    const float LinearTerm = (std::pow(WMass, 2) - Lepton.m2())/2 + MissingEt.px() * Lepton.px() + MissingEt.py() * Lepton.py();

    const float LeptonSq = std::pow(Lepton.e(), 2) - std::pow(Lepton.pz(), 2);
    const float MetSq = std::pow(MissingEt.px(), 2) + std::pow(MissingEt.py(), 2);

    const float Radicand = std::pow(Lepton.pz(), 2) * (std::pow(LinearTerm, 2)-  LeptonSq * MetSq );

    std::vector<HDoublet> Doublets;
    if (Radicand < 0) {
        // TODO implemement a way to deal with these solutions
        Print(HInformation, "imaginary sqrt");
        return Doublets;
    }
    const float Sqrt = std::sqrt(Radicand);

    const float Neutrino1E = (Lepton.e() * LinearTerm - Sqrt) / LeptonSq;
    const float Neutrino1Pz = ( std::pow(Lepton.pz(), 2) * LinearTerm - Lepton.e() * Sqrt) / Lepton.pz() / LeptonSq;
    const fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), Neutrino1Pz, Neutrino1E);
    Print(HDebug, "Neutrnio 1", Neutrino1);
    HDoublet Doublet1(Lepton,Neutrino1);
    Doublet1.SetTag(Doublet.GetTag());
//     if (Doublet1.GetDoubletJet().m() > 0) Doublets.push_back(Doublet1);

    const float Neutrino2E = (Lepton.e() * LinearTerm + Sqrt) / LeptonSq;
    const float Neutrino2Pz = (std::pow(Lepton.pz(), 2) * LinearTerm + Lepton.e() * Sqrt) / Lepton.pz() / LeptonSq;
    const fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), Neutrino2Pz, Neutrino2E);
    Print(HDebug, "Neutrnio 2", Neutrino2);
    HDoublet Doublet2(Lepton,Neutrino2);
    Doublet2.SetTag(Doublet.GetTag());
//     if (Doublet2.GetDoubletJet().m() > 0) Doublets.push_back(Doublet2);

    if (std::abs(Neutrino1Pz) < std::abs(Neutrino2Pz)) Doublets.push_back(Doublet1);
    else Doublets.push_back(Doublet2);

    return Doublets;

}
