# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger(HBottomTagger *const NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    TaggerName = "TopSemi";
    SignalNames = {"TopSemi"};
    BackgroundNames = {"NotTopSemi"};
    CandidateBranchName = "TopSemi";

    Branch = new HTopSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();

}

hanalysis::HTopSemiTagger::~HTopSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->PairMass, "PairMass"));

    Observables.push_back(NewObservable(&Branch->TriplePt, "TriplePt"));
    Observables.push_back(NewObservable(&Branch->PairPt, "PairPt"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
    Observables.push_back(NewObservable(&Branch->MissingEt, "MissingEt"));

    Observables.push_back(NewObservable(&Branch->PairDeltaPhi, "PairDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->PairDeltaRap, "PairDeltaRap"));
    Observables.push_back(NewObservable(&Branch->PairDeltaR, "PairDeltaR"));

    Observables.push_back(NewObservable(&Branch->TripleDeltaPhi, "TripleDeltaPhi"));
    Observables.push_back(NewObservable(&Branch->TripleDeltaRap, "TripleDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TripleDeltaR, "TripleDeltaR"));

    Observables.push_back(NewObservable(&Branch->BottomBdt, "BottomBdt"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HTopSemiTagger::FillBranch(HTopSemiBranch *const TopSemiBranch, const HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.GetBdt());

    TopSemiBranch->Mass = Triplet.GetTripletJet().m();
    TopSemiBranch->PairMass = Triplet.GetDoubletJet().m();

    TopSemiBranch->TriplePt = Triplet.GetTripletJet().pt();
    TopSemiBranch->PairPt = Triplet.GetDoubletJet().pt();

    TopSemiBranch->JetPt = Triplet.GetJet().pt();
    TopSemiBranch->LeptonPt = Triplet.GetDoublet().GetJet1().pt();
    TopSemiBranch->MissingEt = Triplet.GetDoublet().GetJet2().pt();

    TopSemiBranch->TripleDeltaR = Triplet.GetDeltaR();
    TopSemiBranch->TripleDeltaRap = Triplet.GetDeltaRap();
    TopSemiBranch->TripleDeltaPhi = Triplet.GetDeltaPhi();

    TopSemiBranch->PairDeltaR = Triplet.GetDoublet().GetDeltaR();
    TopSemiBranch->PairDeltaRap = Triplet.GetDoublet().GetDeltaRap();
    TopSemiBranch->PairDeltaPhi = Triplet.GetDoublet().GetPhiDelta();

    TopSemiBranch->BottomBdt = Triplet.GetBdt();
    TopSemiBranch->TopTag = Triplet.GetTag();

}

void hanalysis::HTopSemiTagger::FillBranch(const HTriplet &Triple)
{
    Print(HInformation, "Fill Top Tagger", Triple.GetBdt());

    FillBranch(Branch, Triple);

}


class SortJetByTopMass
{
public:
    inline bool operator()(const hanalysis::HTriplet &Triplet1, const hanalysis::HTriplet &Triplet2) {
        hanalysis::HObject Object;
        return (std::abs(Triplet1.GetTripletJet().m() - Object.TopMass) < std::abs(Triplet2.GetTripletJet().m() - Object.TopMass));
    }
};


std::vector<HTopSemiBranch *> hanalysis::HTopSemiTagger::GetBranches(HEvent *const Event, const HObject::HState State)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {WId, TopId, HiggsId, CpvHiggsId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());

    Jets = BottomTagger->GetBottomBdt(Jets,BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Leptons.erase(Lepton);
        else ++Lepton;
    }

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet Doublet(Lepton, MissingEt);
        Doublets.push_back(Doublet);
    }
    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    for (auto & PreDoublet : Doublets)
        for (const auto & Jet : Jets) {
            HTriplet PreTriplet(PreDoublet, Jet);
            PreTriplet.SetTag(GetTripletTag(PreTriplet));
            if (PreTriplet.GetTag() != State) continue;
            HJets Neutrinos = GetNeutrinos(PreTriplet);
            if (Neutrinos.size() < 1) continue;
            for (const auto & Neutrino : Neutrinos) {
                HDoublet Doublet(PreTriplet.GetDoublet().GetJet1(), Neutrino);
                HTriplet Triplet(Doublet, Jet);
                if (Triplet.GetTripletJet().m() < 0) continue;
                if (Triplet.GetDoubletJet().m() < 0) continue;
                Triplet.SetTag(PreTriplet.GetTag());
                Triplets.push_back(Triplet);
            }
        }


        if (State == HSignal && Triplets.size()>1) {
        std::sort(Triplets.begin(), Triplets.end(), SortJetByTopMass());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    Print(HInformation, "Number Triplets", Triplets.size());

    std::vector<HTopSemiBranch *> TopSemiBranches;
    for (const auto & Triplet : Triplets) {
        HTopSemiBranch *TopSemiBranch = new HTopSemiBranch();
        FillBranch(TopSemiBranch, Triplet);
        TopSemiBranches.push_back(TopSemiBranch);
    }

    return TopSemiBranches;

}

hanalysis::HObject::HState hanalysis::HTopSemiTagger::GetTripletTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Triplet.GetDoublet().GetJet1().user_index()) != WId) return HBackground;
    if (std::abs(Triplet.GetJet().user_index()) != TopId) return HBackground;
    if (sgn(Triplet.GetDoublet().GetJet1().user_index()) != sgn(Triplet.GetJet().user_index())) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetTopSemiBdt(HJets Jets, HJets Leptons,fastjet::PseudoJet MissingEt, const HReader * const TopSemiReader, const HState State) {

  for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
    if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Jets.erase(Lepton);
    else  ++Lepton;
  }

  std::vector<HDoublet> Doublets;
  for (const auto & Lepton : Leptons) {
    HDoublet Doublet(Lepton, MissingEt);
    Doublets.push_back(Doublet);
  }
  Print(HInformation, "Number Doublets", Doublets.size());

  std::vector<HTriplet> Triplets;
  for (auto & PreDoublet : Doublets)
    for (const auto & Jet : Jets) {
      HTriplet PreTriplet(PreDoublet, Jet);
      PreTriplet.SetTag(GetTripletTag(PreTriplet));
      if (State == HSignal && PreTriplet.GetTag() != State) continue;
      HJets Neutrinos = GetNeutrinos(PreTriplet);
      if (Neutrinos.size() < 1) continue;
      const int Tag = PreTriplet.GetTag();
      for (const auto & Neutrino : Neutrinos) {
        HDoublet Doublet(PreTriplet.GetDoublet().GetJet1(), Neutrino);
        HTriplet Triplet(Doublet, Jet);
        FillBranch(Triplet);
        Triplet.SetBdt(TopSemiReader->GetBdt());
        Triplets.push_back(Triplet);
      }
    }
return Triplets;
}


HJets hanalysis::HTopSemiTagger::GetNeutrinos(const HTriplet &Triplet)const
{
    const fastjet::PseudoJet Jet = Triplet.GetJet();
    const fastjet::PseudoJet Lepton = Triplet.GetDoublet().GetJet1();
    const fastjet::PseudoJet MissingEt = Triplet.GetDoublet().GetJet2();

    const float RHS = std::pow(TopMass, 2) - std::pow(WMass, 2) - (Lepton + Jet).m2() + Lepton.m2() + 2 * (MissingEt.px() * Jet.px() + MissingEt.py() * Jet.py());

    const float JetSq = std::pow(Jet.e(), 2) - std::pow(Jet.pz(), 2);
    const float MetSq = std::pow(MissingEt.px(), 2) + std::pow(MissingEt.py(), 2);

    const float Rad = std::pow(Jet.e(), 2) * (-4 * JetSq * MetSq + std::pow(RHS, 2));

    HJets Neutrinos;
    if (Rad < 0) {
        Print(HError, "imaginary sqrt");
        return Neutrinos;
    }

    const float Neutrino1Pz = (Jet.pz() * RHS - std::sqrt(Rad)) / 2 / JetSq;
    const float Neutrino1E = (std::pow(Jet.e(), 2) * RHS - Jet.pz() * std::sqrt(Rad)) / 2 / Jet.e() / JetSq;
    fastjet::PseudoJet Neutrino1(MissingEt.px(), MissingEt.py(), Neutrino1Pz, Neutrino1E);
//     Print(HError, "Neutrnio 1", Neutrino1);
    Neutrinos.push_back(Neutrino1);

    const float Neutrino2Pz = (Jet.pz() * RHS + std::sqrt(Rad)) / 2 / JetSq;
    const float Neutrino2E = (std::pow(Jet.e(), 2) * RHS + Jet.pz() * std::sqrt(Rad)) / 2 / Jet.e() / JetSq;
    fastjet::PseudoJet Neutrino2(MissingEt.px(), MissingEt.py(), Neutrino2Pz, Neutrino2E);
//     Print(HError, "Neutrnio 2", Neutrino2);
    Neutrinos.push_back(Neutrino2);

    return Neutrinos;

}
