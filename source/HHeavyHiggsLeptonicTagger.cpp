# include "HHeavyHiggsLeptonicTagger.hh"

hanalysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger(HBottomTagger *const NewBottomTagger, HTopLeptonicTagger *const NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader = new HReader(TopLeptonicTagger);

    TaggerName = "HeavyHiggsLeptonic";
    SignalNames = {"HeavyHiggsLeptonic"};
    BackgroundNames = {"NotHeavyHiggsLeptonic"};
    CandidateBranchName = "HeavyHiggsLeptonic";

    Branch = new HHeavyHiggsLeptonicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsLeptonicTagger::~HHeavyHiggsLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;

}

void hanalysis::HHeavyHiggsLeptonicTagger::FillBranch(const hanalysis::HSextet &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    FillBranch(Branch, TriplePair);

}

void hanalysis::HHeavyHiggsLeptonicTagger::FillBranch(HHeavyHiggsLeptonicBranch *HeavyHiggsBranch, const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = Sextet.GetSextetJet().m();
    HeavyHiggsBranch->HeavyHiggsPt = Sextet.GetSextetJet().m();

    HeavyHiggsBranch->TopDeltaR = Sextet.GetDeltaR();
    HeavyHiggsBranch->TopDeltaRap = Sextet.GetDeltaRap();
    HeavyHiggsBranch->TopDeltaPhi = Sextet.GetDeltaPhi();

    HeavyHiggsBranch->LargerWDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch->LargerWDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch->LargerWDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch->SmallerWDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch->SmallerWDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch->SmallerWDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch->LargerNeutrinoDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch->LargerNeutrinoDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch->LargerNeutrinoDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch->SmallerNeutrinoDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch->SmallerNeutrinoDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch->TopBdt = Sextet.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = Sextet.GetTag();

}

void hanalysis::HHeavyHiggsLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}

struct SortPairByMass {
    inline bool operator()(const hanalysis::HQuartet &Pair1, const hanalysis::HQuartet &Pair2) {
        return (Pair1.GetMassDifference(400) > Pair2.GetMassDifference(400));
    }
};

struct SortByError {
    inline bool operator()(const hanalysis::HSextet &Pair1, const hanalysis::HSextet &Pair2) {
        return (Pair1.GetError() < Pair2.GetError());
    }
};

std::vector< HHeavyHiggsLeptonicBranch * > hanalysis::HHeavyHiggsLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HState State)
{
    Print(HInformation, "Get Higgs Tags");


    JetTag->HeavyParticles = {TopId, HeavyHiggsId, WId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBottomBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<HDoublet> Doublets = TopLeptonicTagger->GetTopLeptonicBdt(Jets, Leptons, TopLeptonicReader, State);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Neutrinos = Event->GetParticles()->GetNeutrinos();

    Print(HInformation, "Number of Doublets", Doublets.size());


    std::vector<HSextet> Sextets;
    for (const auto & Doublet1 : Doublets) {
      Print(HInformation, "Doublet 1", GetParticleName(Doublet1.GetJet1().user_index()),GetParticleName(Doublet1.GetJet2().user_index()));
        for (const auto & Doublet2 : Doublets) {
          Print(HInformation, "Doublet 2", GetParticleName(Doublet2.GetJet1().user_index()),GetParticleName(Doublet2.GetJet2().user_index()));
        if (Doublet1.GetJet1() == Doublet2.GetJet1()) continue;
            if (Doublet1.GetJet2() == Doublet2.GetJet2()) continue;
            HQuartet Quartet(Doublet1, Doublet2, MissingEt);
            Quartet.SetTag(GetQuartetTag(Quartet));
            if (Quartet.GetTag() != State) continue;
            std::vector<HSextet> PreSextets;
            if (State == HSignal) {
                HSextet Sextet = Quartet.GetSextet(Neutrinos);
                PreSextets.push_back(Sextet);
            } else PreSextets = Quartet.GetSextets();

            for (auto & Sextet : PreSextets) {
                if (Sextet.GetSextetJet().m() < 10) continue;
                if (Sextet.GetError() < 0) continue; // FIXME Was mach das noch mal?
                Sextet.SetTag(Quartet.GetTag());
                Sextets.push_back(Sextet);
            }
        }
    }
    Print(HInformation, "Numeber of Sextets", Sextets.size());


    if (State == HSignal && Sextets.size() > 1) {
        Print(HError, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByError());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsLeptonicBranch *> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) {
        HHeavyHiggsLeptonicBranch *HeavyHiggsLeptonicBranch = new HHeavyHiggsLeptonicBranch();
        FillBranch(HeavyHiggsLeptonicBranch, Sextet);
        HeavyHiggsBranches.push_back(HeavyHiggsLeptonicBranch);
    }

    return HeavyHiggsBranches;

}

hanalysis::HObject::HState hanalysis::HHeavyHiggsLeptonicTagger::GetQuartetTag(const HQuartet &Quartet)
{
    Print(HInformation, "Get Triple Tag");

    if (Quartet.GetDoublet1().GetJet1().user_index() != -Quartet.GetDoublet2().GetJet1().user_index()) return HBackground;
    if (Quartet.GetDoublet1().GetJet2().user_index() != -Quartet.GetDoublet2().GetJet2().user_index()) return HBackground;

    return HSignal;
}

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsLeptonicTagger::GetHeavyHiggsLeptonicBdt(std::vector<HDoublet> Doublets ,fastjet::PseudoJet MissingEt, const HReader *const HeavyHiggsLeptonicReader, const HState State)
{

  std::vector<HSextet> Sextets;
  for (const auto & Doublet1 : Doublets) {
    for (const auto & Doublet2 : Doublets) {
      if (Doublet1.GetJet1() == Doublet2.GetJet1()) continue;
      if (Doublet1.GetJet2() == Doublet2.GetJet2()) continue;
      HQuartet Quartet(Doublet1, Doublet2, MissingEt);
      Quartet.SetTag(GetQuartetTag(Quartet));
      if (State == HSignal && Quartet.GetTag() == HBackground) continue;
      std::vector<HSextet> PreSextets;
      PreSextets = Quartet.GetSextets();
      for (auto & Sextet : PreSextets) {
        if (Sextet.GetSextetJet().m() < 10) continue;
        if (Sextet.GetError() < 0) continue; // FIXME Was mach das noch mal?
        FillBranch(Sextet);
        Sextet.SetBdt(HeavyHiggsLeptonicReader->GetBdt());
        Sextet.SetTag(Quartet.GetTag());
        Sextets.push_back(Sextet);
      }
    }
  }
  return Sextets;
}
